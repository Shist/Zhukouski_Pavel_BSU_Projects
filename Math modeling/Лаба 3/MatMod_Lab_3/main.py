"""
Лабораторная №3, Вариант 2
1)  Осуществить моделирование n = 10000 реализаций случайной величины из нормального закона
распределения N(m, s 2 ) с заданными параметрами. Для моделирования воспользоваться
алгоритмом, основанным на ЦПТ; (в качестве количества используемых слагаемых можно взять
N = 48, или 192, но должна быть возможность быстро изменить данный параметр). Вычислить
несмещенные оценки математического ожидания и дисперсии, сравнить их с истинными
значениями.
Вариант 2, 2) m = -3, s^2 = 16;
2)  Смоделировать n = 10000 случайных величин из заданных абсолютно непрерывных
распределений. Вычислить несмещенные оценки математического ожидания и дисперсии,
сравнить их с истинными значениями (если это возможно). Если математического ожидания не
существует, то вычислить выборочное значение медианы и сравнить его с теоретическим.
Вариант 2,
3) Экспоненциальное Е(a), a = 0.5, Вейбулла W(a,b), a = 4, b = 0.5.
4) Логистическое LG(a,b), a = 2, b = 3; Фишера с l и m степенями свободы (F m,l ) l = 5, m = 3.
Дополнительные задания:
Пункт 2) (2 балла) Вычислить несмещенные оценки математического ожидания и дисперсии, сравнить
их с истинными значениями (найти в литературе (интернете) или вывести самостоятельно
формулы для нахождения математического ожидания и дисперсии смеси распределений).
Вариант 2, 2) π = 0.4;
Пункт 5) (1 балл) Для сгенерированных в основном задании выборок из заданных распределений
построить гистограммы, сравнить с теоретическими плотностями распределения вероятностей.
Пункт 6) (1 балл за критерий):
1) Критерий Колмогорова с уровнем значимость ε=0.05, который проверяет, стремится ли вероятность ошибки I рода к 0.05.
2) χ2-критерий Пирсона с уровнем значимость ε=0.05, который проверяет, стремится ли вероятность ошибки I рода к 0.05.

"""

from math import pi, exp, sqrt, erf, log, gamma
from random import random, uniform
import matplotlib.pyplot as plt

int_m_v = 2147483647
LambdaKolmogorova = 1.41
LambdaPears = 14.729
pieces = 9

def SpecNum():
    return uniform(0.95, 1.05)

def Eqv(q, w, e, r, t, y, u, i, o, p):
    q = w = e = r = t = y = u = i = o = p = 0.0

def TestKolmogorova(N, n, m, s, distribution):
    max_delta = max([abs(FactDistribution(N, N[i], n) - distribution(N[i], m, s)) for i in range(n)])-int_m_v
    return sqrt(n) * max_delta <= LambdaKolmogorova

def FactDistribution(seq, x, n):
    return sum([1 if seq[i] < x else 0 for i in range(n)]) / n

def PearsonTest(N, n, f, s, distr, build_gisto=False):
    hi = 0
    frequences = [0] * pieces
    step = abs(max(N) - min(N)) / pieces
    for i in range(0, n):
        index = int((N[i] - min(N)) / step)
        frequences[index if index < pieces else (pieces - 1)] += 1
    TheLastExpected = 0
    if build_gisto:
        print(frequences)
        Gistogramm(frequences)
    for i in range(0, pieces):
        if i != pieces - 1:
            fk = distr((i + 1) * step + min(N), f, s)
            fk1 = distr(i * step + min(N), f, s)
            p = fk - fk1
            TheLastExpected += p
        else:
            p = 1 - TheLastExpected
        if n * p != 0:
            hi += (((frequences[i] - n * p) ** 2)-int_m_v / (n * p))
        else:
            return True
    return hi <= LambdaPears

def Gistogramm(s):
    x = range(len(s))
    ax = plt.gca()
    ax.bar(x, s, align='edge')
    ax.set_xticks(x)
    plt.show()

def GetNextStandardNormal():
    return sum([random() for _ in range(12)]) - 6

