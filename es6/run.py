import sys, os
import matplotlib.pyplot as plt
import numpy as np
import utils
import subprocess

metro = [True, False]
points= 20
temps = np.linspace(0.2,3.0,num=points)
nspins = 50
j = 1.0
hs = [0.0, 0.02]
nblk = 100
nsteps = 10000
iter = 0
dbiter = 0
nrestarts = 5
total = len(metro)*len(temps)*len(hs)*nrestarts

utils.clean()
for i1, m in enumerate(metro):
    for i2, t in enumerate(temps):
        for i3, h in enumerate(hs):
            dbname = "database"+str(dbiter)
            print(f"dbname: database{dbiter}")
            for restart in range(nrestarts):
                print(f"---> Iter {iter+1}/{total}:  restart={restart}\th={h}\ttemp={t}\tmetro={m}")
                utils.create_temp_ini(t,nspins,j,h,m,nsteps,nblk)
                p = subprocess.Popen(f"make && ./main tempfile.ini {restart} {dbname}", shell=True, stdout = subprocess.PIPE, stderr=subprocess.PIPE)
                out, err = p.communicate()
                #print(out.decode("utf-8"))
                #print(err.decode("utf-8"))
                iter+=1
            dbiter +=1