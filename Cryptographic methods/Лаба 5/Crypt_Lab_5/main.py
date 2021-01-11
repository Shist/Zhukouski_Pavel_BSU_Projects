from Cryptodome.Util.number import inverse

def CheckSignature(p, g, m, y, a, b):
    if (pow(y, a, p) * pow(a, b, p)) % p == pow(g, m, p):
        print("Valid Signature")
    else:
        print("Invalid Signature")


def GenerateSignature(p, q, g, m, x, k):
    a = pow(g, k, p)
    b = (m - x * a) * inverse(k, q) % q
    print("Digital View:")
    print("a/r: ", hex(a))
    print("b/s: ", hex(b))


print("Choose Task (Check signature or generate signature):\n1) Check Signature\n2) Generate Signature")
choice = int(input())
if choice == 1:
    p = int(input("Enter p: "), 16)
    q = int(input("Enter q: "), 16)
    g = int(input("Enter g: "), 16)
    m = int(input("Enter message: "), 16)
    y = int(input("Enter public key: "), 16)
    a = int(input("Enter a/r: "), 16)
    b = int(input("Enter b/s: "), 16)
    CheckSignature(p, g, m, y, a, b)
elif choice == 2:
    p = int(input("Enter p: "), 16)
    q = int(input("Enter q: "), 16)
    g = int(input("Enter g: "), 16)
    m = int(input("Enter message: "), 16)
    x = int(input("Enter secret key: "), 16)
    k = int(input("Enter random number: "), 16)
    GenerateSignature(p, q, g, m, x, k)