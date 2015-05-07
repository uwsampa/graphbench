#!/usr/bin/env python

from matplotlib import pyplot as PLT
from matplotlib.backends.backend_pdf import PdfPages
import numpy as NP
import collections
import sys

if len(sys.argv) != 2:
  print "Usage: verify.py <filename>"
  exit(1)

with open(sys.argv[1]) as f:
  v = NP.loadtxt(f, dtype='int', comments='#', usecols=[1])

v_hist = NP.ravel(v)   # 'flatten' v

vertex_degrees = collections.Counter(v_hist)
degrees = collections.Counter(vertex_degrees.values())

with PdfPages('figure.pdf') as pdf:
	fig = PLT.figure()
	ax1 = fig.add_subplot(111)

	ax1.scatter(degrees.keys(), degrees.values())

	ax1.set_xscale('log')
	ax1.set_yscale('log')

	PLT.plot()
	pdf.savefig()
