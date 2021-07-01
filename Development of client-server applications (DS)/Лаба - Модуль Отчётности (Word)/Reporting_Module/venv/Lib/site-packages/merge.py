def merge(a, b):
    i = j = 0
    c = []
    while i < len(a) and j < len(b):
        if a[i] <= b[j]:
            c.append(a[i])
            i += 1
        else:
            c.append(b[j])
            j += 1

    if i == len(a):
        for j in b[j:]:
            c.append(j)

    else:
        for i in a[i:]:
            c.append(i)

    return c


def merge_sort(lists):
    if len(lists) <= 1:
        return lists

    mid = int(len(lists)/2)
    left = merge_sort(lists[:mid])
    right = merge_sort(lists[mid:])
    return merge(left, right)

a = input("Give me a number list(enter'q'to quit):")
while a !=  'q':
    if isinstance(a, int):
        print(merge_sort(a))
    else:
        a = input("Give me a number list(enter'q'to quit):")
        print(merge_sort(a))