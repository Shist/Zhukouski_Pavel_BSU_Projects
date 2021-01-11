from math import log, sqrt, exp
from numpy.random import uniform
import matplotlib.pyplot as plt
import numpy as np

"""
Вычислить значение интеграла, используя метод Монте-Карло. Оценить точность.
1. По методу Монте-Карло вычислить приближенное значения интегралов.
2. Сравнить полученное значение либо с точным значением (если его
получится вычислить), либо с приближенным, полученным в каком-либо
математическом пакете (например, в mathematica). Для этого построить
график зависимости точности вычисленного методом Монте-Карло
интеграла от числа итераций n.
Вариант 2
I1 = Integral(-oo, oo)_(e^(-x^6)dx)
I2 = Integral(x^2 + y^2 < 1)_((Integral_(ln(1 / sqrt(x^2 + y^2)))dx)dy)
"""

size = 6

minus_infinity = -999
infinity = 999

ExactFirstResult = 1.85544  # Источник точного ответа: WolframAplha https://www.wolframalpha.com/input/?i=integrate+exp%28-x%5E%286%29%29%2C+x+%3D+-oo..oo
def CalculateFirstIntegral(n, a, b, sum):
    for i in range(n):
        x = a + (b - a) * uniform()
        s = exp((-1)*pow(x, 6))
        sum += s
    FirstAnswer = sum * float(b - a) / float(n)
    return FirstAnswer

ExactSecondResult = 1.57079  # Источник точного ответа: решение от руки (https://c.radikal.ru/c41/2005/70/f6d4eaecc368.png)
def CalculateSecondIntegral(n, sum):
    for i in range(n):
        x = uniform(-1.0, 1.0)
        y = uniform(-1.0, 1.0)
        s = log(1.0 / (sqrt(x**2.0 + y**2.0)))
        if x**2.0 + y**2.0 < 1.0:
            sum += s
    SecondAnswer = sum * 4.0 / float(n)  # Домножаем на 4 по причине двух равномерных распределений с плотностями 1/2 каждая
    return SecondAnswer

def DrawIntegralsGraphics(n):
    x = np.arange(100000, n + 1, 100000)
    FirstPlot = []
    SecondPlot = []
    for i in range(100000, n + 1, 100000):
        FirstPlot.append(abs(CalculateFirstIntegral(i, minus_infinity, infinity, 0.0) - ExactFirstResult))
        SecondPlot.append(abs(CalculateSecondIntegral(i, 0.0) - ExactSecondResult))
    y1 = FirstPlot
    y2 = SecondPlot
    plt.plot(x, y1)
    plt.plot(x, y2)
    plt.xlabel("Количество итераций (в единицах)")
    plt.ylabel("Разница в подсчётов")
    plt.show()

if __name__ == '__main__':
    n = 10**size
    FirstResult = CalculateFirstIntegral(n, minus_infinity, infinity, 0.0)
    print("Расчёт интегралов для количества итераций, равного:", n)
    print("Расчёт первого интеграла...")
    print("Приближённое решение первого интеграла программой: I =", FirstResult)
    print("Точное решение первого интеграла: I =", ExactFirstResult)
    print("Модуль разницы приближённого и точного решений:", abs(FirstResult - ExactFirstResult))
    SecondResult = CalculateSecondIntegral(n, 0.0)
    print("Расчёт второго интеграла...")
    print("Приближённое решение второго интеграла программой: I =", SecondResult)
    print("Точное решение второго интеграла: I =", ExactSecondResult)
    print("Модуль разницы приближённого и точного решений:", abs(SecondResult - ExactSecondResult))
    print("Расчёт зависимости разницы подсчётов от размерности итераций для графика...")
    DrawIntegralsGraphics(n)
    print("График выведен, программа завершила свою работу.")