# a) По аналогии с разобранным примером составьте список фамилий группы и запишите его в текстовый файл.
# Распечатайте созданный файл.
f = open('group_info.txt', 'w')
group_list = ["Bandyuk",
               "Grishkin",
               "Zhukovsky",
               "Konovalova",
               "Koptev",
               "Kokhovets",
               "Malyavko",
               "Makhnitsky",
               "Rogozenko",
               "Rubatsky",
               "Shikovets"]
for student in group_list:
    f.write(student + '\n')
f.close()
f = open('group_info.txt', 'r')
print(f.read())
f.close()

# b) Распечатайте созданный файл фамилий построчно, добавив перед каждой фамилией ее порядковый номер.
f = open('group_info.txt', 'r')
num = 1
for line in f:
    print(str(num) + ") " + line, end='')
    num += 1
f.close()

# c) Создайте файл, добавив к каждой фамилии имя. Распечатайте его построчно.
f = open('group_new_info.txt', 'w')
group_full_list = ["Bandyuk Paul",
                   "Grishkin Andrew",
                   "Zhukovsky Paul",
                   "Konovalova Valeria",
                   "Koptev Gleb",
                   "Kokhovets Alexey",
                   "Malyavko Alexandra",
                   "Makhnitsky Nikita",
                   "Rogozenko Dmitriy",
                   "Rubatsky Andrew",
                   "Shikovets Alexander"]
for student in group_full_list:
    f.write(student + '\n')
f.close()
f = open('group_new_info.txt', 'r')
print(f.read())
f.close()

# d) Распечатайте из последнего файла только фамилию и первую букву имени.
f = open('group_new_info.txt', 'r')
for line in f:
    two_words = line.split()
    result_str = two_words[0]
    result_str += ' '
    result_str += two_words[1][0]
    print(result_str)
f.close()