import numpy as np
import matplotlib.pyplot as plt
import time

"""
Лаба 3, Вариант 15, Задание 3, Матрица 15
Задание 3. Метод релаксации 2
Дана матрица A (указана в варианте, см. список 1 ниже).
1. Написать программу, которая решает СЛАУ Ax = b методом релаксации (в качестве вектора b взять вектор,
соответствующий какому-нибуь заданному значению x).
2. Экспериментально подобрать значение параметра w = w*, при котором сходимость будет наиболее быстрой.
3. Для подтверждения своего вывода построить совмещенную диаграмму сходимости для как минимум пяти различных
значений w (включая w*).
4. Теоретически доказать сходимость метода релаксации при w = w*.
"""

# Требуемая точность
Epsilon = 0.00000000001

# Размерность
N = 3

# Заданная матрица A
A = np.array([[-2., -2., -3.],
              [0., -4., 0.],
              [4., 0., -1.]])

# Возьмём в качестве вектора-ответа вектор (10, 10, 10), а начальное приближение (0, 0, 0):
X0 = np.array([0., 0., 0.])

# Тогда вектор b будет таким:
b = np.array([-70., -40., 30.])

# Значения w для экспериментов
w1 = 0.005
w2 = 0.01
w3 = 0.05
w4 = 0.1
w5 = 0.5  # <-- Вероятно, это наш w* (у него по наблюдениям лучшее время сходимости)


#  || A*X = b || --> min (Норма невязки)
#  Посчитать норму невязки
def ResidualRate(X):
    AX = np.dot(A, X)
    AX_b = AX - b
    return np.linalg.norm(AX_b)


# Решение СЛАУ методом релаксации (передаём омегу и массив, в котором будет собирать информацию о невязках на итерациях)
def RelaxationMethod(w, ResRateArr):
    StartTime = time.time()

    print("При X0 =", X0, "и w =", w)

    L = np.zeros((N, N))  # Нижнетреугольная матрица
    for i in range(N):  # да, наверняка есть встроенная в numpy функция, но мне было быстрее ручками прописать
        for j in range(i):
            L[i, j] = A[i, j]

    R = np.zeros((N, N))  # Верхнетреугольная матрица
    for i in range(N):  # да, наверняка есть встроенная в numpy функция, но мне было быстрее ручками прописать
        for j in range(i + 1, N):
            R[i, j] = A[i, j]

    D = np.zeros((N, N))  # Диагональная матрица
    for i in range(N):  # да, наверняка есть встроенная в numpy функция, но мне было быстрее ручками прописать
        for j in range(N):
            if i == j:
                D[i, j] = A[i, j]

    ObrD = np.linalg.inv(D)  # Матрица D^(-1), обратная матрице D

    UnitMatrix = np.eye(N)  # Единичная матрица размера NxN

    # B(w) = (I + w*D^(-1)*L)^(-1)*((1 - w)*I - w*D^(-1)*R)
    wObrDL = w*np.dot(ObrD, L)  # wD^(-1)L
    I_wObrDL = UnitMatrix + wObrDL  # I + wD^(-1)L
    I_wOBrDL_Obr = np.linalg.inv(I_wObrDL)  # (I + wD^(-1)L)^(-1)
    wObrDR = w*np.dot(ObrD, R)  # wD^(-1)R
    I_1_w_wObrDR = (1 - w)*UnitMatrix - wObrDR  # (1-w)I - wD^(-1)R
    B = np.dot(I_wOBrDL_Obr, I_1_w_wObrDR)  # B(w) = (I + w*D^(-1)*L)^(-1)*((1 - w)*I - w*D^(-1)*R)
    print("Матрциа B =\n", B)

    NormI_wObrDL_Obr = np.linalg.norm(I_wOBrDL_Obr)  # Норма первой части
    print("Норма первой части - Norm((I + wD^(-1)L)^(-1)) =", NormI_wObrDL_Obr)
    NormI_1_w_wObrDR = np.linalg.norm(I_1_w_wObrDR)  # Норма второй части
    print("Норма второй части - Norm((1-w)I - wD^(-1)R) =", NormI_1_w_wObrDR)
    NormB = np.linalg.norm(B)  # Норма матрицы B
    print("Норма матрицы B =", NormB)
    EigenValuesB = np.linalg.eigvals(B)  # Вектор, хранящий в себе собственные значения матрицы B
    print("Собственные значения матрицы B\n", EigenValuesB)
    MaxEigenValueB = 0.
    for i in range(EigenValuesB.size):
        if abs(EigenValuesB[i]) > MaxEigenValueB:
            MaxEigenValueB = abs(EigenValuesB[i])
    print("Максимальное по модулю из собственных значений матрицы B =", MaxEigenValueB)

    if NormI_wObrDL_Obr*NormI_1_w_wObrDR < 1.:  # Если произведение норм двух частей < 1, то
        print("Произведение норм двух частей < 1.0, процесс сходится")
    elif NormB < 1.:  # Если норма самой матрицы B < 1, то
        print("Норма матрицы B < 1.0, процесс сходится")
    elif MaxEigenValueB < 1.:  # Если максимальное по модулю собственное значение матрицы < 1, то
        print("Максимальное по модулю собственное значение матрицы B < 1.0, процесс сходится")
    else:
        print("Произведение норм двух частей, Норма матрицы B и наибольшее по модулю собственное её значение >= 1.0,"
              " процесс не сходится...")

    # x_k+1_i = (1 - w)*x_k_i + (w / a_ii)*(b_i - Sum_i-1_j=1_(a_ij*x_k+1+j) - Sum_n_j=i+1_(a_ij*x_k_j))
    Xk = X0  # Вектор Xk - нужен для нахождения вектора Xk+1 в последующих итерациях
    Xk_1 = np.zeros(N)  # Вектор Xk+1 - следующий вектор-ответ
    IterationsAmount = 0  # Количество итераций
    CurrResRate = ResidualRate(Xk)  # Текущая невязка
    while CurrResRate > Epsilon:
        IterationsAmount += 1  # На каждой итерации приплюсовываем единицу к счетчику итераций
        for i in range(N):
            FirstSum = 0
            for j in range(i - 1):
                FirstSum += (A[i, j] * Xk[j])

            SecondSum = 0
            for j in range(i + 1, N):
                SecondSum += (A[i, j] * Xk[j])

            Xk_1[i] = (1 - w) * Xk[i] + (w / A[i, i]) * (b[i] - FirstSum - SecondSum)

        Xk = Xk_1  # Говорим, что вектор Xk+1 в следующей итерации будет просто Xk
        CurrResRate = ResidualRate(Xk)  # Текущая невязка
        ResRateArr.append(CurrResRate)  # Добавляем текущую невязку в список невязок для графика
    print("x1 =", Xk)

    print("Общее время работы процесса: %s seconds" % (time.time() - StartTime), "\n")

    return IterationsAmount  # По завершении процесса возвращаем количество итераций, которое нам понадобилось

