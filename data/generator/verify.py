#!/usr/bin/python
from matplotlib import pyplot as PLT
import numpy as NP

with open('out14.txt') as f:
  v = NP.loadtxt(f, dtype='int', usecols=[0, 1])

from matplotlib import pyplot as PLT

# v_hist = v;
v_hist = NP.ravel(v)   # 'flatten' v
fig = PLT.figure()
ax1 = fig.add_subplot(111)

n, bins, patches = ax1.hist(v_hist, bins=NP.logspace(1, 5, 100), facecolor='green', log=True)
ax1.set_xscale('log')
ax1.invert_xaxis()
PLT.show()