import numpy as np
from numpy.linalg import linalg
import matplotlib.pyplot as plt
import time

SIZE = 9

# Ответ: X1 = [ 1, 1, 1, 1, 1, 1, 1, 1, 1 ]
X1_answer = np.array([1, 1, 1, 1, 1, 1, 1, 1, 1])
# https://matrixcalc.org/slu.html#solve-using-Gaussian-elimination%28%7B%7B1,1,1,1,1,1,1,1,1,9%7D,%7B1,2,4,8,16,32,64,128,256,511%7D,%7B1,3,9,27,81,243,729,2187,6561,9841%7D,%7B1,4,16,64,256,1024,4096,16384,65536,87381%7D,%7B1,5,25,125,625,3125,15625,78125,390625,488281%7D,%7B1,6,36,216,1296,7776,46656,279936,1679616,2015539%7D,%7B1,7,49,343,2401,16807,117649,823543,5764801,6725601%7D,%7B1,8,64,512,4096,32768,262144,2097152,16777216,19173961%7D,%7B1,9,81,729,6561,59049,531441,4782969,43046721,48427561%7D%7D%29
A1 = np.array([[1., 1., 1., 1., 1., 1., 1., 1., 1.],
               [1., 2., 4., 8., 16., 32., 64., 128., 256.],
               [1., 3., 9., 27., 81., 243., 729., 2187., 6561.],
               [1., 4., 16., 64., 256., 1024., 4096., 16384., 65536.],
               [1., 5., 25., 125., 625., 3125., 15625., 78125., 390625.],
               [1., 6., 36., 216., 1296., 7776., 46656., 279936., 1679616.],
               [1., 7., 49., 343., 2401., 16807., 117649., 823543., 5764801.],
               [1., 8., 64., 512., 4096., 32768., 262144., 2097152., 16777216.],
               [1., 9., 81., 729., 6561., 59049., 531441., 4782969., 43046721.]])

b1 = np.array([9., 511., 9841., 87381., 488281., 2015539., 6725601., 19173961., 48427561.])

# Ответ: X2 = [ 1, 2, 3, 4, 5, 6, 7, 8, 9 ]
X2_answer = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9])
# https://matrixcalc.org/slu.html#solve-using-Gaussian-elimination%28%7B%7B-3,-1,-1,1,4,2,3,-4,-1,8%7D,%7B-3,-1,4,1,0,3,-5,5,5,79%7D,%7B-6,-2,3,5,3,-3,-4,-3,1,-27%7D,%7B-12,-4,6,7,2,0,1,-2,-1,18%7D,%7B-24,-8,12,14,9,4,4,-1,5,186%7D,%7B-48,-16,24,28,18,6,-2,1,-2,206%7D,%7B-96,-32,48,56,36,12,-3,2,4,491%7D,%7B-192,-64,96,112,72,24,-6,-2,5,907%7D,%7B0,-1,3,0,2,2,-5,-3,4,6%7D%7D%29
A2 = np.array([[-3., -1., -1., 1., 4., 2., 3., -4., -1.],
               [-3., -1., 4., 1., 0., 3., -5., 5., 5.],
               [-6., -2., 3., 5., 3., -3., -4., -3., 1.],
               [-12., -4., 6., 7., 2., 0., 1., -2., -1.],
               [-24., -8., 12., 14., 9., 4., 4., -1., 5.],
               [-48., -16., 24., 28., 18., 6., -2., 1., -2.],
               [-96., -32., 48., 56., 36., 12., -3., 2., 4.],
               [-192., -64., 96., 112., 72., 24., -6., -2., 5.],
               [0., -1., 3., 0., 2., 2., -5., -3., 4.]])

b2 = np.array([8., 79., -27., 18., 186., 206., 491., 907., 6.])

# Ответ: вообще говоря, целое множество решений: X3 = [ -13/2 + 5/2*x3, -5/2 + 3/2*x3, x3, 4, 5, 6, 7, 8, 9 ]
X3_answer = np.array(['-13/2 + 5/2*x3', '-5/2 + 3/2*x3', 'x3', '4', '5', '6', '7', '8', '9'])
# https://matrixcalc.org/slu.html#solve-using-Gaussian-elimination%28%7B%7B2,0,-5,-3,1,1,3,2,2,41%7D,%7B2,0,-5,-5,2,-1,4,-2,-3,-44%7D,%7B4,0,-10,-1,5,-3,1,-5,-5,-101%7D,%7B8,0,-20,-9,5,1,1,-5,4,-54%7D,%7B16,0,-40,-18,13,1,-1,0,-3,-139%7D,%7B32,0,-80,-36,26,-1,0,-1,-5,-281%7D,%7B64,0,-160,-72,52,-2,8,0,-2,-418%7D,%7B128,0,-320,-144,104,-4,16,-11,5,-843%7D,%7B-1,1,1,3,0,-3,0,-5,3,-15%7D%7D%29
A3 = np.array([[2., 0., -5., -3., 1., 1., 3., 2., 2.],
               [2., 0., -5., -5., 2., -1., 4., -2., -3.],
               [4., 0., -10., -1., 5., -3., 1., -5., -5.],
               [8., 0., -20., -9., 5., 1., 1., -5., 4.],
               [16., 0., -40., -18., 13., 1., -1., 0., -3.],
               [32., 0., -80., -36., 26., -1., 0., -1., -5.],
               [64., 0., -160., -72., 52., -2., 8., 0., -2.],
               [128., 0., -320., -144., 104., -4., 16., -11., 5.],
               [-1., 1., 1., 3., 0., -3., 0., -5., 3.]])

