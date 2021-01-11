# Подключаем необходимые библиотеки
import math

print("Введите точность вычислений для функции:")
epsilon = float(input())  # Точность вычислений
print("Введите значение аргумента x:")
x = float(input())  # Число x, которые мы будем подавать на вход функции
print("\nВведённая точность вычислений для нашей функции:", epsilon)
print("Введённое значение аргумента x: ", x)
sum = 0  # Накопившаяся сумма ряда Тейлора
a = x  # Дополнительная переменная, которая нам нужна для подсчёта слагаемых ряда Тейлора
i = 1  # Дополнительная переменная, которая нам нужна для подсчёта слагаемых ряда Тейлора
while abs(a) > epsilon:  # Пока не достигнем нужной точности, будем считать новое число ряда (оно все меньше и меньше)
    sum += a  # Добавляем к сумме ряда новое слагаемое
    a *= x / (i + 1)  # Считаем новое слагаемое
    i += 1  # Делаем инкремент переменной i (это нужно для нового факториала)
fault = abs(sum - math.expm1(x))  # Погрешность наших вычислений относительно библиотечной функции
print("Эталонное значение вычислений библиотечной функции math.exmp1(x): ", math.expm1(x))
print("Получившееся значение нашей функции (через ряд Тейлора): ", sum)
print("Погрешность вычислений составляет: ", fault)
