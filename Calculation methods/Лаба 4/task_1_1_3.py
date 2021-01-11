from math import atan
import numpy as np
import matplotlib.pyplot as plt

# f(x) = (x - 4)*arctg(x^2 - 3)
# Корни: -sqrt(3), sqrt(3), 4.
X_1 = -3**(1/2)
X_2 = 3**(1/2)
X_3 = 4

# Концы отрезка [a; b] для 1-ого корня
a1 = -3.0
b1 = -1.5

# Концы отрезка [a; b] для 2-ого корня
a2 = 1.5
b2 = 3.0

# Концы отрезка [a; b] для 3-его корня
a3 = 3.0
b3 = 6.0

# Точность
Epsilon = 1e-12

# Наша функция
def Foo(X):
    return (X - 4.0)*atan(X**2 - 3.0)

# 2-ая производная от исходной функции (нужна, чтобы выбрать нужное начальное приближение в методе хорд)
def Foo2(X):
    return 4*X/((3 - X**2)**2 + 1) - (X - 4)/(((-8)*(3 - X**2)*(X**2))/(((3 - X**2)**2 + 1)**2) + (-2)/((3 - X**2)**2 + 1))

# Метод Бисекции
def BisectionMethod(f, a, b, Eps, ResRateArr, needed_X):
    a0 = a  # Запомним, каким a было изначально
    b0 = b  # Запомним, каким b было изначально
    Xk = 0  # Искомое решение
    print("Расчёты итераций для Xk...")
    Count = 0  # Счётчик итераций
    while abs(b - a) > 2.0*Eps:
        Xk = (a + b) / 2.0
        if f(Xk)*f(a) < 0:
            b = Xk
        else:
            a = Xk
        Count += 1  # Делаем инкремент итерации на счётчике
        nevyazka = abs(needed_X - Xk)
        ResRateArr.append(nevyazka)  # Запоминаем невязку на каждой итерации
        print(Count, ") Xk =", Xk, ", |X* - Xk| =", nevyazka)
    print("Корень функции, полученный с помощью метода бисекции на отрезке [", a0, ";", b0, "]:", Xk)
    return Count

# Метод Хорд
def ChordMethod(f, f2, a, b, Eps, ResRateArr, needed_X):
    a0 = a  # Запомним, каким a было изначально
    b0 = b  # Запомним, каким b было изначально
    if np.sign(f(a)) == np.sign(f2(a)):  # Если знак f(a) == f''(a), то берем X0 = a и X1 = b, иначе - берём X0 = b и X1 = a
        X0 = a
        X1 = b
    else:
        X0 = b
        X1 = a
    Xk = X1 - f(X1)*((X1 - X0)/(f(X1) - f(X0)))  #Xk = X2
    Xk_1 = f(4.0) + 1  #Xk+1, просто инициализируем чем-нибудь, отличным от 0
    print("Расчёты итераций для Xk...")
    Count = 0  # Счётчик итераций
    while abs(f(Xk_1)) >= Eps:
        Xk_1 = Xk - f(Xk) * ((Xk - X0) / (f(Xk) - f(X0)))
        Xk = Xk_1
        Count += 1  # Делаем инкремент итерации на счётчике
        nevyazka = abs(needed_X - Xk)
        ResRateArr.append(nevyazka)  # Запоминаем невязку на каждой итерации
        print(Count, ") Xk =", Xk, ", |X* - Xk| =", nevyazka)
    print("Корень функции, полученный с помощью метода хорд на отрезке [", a0, ";", b0, "]:", Xk)
    return Count  # Возвращаем количество итераций, которое нам понадобилось

print("\nФункция: f(x) = (x - 4)*arctg(x^2 - 3)")
print("Корни этой функции, расчитанные теоретически: -sqrt(3), sqrt(3), 4")

