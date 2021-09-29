import numpy as np
import subprocess
from rich.console import Console
c = Console()

## ------------- FUNCTIONS ----------------
def create_temp_ini(pos:tuple,sampling:str,runs:int,blocklength:int):
    content = f"""[DEFAULT]

[simulation]
runs = {runs}
blocks = {blocklength}
x0 = {pos[0]}
y0 = {pos[1]}
z0 = {pos[2]}
delta = 1
sampling = {sampling}

[settings]
test = true
logger_debug = true
data_debug = false
timeseries = false    
"""
    file = open("tempfile.ini","w+")
    file.write(content)
    file.close()

def clean():
    subprocess.run("./clean.sh",shell=True)

### -------------- MAIN -------------------

samplings = ("normal","gauss")
starting_positions = (
    (0,0,0),
    (1,1,1),
    (2,2,2),
    (3,3,3),
    (4,4,4),
    (10,0,-10)
)


clean()
for i1, sampling in enumerate(samplings):
    c.print(f" ----------------------------   {sampling}  ---------------------------- ",style="bold blue on white")
    for i2, start in enumerate(starting_positions):
        print("Iteration: ",i2)
        print("Starting position: ",start)
        create_temp_ini(start,sampling,100000,100)
        p = subprocess.Popen("make && ./main tempfile.ini", shell=True, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
        out, err = p.communicate()
        print("")
    print("\n")
