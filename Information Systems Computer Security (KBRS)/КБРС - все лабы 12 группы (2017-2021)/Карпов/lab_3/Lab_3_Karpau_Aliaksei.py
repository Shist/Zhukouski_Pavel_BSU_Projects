import hashlib
import random

curve = { "M": 211, "a": 0,"b": -4, "g": (2, 2),"n": 0}
my_points = []
def define_coefficients(M):
    curve["M"] = M
    a, b = 0, 0
    while b < M:
        while a < M:
            if (4 * pow(a, 3) + 27 * pow(b, 2)) % M != 0:
                curve["a"] = a
                curve["b"] = b
                print("Coeffs:", a, b)
                return
            else:
                a += 1
        b += 1
def get_all_elements():
    x = 0
    while x < curve["M"]:
        y = 0
        while y < curve["M"]:
            if (is_on_curve((x, y))):
                my_points.append((x, y))
            y += 1
        x += 1

    curve["n"] = len(my_points) + 1
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
def inverse_mod(k, p):
    if k == 0:
        raise ZeroDivisionError('Деление на 0')

    if k < 0:
        return p - inverse_mod(-k, p)

    gcd, x, _ = extended_euclidean_algorithm(k, p)

    assert gcd == 1
    assert (k * x) % p == 1

    return x % p
def is_on_curve(point):
    if point is None:
        return True

    x, y = point
    return (y * y - x * x * x - curve["a"] * x - curve["b"]) % curve["M"] == 0
def point_neg(point):
    assert is_on_curve(point)

    if point is None:
        return None

    x, y = point
    result = (x, -y % curve["M"])

    assert is_on_curve(result)

    return result
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
        m = (3 * x1 * x1 + curve["a"]) * inverse_mod(2 * y1, curve["M"])
    else:
        m = (y1 - y2) * inverse_mod(x1 - x2, curve["M"])
    x3 = m * m - x1 - x2
    y3 = y1 + m * (x3 - x1)
    result = (x3 % curve["M"],
              -y3 % curve["M"])

    assert is_on_curve(result)

    return result
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

def make_keypair():
    private_key = random.randrange(1, curve["n"])
    public_key = scalar_mult(private_key, curve["g"])

    return private_key, public_key
def hash_message(message):
    message_hash = hashlib.sha512(message).digest()
    e = int.from_bytes(message_hash, 'big')
    z = e >> (e.bit_length() - curve["n"].bit_length())

    assert z.bit_length() <= curve["n"].bit_length()

    return z
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
def verify_signature(public_key, message, signature):
    z = hash_message(message)
    r, s = signature

    w = inverse_mod(s, curve["n"])
    u1 = (z * w) % curve["n"]
    u2 = (r * w) % curve["n"]

    x, _ = point_add(scalar_mult(u1, curve["g"]),
                     scalar_mult(u2, public_key))

    if (r % curve["n"]) == (x % curve["n"]):
        return 'SUCCESS'
    else:
        return 'FAIL'
get_all_elements()
print(curve)
print()
first_private_key, first_public_key = make_keypair()
print("First Key")
print("Private key:", first_private_key)
print("Public key: ({0}, {1})".format(*first_public_key))
print()
second_private_key, second_public_key = make_keypair()
print("==============\nSecond key")
print("Private key:", second_private_key)
print("Public key: ({0}, {1})".format(*second_public_key))
s1 = scalar_mult(first_private_key, second_public_key)
s2 = scalar_mult(second_private_key, first_public_key)
assert s1 == s2
print()
print('==============\nShared secret: ({0}, {1})'.format(*s1))
print()
private, public = make_keypair()
print("Private key:", private)
print("Public key: ({0}, {1})".format(*public))
msg = b'Aliaksei Karpau'
signature = sign_message(private, msg)
print()
print('==============\nMessage:', msg)
print('Sign: ({0}, {1})'.format(*signature))
print('Result:', verify_signature(public, msg, signature))
msg = b'Stas Bychkou'
print()
print('Message:', msg)
print('Result:', verify_signature(public, msg, signature))
private, public = make_keypair()
msg = b'Sample '
print()
print('Message:', msg)
print("Public: (0x{:x}, 0x{:x})".format(*public))
print('Result:', verify_signature(public, msg, signature))