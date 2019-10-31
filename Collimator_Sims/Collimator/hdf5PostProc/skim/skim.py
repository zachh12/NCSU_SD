import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

def main():
    configs = pd.read_hdf("../../configs.h5", key='data')
    print(configs[50:70])
    exit()
    #51, 53
    configs.iloc[51]['source'] = 3
    configs.iloc[53]['source'] = 3
    configs1 = configs[configs['source'] == 1]
    win = within(5, configs1.index)
    #plt.close()
    #weights = []
    #for idx in configs1.index:
    #    con = configs1.loc[idx]
    #    weights.append(((((con['routter']/10)**2)*3.14)*(con['colHeight']/10))*(11.4/1000))

    #plt.scatter(weights, win)
    ##plt.title("1.4 MeV Mass vs Precision")
    ##plt.ylabel("Fraction of Beam Within 5mm")
    #plt.xlabel("Mass (kg)")
    #plt.axvline(x=22.5, color='r')
    plt.show()

def histAll(idxs):
    plt.figure(0)
    for idx in idxs:
        try:
            plt.hist(skim(idx)['x'], histtype='step', bins=50, alpha=0.7)
        except:
            print(idx)
    plt.axvline(x=-2.5)
    plt.axvline(x=2.5)
    plt.ylabel("Counts/14s/uCi/4cm")

def plot(idx):
    df = pd.read_hdf("../" + str(idx) + "geomprocessed.hdf5")
    df = df[(df['x'] < 100) & (df['x'] > -100)]
    df = df[(df['y'] < 100) & (df['y'] > -100)]
    df = df[(df['energy'] > 0.6)]
    df = df[df['z'] > -.4]
    plt.figure(0)
    plt.hist(df['x'], histtype='step', bins=40)
    plt.figure(1)
    r = np.sqrt(df['x']**2 + df['y']**2)
    plt.scatter(df['energy'], r)
    df5 = df[r < 2.5]
    plt.figure(2)
    plt.scatter(df['z'], r)
    print(np.std(df['x']))
    print(len(df5)/len(df))


def within(bounds, idxs):
    #plt.figure(1)
    in5 = []
    for idx in idxs:
        try:
            df = skim(idx)
            radius = np.sqrt(df['x']**2 + df['y']**2)
            xin = df[radius < (bounds/2)]
            in5.append(len(xin)/len(df))
        except:
            in5.append(0)

    label = ""
    if idxs[0] == 0:
        label = "Cs-137 (0.631 MeV)"
    elif idxs[0] == 1:
        label = "K-40 (1.41 MeV)"
    else:
        label = "Tl-208 (2.615 MeV)"
    plt.scatter(idxs, in5, label=label)
    plt.show()
    #return in5


def skim(idx):
    sim = pd.read_hdf("../" + str(idx) + "geomprocessed.hdf5")
    sim = sim[(sim['x'] < 100) & (sim['x'] > -100)]
    sim = sim[(sim['y'] < 100) & (sim['y'] > -100)]
    sim = sim[sim['energy'] > 0.3]
    sim = sim[sim['z'] > -.15]
    return sim

if __name__ == "__main__":
    main()