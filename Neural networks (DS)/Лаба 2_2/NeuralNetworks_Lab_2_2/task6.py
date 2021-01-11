import random

# a) Определите: сколько гласных и сколько согласных букв в строке.
some_str = "Neural Networks"
vow_count = 0  # Гласные
cons_count = 0  # Согласные
for i in some_str:
    letter = i.lower()  # Приводим букву к нижнему регистру
    if letter == "a" or letter == "e" or letter == "i" or letter == "o" or letter == "u" or letter == "y":
        vow_count += 1
    else:
        cons_count += 1
print("Vowels: ", vow_count)
print("Consonants: ", cons_count)

# b) Дано предложение, слова которого отделены пробелами, в конце предложения точка. Напишите каждое слово, начиная
# его с большой буквы и заканчивая точкой.
some_sentence = "Python is one of the most popular languages."
print(some_sentence.title())

# c) Дана строка. Определите частоту, с которой входят разные буквы в эту строку.
some_str = "apple"
whole_amount = len(some_str)
# Для каждой буквы считаем её количество в строке, делим на общее количество и умножаем на 100%
stats = {letter: str(some_str.count(letter) / whole_amount * 100) + "%" for letter in set(some_str)}
print(stats)

# d) Дана строка. Группы символов между пробелами считаются словами. Определите сколько слов начинается и
# заканчивается одной и той же буквой.
some_str = "apple banana eye sos image a"
words = some_str.split()
count = 0
for word in words:
    word_length = len(word)
    if word_length == 1:  # Если в слове одна буква, то мы в любом случае его засчитываем
        count += 1
    elif word[0] == word[word_length - 1]:
        count += 1
print(count)

# e) Создайте список из случайных целочисленных значений. Определите максимальный и минимальный элементы в нем.
# Если таких элементов несколько, то выведите значение и индексы всех таких элементов.
some_list = random.sample(range(-100, 100), 5)
print("Generated array:", some_list)
max_value = -101
max_value_indexes = []
min_value = 101
min_value_indexes = []
for i in range(len(some_list)):
    if some_list[i] > max_value:
        max_value = some_list[i]
        max_value_indexes.clear()
        max_value_indexes.append(i)
    elif some_list[i] == max_value:
        max_value_indexes.append(i)
    if some_list[i] < min_value:
        min_value = some_list[i]
        min_value_indexes.clear()
        min_value_indexes.append(i)
    elif some_list[i] == min_value:
        min_value_indexes.append(i)
print("Maximal value in the list:", max_value)
print("The indexes of elements with maximal value in the list:", max_value_indexes)
print("Minimal value in the list:", min_value)
print("The indexes of elements with minimal value in the list:", min_value_indexes)

# f) В списке перепишите все ненулевые элементы в начало списка (сохраняя порядок), а нулевые - в конец.
some_list = [42, 0, 12, 514, 0, 341, 0, 0, 1004]
some_list.sort(key=lambda x: not x)
print(some_list)