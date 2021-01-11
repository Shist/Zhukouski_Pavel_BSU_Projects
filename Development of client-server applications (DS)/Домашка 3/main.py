from decimal import Decimal

a = Decimal("123456789.1")
b = Decimal("123456787.1")
c = Decimal("87654321098765432.1")
d = Decimal("87654321098765431.1")
print(a, "-", b, "= ", a - b)
print(c, "-", d, "= ", c - d)