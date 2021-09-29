import numpy as np
import subprocess
import math

def make():
    subprocess.run("make", shell=True)

def clear(dir=None):
    if dir is not None:
        assert isinstance(dir,str)
        dir = dir.lower()
        assert dir in ["pigs","pimc"]
        subprocess.run(f"make clean{dir}", shell=True)
    else:
        subprocess.run("make clean", shell=True)

def create_temp_inputfile(temp:float):
    content = f"""timeslices				30
temperature				{temp}
imaginaryTimePropagation		8.0
                                                                                                                 
brownianMotionReconstructions           0
delta_translation			1.8
brownianBridgeReconstructions		20
brownianBridgeAttempts			4
                                                                                                                 
MCSTEPS					4000
equilibration				2000
blocks					20
wavefunction_type					flat
                                                                                                                 
histogram_bins				400
histogram_start				-10
histogram_end				10
timeslices_interval_for_averages	1 29
"""
    file = open("tempfile.pimc","w+")
    file.write(content)
    file.close()

temps = [math.pow(2,i) for i in range(0,5)]

clear("pimc")
make()
for t in temps:
    print("Running PIMC with tempereature ",t)
    create_temp_inputfile(t)
    p = subprocess.Popen("./qmc1d tempfile.pimc", shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    out, err = p.communicate()
    print(out.decode("utf-8"))
    print(err.decode("utf-8"))

subprocess.run("rm -f tempfile.pimc")