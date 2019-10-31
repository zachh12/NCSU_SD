# draw energy histograms from each detector

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import sys
plt.style.use("mplstyle.txt")

plt.figure(0)
df =  pd.read_hdf("25geomprocessed.hdf5", key="procdf")
df = df[(df['x'] < 100) & (df['x'] > -100) & (df['y'] < 100) & (df['y'] > -100)]
df = df[df['z'] > -.2]
df = df[df['energy'] > .7]
r = np.sqrt(df['x']**2 + df['y']**2)
plt.scatter(df['energy'], r)
plt.figure(1)
radius = np.sqrt(df['x']**2 + df['y']**2)
df5 = df[radius < 2.5]
df10 = df[radius < 5]
df15 = df[radius < 7.5]
df20 = df[radius < 10]
df30 = df[radius < 15]
num = len(df)
plt.scatter([5, 10, 15, 20, 30], [len(df5)/num, len(df10)/num, len(df15)/num, len(df20)/num, len(df30)/num])
plt.show()