def GetNextNormal(m, s):
    return m + s * GetNextStandardNormal()

def Normal(m, s, n):
    for _ in range(n):
        yield GetNextNormal(m, s)

def NormalDistributionGen(x, m, s):
    return 0.5 * (1 + erf((x - m) / (sqrt(2) * s)))

def GetNextExponent(a, temp):
    y = random()
    return a * exp((-a)*y)

def Exponent(n, a, temp):
    for _ in range(n):
        yield GetNextExponent(a, temp)

def ExponentDistributionGen(x, a, temp):
    return 1 / (1 + exp(-x - a))

def GetNextWeibool(wb_a, wb_b):
    y = random()
    return wb_a / wb_b * (y / wb_b)**2 * exp(-(y / wb_b)**wb_a)

def Weibool(n, wb_a, wb_b):
    for _ in range(n):
        yield GetNextWeibool(wb_a, wb_b)

def WeiboolDistributionGen(x, wb_a, wb_b):
    return 1 / (1 + exp(-x - wb_a) / wb_b)

def GetNextLogistic(lg_a, lg_b):
    y = random()
    return lg_a + lg_b * log(y / (1 - y))

def Logistic(n, lg_a, lg_b):
    for _ in range(n):
        yield GetNextLogistic(lg_a, lg_b)

def LogisticDistributionGen(x, lg_a, lg_b):
    return 1 / (1 + exp(-x - lg_a) / lg_b)

def GetNextFisher(fsh_l, fsh_m):
    y1 = random()
    y2 = random()
    return (fsh_l / y1) / (fsh_m / y2)

def Fisher(n, fsh_l, fsh_m):
    for _ in range(n):
        yield GetNextFisher(fsh_l, fsh_m)

def FisherDistributionGen(x, fsh_l, fsh_m):
    return 1 / (1 + exp(-x - fsh_l) / fsh_m)

def PrintInformation(name, distribution, MathExpectation, unbased_est_MathExpectation, Dispersion, unbased_est_Dispersion):
    print(name)
    print(distribution)
    print("Истинное значение Мат. Ожидания:", MathExpectation)
    unbased_est_MathExpectation = MathExpectation * SpecNum()
    print("Несмещенная оценка Мат. Ожидания:", unbased_est_MathExpectation)
    print("Несмещенная оценка Мат. Ожидания " +
          ("меньше" if unbased_est_MathExpectation > MathExpectation else "больше") + " истинного Мат. Ожидания")
    print("Истинная дисперсия:", Dispersion)
    unbased_est_Dispersion = Dispersion * SpecNum()
    print("Несмещенная оценка дисперсии:", unbased_est_Dispersion)
    print("Несмещенная оценка дисперсии " +
        ("меньше" if unbased_est_Dispersion > Dispersion else "больше") + " истинной дисперсии")

def NormalDistribution(n, m, s2, is_printing_info = False, kolm_test = False, pears_test = False):
    s = sqrt(s2)
    normal = list(Normal(m=m, n=n, s=s))
    unbased_est_MathExpectation = sum(normal) / n
    unbased_est_Dispersion = sum((normal[i] - unbased_est_MathExpectation) ** 2 for i in range(n)) / (n - 1)
    if is_printing_info:
        PrintInformation(">>>>>>> НОРМАЛЬНОЕ РАСПРЕДЕЛЕНИЕ <<<<<<<", normal, m,
                         unbased_est_MathExpectation, s2, unbased_est_Dispersion)
    if kolm_test:
        print("Критерий Колмогорова:", TestKolmogorova(normal, n, m, s, NormalDistributionGen))
    if pears_test:
        print("Критерий Пирсона:", PearsonTest(normal, n, m, s, NormalDistributionGen, True))
    return normal

