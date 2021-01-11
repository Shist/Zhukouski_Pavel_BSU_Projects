# a) Даны четыре действительных числа: x1, y1, x2, y2. Напишите функцию distance(x1, y1, x2, y2), вычисляющая расстояние
# между точкой (x1,y1) и (x2,y2). Считайте четыре действительных числа и выведите результат работы этой функции.

# e) В написанную в пункте a) программу добавьте обработку не менее двух типов исключений.

def distance(_x1, _y1, _x2, _y2):
    return ((_x2 - _x1)**2 + (_y2 - _y1)**2)**0.5

try:
    print("task a)")
    print("Enter x1:")
    x1 = float(input())
    print("Enter y1:")
    y1 = float(input())
    print("Enter x2:")
    x2 = float(input())
    print("Enter xy:")
    y2 = float(input())
    print("The distance between (", x1, ",", y1, ") and (", x2, ",", y2, ") is", distance(x1, y1, x2, y2))
except ValueError:
    print("ValueError: Some number was entered incorrectly")
except RuntimeError:
    print("RuntimeError: An unknown error has occurred at runtime")

# b) Дано действительное положительное число a и целоe число n. Вычислите a^n. Решение оформите в виде функции
# power(a, n). Стандартной функцией возведения в степень можно пользоваться для проверки результата.

def power(_a, _n):
    result = 1.0
    if _n >= 0.0:
        for i in range(_n):
            result *= _a
    else:
        _n = -_n
        for i in range(_n):
            result /= _a
    return result

print("\ntask b)")
print("Enter a:")
a = float(input())
print("Enter n:")
n = int(input())
print("Power(", a, ",", n, ") =", power(a, n), "; standard function pow(", a, ",", n, ") =", pow(a, n))

# c) Напишите функцию capitalize(), которая принимает слово из маленьких латинских букв и возвращает его же, меняя
# первую букву на большую. Например, print(capitalize('word')) должно печатать слово Word. На вход подаётся строка,
# состоящая из слов, разделённых одним пробелом. Слова состоят из маленьких латинских букв. Напечатайте исходную
# строку, сделав так, чтобы каждое слово начиналось с большой буквы. При этом используйте вашу функцию capitalize().
# Напомним, что в Питоне есть функция ord(), которая по символу возвращает его код в таблице ASCII, и функция chr(),
# которая по коду символа возвращает сам символ. Например, ord('a') == 97, chr(97) == 'a'.

def capitalize(_word):
    ascii_num = ord(_word[:1])
    ascii_num -= 32
    return chr(ascii_num) + _word[1:]

print("\ntask c)")
print("Enter your words with little letters:")
words = input().split()
print("Your words, but with big letters:")
result_words = ""
for word in words:
    result_words += (capitalize(word) + " ")
print(result_words)

# d) Напишем функцию max(), которая принимает переменное число аргументов и возвращает максимум из них (на самом деле,
# такая функция уже встроена в Питон).

def max(*_nums):
    result = nums[0]
    for num in nums:
        if num > result:
            result = num
    return result

print("\ntask d)")
print("Enter your elements:")
nums = list(map(float, input().split()))
print("max(", str(nums), ") =", max(nums))