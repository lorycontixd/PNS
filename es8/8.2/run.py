from operator import sub
import os
import numpy as np
import string
import subprocess
import utils

subprocess.run('make cleanauto', shell=True)
subprocess.run('make', shell=True)

mu_min=0.6
mu_max=1.0
sigma_min=0.4
sigma_max=0.8

for mu in np.linspace(mu_min, mu_max, 40):
	for sigma in np.linspace(sigma_min, sigma_max, 40):
		print ("Mu: ",utils.limit(mu),"\tSigma: ",utils.limit(sigma))
		p = subprocess.Popen(f"./main {format(mu)} {format(sigma)} true", shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
		out, err = p.communicate()
		print(out.decode("utf-8"))
		print(err.decode("utf-8"))
		print("")

mu,sigma,ene= np.loadtxt("outputs/automation/energies.dat", usecols=(0,1,2), delimiter='	', unpack='true')
ind = np.argmin(ene)
print("\n\nBest set of parameters:\nmu=",mu[ind]," sigma=",sigma[ind],"\npotential energy=",ene[ind],"\n\n")

file = open("./outputs/automation/best.dat","w+")
file.write(f"{mu[ind]}\t{sigma[ind]}\t{ene[ind]}")
file.close()

#os.system('make clean')
#os.system('make isto')
#os.system('./main_isto'+' '+format(mu[ind])+' '+format(sigma[ind]))
