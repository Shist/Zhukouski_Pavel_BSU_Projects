# Задание 3.  (из темы 4.2, тест 4):
# Построить и обучить нейронные сети с одним и двумя скрытыми слоями для распознавания прописных букв русского
# алфавита. В качестве входных данных использовать свои инициалы (ФИО).
import numpy as np

def nonlin(x, deriv=False):
    if deriv:
        return x * (1 - x)
    return 1 / (1 + np.exp(-x))

def normalize(X):
    return (X - X.mean()) / X.std()

X = np.array([[int('0011000', 2), int('0011000',  2), int('0100100', 2) , int('1000010', 2),
                   int('1111110', 2), int('1000010', 2), int('1000010', 2), int('1000010', 2)],  # Ж
              [int('1000010', 2), int('1000100', 2), int('1001000', 2), int('1010000', 2),
                   int('1110000', 2), int('1001000', 2), int('1000100', 2), int('1000010', 2)],  # П
              [int('0111100', 2), int('1000010', 2), int('1000000', 2), int('1000000', 2),
                   int('1000000', 2), int('1000000', 2), int('1000010', 2), int('0111100', 2)]])  # С

y = np.array([[1, 0, 0],
              [0, 1, 0],
              [0, 0, 1]])

for x in range(len(X)):
    X[x] = normalize(X[x])
for y_ in range(len(y)):
    y[y_] = normalize(y[y_])

syn0 = 2*np.random.random((8, 12)) - 1
syn1 = 2*np.random.random((12, 3)) - 1

l0 = 0
l2 = 0
l2_error = 0

for j in range(60000):
    l0 = X
    l1 = nonlin(np.dot(l0, syn0))
    l2 = nonlin(np.dot(l1, syn1))
    l2_error = y - l2
    if (j % 10000) == 0:
        print('Error: ' + str(np.mean(np.abs(l2_error))))
    l2_delta = l2_error * nonlin(l2, deriv=True)
    l1_error = l2_delta.dot(syn1.T)
    l1_delta = l1_error * nonlin(l1, deriv=True)
    syn1 += l1.T.dot(l2_delta)
    syn0 += l0.T.dot(l1_delta)

print("Result: ", l2)

X = np.array([[int('1011010', 2), int('1110000', 2), int('0011001', 2), int('0011100', 2),
                   int('1000010', 2), int('1011101', 2), int('1011010', 2), int('1011010', 2)]])  # Новая буква

for x in range(len(X)):
    X[x] = normalize(X[x])

l0 = X
l1 = nonlin(np.dot(l0, syn0))
l2 = nonlin(np.dot(l1, syn1))

print('Output for new letter: ')
print(l2)