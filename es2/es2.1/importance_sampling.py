from matplotlib import pyplot as plt
import math
import numpy as np

def f(x):
    return (np.pi/2)*np.cos((np.pi/2)*x)

def g(x):
    return 2*(1-x)

x = np.arange(0,1,0.01)
fy = [f(i) for i in x]
gy = [g(i) for i in x]

plt.title("Importance sampling distribution")
plt.xlabel("x")
plt.ylabel("y")
plt.plot(x,fy,label="integrand")
plt.plot(x,gy,label="p(x)")
plt.legend()
plt.show()