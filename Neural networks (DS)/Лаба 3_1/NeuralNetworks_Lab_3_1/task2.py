from random import randrange

# a) Даны два списка чисел. Посчитайте, сколько чисел содержится одновременно как в первом списке, так и во втором.
# Примечание. Эту задачу на Питоне можно решить в одну строчку.
some_list_1 = [1, 2, 3, 4]
some_list_2 = [5, 6, 7]
print("First list:", len(some_list_1), "numbers\nSecond list:", len(some_list_2), "numbers")

# b) Во входной строке записана последовательность чисел через пробел. Для каждого числа выведите слово
# YES (в отдельной строке), если это число ранее встречалось в последовательности или NO, если не встречалось.
some_input_str = "1 2 2 3 3 3 4 4 4 4"
numbers_list = list(map(int, some_input_str.split(" ")))  # Разбиваем строку с числами и запоминаем в список все числа
numbers_set = set()  # Множество, в которое будем класть числа
print("Input string:", some_input_str)
for num in numbers_list:
    print(num, "- NO") if num not in numbers_set else print(num, "- YES")
    numbers_set.add(num)

# c) Аня и Боря любят играть в разноцветные кубики, причем у каждого из них свой набор и в каждом наборе все кубики
# различны по цвету. Однажды дети заинтересовались, сколько существуют цветов таких, что кубики каждого цвета
# присутствуют в обоих наборах. Для этого они занумеровали все цвета случайными числами от 0 до 108. На этом их
# энтузиазм иссяк, поэтому вам предлагается помочь им в оставшейся части.
# В первой строке входных данных записаны числа N и M — число кубиков у Ани и Бори. В следующих N строках заданы номера
# цветов кубиков Ани. В последних M строках номера цветов Бори.
# Найдите три множества: номера цветов кубиков, которые есть в обоих наборах; номера цветов кубиков, которые есть
# только у Ани и номера цветов кубиков, которые есть только у Бори. Для каждого из множеств выведите сначала
# количество элементов в нем, а затем сами элементы, отсортированные по возрастанию.
cubes_list = list(range(1, 109))  # Список всех цветов кубиков
N = 37  # Пусть у Ани 37 кубиков
Anya_cubes = set()  # Множество с кубиками у Ани (почему множество - чтобы цвета кубиков не повторялись)
while len(Anya_cubes) != N:  # Пока не накопится N уникальных кубиков, будем подбирать их из списка всех цветов кубиков
    Anya_cubes.add(cubes_list.pop(randrange(0, len(cubes_list))))
cubes_list = list(range(1, 109))  # Обновляем список всех цветов кубиков
M = 41  # Пусть у Бори 41 кубик
Borya_cubes = set()  # Множество с кубиками у Бори (почему множество - чтобы цвета кубиков не повторялись)
while len(Borya_cubes) != M:  # Пока не накопится N уникальных кубиков, будем подбирать их из списка всех цветов кубиков
    Borya_cubes.add(cubes_list.pop(randrange(0, len(cubes_list))))
Common_cubes = Anya_cubes.intersection(Borya_cubes)  # Кубики, которые есть у обоих
Only_Anya_cubes = Anya_cubes.difference(Borya_cubes)  # Кубики, которые есть только у Ани
Only_Borya_cubes = Borya_cubes.difference(Anya_cubes)  # Кубики, которые есть только у Бори
print("Anya has", N, "cubes, they are:\n", sorted(Anya_cubes))
print("Borya has", M, "cubes, they are:\n", sorted(Borya_cubes))
print("Set of cubes that both have, whole count -", len(Common_cubes), ", they are:\n", sorted(Common_cubes))
print("Only Anya's set of cubes, whole count -", len(Only_Anya_cubes), ", they are:\n", sorted(Only_Anya_cubes))
print("Only Borya's set of cubes, whole count -", len(Only_Borya_cubes), ", they are:\n", sorted(Only_Borya_cubes))

# d) Август и Беатриса играют в игру. Август загадал натуральное число от 1 до n. Беатриса пытается угадать это число,
# для этого она называет некоторые множества натуральных чисел. Август отвечает Беатрисе YES, если среди названных ей
# чисел есть задуманное или NO в противном случае. После нескольких заданных вопросов Беатриса запуталась в том, какие
# вопросы она задавала и какие ответы получила и просит вас помочь ей определить, какие числа мог задумать Август.
# В первой строке задано n - максимальное число, которое мог загадать Август. Далее каждая строка содержит вопрос
# Беатрисы (множество чисел, разделенных пробелом) и ответ Августа на этот вопрос.
# Вы должны вывести через пробел, в порядке возрастания, все числа, которые мог задумать Август.
N = 100  # Пусть Август мог задагадать числа от 1 до 100
Numbers_list = list(range(1, N + 1))  # Список чисел, которые мог загадать Август
August_Num = randrange(1, N + 1)  # Август загадал какое-то случайное число
print("August made a number:", August_Num)
Beatris_guess = set(Numbers_list)  # Финальная догадка Беатрис (множество каких-то чисел)
for tries in range(5):  # Предположим, Беатрис загадывала 5 множеств
    Numbers_list = list(range(1, N + 1))  # Беатрис не помнит, что загадывала, потому обновляем список чисел
    Beatris_question = set()  # Текущая догадка Беатрис (множество каких-то чисел)
    for i in range(20):  # Выберем 20 случайных чисел из списка с числами
        Beatris_question.add(Numbers_list.pop(randrange(0, len(Numbers_list))))
    print(tries + 1, "Beatris' guess:\n", Beatris_question)
    print(tries + 1, "August's answer:")
    if August_Num in Beatris_question:
        Beatris_guess = Beatris_guess.intersection(Beatris_question)
        print("YES")
    else:
        print("NO")
print("Set of numbers that August could made:\n", sorted(Beatris_guess))