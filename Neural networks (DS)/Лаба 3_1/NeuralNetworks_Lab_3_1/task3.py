from collections import Counter

# a) В единственной строке записан текст. Для каждого слова из данного текста подсчитайте, сколько раз оно встречалось
# в этом тексте ранее.
# Словом считается последовательность непробельных символов идущих подряд, слова разделены одним или большим числом
# пробелов или символами конца строки.
some_text = "I love cookies\nWe love ice-cream\nThey like apples\nYou like cakes\nThey also like chocolate"
print("TEXT:\n" + some_text)
word_amount = {}  # Создаём словарь со словами
for word in some_text.split():  # Для каждого слова из текста...
    word_amount[word] = word_amount.get(word, 0) + 1  # Повышаем его счетчик в словаре на 1, если втретилось
print("Result:", word_amount)

# b) Вам дан словарь, состоящий из пар слов. Каждое слово является синонимом к парному ему слову. Все слова в словаре
# различны.
# Для слова из словаря, записанного в последней строке, определите его синоним.
print("Enter the number of pairs at the dictionary:")
N = int(input())  # Пусть в словаре N пар слов
Syn_words = {}  # Создаём словарь
for i in range(N):
    print("Now enter the", (i + 1), "pair:")
    first_word, second_word = input().split()  # Вводим два слова через пробел
    Syn_words[first_word] = second_word
    Syn_words[second_word] = first_word
print("Enter the word for searching its synonym:")
Needed_word = input()
print("The synonym to word " + Needed_word + " is " + Syn_words[Needed_word])

# c) Дан текст: в первой строке задано число строк, далее идут сами строки. Выведите слово, которое в этом тексте
# встречается чаще всего. Если таких слов несколько, выведите то, которое меньше в лексикографическом порядке.
word_counter = {}  # Словарь со счётчиками для каждого слова в тексте
print("Enter the number of lines in the text:")
N = int(input())  # Число строк
for i in range(N):
    print("Enter", (i + 1), "line:")
    next_str = input().split()  # Очередная строка текста, делим её на слова и помещаем в массив next_str
    for word in next_str:
        word_counter[word] = word_counter.get(word, 0) + 1  # Считаем каждое слово и запоминаем в словаре
max_count = max(word_counter.values())  # Число самой большой встречаемости какого-то слова
most_met_words = []  # Список самых встречаемых слов (из них выберем лексикографически меньшее)
for count in word_counter.items():
    if count[1] == max_count:
        most_met_words.append(count[0])
print("Most met words are:", most_met_words)
print("These words met", max_count, "times.")
print("Lexicographically smallest from these words:", min(most_met_words))

# d) Дан текст: в первой строке записано количество строк в тексте, а затем сами строки. Выведите все слова,
# встречающиеся в тексте, по одному на каждую строку. Слова должны быть отсортированы по убыванию их количества
# появления в тексте, а при одинаковой частоте появления — в лексикографическом порядке.
# Указание. После того, как вы создадите словарь всех слов, вам захочется отсортировать его по частоте встречаемости
# слова. Желаемого можно добиться, если создать список, элементами которого будут кортежи из двух элементов: частота
# встречаемости слова и само слово. Например, [(2, 'hi'), (1, 'what'), (3, 'is')]. Тогда стандартная сортировка будет
# сортировать список кортежей, при этом кортежи сравниваются по первому элементу, а если они равны — то по второму.
# Это почти то, что требуется в задаче.
Words = []  # Список слов
print("Enter the number of lines in the text:")
N = int(input())  # Число строк в тексте
for i in range(N):
    print("Enter", (i + 1), "line:")
    Words.extend(input().split())  # Добавляем в список слов слова из очередной строки текста
Word_counter = Counter(Words)  # Создаём словарь с этими словами для их подсчёта
Pairs_count_word = []  # Список пар типа (количество повторений, слово)
for i in Word_counter.items():  # Для каждой пары (слово, количество повторений)
    Pairs_count_word.append((-i[1], i[0]))  # Запоминаем (-количество повторений, слово), берём минус для сортировки
Result_words = []  # Список с результатом сортировки слов
Pairs_count_word = sorted(Pairs_count_word)  # Сортируем слова
for pair in Pairs_count_word:
    Result_words.append(pair[1])
for word in Result_words:
    print(word)