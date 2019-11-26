from numpy import *
from matplotlib.pylab import *

itera = loadtxt("iteraciones.txt")
nx = loadtxt("nx.txt")

figure(figsize=(5,7))
for i in range(len(itera)):
    plot(nx,itera)
savefig("iteraciones.png")
