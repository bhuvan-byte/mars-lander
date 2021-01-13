import matplotlib.pyplot as plt
file=open("output.txt")
arr1=[float(x) for x in file.readline()[1:-4].split(',')]
arr2=[float(x)*25 for x in file.readline()[1:-4].split(',')]

plt.plot(arr1)
plt.plot(arr2)
plt.ylabel('some numbers')
plt.savefig("plot.png")
