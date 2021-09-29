import numpy as np
import subprocess

def clean():
    subprocess.run("make clean", shell=True)
    print("Removed previous outputs with make.")

states = ("solid","liquid","gas")
nrestarts = 10

clean()

for state in states:
    print(f"----> Running {state} state")
    for i in range(nrestarts):
        if i==nrestarts-1:
            eqrun = "false"
        else:
            eqrun = "true"
        print(f"--> Iter: {i+1}/{nrestarts}\tRestart: {i}\tEqrun: {eqrun}")
        p = subprocess.Popen(f"make && ./main input_files/{state}.ini {i} {eqrun}", shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        out, err = p.communicate()
        #print(out.decode("utf-8"))
        #print(err.decode("utf-8"))
    print("")