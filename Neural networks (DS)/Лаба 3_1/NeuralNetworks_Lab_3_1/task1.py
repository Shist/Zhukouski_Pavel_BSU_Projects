# a) Во второй элемент кортежа (1, [2, 3]) добавьте еще один элемент: 4.
some_cortege = (1, [2, 3])
some_cortege[1].append(4)
print(some_cortege)

# b) К кортежу (1, [2, 3]) добавьте список из трех элементов.
some_cortege = (1, [2, 3])
some_list = [4, 5, 6]
some_cortege = list(some_cortege)  # Временно превращаем кортеж в список
some_cortege.append(some_list)  # Добавляем в него наш список
some_cortege = tuple(some_cortege)  # И первращаем обратно в кортеж
print(some_cortege)

# c) К кортежу (1, [2, 3]) добавьте еще один элемент: строку.
some_cortege = (1, [2, 3])
some_str = "apple"
some_cortege = list(some_cortege)  # Временно превращаем кортеж в список
some_cortege.append(some_str)  # Добавляем в него нашу строку
some_cortege = tuple(some_cortege)  # И первращаем обратно в кортеж
print(some_cortege)

# d) Во втором элементе кортежа (1, [2, 3]) повторите еще раз имеющийся список.
some_cortege = (1, [2, 3])
some_cortege = list(some_cortege)  # Временно превращаем кортеж в список
some_cortege.append(some_cortege[1])  # Добавляем в него копию второго элемента - наш меньший список
some_cortege = tuple(some_cortege)  # И первращаем обратно в кортеж
print(some_cortege)