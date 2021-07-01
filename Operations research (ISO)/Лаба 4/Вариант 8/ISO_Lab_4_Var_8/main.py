# Жуковский Павел, 3 курс, 12 группа
# ИСО, Лабораторная Работа №4, Вариант 8

import numpy as np

"""
Вариант 8
Найти такие X1, X2, X3, что:
3*X1 + 7*X2 + 15*X3 --> max
s.t. 2*X1 + 3*X2 + 6*X3 <= 10
X1, X2, X3 >= 0 - целые
"""

# Количество предметов
my_N = 3

# Ценности предметов
my_v = np.array([3, 7, 15])

# Веса предметов
my_w = np.array([2, 3, 6])

# Максимальная грузоподъёмность:
my_W = 10

# Матрица, содержащая в себе таблицу
my_Table = np.zeros((my_N, my_W))

# Функция, решающая задачу о рюкзаке 0/1 алгоритмом, обновляя данные в таблице Table
# Вход:
# Таблица с данными Table
# Ценности предметов(загруженные в массив v)
# Веса предметов(загруженные в массив w)
# Количество предметов(n)
# Грузоподъемность(W)
# Возвращает элемент последнего столбца последней строки
def Knapsack(Table, N, v, w, W):
    for j in range(W):
        Table[0][j] = 0
    for i in range(N):
        for j in range(W):
            if w[i] > j:
                Table[i][j] = Table[i - 1][j]
            else:
                Table[i][j] = max(Table[i][j - 1], Table[i][j - w[i]] + v[i])
    return Table[N - 1][W - 1]

Result = Knapsack(my_Table, my_N, my_v, my_w, my_W)

cost_left = Result
X = np.zeros(3)
line = my_N - 1
col = my_W - 1
while cost_left != 0:
    while my_Table[line][col] < my_v[line]:
        line -= 1
    cost_left -= my_v[line]
    X[line] += 1
    col -= my_w[line]

print("Задача:")
print("max " + str(my_v[0]) + "*X1 + " + str(my_v[1]) + "*X2 + " + str(my_v[2]) + "*X3")
print("s.t. " + str(my_w[0]) + "*X1 + " + str(my_w[1]) + "*X2 + " + str(my_w[2]) + "*X3 <=", my_W)
print("X1, X2, X3 >= 0 - целые")
print("Таблица, после работы алгоритма:")
print(my_Table)
print("Оптимальное решение max =", Result, "достигается при следующих значениях:")
print("x1 =", X[0], ", x2 =", X[1], ", x3 =", X[2])
