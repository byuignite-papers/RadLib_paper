
import numpy as np
import matplotlib
matplotlib.use('PDF')       
import matplotlib.pyplot as plt

########################################################################

#-------------- DEFINE THE DATA TO PLOT (or get it from somewhere)

git = np.loadtxt('fds_test_line.csv', delimiter=',')
wsgg = np.loadtxt('fds_wsgg_line.csv', delimiter=',')
rcslw = np.loadtxt('fds_rcslw_line.csv', delimiter=',')
exp_m = np.loadtxt('exp/rad_mean_exp.csv', delimiter=',')
exp_r = np.loadtxt('exp/rad_rms_exp.csv', delimiter=',')

#-------------- SET UP SOME PLOT BOILERPLATE

matplotlib.rcParams.update({'font.size':20, 'figure.autolayout': True}) 
fig, ax = plt.subplots()
ax.tick_params(direction='in', top=True, right=True)

########################################################################


#-------------- MAKE THE PLOT

plt.cla()

ax.plot(rcslw[:,1], rcslw[:,0], '-',  color='black', linewidth=1) 
ax.plot(wsgg[:,1],  wsgg[:,0],  '--', color='black',  linewidth=1) 
ax.plot(git[:,1],   git[:,0],   ':',  color='black', linewidth=1) 
ax.plot(exp_m[:,0], exp_m[:,1], 'o',  color='black', linewidth=1, fillstyle='none') 

ax.set_xlabel("Radiative Emission (kW/m)", fontsize=22)
ax.set_ylabel("Height (cm)",               fontsize=22)
ax.set_xlim([0,15])
ax.set_ylim([0,90])

ax.legend(['RCSLW', 'WSGG', 'FDS default', 'Exp'], loc='upper right', frameon=False, fontsize=16)

#-------------- SAVE PLOT TO FILE CALLED plot.pdf (the ".pdf" is left off below)

plt.savefig("plot_rad_mean")

########################################################################

plt.cla()

#-------------- MAKE THE PLOT

ax.plot(rcslw[:,2], rcslw[:,0], '-',  color='black', linewidth=1) 
ax.plot(wsgg[:,2],  wsgg[:,0],  '--', color='black',  linewidth=1) 
ax.plot(git[:,2],   git[:,0],   ':',  color='black', linewidth=1) 
ax.plot(exp_r[:,0], exp_r[:,1], 'o',  color='black', linewidth=1, fillstyle='none') 

ax.set_xlabel("RMS Radiative Emission (kW/m)", fontsize=22)
ax.set_ylabel("Height (cm)",               fontsize=22)
ax.set_xlim([0,15])
ax.set_ylim([0,90])

ax.legend(['RCSLW', 'WSGG', 'FDS default'], loc='upper right', frameon=False, fontsize=16)

#-------------- SAVE PLOT TO FILE CALLED plot.pdf (the ".pdf" is left off below)

plt.savefig("plot_rad_rms")
