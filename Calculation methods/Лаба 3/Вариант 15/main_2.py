import numpy as np
import matplotlib.pyplot as plt
import time

"""
Лаба 3, Вариант 15, Задание 5, Метод 3, Задача 1
Задание 5. Итерационные методы для разреженных СЛАУ особого вида
Дана матрица A (указана в варианте, см. список 1 ниже).
1. Написать программу, которая при данном n решает СЛАУ Anx = bn указанным в варианте методом (метод релаксации, где 
параметр w выбирается экспериментально). Здесь An - разреженные матрицы размерности n из списка 2 (см. ниже), указанные 
в варианте.
- Матрицу An следует либо хранить в одном из форматов для разреженных матриц, либо сразу реализовать итерационный метод,
учитывая известную структуру матрицы. Хранить в памяти матрицу An целиком со всеми нулями запрещено!
- Вектор bn выбирать таким образом, чтобы он соответствовал некоторому заранее заданному решению.
- Критерий остановки итераций: ||Anx^k - bn|| < Epsilon
2. Подтвердить правильность работы программы на примере нескольких СЛАУ размерности 5-10.
3. Построить диаграмму сходимости (общую) для n = 100, 1000, 10000.
4. Построить диаграмму, в которой по оси абсцисс изменяется n = [10^(k/2)], k = 1, ..., 12, а на оси ординат отложено
время работы, которое требуется, чтобы норма невязки не превышала 10^(-8).

ВИД МАТРИЦЫ:
1. Матрица An, где по диагонали - размерность матрицы (число n), а по краям - единицы (между n и 1 ставятся нули).
"""

# Требуемая точность
Epsilon = 0.00000001  # 10^(-8)

# Значение w* = 0.5
w = 0.5


# Данная функция возвращает нужную форму нашей матрицы лишь по заданной размерности N
def GenerateSpecificMatrix(N):
    Matrix = np.zeros((N, N))
    for i in range(N):
        Matrix[i][0] = 1
        Matrix[0][i] = 1
        Matrix[N - i - 1][N - 1] = 1
        Matrix[N - 1][N - i - 1] = 1
        Matrix[i][i] = N
    return Matrix


#  || A*X = b || --> min (Норма невязки)
#  Посчитать норму невязки особой матрицы
def ResidualRate(N, X, b):
    A = GenerateSpecificMatrix(N)
    AX = np.dot(A, X)
    AX_b = AX - b
    return np.linalg.norm(AX_b)


