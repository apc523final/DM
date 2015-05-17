import numpy as np
import matplotlib.pyplot as pp
import math


theta1 = np.loadtxt("theta1.txt",unpack=True)

n1 = theta1[0]
time1 = np.add(np.multiply(60,theta1[1]), theta1[2])
pp.plot(n1,time1,label='Tree Code',lw=2)
pp.scatter(n1,time1)

theta0 = np.loadtxt("theta0.txt",unpack=True)

n0 = theta0[0]
time0 = np.add(np.multiply(60,theta0[1]), theta0[2])

pp.plot(n0,time0,label='Pure N-body',lw=2)
pp.scatter(n0,time0,color='green')

pp.xscale(u'log')
pp.yscale(u'log')

pp.xlim(8,1170)

x=np.linspace(5,1200,100)
N2 = np.multiply(x,x)
N2 = np.multiply(N2,.0001)

logN = []
for i in range(len(x)):
    logN.append(math.log(x[i],2))

NlogN = np.multiply(x,logN)
NlogN = np.multiply(NlogN,.0003)

pp.plot(x,N2,'--',lw=.8,label='N$^2$ scaling')
pp.plot(x,NlogN,'--',lw=.8,label='NlogN scaling')

#pp.plot(range(len(x1)),x1,label='x1')
#pp.plot(range(len(y1)),y1,label='y1')
#pp.plot(range(len(x2)),x2,label='x2')
#pp.plot(range(len(x1)),y2,label='y2')
#pp.plot(range(len(x1)),energy,label='energy')

#pp.xlim(20,30)

pp.legend(loc='best')

pp.ylabel("Calculation time (seconds)")
pp.xlabel("Number of particles")

pp.savefig('scaling.pdf')

