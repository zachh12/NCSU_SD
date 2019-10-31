import os
sources = [(55, 137), (19, 40), (81, 208)]

def makeM(idx, conf):
    name = str(idx) + "macro.mac"
    f = open(name, "a")
    f.write("/run/verbose 1\n")
    f.write("/g4simple/setRandomSeed true\n")
    f.write("/g4simple/setReferencePhysList Shielding\n")
    f.write("/g4simple/setDetectorGDML " + str(idx) + "geom.gdml false\n")
    f.write("/g4simple/setOutputFormat hdf5\n")
    out = str(idx) + "geom"
    f.write("/analysis/setFileName " + out + "\n")
    f.write("/g4simple/setVolID geDetector_PV 1\n")
    f.write("/run/initialize\n")
    f.write("#/g4simple/listPhysVols\n")
    f.write("/gps/particle ion\n")
    source = sources[int(conf['source'])]
    src = str(str(source[0]) + " " + str(source[1]) + " ")
    f.write("/gps/ion " + src + "0 0\n")
    f.write("/gps/energy 0.0 MeV\n")
    f.write("/gps/pos/type Plane\n")
    f.write("/gps/pos/shape Circle\n")
    f.write("/gps/pos/radius 1.5 mm\n")
    colH = conf['colHeight']
    srcH = colH + 30
    f.write("/gps/pos/centre 0 0 " + str(srcH) +  " mm\n")
    f.write("/gps/pos/confine source_PV\n")
    f.write("/run/beamOn 500000\n")
    f.close()