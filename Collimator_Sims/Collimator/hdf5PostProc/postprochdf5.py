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

#import matplotlib.pyplot as plt
#plt.hist(g4sntuple['KE']['pages'])
#plt.show()
#print((g4sntuple['KE']['pages'][2]))
#exit()
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
g4sdf = g4sdf.join(pd.DataFrame(np.array(g4sntuple['KE']['pages']), 
                   columns=['KE']), lsuffix = '_caller', rsuffix = '_other')
# apply E cut / detID cut and sum Edeps for each event using loc, groupby, and sum
# write directly into output dataframe


#df = g4sdf[g4sdf['event'] == 32779]
#32779
#exit()
detector_hits = g4sdf.loc[(g4sdf.volID == 1) & (g4sdf.KE > 0) & (g4sdf.z < 1)]
procdf = pd.DataFrame(detector_hits.groupby(['event','volID','iRep'], as_index=False)['Edep'].sum())
procdf = procdf.rename(columns={'iRep':'detID', 'Edep':'energy'})
x, y, z, KE = [], [], [], []
df = g4sdf[(g4sdf['volID'] == 1) & (g4sdf['z'] < 1)]
for event in procdf['event']:
  dfx = (df[(df['event'] == event)])
  try:
    idx = np.argmax(list(dfx['KE']))
    x.append(dfx['x'].iloc[idx])
    y.append(dfx['y'].iloc[idx])
    z.append(dfx['z'].iloc[idx])
    KE.append(dfx['KE'].iloc[idx])
  except:
    print(dfx)
    x.append(1000)
    y.append(1000)
    z.append(-100)
    exit()

procdf['x'] = x
procdf['y'] = y
procdf['z'] = z
procdf['KE'] =KE
# apply energy resolution function
#procdf['energy'] = procdf['energy'] + np.sqrt(procdf['energy'])*pctResAt1MeV/100.*np.random.randn(len(procdf['energy']))

# write to output file
procdf.to_hdf(sys.argv[1].split(".")[0] + 'processed.hdf5', key='procdf', mode='w')

