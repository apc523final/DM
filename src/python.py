import numpy as np
import matplotlib.pyplot as pp

x1,y1,z1,x2,y2,z2,energy = np.loadtxt("candelete.txt",unpack=True)

pp.plot(range(len(x1)),x1,label='x1')
pp.plot(range(len(y1)),y1,label='y1')
pp.plot(range(len(x2)),x2,label='x2')
pp.plot(range(len(x1)),y2,label='y2')
pp.plot(range(len(x1)),energy,label='energy')

#pp.xlim(20,30)

pp.legend(loc='lower left')

pp.savefig('temp.pdf')

