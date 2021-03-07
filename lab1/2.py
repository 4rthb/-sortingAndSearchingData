import ciura
import shellsort
import time
import pandas as pd
from numpy import random
import matplotlib.pyplot as plt

arrays = [
    random.randint(10000000, size=(100)),
    random.randint(10000000, size=(1000)),
    random.randint(10000000, size=(10000)),
    random.randint(10000000, size=(100000))
]

times = {
    'ciura' : [],
    'shellsort' : []
}

for arr in arrays:
    print("---->Array of size: ",len(arr))
    print("--------->Shellsort")
    t0 = time.process_time()
    shellsort.concha(arr.copy())
    times['shellsort'].append(time.process_time()-t0)
    print("--------->Ciura")
    t0 = time.process_time()
    ciura.conchaC(arr.copy())
    times['ciura'].append(time.process_time()-t0)

df = pd.DataFrame(times, index=['10^2','10^3','10^4','10^5'])
print(df)
plt.figure()
pic = df.plot(colormap="tab10", marker='D', markersize=7, title="Efficiency of n/2 sequence vs Ciura sequence")
plt.xlabel('Size of Array')
plt.ylabel('Time to sort')
plt.show()
pic = df.plot(colormap="tab10", marker='D', markersize=7, title="Efficiency of n/2 sequence vs Ciura sequence")
plt.xlabel('Size of Array')
plt.ylabel('Time to sort')
plt.savefig("shellgraph.png")



