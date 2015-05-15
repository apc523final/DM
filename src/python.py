import numpy as np
import matplotlib.pyplot as pp

#x1,y1,z1,x2,y2,z2,energy = np.loadtxt("candelete.txt",unpack=True)
#x1,y1,z1,x2,y2,z2,com0x,com0y,com1x,com1y = np.loadtxt("candelete.txt",unpack=True)

energy1 = np.loadtxt("theta1energy.out",unpack=True)

pp.plot(range(len(energy1)),energy1,label="theta=1")

energy0 = np.loadtxt("theta0energy.out",unpack=True)

pp.plot(range(len(energy0)),energy0,label="theta=0")

#pp.plot(range(len(x1)),x1,label='x1')
#pp.plot(range(len(y1)),y1,label='y1')
#pp.plot(range(len(x2)),x2,label='x2')
#pp.plot(range(len(x1)),y2,label='y2')
#pp.plot(range(len(x1)),energy,label='energy')

#pp.xlim(20,30)

pp.legend(loc='best')

pp.savefig('temp.pdf')

