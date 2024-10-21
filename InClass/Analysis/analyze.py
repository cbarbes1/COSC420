from matplotlib import pyplot as plt

def speed_up(p, fp, fs):
    speedup = 1/(fs + (fp/p))
    return round(speedup, 3)

def get_speedup_list(fp, plist):
    fs = 1-fp
    splist = []
    for p in plist:
        splist.append(speed_up(p, fp, fs))

    return splist

fp_list = [0.95, 0.90, 0.75, 0.50]
p_list = [5, 10, 100, 1000, 10000]
for fp in fp_list:
    speedup_list = get_speedup_list(fp, p_list)
    print(f"Speedups for fp = {fp} on each respective processor value {p_list} ==>",speedup_list)
    plt.plot(p_list, speedup_list)
    plt.xscale('log')
    plt.xticks(p_list, p_list)
    plt.legend(fp_list)
    plt.title("Speedup per # of Processors")
    plt.ylabel("Speedup")
    plt.xlabel("Processors")

plt.show()

p = 2
T1 = 0.98
Tp = 0.5
print("Ideal Run time for 2 processors: ",T1/p)
speedup = T1/Tp
print(f"Speedup on {p} processors",speedup)
efficiency = speedup/p
print(f"Efficiency on {p} processors",efficiency)

p = 8
Tp = 0.25
print("Ideal Run time for 8 processors: ",T1/p)
speedup = T1/Tp
print(f"Speedup on {p} processors",speedup)
efficiency = speedup/p
print(f"Efficiency on {p} processors",efficiency)
