from math import ceil
import os
import re
import shutil
import subprocess
import sys

# Determine root of bootloader project to find related files
boot_project_root = os.path.abspath(os.path.join(os.path.abspath(os.path.dirname(__file__)), "../../../.."))

# Initialize an empty string for the message
message_str = ""

# Make sure python3 is used
if not sys.version_info >= (3, 3):
    print(
        "ERROR: The MCUboot signing script requires version Python version 3.3 or later. The python command can be modified in the MCUboot properties. Current Python version used is:\n"
        + sys.version
    )
    sys.exit(1)

# Determine version
if os.getenv("MCUBOOT_IMAGE_VERSION") is not None:
    # Version defined in environment variable
    if "-v" in sys.argv or "--version" in sys.argv:
        print(
            "ERROR: Remove -v and --version from Signing Options > Custom and Signing Options > TrustZone > Custom (Image 2) to use MCUBOOT_IMAGE_VERSION.",
            file=sys.stderr,
        )
        sys.exit(1)
    else:
        sys.argv.insert(sys.argv.index("sign") + 1, "--version")
        sys.argv.insert(sys.argv.index("sign") + 2, os.getenv("MCUBOOT_IMAGE_VERSION"))
        message_str = (
            "Packaging application image with version from environment variable MCUBOOT_IMAGE_VERSION: "
            + os.getenv("MCUBOOT_IMAGE_VERSION")
        )

if "-v" in sys.argv or "--version" in sys.argv:
    # Do nothing, version is passed from command line
    pass
else:
    # Version missing
    print(
        'ERROR: The application image version must be defined. Pass version using "-v" or "--version" or by defining the environment variable MCUBOOT_IMAGE_VERSION.',
        file=sys.stderr,
    )
    sys.exit(1)

# Determine key
mcuboot_image_signing_key = os.getenv("MCUBOOT_IMAGE_SIGNING_KEY")
if mcuboot_image_signing_key is not None:
    # Key defined in environment variable
    # Verify the key exists
    if not os.path.exists(mcuboot_image_signing_key):
        print(
            "ERROR: Could not find conversion tool set in MCUBOOT_IMAGE_SIGNING_KEY: " + mcuboot_image_signing_key,
            file=sys.stderr,
        )
        sys.exit(1)
    # Add key to command line
    if "-k" in sys.argv or "--key" in sys.argv:
        print(
            "ERROR: Remove -k and --key from Signing Options > Custom and Signing Options > TrustZone > Custom (Image 2) to use MCUBOOT_IMAGE_SIGNING_KEY.",
            file=sys.stderr,
        )
        sys.exit(1)
    else:
        sys.argv.insert(sys.argv.index("sign") + 1, "--key")
        sys.argv.insert(sys.argv.index("sign") + 2, mcuboot_image_signing_key)
        message_str += " and key from MCUBOOT_IMAGE_SIGNING_KEY: " + mcuboot_image_signing_key

# Determine Encryption key
mcuboot_image_enc_key = os.getenv("MCUBOOT_IMAGE_ENC_KEY")
if mcuboot_image_enc_key is not None:
    # Key defined in environment variable
    # Verify the key exists
    if not os.path.exists(mcuboot_image_enc_key):
        print(
            "ERROR: Could not find conversion tool set in MCUBOOT_IMAGE_ENC_KEY: " + mcuboot_image_enc_key,
            file=sys.stderr,
        )
        sys.exit(1)
    # Add key to command line
    if "-E" in sys.argv or "--encrypt" in sys.argv:
        print(
            "ERROR: Remove -E and --encrypt from Signing Options > Custom and Signing Options > TrustZone > Custom (Image 2) to use MCUBOOT_IMAGE_ENC_KEY.",
            file=sys.stderr,
        )
        sys.exit(1)
    else:
        sys.argv.insert(sys.argv.index("sign") + 1, "--encrypt")
        sys.argv.insert(sys.argv.index("sign") + 2, mcuboot_image_enc_key)
        message_str += " and encryption key from MCUBOOT_IMAGE_ENC_KEY: " + mcuboot_image_enc_key
        # Updated the file extension to include encrypted
        output_file = sys.argv[-1]
        output_file = output_file + ".encrypted"
        sys.argv[-1] = output_file
else:
    print(" ")

# Determine if the input file is .elf or binary format
input_file = sys.argv[-2]
if not os.path.exists(input_file):
    print("ERROR: Could not find input file: " + input_file, file=sys.stderr)
    sys.exit(1)