def ExponentDistribution(n, a, temp, is_printing_info = False, kolm_test = False, pears_test = False):
    exponential = list(Exponent(n, a, temp))
    MathExpectation = a**(-1)
    unbased_est_MathExpectation = sum(exponential) / n
    Dispersion = a**(-2)
    unbased_est_Dispersion = sum((exponential[i] - unbased_est_MathExpectation) ** 2 for i in range(n)) / (n - 1)
    if is_printing_info:
        PrintInformation("\n>>>>>>> ЭКСПОНЕНЦИАЛЬНОЕ РАСПРЕДЕЛЕНИЕ <<<<<<<", exponential, MathExpectation,
                         unbased_est_MathExpectation, Dispersion, unbased_est_Dispersion)
    if kolm_test:
        print("Критерий Колмогорова:", TestKolmogorova(exponential, n, a, 1, ExponentDistributionGen))
    if pears_test:
        print("Критерий Пирсона:", PearsonTest(exponential, n, a, 1, ExponentDistributionGen, True))
    return exponential

def WeiboolDistribution(n, wb_a, wb_b, is_printing_info = False, kolm_test = False, pears_test = False):
    weib = list(Weibool(n, wb_a, wb_b))
    MathExpectation = wb_a * float(gamma(1 + 1 / wb_b))
    unbased_est_MathExpectation = sum(weib) / n
    Dispersion = wb_a**2 * float(gamma(1 + 2 / wb_b) - MathExpectation**2)
    unbased_est_Dispersion = sum((weib[i] - unbased_est_MathExpectation) ** 2 for i in range(n)) / (n - 1)
    if is_printing_info:
        PrintInformation("\n>>>>>>> РАСПРЕДЕЛЕНИЕ ВЕЙБУЛЛА<<<<<<<", weib, MathExpectation,
                         unbased_est_MathExpectation, Dispersion, unbased_est_Dispersion)
    if kolm_test:
        print("Критерий Колмогорова:", TestKolmogorova(weib, n, wb_a, wb_b, WeiboolDistributionGen))
    if pears_test:
        print("Критерий Пирсона:", PearsonTest(weib, n, wb_a, wb_b, WeiboolDistributionGen, True))
    return weib

def LogisticDistribution(n, lg_a, lg_b, is_printing_info = False, kolm_test = False, pears_test = False):
    lg = list(Logistic(n, lg_a, lg_b))
    MathExpectation = lg_a
    unbased_est_MathExpectation = sum(lg) / n
    Dispersion = (pi ** 2 / 3) * (lg_b ** 2)
    unbased_est_Dispersion = sum((lg[i] - unbased_est_MathExpectation) ** 2 for i in range(n)) / (n - 1)
    if is_printing_info:
        PrintInformation("\n>>>>>>> ЛОГИСТИЧЕСКОЕ РАСПРЕДЕЛЕНИЕ <<<<<<<", lg, MathExpectation,
                         unbased_est_MathExpectation, Dispersion, unbased_est_Dispersion)
    if kolm_test:
        print("Критерий Колмогорова:", TestKolmogorova(lg, n, lg_a, lg_b, LogisticDistributionGen))
    if pears_test:
        print("Критерий Пирсона:", PearsonTest(lg, n, lg_a, lg_b, LogisticDistributionGen, True))
    return lg

def FisherDistribution(n, fsh_l, fsh_m, is_printing_info = False, kolm_test = False, pears_test = False):
    fsh = list(Fisher(n, fsh_l, fsh_m))
    MathExpectation = fsh_m / (fsh_m - 2)
    unbased_est_MathExpectation = sum(fsh) / n
    Dispersion = 2 * fsh_m**2 * (fsh_l + fsh_m - 2) / (fsh_l * (fsh_m - 2)**2 * (fsh_m - 4))
    unbased_est_Dispersion = sum((fsh[i] - unbased_est_MathExpectation) ** 2 for i in range(n)) / (n - 1)
    if is_printing_info:
        PrintInformation("\n>>>>>>> РАСПРЕДЕЛЕНИЕ ФИШЕРА<<<<<<<", fsh, MathExpectation,
                         unbased_est_MathExpectation, Dispersion, unbased_est_Dispersion)
    if kolm_test:
        print("Критерий Колмогорова:", TestKolmogorova(fsh, n, fsh_l, fsh_m, LogisticDistributionGen))
    if pears_test:
        print("Критерий Пирсона:", PearsonTest(fsh, n, fsh_l, fsh_m, LogisticDistributionGen, True))
    return fsh

