import sys, h5py
import pandas as pd
import numpy as np

# Modify this value for different energy resolution
pctResAt1MeV = 0;

if(len(sys.argv) != 2):
    print('Usage: postprochdf5.py [filename.hdf5]')
    sys.exit()

# have to open the input file with h5py (g4 doesn't write pandas-ready hdf5)
g4sfile = h5py.File(sys.argv[1], 'r')
g4sntuple = g4sfile['default_ntuples']['g4sntuple']

# build a pandas DataFrame from the hdf5 datasets we will use
g4sdf = pd.DataFrame(np.array(g4sntuple['event']['pages']), columns=['event'])
g4sdf = g4sdf.join(pd.DataFrame(np.array(g4sntuple['step']['pages']), columns=['step']), 
                   lsuffix = '_caller', rsuffix = '_other')
g4sdf = g4sdf.join(pd.DataFrame(np.array(g4sntuple['Edep']['pages']), columns=['Edep']), 
                   lsuffix = '_caller', rsuffix = '_other')
g4sdf = g4sdf.join(pd.DataFrame(np.array(g4sntuple['volID']['pages']), 
                   columns=['volID']), lsuffix = '_caller', rsuffix = '_other')
g4sdf = g4sdf.join(pd.DataFrame(np.array(g4sntuple['iRep']['pages']), 
                   columns=['iRep']), lsuffix = '_caller', rsuffix = '_other')
g4sdf = g4sdf.join(pd.DataFrame(np.array(g4sntuple['x']['pages']), 
                   columns=['x']), lsuffix = '_caller', rsuffix = '_other')
g4sdf = g4sdf.join(pd.DataFrame(np.array(g4sntuple['y']['pages']), 
                   columns=['y']), lsuffix = '_caller', rsuffix = '_other')
g4sdf = g4sdf.join(pd.DataFrame(np.array(g4sntuple['z']['pages']), 
                   columns=['z']), lsuffix = '_caller', rsuffix = '_other')

#Can vectorize by making NaN placeholders then simply filling if
#not already filled using a basic loop
#df = g4sdf[(g4sdf.x > -100) & (g4sdf.x < 100) & (g4sdf.z > -50) & (g4sdf.z < 30)]

# apply E cut / detID cut and sum Edeps for each event using loc, groupby, and sum
# write directly into output dataframe
detector_hits = g4sdf.loc[(g4sdf.volID == 1) & (g4sdf.Edep > 0.0)]

procdf = pd.DataFrame(detector_hits.groupby(['event','volID','iRep'], as_index=False)['Edep'].sum())
procdf = procdf.rename(columns={'iRep':'detID', 'Edep':'energy'})
x, y, z = [], [], []
for event in procdf['event']:
  dfx = (g4sdf[(g4sdf['event'] == event) & (g4sdf['volID'] == 1)])
  try:
    idx = np.argmax(list(dfx['Edep']))
    x.append(dfx['x'].iloc[idx])
    y.append(dfx['y'].iloc[idx])
    z.append(dfx['z'].iloc[idx])
  except:
    print(dfx)
    x.append(1000)
    y.append(1000)
    z.append(-100)
    exit()

#plt.figure(1)
print(len(x))
#plt.scatter(x, z)
#plt.figure(2)
#plt.hist(x)
#plt.show()
procdf['x'] = x
procdf['y'] = y
procdf['z'] = z
# apply energy resolution function
#procdf['energy'] = procdf['energy'] + np.sqrt(procdf['energy'])*pctResAt1MeV/100.*np.random.randn(len(procdf['energy']))

# write to output file
procdf.to_hdf(sys.argv[1].split(".")[0] + 'processed.hdf5', key='procdf', mode='w')

