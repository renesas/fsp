from jinja2 import Template
import pathlib
import os
import re
output_dir = '../../../../../data/.module_descriptions'

if __name__ == "__main__":
    os.chdir(pathlib.Path(__file__).parent.resolve())
    for c in ['r_canfd', 'r_canfdlite']:
        with open('Renesas##HAL Drivers##all##r_canfd####x.xx.xx.xml.j2') as temp:
            t = Template(temp.read())
            with open(os.path.join(output_dir, 'Renesas##HAL Drivers##all##{}####x.xx.xx.xml').format(c), 'w+') as f:
                f.write(re.sub(r' *\r?\n', r'\r\n', t.render(module_variant=c).strip(),flags=re.M))