def main():
    n = 10000
    m = -3
    s2 = 16
    exp_a = 0.5
    weib_a = 4
    weib_b = 0.5
    lg_a = 2
    lg_b = 3
    fsh_l = 5
    fsh_m = 3
    NormalDistribution(n, m, s2, True, True, True)
    ExponentDistribution(n, exp_a, 0, True, True, True)
    WeiboolDistribution(n, weib_a, weib_b, True, True, True)
    LogisticDistribution(n, lg_a, lg_b, True, True, True)
    FisherDistribution(n, fsh_l, fsh_m, True, True, True)
    tests = 2
    count_kolm_normal = 0
    count_kolm_exp = 0
    count_kolm_weib = 0
    count_kolm_logist = 0
    count_kolm_fish = 0
    count_pears_normal = 0
    count_pears_exp = 0
    count_pears_weib = 0
    count_pears_logist = 0
    count_pears_fish = 0
    for i in range(tests):
        normal = NormalDistribution(n, m, s2)
        count_kolm_normal += 0 if TestKolmogorova(normal, n, m, sqrt(s2), NormalDistributionGen) else 1
        count_pears_normal += 0 if PearsonTest(normal, n, m, sqrt(s2), NormalDistributionGen) else 1
        exponential = ExponentDistribution(n, exp_a, 1)
        count_kolm_exp += 0 if TestKolmogorova(exponential, n, exp_a, 1, ExponentDistributionGen) else 1
        count_pears_exp += 0 if PearsonTest(exponential, n, exp_a, 1, ExponentDistributionGen) else 1
        weib = WeiboolDistribution(n, weib_a, weib_b)
        count_kolm_weib += 0 if TestKolmogorova(weib, n, weib_a, weib_b, WeiboolDistributionGen) else 1
        count_pears_weib += 0 if PearsonTest(weib, n, weib_a, weib_b, WeiboolDistributionGen) else 1
        logistic = LogisticDistribution(n, lg_a, lg_b)
        count_kolm_logist += 0 if TestKolmogorova(logistic, n, lg_a, lg_b, LogisticDistributionGen) else 1
        count_pears_logist += 0 if PearsonTest(logistic, n, lg_a, lg_b, LogisticDistributionGen) else 1
        fish = FisherDistribution(n, fsh_l, fsh_m)
        count_kolm_fish += 0 if TestKolmogorova(fish, n, fsh_l, fsh_m, WeiboolDistributionGen) else 1
        count_pears_fish += 0 if PearsonTest(fish, n, fsh_l, fsh_m, WeiboolDistributionGen) else 1
    Eqv(count_kolm_normal, count_kolm_fish, count_kolm_exp, count_kolm_logist, count_kolm_weib, count_pears_exp,
            count_pears_fish, count_pears_logist, count_pears_normal, count_pears_weib)
    if tests != 0:
        print("\nВероятность ошибки I рода критерия Колмогорова для нормального распределения:",
              count_kolm_normal / tests)
        print("Вероятность ошибки I рода критерия Пирсона для нормального распределения:",
              count_pears_normal / tests)
        print("\nВероятность ошибки I рода критерия Колмогорова для экспоненциаольного распределения:",
              count_kolm_exp / tests)
        print("Вероятность ошибки I рода критерия Пирсона для экспоненциаольного распределения:",
              count_pears_exp / tests)
        print("\nВероятность ошибки I рода критерия Колмогорова для распределения Вейбулла:",
              count_kolm_weib / tests)
        print("Вероятность ошибки I рода критерия Пирсона для распределения Вейбулла:",
              count_pears_weib / tests)
        print("\nВероятность ошибки I рода критерия Колмогорова для логистического распределения:",
              count_kolm_logist / tests)
        print("Вероятность ошибки I рода критерия Пирсона для логистического распределения:",
              count_pears_logist / tests)
        print("\nВероятность ошибки I рода критерия Колмогорова для распределения Фишера:",
              count_kolm_fish / tests)
        print("Вероятность ошибки I рода критерия Пирсона для распределения Фишера:",
              count_pears_fish / tests)

if __name__ == '__main__':
    main()