# draw energy histograms from each detector

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import sys
#plt.style.use("mplstyle.txt")


df =  pd.read_hdf("outprocessed.hdf5", key="procdf")
df = df[df['KE'] > 2.614]
print(len(df))
radius = np.sqrt(df['x']**2 + df['y']**2)
plt.figure(0)
plt.hist(radius, bins=250, histtype='step')
plt.figure(1)
df1 = df[radius < 2.5]
plt.hist(df['x'], bins=50, histtype='step')
plt.hist(df1['x'], bins=5, histtype='step')
print(len(df1))
print(len(df1)/len(df))
plt.figure(2)
#print(df)
plt.hist(df['x'], bins=50)
plt.show()
exit()

plt.figure(0)
plt.scatter(df['x'], df['z'])
#exit()
#df = df[df['z'] > -.3]
#df = df[df['energy'] > .2]
r = np.sqrt(df['x']**2 + df['y']**2)
df1 = df[(df['x'] < 100) & (df['x'] > -100) & (df['y'] < 100) & (df['y'] > -100)]
#df1 = df[r < 100]
plt.figure(1)
plt.hist(df['x'], bins=100)
#plt.xlim(-100,100)
plt.yscale('log')
plt.figure(2)
plt.hist(df1['x'], bins=100)
plt.yscale('log')
plt.show()
#exit()

dfE = df[(df['energy'] > 0.3)]
x_hl = 100
y_hl = 100
dfE = dfE[(dfE['x'] > -x_hl) & (dfE['x'] < x_hl)]
dfE = dfE[(dfE['y'] > -y_hl) & (dfE['y'] < y_hl)]
radius = np.sqrt(dfE['x']**2 + dfE['y']**2)
plt.figure(0, figsize=(6,6))
plt.scatter(df['x'], df['y'], alpha=0.25)
#circle1 = plt.Circle((0, 0), 2.5, color='r', fill=False)
#ax.add_artist(circle1)
plt.title("Distribution")
plt.xlabel("X (mm)")
plt.ylabel("Y (mm)")
plt.xlim(-x_hl, x_hl)
plt.ylim(-y_hl, y_hl)

plt.figure(2)
plt.scatter(dfE['x'], dfE['y'], alpha=0.2)
plt.title("Full Energy Events")
plt.xlabel("X (mm)")
plt.ylabel("Y (mm)")
plt.xlim(-x_hl, x_hl)
plt.ylim(-y_hl, y_hl)


plt.figure(4)
plt.scatter(radius, dfE['z'], alpha=0.4)
plt.title("Location of Interaction")
plt.xlabel("Radius (mm)")
plt.ylabel("Depth (mm)")
#plt.xticks((np.arange(0, 100, step=0.2)))

plt.figure(5)
plt.title("R vs E")
plt.scatter(df['energy'], np.sqrt(df['x']**2 + df['y']**2), alpha=0.3)
plt.title("Energy vs Radius of Interaction")
plt.xlabel("Energy (MeV)")
plt.ylabel("Radius (mm)")
plt.ylim(-10, 150)

plt.figure(6)
plt.title("Radius of Full Energy")
r1 = dfE#[radius < 10]
plt.hist(np.sqrt(r1['x']**2 + r1['y']**2), bins=90)
plt.xlabel("Radius of Interaction (mm)")
plt.figure(7)
plt.hist(df['energy'], bins=90)
plt.xlabel("Energy (MeV)")
#plt.xlim(1,1.6)

plt.figure(9)
dfT = dfE[dfE['z'] > 17.5]
plt.scatter(np.sqrt(dfT['x']**2 + dfT['y']**2), dfT['z'])
plt.title("Interaction Location")
plt.xlabel("Radius (mm)")
plt.ylabel("Depth (mm)")
print("Good Rate: ", len(dfT)/(1000000/37000))
print("Rate : ", len(dfE)/(1000000/37000))

dfr5 = dfE[radius < 2.5]
dfr7 = dfE[radius < 3.75]
dfr10 = dfE[radius < 5.0]
dfr12 = dfE[radius < 6.0]
dfr15 = dfE[radius < 7.5]

try:
    print("Counts: ", len(dfE), len(dfr5), len(dfr7), len(dfr10), len(dfr12))
    print("5mm: ", 100*(len(dfr5)/len(dfE)))
    print("7.5mm: ", 100*(len(dfr7)/len(dfE)))
    print("10mm: ", 100*(len(dfr10)/len(dfE)))
    print("12mm: ", 100*(len(dfr12)/len(dfE)))
    print("15mm: ", 100*(len(dfr15)/len(dfE)))
except:
    print("?")

plt.show()
