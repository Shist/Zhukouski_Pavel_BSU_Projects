# Задание 1.  (из  темы  4.2, тест 1):
# Построить прогноз курса доллара США на основе курсов за 4 предшествующих дня на основе имеющихся у нас значений
# курса за 13 дней начиная с 01.01.2019: https://www.nbrb.by/statistics/Rates/RatesDaily.asp .
import numpy as np


def nonlin(x, deriv=False):
    if deriv:
        return x * (1 - x)
    return 1 / (1 + np.exp(-x))


X = np.array([[2.5574, 2.5574, 2.5574, 2.5666],
              [2.5574, 2.5574, 2.5666, 2.5707],
              [2.5574, 2.5666, 2.5707, 2.5653],
              [2.5666, 2.5707, 2.5653, 2.5538],
              [2.5707, 2.5653, 2.5538, 2.5538],
              [2.5653, 2.5538, 2.5538, 2.5538],
              [2.5538, 2.5538, 2.5538, 2.5597],
              [2.5538, 2.5538, 2.5592, 2.5640],
              [2.5538, 2.5592, 2.5640, 2.5692]])
Y = np.array([[2.5706],
              [2.5652],
              [2.5537],
              [2.5537],
              [2.5537],
              [2.5596],
              [2.5641],
              [2.5698],
              [2.5543]])

np.random.seed(1)
X /= 10
Y /= 10

syn0 = 2 * np.random.random((4, 9))
syn1 = 2 * np.random.random((9, 1))

for j in range(60000):

    l0 = X
    l1 = nonlin(np.dot(l0, syn0))
    l2 = nonlin(np.dot(l1, syn1))

    l2_error = Y - l2
    if (j % 10000) == 0:
        print('Error: ' + str(np.mean(np.abs(l2_error))))

    l2_delta = l2_error * nonlin(l2, deriv=True)

    l1_error = l2_delta.dot(syn1.T)

    l1_delta = l1_error * nonlin(l1, deriv=True)

    syn1 += l1.T.dot(l2_delta)
    syn0 += l0.T.dot(l1_delta)

# прогноз

X = np.array([[2.5729, 2.5708, 2.5629, 2.5466]])
print('American dollar 4 previous days: ', X)
Y = np.array([[2.5460]])
print('American dollar today: ', Y)

# Нормализуем
X /= 10

l0 = X
l1 = nonlin(np.dot(l0, syn0))
l2 = nonlin(np.dot(l1, syn1))
l2 *= 10

l2_error = Y - l2

print('Predicted american dollar tomorrow: ', l2)
print('Prediction Error: ', l2_error)