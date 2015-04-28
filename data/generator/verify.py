#!/usr/bin/python
from matplotlib import pyplot as PLT
import numpy as NP

with open('out10.txt') as f:
  v = NP.loadtxt(f, delimiter="	", dtype='float', usecols=None)

from matplotlib import pyplot as PLT

v_hist = NP.ravel(v)   # 'flatten' v
fig = PLT.figure()
ax1 = fig.add_subplot(111)

n, bins, patches = ax1.hist(v_hist, normed=1, bins=1000, facecolor='green')
PLT.show()