# Значения t, в которых будем хранить времена работы всех процессов
ResRateArr1 = []  # Список ординат (норм невязки на разных итерациях) для графика 1-ого процесса
IterAmount1 = RelaxationMethod(w1, ResRateArr1)
IterArr1 = np.arange(1, IterAmount1 + 1)  # Массив абсцисс (количества итераций) для графика 1-ого процесса
ResRateArr2 = []  # Список ординат (норм невязки на разных итерациях) для графика 2-ого процесса
IterAmount2 = RelaxationMethod(w2, ResRateArr2)
IterArr2 = np.arange(1, IterAmount2 + 1)  # Массив абсцисс (количества итераций) для графика 2-ого процесса
ResRateArr3 = []  # Список ординат (норм невязки на разных итерациях) для графика 3-его процесса
IterAmount3 = RelaxationMethod(w3, ResRateArr3)
IterArr3 = np.arange(1, IterAmount3 + 1)  # Массив абсцисс (количества итераций) для графика 3-его процесса
ResRateArr4 = []  # Список ординат (норм невязки на разных итерациях) для графика 3-его процесса
IterAmount4 = RelaxationMethod(w4, ResRateArr4)
IterArr4 = np.arange(1, IterAmount4 + 1)  # Массив абсцисс (количества итераций) для графика 4-ого процесса
ResRateArr5 = []  # Список ординат (норм невязки на разных итерациях) для графика 5-ого процесса
IterAmount5 = RelaxationMethod(w5, ResRateArr5)
IterArr5 = np.arange(1, IterAmount5 + 1)  # Массив абсцисс (количества итераций) для графика 5-ого процесса
plt.semilogy(IterArr1, ResRateArr1, label = 'w1')
plt.semilogy(IterArr2, ResRateArr2, label = 'w2')
plt.semilogy(IterArr3, ResRateArr3, label = 'w3')
plt.semilogy(IterArr4, ResRateArr4, label = 'w4')
plt.semilogy(IterArr5, ResRateArr5, label = 'w5')
plt.xlabel("Номер итерации")
plt.ylabel("Норма невязки на этой итерации")
plt.legend()
plt.show()