import sys


class MatrixChain:
    def __init__(self):
        self.data = []
        self.answ = ''
        self.setter()
        self.multiplyOrder(self.data)
        self.saver()

    def setter(self):
        with open('input.txt', 'r') as file:
            data = file.read().split('\n')
            for i in range(1, len(data)):
                data[i] = data[i].split(' ')
            for i in range(1, int(data[0]) + 1):
                self.data.append(int(data[i][0]))
                if i == int(data[0]):
                    self.data.append(int(data[i][1]))

    def multiplyOrder(self, p):
        n = len(p) - 1
        dp = [[0 for col in range(n + 1)] for row in range(n + 1)]

        for l in range(2, n + 1):
            for i in range(1, n - l + 2):
                j = i + l - 1
                dp[i][j] = sys.maxsize
                for k in range(i, j):
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j]);
        self.answ = dp[1][n]

    def saver(self):
        with open('output.txt', 'w', encoding='utf-8') as fi:
            fi.write(str(self.answ))


if __name__ == '__main__':
    lol = MatrixChain()
