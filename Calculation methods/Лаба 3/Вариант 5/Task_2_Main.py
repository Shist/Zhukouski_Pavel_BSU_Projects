import matplotlib.pyplot as plt
import numpy as np
import time

# Лабораторная №3, Вариант №5, Задание №2, Матрица №5
# Задание №2. Метод релаксации 1
# Дана матрица A (указана в варианте, см. список 1 ниже).
# 1. Написать программу, которая решает СЛАУ Ax = b методом релаксации (в качестве вектора b взять вектор,
# соответствующий какому-нибуь заданному значению x). Экспериментально подобрать значение параметра w, при котором
# итерационный процесс сходится w1), а также значение, при котором он расходится (w0).
# 2. Путем теоретического анализа подтвердить сходимость и расходимость.
# 3. Построить логарифмическую диаграмму сходимости (совмещенную) для w = w0, w1, w = 1 и еще двух любых значений от 0
# до 2.

# Номер итерационного процесса
ProcessNum = 1

# Требуемая точность (для итераций)
Epsilon = 0.00000001

# Размерность матрицы
N = 3

# Заданная матрица A
A = np.array([[-1., 1., -1.],
              [-1., 4., -2.],
              [2., -3., 5.]])

# Возьмём начальное приближение (0, 0, 0):
X0 = np.array([0., 0., 0.])

# В качестве вектора-ответа возьмём вектор (7, 7, 7), тогда вектор b = A*(7, 7, 7) будет таким:
b = np.array([-7., 7., 28.])

# Значения w для экспериментов (w0 - не сходится, w1 - сходится, w2 - единица, w3 и w4 - любые от 0 до 2)
w0 = 2.5
w1 = 1.5
w2 = 1.0
w3 = 0.5
w4 = 0.1

#  Посчитать норму невязки || A*X = b || --> min
def ResidualRate(X):
    AX = np.dot(A, X)  # A*X
    AX_b = AX - b  # A*X - b
    return np.linalg.norm(AX_b)  # || A*X - b ||

# Решение СЛАУ методом релаксации
def RelaxationMethod(w, ResRateArr):
    print("\n█████████████████████████████████████████████████████████████████████████████████████████\n")

    global ProcessNum
    print("ПРОЦЕСС №", ProcessNum, "\n")
    ProcessNum += 1

    StartTime = time.time()

    print("Заданная точность Epsilon =", Epsilon, "\n")
    print("Начальное приближение X0 =", X0, "\n")
    print("Параметр релаксации w =", w, "\n")

    L = np.tril(A, k=-1)  # Нижнетреугольная матрица (на диагонали нужны нолики)

    R = np.triu(A, k=1)  # Верхнетреугольная матрица (на диагонали нужны нолики))

    D = np.diag(np.diag(A))  # Диагональная матрица (со всеми нулями, т.к. это удобнее для последующего умножения)

    ObrD = np.linalg.inv(D)  # Матрица D^(-1), обратная матрице D

    UnitMatrix = np.eye(N)  # Единичная матрица размера NxN

    # B(w) = (I + w*D^(-1)*L)^(-1)*((1 - w)*I - w*D^(-1)*R)
    I_wOBrDL_Obr = np.linalg.inv(UnitMatrix + w*np.dot(ObrD, L))  # 1) (I + wD^(-1)L)^(-1)
    I_1_w_wObrDR = (1 - w)*UnitMatrix - w*np.dot(ObrD, R)  # 2) (1-w)I - wD^(-1)R

    B = np.dot(I_wOBrDL_Obr, I_1_w_wObrDR)  # B(w) = (I + w*D^(-1)*L)^(-1)*((1 - w)*I - w*D^(-1)*R)
    print("B = (I + wD^(-1)L)^(-1)*((1-w)I - wD^(-1)R)\n\nB =\n", B, "\n")

    NormI_wObrDL_Obr = np.linalg.norm(I_wOBrDL_Obr)  # Норма первой части
    print("1) Norm((I + wD^(-1)L)^(-1)) =", NormI_wObrDL_Obr, "\n")
    NormI_1_w_wObrDR = np.linalg.norm(I_1_w_wObrDR)  # Норма второй части
    print("2) Norm((1-w)I - wD^(-1)R) =", NormI_1_w_wObrDR, "\n")

    BothPartsMult = NormI_wObrDL_Obr*NormI_1_w_wObrDR  # Произведение обоих частей

    if BothPartsMult < 1.:  # Если произведение норм двух частей < 1, то
        print("Произведение норм двух частей =", BothPartsMult, "< 1.0 => процесс сходится.\n")
    else:
        print("Произведение норм двух частей =", BothPartsMult, ">= 1.0, требуются дальнейшие исследования...\n")

        NormB = np.linalg.norm(B)  # Норма матрицы B
        print("Norm(B) = Norm((I + wD^(-1)L)^(-1)*((1-w)I - wD^(-1)R)) =", NormB, "\n")

        if NormB < 1.:  # Если норма самой матрицы B < 1, то
            print("Норма матрицы B =", NormB, "< 1.0 => процесс сходится.\n")
        else:
            print("Норма матрицы B =", NormB, ">= 1.0, требуются дальнейшие исследования...\n")

            EigenValuesB = np.linalg.eigvals(B)  # Вектор, хранящий в себе собственные значения матрицы B
            print("Собственные значения матрицы B:\n", EigenValuesB, "\n")
            MaxEigenValueB = 0.
            for i in range(EigenValuesB.size):
                if abs(EigenValuesB[i]) > MaxEigenValueB:
                    MaxEigenValueB = abs(EigenValuesB[i])
            print("Наибольшее по модулю из собственных значений матрицы B =", MaxEigenValueB, "\n")

            if MaxEigenValueB < 1.:  # Если максимальное по модулю собственное значение матрицы < 1, то
                print("Наибольшее по модулю собственное значение матрицы B =", MaxEigenValueB, "< 1.0 => процесс сходится.\n")
            else:
                print("Наибольшее по модулю собственное значение матриц =", MaxEigenValueB, ">= 1.0 => процесс расходится.\n")

    print("Процесс начал вычислительные итерации...\n")

    # x_k+1_i = (1 - w)*x_k_i + (w / a_ii)*(b_i - Sum_i-1_j=1_(a_ij*x_k+1+j) - Sum_n_j=i+1_(a_ij*x_k_j))
    Xk = X0  # Вектор Xk - нужен для нахождения вектора Xk+1 в последующих итерациях
    Xk_1 = np.zeros(N)  # Вектор Xk+1 - следующий вектор-ответ
    IterationsAmount = 0  # Количество итераций
    CurrResRate = ResidualRate(Xk)  # Текущая невязка
    while CurrResRate > Epsilon:
        IterationsAmount += 1  # На каждой итерации приплюсовываем единицу к счетчику итераций
        for i in range(N):
            FirstSum = 0
            for j in range(i):
                FirstSum += (A[i, j] * Xk_1[j])

            SecondSum = 0
            for j in range(i + 1, N):
                SecondSum += (A[i, j] * Xk[j])

            Xk_1[i] = (1 - w) * Xk[i] + (w / A[i, i]) * (b[i] - FirstSum - SecondSum)

        Xk = Xk_1  # Говорим, что вектор Xk+1 в следующей итерации будет просто Xk
        CurrResRate = ResidualRate(Xk)  # Текущая невязка
        ResRateArr.append(CurrResRate)  # Добавляем текущую невязку в список невязок для графика

    print("После", IterationsAmount, "итерации был подобран X =", Xk, "\n")

    print("Общее время работы процесса: %s seconds" % (time.time() - StartTime), "\n")

    return IterationsAmount  # По завершении процесса возвращаем количество итераций, которое нам понадобилось


