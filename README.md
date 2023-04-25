## Overview

Flexible Software Package (FSP) for Renesas RA MCU Family

FSP is the next generation Arm® MCU software package from Renesas, that enables secure devices and IoT connectivity through production ready peripheral drivers, Azure RTOS or FreeRTOS, and portable middleware stacks.
FSP includes best-in-class HAL drivers with high performance and low memory footprint. Middleware stacks with Azure RTOS and FreeRTOS integration are included to ease implementation of complex modules like communication and security.
The e² studio ISDE provides support with intuitive configurators and intelligent code generation to make programming and debugging easier and faster.

FSP uses an open software ecosystem and provides flexibility in using your preferred RTOS, legacy code, and third-party ecosystem solutions.

### Current Release

[FSP v4.4.0](https://github.com/renesas/fsp/releases/tag/v4.4.0)

### Supported RA MCU Kits

- EK-RA2A1
- EK-RA2E1
- EK-RA2E2
- EK-RA2L1
- EK-RA4M1
- EK-RA4M2
- EK-RA4M3
- EK-RA4W1
- EK-RA6M1
- EK-RA6M2
- EK-RA6M3
- EK-RA6M3G
- EK-RA6M4
- CK-RA6M5
- EK-RA6M5
- FPB-RA2E1
- FPB-RA2E2
- FPB-RA4E1
- FPB-RA6E1
- MCK-RA6T2
- RSSK-RA2L1
- RSSK-RA6T1
- FPB-RA4E2
- FPB-RA6E2
- EK-RA4E2
- EK-RA6E2
- MCK-RA4T1
- MCK-RA6T3


### Supported Software Packaged with FSP

For a list of software modules packaged with FSP, see [Supported Software](SUPPORTED_SOFTWARE.md).

### Product Security Advisories

[Product Security Advisories](https://github.com/renesas/fsp/issues?q=label%3Aproduct_security_advisory) for FSP and third party software (where available) are tagged with the 'product_security_advisory' label. Please check these issues for information from the respective vendors for affected versions and a recommended workaround or patch upgrade.

### Known Issues

[Visit GitHub Issues for this project.](https://github.com/renesas/fsp/issues)

[Critical issues](https://github.com/renesas/fsp/issues?q=label%3Acritical+is%3Aclosed) that cause an MCU to operate out of the hardware manual documented specifications are tagged with the 'critical' label. Please check critical issues before going to production for a workaround or recommended patch upgrade.

### Setup Instructions

#### For existing users that are using FSP with e² studio

- FSP versions of 2.0.0 and later require a minimum e² studio version of 2020-10.
- FSP versions of 2.3.0 and later require a minimum e² studio version of 2021-01.
- FSP versions of 3.0.0 and later require a minimum e² studio version of 2021-04.
- FSP versions of 3.2.0 and later require a minimum e² studio version of 2021-07.
- FSP versions of 3.4.0 and later require a minimum e² studio version of 2021-10.
- FSP versions of 3.6.0 and later require a minimum e² studio version of 2022-01.
- FSP versions of 3.7.0 and later require a minimum e² studio version of 2022-04.
- FSP versions of 4.0.0 and later require a minimum e² studio version of 2022-07.
- FSP versions of 4.1.0 and later require a minimum e² studio version of 2022-10.
- FSP versions of 4.3.0 and later require a minimum e² studio version of 2023-01.
- FSP versions of 4.4.0 and later require a minimum e² studio version of 2023-04.

If you have already installed a previous FSP release that included e² studio then you can download the packs separately. These are available for download under the Assets section for each release. There is a zipped version, FSP_Packs_\<version\>.zip, that will work on any supported OS. There is also a self-extracting installer version, FSP_Packs_\<version\>.exe, that will work on Windows.

When using the zipped version of the packs the zip file should be extracted into the e² studio support area. This directory is typically found under the user's home directory with a path such as `~/.eclipse/com.renesas.platform_2047834950`. The number on the end of the path is unique to each e² studio installation. If you have two e² studio installations then you will have two directories with names of the format `~/.eclipse/com.renesas.platform_<unique_number>`. Please note that e² studio must have been run at least once for this directory to be created. You can find the support area for a particular e² studio installation by clicking `Help >> About e² studio`. In the window that pops up click `Installation Details` and choose the `Support Folders` tab. The e² studio support area path will be shown.

#### For new users that are using FSP with e² studio

1.	Download the FSP with e² studio Installer from the Assets section of the [current release](https://github.com/renesas/fsp/releases/tag/v4.4.0).
2.	Run the installer. This will install the e² studio tool, FSP packs, GCC toolchain and other tools required to use this software. No additional installations are required.

#### If using RA Smart Configurator (RASC) with IAR Embedded Workbench or Keil MDK ####

1.  See [RASC User Guide for MDK and IAR](https://renesas.github.io/fsp/_s_t_a_r_t__d_e_v.html#RASC-MDK-IAR-user-guide).

### Starting Development

1. Open e² studio and click File > New > C/C++ Project.
2. In the window that pops up, choose Renesas RA in the left pane.

### Related Links

FSP Releases :  https://github.com/renesas/fsp/releases

FSP Documentation : https://renesas.github.io/fsp

FSP Webpage: www.renesas.com/ra/fsp

RA Product Information: www.renesas.com/ra

RA Product Support Forum: www.renesas.com/ra/forum

e² studio : www.renesas.com/e2studio

Example Projects : www.renesas.com/ra/example-projects

Knowledge Base: https://en-support.renesas.com/knowledgeBase/category/31087

Support: www.renesas.com/support
