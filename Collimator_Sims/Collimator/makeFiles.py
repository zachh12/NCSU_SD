import numpy as np
import pandas as pd
import os
from makeMacro import makeM
from makeGeo import makeG
import subprocess
from subprocess import Popen
sources = [(55, 137), (19, 40), (81, 208)]

def main():
    #create()
    df = pd.read_hdf('configs.h5', key='data')
    print(len(df))
    #exit()
    for i in range(89, 95):
        print(df.iloc[i])
        simConfig(i, df.iloc[i])

def simConfig(idx, conf):
    try:
        os.remove(str(idx) + "macro.mac")
        os.remove(str(idx) + "geom.gdml")
    except:
        print("Not existing...")
    #Make geometry + macro
    makeM(idx, conf)
    makeG(idx, conf)
    #Run g4simple
    mac = str(idx) + "macro.mac"
    cmd = "g4simple " + mac
    #os.system("g4simple")
    #Popen("g4simple")
    #Popen("./test.sh" , shell=False)
    #delete geo/macro
    #exit()


def create():
    #try:
    #    df = pd.read_hdf('configs.h5', key='data')
    #except:
    #    cols = ['rinner', 'routter', 'colHeight', 'source']
    #   df = pd.DataFrame(columns=cols)
    df = pd.read_hdf('configs.h5', key='data')
    rinner = [2, 2.5, 3]
    rinner = [2.5, 3]
    #routter = [70, 85, 100]
    routter = [120]
    #1mm above to "cover"
    #colHeight = [70, 100, 120]
    colHeight = [150]
    #Cs, K, Th
    #source = [0, 1]
    source = [2]

    for ri in rinner:
        for ro in routter:
            for cZ in colHeight:
                for s in source:
                    df.loc[len(df)] = (ri, ro, cZ, s)
    df.to_hdf('configs.h5', key='data')


if __name__ == "__main__":
    main()