b3 = np.array([41., -44., -101., -54., -139., -281., -418., -843., -15.])


# Максимум-норма (максимум из суммы модулей элементов строк)
def MaximumNorma(A, size):
    max_sum = 0.
    for i in range(size):
        curr_sum = 0.
        for j in range(size):
            curr_sum += abs(A[i][j])
        if curr_sum > max_sum:
            max_sum = curr_sum
    return max_sum


# Найти число обусловленности матрицы
def ConditionNumber(A, size):
    return MaximumNorma(A, size) * MaximumNorma((linalg.inv(A)), size)


#  Функция, получающая на вход матрицу A, размерность size матрицы A, а также вектор b, и возвращающая вектор X
def GaussSelectingMainElementThroughoutWholeMatrix(A, size, b):
    ColsTranspVector = np.arange(size)  # Вектор перестановок для столбцов
    for diag_ind in range(size - 1):
        max_element = A[diag_ind][diag_ind]
        max_el_i = diag_ind
        max_el_j = diag_ind
        for i in range(diag_ind, size):
            for j in range(diag_ind, size):
                if abs(A[i][j]) > max_element:
                    max_element = abs(A[i][j])
                    max_el_i = i
                    max_el_j = j
        A[[diag_ind, max_el_i], :] = A[[max_el_i, diag_ind], :]  # Меняем сначала строки местами
        b[[diag_ind, max_el_i]] = b[[max_el_i, diag_ind]]  # В том числе меняем и элементы вектора b
        A[:, [diag_ind, max_el_j]] = A[:, [max_el_j, diag_ind]]  # Потом меняем столбцы местами
        ColsTranspVector[[diag_ind, max_el_j]] = ColsTranspVector[
            [max_el_j, diag_ind]]  # Запоминаем перестановку столбцов
        for i in range(diag_ind + 1, size):  # Зануляем все элементы ниже главного в текущем столбце
            koeff = (-1) * A[i][diag_ind] / A[diag_ind][diag_ind]
            for j in range(diag_ind,
                           size):  # Ко всей строке и к вектору b мы вынуждены прибавить тот коэффициент, что прибавли к A[i][diag_ind]
                A[i][j] += koeff * A[diag_ind][j]
            b[i] += koeff * b[diag_ind]
    transp_X = np.zeros(size)  # Здесь мы уже имеем заполненную в левой нижней части нулями матрицу...
    j = size - 1
    for i in range(size - 1, -1, -1):
        for l in range(j + 1, size):
            b[i] -= A[i][l] * transp_X[l]
        transp_X[i] = b[i] / A[i][j]
        j -= 1
    X = np.zeros(size)  # Мы нашли вектор X, но его элементы пока перепутаны, нужно переставить их по нашей перестановке
    for i in range(size):
        X[i] = transp_X[ColsTranspVector[i]]
    return X


X1 = GaussSelectingMainElementThroughoutWholeMatrix(A1, SIZE, b1)
print("Определитель первой матрицы: det(A1) =", linalg.det(A1))
print("Решение первой системы c помощью NymPy: X1 =", X1)
print("Точное решение первой системы: X1 =", X1_answer, '\n')

X2 = GaussSelectingMainElementThroughoutWholeMatrix(A2, SIZE, b2)
print("Определитель второй матрицы: det(A2) =", linalg.det(A2))
print("Решение второй системы c помощью NymPy: X2 =", X2)
print("Точное решение второй системы: X2 =", X2_answer, '\n')

X3 = GaussSelectingMainElementThroughoutWholeMatrix(A3, SIZE, b3)
print("Определитель третьей матрицы: det(A3) =", linalg.det(A3))
print("Решение третьей системы c помощью NymPy: X3 =", X3)
print("Точное решение третьей системы: X3 =", X3_answer, '\n')

print("Число обусловленности максимум-нормы для первой матрицы: X(A1) =", ConditionNumber(A1, SIZE))
print("Число обусловленности максимум-нормы для второй матрицы: X(A2) =", ConditionNumber(A2, SIZE))
print("Число обусловленности максимум-нормы для третьей матрицы: X(A3) =", ConditionNumber(A3, SIZE))

print("Начало эксперимента с замерами времени работы программы на больших системах...")
ExperimentSizeCheck = 70  # Число размерной матриц для экспериментов... Т.е. будем смотреть матрицы размерностей { 1, 2, ..., ExperimentSizeCheck - 1, ExperimentSizeCheck }
SizeArr = np.arange(1, ExperimentSizeCheck + 1)  # Массив абсцисс (размерностей) для графика
TimeArr = np.zeros(ExperimentSizeCheck)  # Массив ординат (времени в секундах) для графика
StartTime = time.time()  # Начало отсчета времени (для замера скорости программы)
previous_time = 0
for i in range(1, ExperimentSizeCheck + 1):
    TimeArr[i - 1] = int(time.time() - StartTime) - previous_time
    previous_time = TimeArr[i - 1]
    A = np.random.rand(i, i)
    b = np.random.rand(i)
    GaussSelectingMainElementThroughoutWholeMatrix(A, i, b)
plt.plot(SizeArr, TimeArr)
plt.xlabel("Размерность системы (в единицах)")
plt.ylabel("Время решения системы (в секундах)")
plt.show()
print("Общее время работы: %s seconds" % (time.time() - StartTime))