with open(input_file, "rb") as f:
    contents = f.read(4)
    if b"\x7fELF" == contents:
        # This is an ELF file. Convert it to binary.

        # Determine conversion tool
        if os.getenv("MCUBOOT_APP_BIN_CONVERTER") is not None:
            # Conversion tool defined in environment variable
            conversion_tool = os.getenv("MCUBOOT_APP_BIN_CONVERTER")
            if not os.path.exists(conversion_tool):
                print(
                    "ERROR: Could not find conversion tool set in MCUBOOT_APP_BIN_CONVERTER: " + conversion_tool,
                    file=sys.stderr,
                )
                sys.exit(1)
        elif shutil.which("arm-none-eabi-objcopy") is not None:
            conversion_tool = "arm-none-eabi-objcopy"
        elif shutil.which("objcopy") is not None:
            conversion_tool = "objcopy"
        elif shutil.which("fromelf") is not None:
            conversion_tool = "fromelf"
        elif shutil.which("ielftool") is not None:
            conversion_tool = "ielftool"
        else:
            print(
                "ERROR: Conversion tool not found. Add objcopy, arm-none-eabi-objcopy, fromelf, or ielftool to the command line or define the full path to one of these in the environment variable MCUBOOT_APP_BIN_CONVERTER",
                file=sys.stderr,
            )
            sys.exit(1)

        # Determine conversion command line
        input_file_no_ext, _ = os.path.splitext(input_file)
        temp_unsigned_binary = input_file_no_ext + ".temp.bin"
        if "objcopy" in conversion_tool:
            conversion_command = [conversion_tool, "-O", "binary", input_file, temp_unsigned_binary]
        elif "fromelf" in conversion_tool:
            conversion_command = [conversion_tool, "--bin" "--output=" + temp_unsigned_binary, input_file]
        elif "ielftool" in conversion_tool:
            conversion_command = [conversion_tool, "--bin", input_file, temp_unsigned_binary]
        else:
            print(
                "ERROR: Conversion tool not supported. MCUBOOT_APP_BIN_CONVERTER must be objcopy, arm-none-eabi-objcopy, fromelf, or ielftool.",
                file=sys.stderr,
            )
            sys.exit(1)

        # Convert ELF to binary.
        subprocess.check_output(conversion_command)
        if not os.path.exists(temp_unsigned_binary):
            print("ERROR: Conversion from elf to binary failed.", file=sys.stderr)
            sys.exit(1)

        # Update command line to pass binary instead of elf file to imgtool
        sys.argv[-2] = temp_unsigned_binary

# Load bsp_linker_info.h and parse the header and slot sizes.
if not os.path.exists("bsp_linker_info.h"):
    print("ERROR: bsp_linker_info.h could not be found.", file=sys.stderr)
    sys.exit(1)
with open("bsp_linker_info.h") as f:
    linker_h = f.read()

sign_script_block: re.Match = re.search(r"^\#ifdef SIGN_SCRIPT_PY\n((?:\#define .+\n)*)\#endif", linker_h, re.MULTILINE)
if sign_script_block:
    captured_defines = sign_script_block.group(1)
    print("Captured Defines:")
    print(captured_defines)
else:
    print("No matching block found.")

# Check if a match was found
if sign_script_block:
    # Get the captured content (the #define lines)
    define_lines = sign_script_block.group(1)  # group(1) contains the content of the first capturing group

    # Now use re.findall() on the extracted string
    script_macros = dict(
        re.findall(r"^\#define (?P<name>[A-Za-z_][A-Za-z0-9_]*) (?P<value>.+)$", define_lines, re.MULTILINE)
    )

if "HEADER_SIZE" not in script_macros:
    print("ERROR: Could not find HEADER_SIZE macro in bsp_linker_info.h.", file=sys.stderr)
    sys.exit(1)
if "SLOT_SIZE" not in script_macros:
    print("ERROR: Could not find SLOT_SIZE macro in bsp_linker_info.h.", file=sys.stderr)
    sys.exit(1)
# Prepare the arguments to insert
new_args = [
    "--header-size",
    script_macros["HEADER_SIZE"],
    "--slot-size",
    script_macros["SLOT_SIZE"],
]

# Grab the erase sector sizes from the existing command line arguments to produce the --max-sectors argument.
if "--flash_erase_size_bytes" not in sys.argv:
    print("ERROR: --flash_erase_size_bytes argument not found.", file=sys.stderr)
    sys.exit(1)
i_min_erase_size = sys.argv.index("--flash_erase_size_bytes")
sector_size = int(sys.argv[i_min_erase_size + 1], 0)

# Remove the sector size arguments
sys.argv.pop(i_min_erase_size)
sys.argv.pop(i_min_erase_size)

# Add the --max-sectors argument
max_sectors = ceil(int(script_macros["SLOT_SIZE"], 0) / sector_size)
new_args.extend(["--max-sectors", str(max_sectors)])

# Insert the new arguments into sys.argv after the script name and operation argument (at index 2)
for arg in reversed(new_args):  # Insert in reverse order to maintain correct final order
    sys.argv.insert(2, arg)
print(message_str)

# Launch imgtool with python3
sys.path.append(boot_project_root + "/ra/mcu-tools/MCUboot/scripts")

from imgtool import main

if __name__ == "__main__":
    print("python imgtool.py " + " ".join(sys.argv[1:]))
    script_path = boot_project_root + "/ra/mcu-tools/MCUboot/scripts/imgtool.py"
    command = ["python", script_path] + sys.argv[1:]
    result = subprocess.run(command, capture_output=True, text=True)
    if result.returncode != 0:
        print(f"ERROR: imgtool.py failed: {result.stderr}", file=sys.stderr)

    sys.exit(1)
