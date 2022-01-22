import hashlib
import random

# Стабильно работающий пример из условия
curve = {
    # Модуль
    "M": 211,

    # Коэффициенты 
    "a": 0,
    "b": -4,

    # Базовая точка
    "g": (2, 2),

    # Порядок группы (его высчитаем ниже)
    "n": 0
}

my_points = []


# Базовые операции

# Ищу первые подходящие a, b
def define_coefficients(M):
    curve["M"] = M
    a, b = 0, 0
    while b < M:
        while a < M:
            if (4*pow(a, 3) + 27*pow(b,2)) % M != 0:
                curve["a"] = a
                curve["b"] = b
                print("Coeffs:", a, b)
                return
            else:
                a += 1
        b += 1


# Кол-во точек нахожу просто перебором, очевидно, что это крайне
# неэффективно при больших M. Правильно пользоваться в таких случаях
# алгоритмом Шуфа, но он был сложен для реализации и тут не столь важен 
# в данный момент.
def get_all_elements():
    x = 0
    while x < curve["M"]:
        y = 0
        while y < curve["M"]:
            if(is_on_curve((x, y))):
                my_points.append((x, y))
            y += 1
        x += 1
    
    curve["n"] = len(my_points) + 1

    # Не понял, как именно искать нужную точку G,
    # если брать случайные, то все ж находится подходящая,
    # но точного алгоритма я не совсем понял
    # curve["g"] = my_points[3]


# Модульная арифметика

# Расширенный алгоритм Евклида
def extended_euclidean_algorithm(a, b):
    s, old_s = 0, 1
    t, old_t = 1, 0
    r, old_r = b, a

    while r != 0:
        quotient = old_r // r
        old_r, r = r, old_r - quotient * r
        old_s, s = s, old_s - quotient * s
        old_t, t = t, old_t - quotient * t

    return old_r, old_s, old_t


# Деление по модулю p
# Найдем обратную величину числа и умножим
def inverse_mod(k, p):
    if k == 0:
        raise ZeroDivisionError('Деление на 0')

    if k < 0:
        return p - inverse_mod(-k, p)

    gcd, x, _ = extended_euclidean_algorithm(k, p)

    assert gcd == 1
    assert (k * x) % p == 1

    return x % p


# Проверка нахождения точки на кривой
def is_on_curve(point):
    if point is None:
        return True

    x, y = point
    return (y * y - x * x * x - curve["a"] * x - curve["b"]) % curve["M"] == 0


# Возвращаем обратную точку
def point_neg(point):
    assert is_on_curve(point)

    if point is None:
        return None

    x, y = point
    result = (x, -y % curve["M"])

    assert is_on_curve(result)

    return result


# Сумма точек
def point_add(point1, point2):
    assert is_on_curve(point1)
    assert is_on_curve(point2)

    if point1 is None:
        return point2
    if point2 is None:
        return point1

    x1, y1 = point1
    x2, y2 = point2

    if x1 == x2 and y1 != y2:
        return None

    if x1 == x2:
        # Точки равны
        m = (3 * x1 * x1 + curve["a"]) * inverse_mod(2 * y1, curve["M"])
    else:
        # Точки не равны
        m = (y1 - y2) * inverse_mod(x1 - x2, curve["M"])

    x3 = m * m - x1 - x2
    y3 = y1 + m * (x3 - x1)
    result = (x3 % curve["M"],
              -y3 % curve["M"])

    assert is_on_curve(result)

    return result


# Умножение точки на скаляр
def scalar_mult(k, point):
    assert is_on_curve(point)

    if k % curve["n"] == 0 or point is None:
        return None

    if k < 0:
        return scalar_mult(-k, point_neg(point))

    result = None
    addend = point

    while k:
        if k & 1:
            result = point_add(result, addend)

        addend = point_add(addend, addend)

        k >>= 1

    assert is_on_curve(result)

    return result


# Генерируем пару ключей
def make_keypair():
    private_key = random.randrange(1, curve["n"])
    public_key = scalar_mult(private_key, curve["g"])

    return private_key, public_key


# Вычисляем хеш сообщения (используем sha512)
def hash_message(message):
    message_hash = hashlib.sha512(message).digest()
    e = int.from_bytes(message_hash, 'big')

    # Обрезаем лишнюю часть
    z = e >> (e.bit_length() - curve["n"].bit_length())

    assert z.bit_length() <= curve["n"].bit_length()

    return z


# Подписываем сообщение 
def sign_message(private_key, message):
    z = hash_message(message)

    r = 0
    s = 0

    while not r or not s:
        k = random.randrange(1, curve["n"])
        x, _ = scalar_mult(k, curve["g"])

        r = x % curve["n"]
        s = ((z + r * private_key) * inverse_mod(k, curve["n"])) % curve["n"]

    return (r, s)


# Верифицируем сигнатурку
def verify_signature(public_key, message, signature):
    z = hash_message(message)
    r, s = signature

    w = inverse_mod(s, curve["n"])
    u1 = (z * w) % curve["n"]
    u2 = (r * w) % curve["n"]

    x, _ = point_add(scalar_mult(u1, curve["g"]),
                     scalar_mult(u2, public_key))

    if (r % curve["n"]) == (x % curve["n"]):
        return 'Верификация успешна!'
    else:
        return 'Ошибка верификации!'



# Задания 1, 2
# Поскольку точного способа нахождения G я не установил,
# Воспользуемся значениями из примера, на который все стабильно работает

# Высчитываем подходящие коэффициенты
# M = 211
# define_coefficients(M)

# Получаем элементы и их кол-во
get_all_elements()

print(curve)
print()

# Задача 3

# Генерация ключей первой стороной
first_private_key, first_public_key = make_keypair()
print("Первая сторона")
print("Приватный ключ:", first_private_key)
print("Публичный ключ: ({0}, {1})".format(*first_public_key))
print()

# Генерация ключей второй стороной
second_private_key, second_public_key = make_keypair()
print("Вторая сторона")
print("Приватный ключ:", second_private_key)
print("Публичный ключ: ({0}, {1})".format(*second_public_key))

# Обмен ключами и высчитывание общего секретного ключа
s1 = scalar_mult(first_private_key, second_public_key)
s2 = scalar_mult(second_private_key, first_public_key)
assert s1 == s2

print()
print('Shared secret: ({0}, {1})'.format(*s1))
print()


# Задача 4

# Генерируем ключи
private, public = make_keypair()
print("Приватный ключ:", private)
print("Публичный ключ: ({0}, {1})".format(*public))

# Сообщение и подпись
msg = b'I want some tee!'
signature = sign_message(private, msg)

print()
print('Сообщение:', msg)
print('Подпиcь: ({0}, {1})'.format(*signature))
print('Верификация:', verify_signature(public, msg, signature))


# Проверим другие сообщения
msg = b'I want pizza!'
print()
print('Сообщение:', msg)
print('Верификация:', verify_signature(public, msg, signature))


# И другую пару ключей
private, public = make_keypair()

msg = b'I want some tee!'
print()
print('Сообщение:', msg)
print("Публичный ключ: (0x{:x}, 0x{:x})".format(*public))
print('Верификация:', verify_signature(public, msg, signature))

input()