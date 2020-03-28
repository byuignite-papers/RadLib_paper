
import numpy as np
import matplotlib
matplotlib.use('PDF')       
import matplotlib.pyplot as plt

########################################################################

#-------------- DEFINE THE DATA TO PLOT (or get it from somewhere)

x = np.linspace(0,10,25)

y_1   = x**0.6
y_2   = np.sin(x)*2
y_3   = np.exp(-0.2*x)*np.cos(x)*2
y_exp = np.loadtxt('data.dat')[:,1]

#-------------- SET UP SOME PLOT BOILERPLATE

matplotlib.rcParams.update({'font.size':20, 'figure.autolayout': True}) 
fig, ax = plt.subplots()
ax.tick_params(direction='in', top=True, right=True)
plt.cla()

#-------------- MAKE THE PLOT

ax.plot(x, y_1,   '-',  color='gray',  linewidth=4) 
ax.plot(x, y_2,   '--', color='blue',  linewidth=1) 
ax.plot(x, y_3,   ':',  color='red',   linewidth=1) 
ax.plot(x, y_exp, 'o',  color='black', markersize=6) 

ax.set_xlabel(r"$v_{rms} + \theta$", fontsize=22)
ax.set_ylabel("position",            fontsize=22)
ax.set_xlim([0,10])
ax.set_ylim([-2,6])

ax.legend(["T (K)", r"$\Delta_{max}=2$", r"$\rho$ (kg/m$^3$)", "Exp"], loc='upper left', frameon=False, fontsize=16)

#-------------- SAVE PLOT TO FILE fig_sample.pdf (the ".pdf" is left off below)

plt.savefig("fig_sample")

