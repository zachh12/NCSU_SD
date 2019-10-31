# draw energy histograms from each detector

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import sys
plt.style.use("mplstyle.txt")

plt.figure(0)
df =  pd.read_hdf("20geomprocessed.hdf5", key="procdf")
df = df[(df['x'] < 100) & (df['x'] > -100) & (df['y'] < 100) & (df['y'] > -100)]


df = df[df['z'] > -.2]
df = df[df['energy'] > .28]
radius = np.sqrt(df['x']**2 + df['y']**2)
df5 = df[radius < 2.5]
df10 = df[radius < 5]
df15 = df[radius < 7.5]
df20 = df[radius < 10]
df30 = df[radius < 15]
num = len(df)
#print(len(df5)/num)
#plt.scatter([5, 10, 15, 20, 30], [len(df5)/num, len(df10)/num, len(df15)/num, len(df20)/num, len(df30)/num], label="Cs-137 (0.631 MeV)")
plt.hist(df['x'], bins=30, label="Cs-137 (0.631 MeV)", histtype='step')

df = pd.read_hdf("21geomprocessed.hdf5", key="procdf")
df = df[(df['x'] < 100) & (df['x'] > -100) & (df['y'] < 100) & (df['y'] > -100)]
df = df[df['z'] > -.3]
df = df[df['energy'] > .55]
radius = np.sqrt(df['x']**2 + df['y']**2)

df5 = df[radius < 2.5]
df10 = df[radius < 5]
df15 = df[radius < 7.5]
df20 = df[radius < 10]
df30 = df[radius < 15]
num = len(df)
#plt.scatter([5, 10, 15, 20, 30], [len(df5)/num, len(df10)/num, len(df15)/num, len(df20)/num, len(df30)/num], label="K-40 (1.4 MeV)")
plt.hist(df['x'], bins=30, label="K-40 (1.4 MeV)", histtype='step')
df = pd.read_hdf("64geomprocessed.hdf5", key="procdf")
df = df[(df['x'] < 100) & (df['x'] > -100) & (df['y'] < 100) & (df['y'] > -100)]
df = df[df['z'] > -.3]
df = df[(df['energy'] > .6) & (df['energy'] < 1.2)]

radius = np.sqrt(df['x']**2 + df['y']**2)
#plt.scatter(df['energy'], radius)
#plt.show()
#exit()
df5 = df[radius < 2.5]
df10 = df[radius < 5]
df15 = df[radius < 7.5]
df20 = df[radius < 10]
df30 = df[radius < 15]
num = len(df)
print(len(df5)/num)
#plt.scatter([5, 10, 15, 20, 30], [len(df5)/num, len(df10)/num, len(df15)/num, len(df20)/num, len(df30)/num],label="Tl-208 (2.615 MeV)")
plt.hist(df['x'], bins=30, label="Tl-208 (2.615 MeV)", histtype='step')
plt.xlabel("X-Position (mm)")
plt.ylabel("Counts per 4 mm")
plt.title("Beam Width vs Precision")
#plt.xlabel("Beam Diameter (mm)")
#plt.ylabel("Fraction within Diameter")

plt.legend()
plt.show()

