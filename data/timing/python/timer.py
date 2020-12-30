import numpy as np
import time
import sys

from pyrad import pyrad_planck_mean as rad_planck_mean
from pyrad import pyrad_wsgg        as rad_wsgg
from pyrad import pyrad_rcslw       as rad_rcslw

#----------------- define parameters

T      = 2000.0     # K
P      = 101325.0   # atm
xH2O   = 0.8        # xH2O=0.2 is roughly stoich. CH4/air products
xCO2   = 0.2        # xCO2=0.1 is roughly stoich. CH4/air products
xCO    = 0.0
xCH4   = 0.0
fvsoot = 0.0

#----------------- create radiation objects

planckmean = rad_planck_mean()
wsgg       = rad_wsgg()
rcslw_comp      = rad_rcslw(4, P, T, xH2O, xCO2, xCO, fvsoot)

n_upper = 24
rc_many = [rad_rcslw(i, P, T, xH2O, xCO2, xCO, fvsoot) for i in range(1, 1+n_upper)]


n_sim = 10000
pm_list = []
for i in range(n_sim):
    t1 = time.time()
    kabs_pm,    awts_pm     = planckmean.get_k_a(T, P, xH2O, xCO2, xCO, xCH4, fvsoot)
    t2 = time.time()
    pm_list.append(t2-t1)
# print(t_list)
pm_tot = np.sum(pm_list)
print("pm", pm_tot)
print(n_sim, pm_tot/n_sim)

wsgg_list = []
for i in range(n_sim):
    t1 = time.time()
    kabs_wsgg,    awts_wsgg     = wsgg.get_k_a(T, P, xH2O, xCO2, xCO, xCH4, fvsoot)
    t2 = time.time()
    wsgg_list.append(t2-t1)
# print(t_list)
wsgg_tot = np.sum(wsgg_list)
print("wsgg", wsgg_tot)
print(n_sim, wsgg_tot/n_sim)

rc_list = []
for i in range(n_sim):
    t1 = time.time()
    kabs_rc,    awts_rc     = rcslw_comp.get_k_a(T, P, xH2O, xCO2, xCO, xCH4, fvsoot)
    t2 = time.time()
    rc_list.append(t2-t1)
# print(t_list)
rc_tot = np.sum(rc_list)
print("rcslw", rc_tot)
print(n_sim, rc_tot/n_sim)

rc_m_list = []
for obj in rc_many:
    rc_i_list = []
    for i in range(n_sim):
        t1 = time.time()
        kabs_rci,    awts_rci = obj.get_k_a(T, P, xH2O, xCO2, xCO, xCH4, fvsoot)
        t2 = time.time()
        rc_i_list.append(t2-t1)
    # print(t_list)
    rc_m_list.append(np.sum(rc_i_list))
print("rcslw_many", rc_m_list)
# print(n_sim, rc12_tot/n_sim)

