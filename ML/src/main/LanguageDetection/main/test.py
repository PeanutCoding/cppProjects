from collections import defaultdict as ddict
import time
nGramSize = 3
textP = ""
nGrams = ddict(int)
i = 0

def count(d, size, path):
    c = ""
    tempC = ''
    start = time.time()
    print("count() Begin count for n-gram-size: ", size)
    with open(path, "r") as f:
        for i in range(size):
            c += f.read(1)
        while True:
            d[c] += 1
            tempC = f.read(1)
            c = c[1::] + tempC
            if not tempC:
                break
    end = time.time()
    print("End counting.\nDuration: " + str(round(end - start, 3) * 1000) + "ms")
    return d
 

def count2(d, size, path):
    text = ""
    start = time.time()
    print("count2() Begin count for n-gram-size: ", size)
    with open(path, "r") as f:
        text = f.readlines()[0]
    for i in range(0, len(text) - size):
        d[text[i:i+size]] += 1
    end = time.time()
    print("End counting.\nDuration: " + str(round(end - start, 3) * 1000) + "ms")
    return d

def readIn(path):
    with open(path, "r") as f:
        print(f.readlines())


mypath = "./../res/Language-Samples/german.txt"
for k in range(nGramSize, 0, -1):
    nGrams = count(nGrams, k, mypath)
print("\n")
for k in range(nGramSize, 0, -1):
    nGrams = count2(nGrams, k, mypath)


#with open("./../res/test2.txt", "w+") as g:
 #   for k, v in nGrams.items():
  #      g.write(k + " " + str(v) + "\n")

mypath = "./../res/test2.txt"
#readIn(mypath)