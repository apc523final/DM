import numpy as np
import matplotlib.pyplot as pp

#x1,y1,z1,x2,y2,z2,energy = np.loadtxt("candelete.txt",unpack=True)
#x1,y1,z1,x2,y2,z2,com0x,com0y,com1x,com1y = np.loadtxt("candelete.txt",unpack=True)

energy = np.loadtxt("candelete.1.txt",unpack=True)

pp.plot(range(len(energy)),energy,label='$\\theta$=1',lw=2)

energy = np.loadtxt("candelete.0.txt",unpack=True)

pp.plot(range(len(energy)),energy,label='$\\theta$=0',lw=2)

pp.axhline(energy[0],xmin=0,xmax=len(energy),color='red',ls='--')

#pp.plot(range(len(x1)),x1,label='x1')
#pp.plot(range(len(y1)),y1,label='y1')
#pp.plot(range(len(x2)),x2,label='x2')
#pp.plot(range(len(x1)),y2,label='y2')
#pp.plot(range(len(x1)),energy,label='energy')

#pp.xlim(20,30)

pp.legend(loc='best')

pp.xlabel("Time (arbitrary units)")
pp.ylabel("Energy (arbitrary units)")

pp.savefig('temp.rk4.pdf')