# Решение СЛАУ методом релаксации для особой матрицы (передаём омегу и массив, в котором будет собирать информацию о
# невязках на итерациях, а также размерность N для особой матрицы)
def RelaxationMethod(w, ResRateArr, N):
    PrintInfoCheck = False  # Флажок, который будет разрешать/запрещать печать информации о завершенном процесса

    if 4 < N < 11:  # Если у нас размерность из диапазона [5, 10], то мы выведем информацию, чтобы свериться
        PrintInfoCheck = True

    StartTime = time.time()

    X = np.ones(N)  # В качестве вектора-ответа возьмём X = (10, 10, 10, ..., 10, 10, 10)
    X[:] = 10

    X0 = np.zeros(N)  # А в качестве начального приближения возьмём X = (0, 0, 0, ..., 0, 0, 0)

    if PrintInfoCheck:
        print("При X0 =", X0, ", w =", w, ", N =", N)

    if PrintInfoCheck:
        print("Особая матрица A =\n", GenerateSpecificMatrix(N))

    b = np.dot(GenerateSpecificMatrix(N), X)  # Расчитываем вектор b

    if PrintInfoCheck:
        print("При векторе-ответе X =", X, "вектор b =", b)

    L = np.zeros((N, N))  # Нижнетреугольная матрица
    for i in range(N):  # да, наверняка есть встроенная в numpy функция, но мне было быстрее ручками прописать
        for j in range(i):
            L[i, j] = GenerateSpecificMatrix(N)[i, j]

    R = np.zeros((N, N))  # Верхнетреугольная матрица
    for i in range(N):  # да, наверняка есть встроенная в numpy функция, но мне было быстрее ручками прописать
        for j in range(i + 1, N):
            R[i, j] = GenerateSpecificMatrix(N)[i, j]

    D = np.zeros((N, N))  # Диагональная матрица
    for i in range(N):  # да, наверняка есть встроенная в numpy функция, но мне было быстрее ручками прописать
        for j in range(N):
            if i == j:
                D[i, j] = GenerateSpecificMatrix(N)[i, j]

    ObrD = np.linalg.inv(D)  # Матрица D^(-1), обратная матрице D

    UnitMatrix = np.eye(N)  # Единичная матрица размера NxN

    # B(w) = (I + w*D^(-1)*L)^(-1)*((1 - w)*I - w*D^(-1)*R)
    wObrDL = w*np.dot(ObrD, L)  # wD^(-1)L
    I_wObrDL = UnitMatrix + wObrDL  # I + wD^(-1)L
    I_wOBrDL_Obr = np.linalg.inv(I_wObrDL)  # (I + wD^(-1)L)^(-1)
    wObrDR = w*np.dot(ObrD, R)  # wD^(-1)R
    I_1_w_wObrDR = (1 - w)*UnitMatrix - wObrDR  # (1-w)I - wD^(-1)R
    B = np.dot(I_wOBrDL_Obr, I_1_w_wObrDR)  # B(w) = (I + w*D^(-1)*L)^(-1)*((1 - w)*I - w*D^(-1)*R)
    if PrintInfoCheck:
        print("Матрциа B =\n", B)

    NormI_wObrDL_Obr = np.linalg.norm(I_wOBrDL_Obr)  # Норма первой части
    if PrintInfoCheck:
        print("Норма первой части - Norm((I + wD^(-1)L)^(-1)) =", NormI_wObrDL_Obr)
    NormI_1_w_wObrDR = np.linalg.norm(I_1_w_wObrDR)  # Норма второй части
    if PrintInfoCheck:
        print("Норма второй части - Norm((1-w)I - wD^(-1)R) =", NormI_1_w_wObrDR)
    NormB = np.linalg.norm(B)  # Норма матрицы B
    if PrintInfoCheck:
        print("Норма матрицы B =", NormB)
    EigenValuesB = np.linalg.eigvals(B)  # Вектор, хранящий в себе собственные значения матрицы B
    if PrintInfoCheck:
        print("Собственные значения матрицы B\n", EigenValuesB)
    MaxEigenValueB = 0.
    for i in range(EigenValuesB.size):
        if abs(EigenValuesB[i]) > MaxEigenValueB:
            MaxEigenValueB = abs(EigenValuesB[i])
    if PrintInfoCheck:
        print("Максимальное по модулю из собственных значений матрицы B =", EigenValuesB)

    if PrintInfoCheck:
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
    CurrResRate = ResidualRate(N, Xk, b)  # Текущая невязка
    while CurrResRate > Epsilon:
        IterationsAmount += 1  # На каждой итерации приплюсовываем единицу к счетчику итераций
        for i in range(N):
            FirstSum = 0
            for j in range(i - 1):
                FirstSum += (GenerateSpecificMatrix(N)[i, j] * Xk[j])

            SecondSum = 0
            for j in range(i + 1, N):
                SecondSum += (GenerateSpecificMatrix(N)[i, j] * Xk[j])

            Xk_1[i] = (1 - w) * Xk[i] + (w / GenerateSpecificMatrix(N)[i, i]) * (b[i] - FirstSum - SecondSum)

        Xk = Xk_1  # Говорим, что вектор Xk+1 в следующей итерации будет просто Xk
        CurrResRate = ResidualRate(N, Xk, b)  # Текущая невязка
        ResRateArr.append(CurrResRate)  # Добавляем текущую невязку в список невязок для графика
    if PrintInfoCheck:
        print("x1 =", Xk)

    if PrintInfoCheck:
        print("Общее время работы процесса: %s seconds" % (time.time() - StartTime), "\n")

    return IterationsAmount  # По завершении процесса возвращаем количество итераций, которое нам понадобилось

# Делаем итерации для размерностей с 5 по 10, чтобы свериться
for i in range(5, 11):
    N = i
    RelaxationMethod(w, [], N)


ResRateArr1 = []  # Список ординат (норм невязки на разных итерациях) для графика 100-ого процесса
IterAmount1 = RelaxationMethod(w, ResRateArr1, 100)
IterArr1 = np.arange(1, IterAmount1 + 1)  # Массив абсцисс (количества итераций) для графика 1-ого процесса
ResRateArr2 = []  # Список ординат (норм невязки на разных итерациях) для графика 1000-ого процесса
IterAmount2 = RelaxationMethod(w, ResRateArr2, 1000)
IterArr2 = np.arange(1, IterAmount2 + 1)  # Массив абсцисс (количества итераций) для графика 2-ого процесса
ResRateArr3 = []  # Список ординат (норм невязки на разных итерациях) для графика 10000-ого процесса
IterAmount3 = RelaxationMethod(w, ResRateArr3, 10000)
IterArr3 = np.arange(1, IterAmount3 + 1)  # Массив абсцисс (количества итераций) для графика 3-его процесса
plt.semilogy(IterArr1, ResRateArr1, label = 'n = 100')
plt.semilogy(IterArr2, ResRateArr2, label = 'n = 1000')
plt.semilogy(IterArr3, ResRateArr3, label = 'n = 10000')
plt.xlabel("Номер итерации")
plt.ylabel("Норма невязки на этой итерации")
plt.legend()
plt.show()