from Crypto.Util.number import inverse, getPrime
from copy import deepcopy
from math import gcd


def BasicCalculation(Data, PrimeNumbersSize):
    P = getPrime(PrimeNumbersSize)
    Q = getPrime(PrimeNumbersSize)

    N = P * Q

    Fi = (P - 1) * (Q - 1)

    E = 0
    for i in range(2, Fi):
        if gcd(i, Fi) == 1:
            E = i
            break

    D = inverse(E, Fi)

    return [EncryptionAndDecryption(Data, N, E, D), [N, E], [N, D]]


def EncryptionAndDecryption(Data, N, E, D):
    TextInNumbers = []
    EncryptedText = []
    DecryptedTextNum = []
    DecryptedText = []
    Total = []

    for letter in Data:
        TextInNumbers.append(ord(letter))
    Total.append(deepcopy(TextInNumbers))

    for i in range(1, len(TextInNumbers)):
        TextInNumbers[i] = pow((TextInNumbers[i] + TextInNumbers[i - 1]), 1, N)
    Total.append(deepcopy(TextInNumbers))

    for i in TextInNumbers:
        EncryptedText.append(pow(i, E, N))
    Total.append(deepcopy(EncryptedText))

    for i in EncryptedText:
        DecryptedTextNum.append(pow(i, D, N))
    Total.append(deepcopy(DecryptedTextNum))

    for i in reversed(range(1, len(DecryptedTextNum))):
        DecryptedTextNum[i] = pow((DecryptedTextNum[i] - DecryptedTextNum[i - 1]), 1, N)
    Total.append(deepcopy(DecryptedTextNum))

    for letter in DecryptedTextNum:
        DecryptedText.append(chr(letter))
    Total.append(''.join(deepcopy(DecryptedText)))

    return Total
