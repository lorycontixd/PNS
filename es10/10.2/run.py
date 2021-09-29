"""
Automation script for TSP Simulated Annealing using MPI for parallelization.
...
"""

import numpy as np
import subprocess
import utils

processes = (2,3,4)
layouts = ("circle","square")

utils.cleanall()
utils.make()
for i1, l in enumerate(layouts):
    print("====> layout: ",l)
    for i2, p in enumerate(processes):
        print("==> Processes: ",p)
        utils.create_temp_ini(l,32,1,"L2",2000,1000,1.004)
        p = subprocess.Popen(f"mpirun -n {p} ./main tempfile.ini", shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        out, err = p.communicate()
        print(out.decode("utf-8"))
        print(err.decode("utf-8"))
    print("")
utils.remove_tempfile()