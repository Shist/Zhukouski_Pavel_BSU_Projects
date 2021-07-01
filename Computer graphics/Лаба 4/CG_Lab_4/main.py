import os

from matplotlib import pyplot as plt
import time


f = plt.figure(1, figsize = (8,8))
ax = f.gca()
ax.set_xlim([0, 50])
ax.set_ylim([0, 50])
f.show()

x1 = 1.0
y1 = 1.0
x2 = 20.0
y2 = 40.0

k = (y2 - y1)/(x2 - x1)
b = y2 - k * x2
dx = abs(x2 - x1)/(max(abs(x2 - x1), abs(y2 - y1) * 2))
if (x2 > x1):
    dx = dx
else:
    dx = -dx

x = x1
y = k * x + b
begin = time.time()
while x < x2:
    ax.plot(x, y, 'ko')
    f.canvas.draw()
    y = k * x + b
    x = x + dx

end = time.time()
print('Time spent: {}'.format(end - begin))




f = plt.figure(2, figsize = (8,8))
ax = f.gca()
ax.set_xlim([0, 50])
ax.set_ylim([0, 50])
f.show()

x1 = 0.0
y1 = 0.0
x2 = 20.0
y2 = 40.0

dx = x2 - x1
dy = y2 - y1

if dx > dy:
    steps = dx
else:
    steps = dy

x_increment = dx / steps
y_increment = dy / steps

begin = time.time()
for i in range(int(steps)):
    ax.plot(x1, y1, 'ko')
    f.canvas.draw()
    x1 = x1 + x_increment
    y1 = y1 + y_increment
end = time.time()
print('Time spent: {}'.format(end - begin))




f = plt.figure(3, figsize = (8,8))
ax = f.gca()
ax.set_xlim([0, 50])
ax.set_ylim([0, 50])
f.show()

x1 = 0.0
y1 = 0.0
x2 = 20.0
y2 = 40.0

dx = x2 - x1
dy = y2 - y1
slope = abs(dy / dx)

error = 0.0
y = y1
x = x1

begin = time.time()
while x < x2:
    ax.plot(x, y, 'ko')
    f.canvas.draw()
    x = x + 1
    error = error + slope
    if error >= 0.5:
        y = y + 1
        error -= 1.0
end = time.time()
print('Time spent: {}'.format(end - begin))




f = plt.figure(4, figsize = (8,8))
ax = f.gca()
ax.set_xlim([-50, 50])
ax.set_ylim([-50, 50])
f.show()

r = 20
x = 0
y = r
d = 3 - 2 * r

def plot(_x, _y, _radius):
    ax.plot(_x, _y, 'ko')
    ax.plot(-_x, _y, 'ko')
    ax.plot(_x, -_y, 'ko')
    ax.plot(-_x, -_y, 'ko')

    ax.plot(_y, _x, 'ko')
    ax.plot(_y, -_x, 'ko')
    ax.plot(-_y, _x, 'ko')
    ax.plot(-_y, -_x, 'ko')
    f.canvas.draw()

begin = time.time()
while y >= x:
    plot(x, y, r)
    x = x + 1
    if d > 0:
        y = y - 1
        d = d + 4 * (x - y) + 10
    else:
        d = d + 4 * x + 6
end = time.time()
print('Time spent: {}'.format(end - begin))

os.system("pause")


"""
Реализованы следующие алгоритмы растеризации отрезков и кривых:
* пошаговый алгоритм
* алгоритм ЦДА
* алгоритм Брезенхема
* алгоритм Брезенхема (окружность)

Все (кроме алгоритма для рисования окружности) рисуют линию на координатной сетке масштаба 50х50.
В сравнительном временном анализе видно, что алгоритм Брезенхема работает быстрее всех.
"""
