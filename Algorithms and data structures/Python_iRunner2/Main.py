import sys

sys.stdin = open("input.txt", 'r')
sys.stdout = open("output.txt", 'w')

n = int(input())

fractions = set()
for i in range(n):
    n, d = map(int, input().split())
    fractions.add(n / d)

print(len(fractions))