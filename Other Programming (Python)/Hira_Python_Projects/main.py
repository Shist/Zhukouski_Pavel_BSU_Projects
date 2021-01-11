import numpy as np

fin = open('input.txt')
N = int(fin.readline())
matrix = np.empty((N, 0)).tolist()
i = 0
for line in fin:
    matrix[i].append(line.split())
    i += 1
for i in matrix:
    print(i)