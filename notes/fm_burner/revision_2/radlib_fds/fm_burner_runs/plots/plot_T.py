
import numpy as np
import matplotlib
matplotlib.use('PDF')       
import matplotlib.pyplot as plt

########################################################################

#-------------- DEFINE THE DATA TO PLOT (or get it from somewhere)

norad   = np.loadtxt('norad_fds_line_T.csv',   delimiter=',')
default = np.loadtxt('default_fds_line_T.csv', delimiter=',')
wsgg    = np.loadtxt('wsgg_fds_line_T.csv',    delimiter=',')
rcslw   = np.loadtxt('rcslw_fds_line_T.csv',   delimiter=',')
exp_m_1p5D = np.loadtxt('../plots/T_mean_1p5D_exp.csv', delimiter=',')
exp_m_2p5D = np.loadtxt('../plots/T_mean_2p5D_exp.csv', delimiter=',')
exp_m_3p5D = np.loadtxt('../plots/T_mean_3p5D_exp.csv', delimiter=',')

#-------------- SET UP SOME PLOT BOILERPLATE

matplotlib.rcParams.update({'font.size':20, 'figure.autolayout': True}) 
fig, ax = plt.subplots()
ax.tick_params(direction='in', top=True, right=True)

########################################################################


#-------------- MAKE THE PLOT

plt.cla()

ax.plot(norad[:,0],   norad[:,6],   ':',  color='black', linewidth=1) 
ax.plot(default[:,0], default[:,6], '-.', color='black', linewidth=1) 
ax.plot(wsgg[:,0],    wsgg[:,6],    '--', color='black', linewidth=1) 
ax.plot(rcslw[:,0],   rcslw[:,6],   '-',  color='black', linewidth=1) 
ax.plot(exp_m_3p5D[:,0], exp_m_3p5D[:,1], '^',  color='black', ms=5, linewidth=1, fillstyle='none') 
plt.text(2.5, 1300, "z=2.5D", color='blue')

ax.plot(norad[:,0],   norad[:,4],   ':',  color='blue', linewidth=1) 
ax.plot(default[:,0], default[:,4], '-.', color='blue', linewidth=1) 
ax.plot(wsgg[:,0],    wsgg[:,4],    '--', color='blue', linewidth=1) 
ax.plot(rcslw[:,0],   rcslw[:,4],   '-',  color='blue', linewidth=1) 
ax.plot(exp_m_2p5D[:,0], exp_m_2p5D[:,1], 's',  color='blue', ms=5, linewidth=1, fillstyle='none') 
plt.text(2.5, 500, "z=3.5D", color='black')

#ax.plot(rcslw[:,0], rcslw[:,2], '-',  color='green', linewidth=1) 
#ax.plot(wsgg[:,0],  wsgg[:,2],  '--', color='green',  linewidth=1) 
#ax.plot(git[:,0],   git[:,2],   ':',  color='green', linewidth=1) 
#ax.plot(exp_m_1p5D[:,0], exp_m_1p5D[:,1], 'o',  color='green', ms=5, linewidth=1, fillstyle='none') 

ax.set_xlabel("Radial position (cm)", fontsize=22)
ax.set_ylabel("T (K)",                fontsize=22)
ax.set_xlim([0,12])
ax.set_ylim([300,1500])

ax.legend(['No Rad.', 'FDS default', 'WSGG', 'RCSLW', 'Exp'], loc='upper right', frameon=False, fontsize=16)

#-------------- SAVE PLOT TO FILE CALLED plot.pdf (the ".pdf" is left off below)

plt.savefig("plot_T_mean")