print("\nПоиск первого корня методом бисекции на отрезке [", a1, ";", b1, "]")
BM_ResRateArr_1 = []  # Массив ординат (норм невязки на разных итерациях) для графика Метода Бисекции для 1-ого корня
BM_IterAmount_1 = BisectionMethod(Foo, a1, b1, Epsilon, BM_ResRateArr_1, X_1)  # Делаем расчёты и запоминаем количество итераций
BM_IterArr_1 = np.arange(1, BM_IterAmount_1 + 1)  # Массив абсцисс (количества итераций) для графика Метода Бисекции для 1-ого корня

print("\nПоиск второго корня методом бисекции на отрезке [", a2, ";", b2, "]")
BM_ResRateArr_2 = []  # Массив ординат (норм невязки на разных итерациях) для графика Метода Бисекции для 2-ого корня
BM_IterAmount_2 = BisectionMethod(Foo, a2, b2, Epsilon, BM_ResRateArr_2, X_2)
BM_IterArr_2 = np.arange(1, BM_IterAmount_2 + 1)  # Массив абсцисс (количества итераций) для графика Метода Бисекции для 2-ого корня

print("\nПоиск третьего корня методом бисекции на отрезке [", a3, ";", b3, "]")
BM_ResRateArr_3 = []  # Массив ординат (норм невязки на разных итерациях) для графика Метода Бисекции для 3-ого корня
BM_IterAmount_3 = BisectionMethod(Foo, a3, b3, Epsilon, BM_ResRateArr_3, X_3)
BM_IterArr_3 = np.arange(1, BM_IterAmount_3 + 1)  # Массив абсцисс (количества итераций) для графика Метода Бисекции для 3-ого корня

print("\nПоиск первого корня методом хорд на отрезке [", a1, ";", b1, "]")
CM_ResRateArr_1 = []  # Массив ординат (норм невязки на разных итерациях) для графика Метода Хорд для 1-ого корня
CM_IterAmount_1 = ChordMethod(Foo, Foo2, a1, b1, Epsilon, CM_ResRateArr_1, X_1)
CM_IterArr_1 = np.arange(1, CM_IterAmount_1 + 1)  # Массив абсцисс (количества итераций) для графика Метода Хорд для 1-ого корня

print("\nПоиск второго корня методом хорд на отрезке [", a2, ";", b2, "]")
CM_ResRateArr_2 = []  # Массив ординат (норм невязки на разных итерациях) для графика Метода Хорд для 2-ого корня
CM_IterAmount_2 = ChordMethod(Foo, Foo2, a2, b2, Epsilon, CM_ResRateArr_2, X_2)
CM_IterArr_2 = np.arange(1, CM_IterAmount_2 + 1)  # Массив абсцисс (количества итераций) для графика Метода Хорд для 2-ого корня

print("\nПоиск третьего корня методом хорд на отрезке [", a3, ";", b3, "]")
CM_ResRateArr_3 = []  # Массив ординат (норм невязки на разных итерациях) для графика Метода Хорд для 3-ого корня
CM_IterAmount_3 = ChordMethod(Foo, Foo2, a3, b3, Epsilon, CM_ResRateArr_3, X_3)
CM_IterArr_3 = np.arange(1, CM_IterAmount_3 + 1)  # Массив абсцисс (количества итераций) для графика Метода Хорд для 3-ого корня

# Строим графики сходимостей
plt.semilogy(BM_IterArr_1, BM_ResRateArr_1, label="BM1, [-3.0; -1.5]")
plt.semilogy(BM_IterArr_2, BM_ResRateArr_2, label="BM2, [1.5; 3.0]")
plt.semilogy(BM_IterArr_3, BM_ResRateArr_3, label="BM3, [3.0; 6.0]")
plt.semilogy(CM_IterArr_1, CM_ResRateArr_1, label="CM1, [-3.0; -1.5]")
plt.semilogy(CM_IterArr_2, CM_ResRateArr_2, label="CM2, [1.5; 3.0]")
plt.semilogy(CM_IterArr_3, CM_ResRateArr_3, label="CM3, [3.0; 6.0]")
plt.title("Диаграммы сходимости")
plt.xlabel("Номер итерации")
plt.ylabel("Норма невязки на этой итерации")
plt.legend()
plt.grid(True)
plt.show()