print("\nМатрица A =\n", A, "\n")
print("Вектор b =\n", b)
# Значения t, в которых будем хранить времена работы всех процессов
ResRateArr1 = []  # Список ординат (норм невязки на разных итерациях) для графика 1-ого процесса
IterAmount1 = RelaxationMethod(w0, ResRateArr1)
IterArr1 = np.arange(1, IterAmount1 + 1)  # Массив абсцисс (количества итераций) для графика 1-ого процесса
ResRateArr2 = []  # Список ординат (норм невязки на разных итерациях) для графика 2-ого процесса
IterAmount2 = RelaxationMethod(w1, ResRateArr2)
IterArr2 = np.arange(1, IterAmount2 + 1)  # Массив абсцисс (количества итераций) для графика 2-ого процесса
ResRateArr3 = []  # Список ординат (норм невязки на разных итерациях) для графика 3-его процесса
IterAmount3 = RelaxationMethod(w2, ResRateArr3)
IterArr3 = np.arange(1, IterAmount3 + 1)  # Массив абсцисс (количества итераций) для графика 3-его процесса
ResRateArr4 = []  # Список ординат (норм невязки на разных итерациях) для графика 3-его процесса
IterAmount4 = RelaxationMethod(w3, ResRateArr4)
IterArr4 = np.arange(1, IterAmount4 + 1)  # Массив абсцисс (количества итераций) для графика 4-ого процесса
ResRateArr5 = []  # Список ординат (норм невязки на разных итерациях) для графика 5-ого процесса
IterAmount5 = RelaxationMethod(w4, ResRateArr5)
IterArr5 = np.arange(1, IterAmount5 + 1)  # Массив абсцисс (количества итераций) для графика 5-ого процесса
plt.semilogy(IterArr1, ResRateArr1, label='w0')
plt.semilogy(IterArr2, ResRateArr2, label='w1')
plt.semilogy(IterArr3, ResRateArr3, label='w2')
plt.semilogy(IterArr4, ResRateArr4, label='w3')
plt.semilogy(IterArr5, ResRateArr5, label='w4')
plt.xlabel("Номер итерации")
plt.ylabel("Норма невязки на этой итерации")
plt.legend()
plt.show()