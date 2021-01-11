#  Жуковский Павел, 2 курс, 13 группа

#  Вариант 2
#  2) Геометрическое – G(p), p = 0.7; Пуассона – П(λ), λ = 2;
#  Вариант 15
#  Бернулли – Bi(1,p), p = 0.3333333; Биномиальное – Bi(m,p), m = 6, p = 0.3333333.

#  + 4-ое доп. задание (2 балла)
#  Реализовать критерий хи-квадрат Пирсона проверки статистической гипотезы о
#  принадлежности смоделированной последовательности к заданному распределению.

from random import random, uniform
from math import log, exp, factorial

n = 1000
p1 = 0.7
p2 = 0.333
l = 2  # Лямбда
m = 6
p3 = 0.333

def bern_distrib(p):
    return 1 if random() < p else 0

def bern_distrib_seq(p, n):
    return [bern_distrib(p) for _ in range(n)]

def geom_distrib(p, n):
    return [int(log(random()) / log(1 - p)) for _ in range(n)]

def geom_distrib_from_bern(p, n):
    result_seq = [0] * n

    counter = 0
    for i in range(n):
        while bern_distrib(p) != 1:
            counter += 1

        result_seq[i] = counter
        counter = 0

    return result_seq

def count_expected_value(sample):
    return sum(sample) / len(sample)

def count_variance(sample):
    expected_value = count_expected_value(sample)

    sample_sum = 0
    for x in sample:
        sample_sum += (x - expected_value) ** 2

    return sample_sum / (len(sample) - 1)

def bern_probability_func(x, p):
    return (p ** x) * ((1 - p) ** (1 - x))

def bern_expected_value(p):
    return p

def bern_variance(p):
    return p * (1 - p)

def geom_probability_func(x, p):
    return p * ((1 - p) ** x)

def geom_expected_value(p):
    return (1 - p) / p

def geom_variance(p):
    return (1 - p) / (p ** 2)

def puas_seq(l, n):
    seq = [0] * n
    for i in range(n):
        p, x, r = exp(-l), 0, uniform(0, 1)
        r -= p

        while r >= 0:
            x += 1
            p *= l/x
            r -= p

        seq[i] = x
    return seq

def puas_probability_func(k, l):
    return (l ** k * exp(-l)) / factorial(k)

def puas_expected_value(l):
    return l

def puas_variance(l):
    return l

def binom_seq(n, m0, p0):
    seq = [0] * n
    for i in range(n):
        m, p = m0, p0
        q = 1 - p
        c, r = p / q, uniform(0, 1)
        p = pow(q, m)
        x = 0
        r -= p
        while r >= 0:
            x += 1
            p *= c * (m + 1 - x) / x
            r -= p
        seq[i] = x
    return seq

def binom_expected_value(m, p):
    return m * p

def binom_variance(m, p):
    return m * p * (1 - p)

def pirson_xi2(sample, p, probability_func):
    k = max(sample) + 1
    counts = [0] * k

    xi2 = 0

    for x in sample:
        counts[x] += 1

    for i in range(k):
        xi2 += ((counts[i] - len(sample) * probability_func(i, p)) ** 2) / (
                    len(sample) * probability_func(i, p))

    return xi2

def binomCoefficient(n, k):
    if k < 0 or k > n:
        return 0
    if k == 0 or k == n:
        return 1
    k = min(k, n - k)
    c = 1
    for i in range(k):
        c = c * (n - i) / (i + 1)
    return c

def binomXi2(seq,n,m,p):
    freq = [0]*(m+1)
    prob = [0]*(m+1)
    for i in seq:
        freq[i]+=1
    for i in range(m+1):
        prob[i] = binomCoefficient(m,i)*pow(p,i)*pow(1-p,m-i)
    s = 0
    for i in range(m+1):
        s += pow(freq[i]- n * prob[i],2)/(n*prob[i])
    return s

def print_results(seq, p, expected_value_func, variance_func, probability_func):
    print("\t Несмещенная оценка мат. ожидания: " + str(count_expected_value(seq)))
    print("\t Истинное мат. ожидание: " + str(expected_value_func(p)))
    print("\t Несмещенная оценка дисперсии: " + str(count_variance(seq)))
    print("\t Истинная дисперсия: " + str(variance_func(p)))
    print("\t xi2: " + str(pirson_xi2(seq, p, probability_func)))
    print()

def print_results_binom(seq, p, m, expected_value_func, variance_func):
    print("\t Несмещенная оценка мат. ожидания: " + str(count_expected_value(seq)))
    print("\t Истинное мат. ожидание: " + str(expected_value_func(m, p)))
    print("\t Несмещенная оценка дисперсии: " + str(count_variance(seq)))
    print("\t Истинная дисперсия: " + str(variance_func(m, p)))
    print("\t xi2: " + str(binomXi2(seq, n, m, p)))
    print()

if __name__ == '__main__':
    bern_seq = bern_distrib_seq(p1, n)
    geom_seq = geom_distrib(p2, n)
    puas_seq = puas_seq(l, n)
    binom_seq = binom_seq(n, m, p3)

    print("Bi(1, {0}):".format(p2))
    print_results(bern_seq, p1, bern_expected_value, bern_variance, bern_probability_func)

    print("G({0}):".format(p1))
    print_results(geom_seq, p2, geom_expected_value, geom_variance, geom_probability_func)

    print("P({0})".format(l))
    print_results(puas_seq, l, puas_expected_value, puas_variance, puas_probability_func)

    print("Bi({0}, {1})".format(m, p3))
    print_results_binom(binom_seq, p3, m, binom_expected_value, binom_variance)
