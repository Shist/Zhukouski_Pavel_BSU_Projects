import math
import random
import module_for_task_2_d

# a) Вычислите логарифм по основанию 2 от 15.
print("log_2(15) =", math.log(15, 2))

# b) Сгенерируйте четыре раза одно и то же число, равномерно распределенное на интервале (0; 1).
state = random.getstate()
num = random.random()
print("first generation:", num)
random.setstate(state)
num = random.random()
print("second generation:", num)
random.setstate(state)
num = random.random()
print("third generation:", num)
random.setstate(state)
num = random.random()
print("fourth generation:", num)

# c) Определите список имен, определенных в данный момент.
names_list = dir()
i = 1
for name in names_list:
    if i % 8 == 0:
        print()
    print(name, end=', ')
    i += 1
print()

# d) Создайте и выполните свой модуль на языке Python.
module_for_task_2_d.Foo()