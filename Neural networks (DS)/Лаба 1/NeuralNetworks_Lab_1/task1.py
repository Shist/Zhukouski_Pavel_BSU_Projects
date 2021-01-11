import math


# DATA
I1_1 = 1
I1_0 = 0
I2_1 = 1
I2_0 = 0

COUNT = 0  # Счётчик тренировочных сетов
ErrorSum = 0

w1 = 0.95
w2 = 0.48
w3 = -0.12
w4 = 0.23
w5 = 1.5
w6 = -1.3


print("Default data:")

print("w1 = ", w1)
print("w2 = ", w2)
print("w3 = ", w3)
print("w4 = ", w4)
print("w5 = ", w5)
print("w6 = ", w6, "\n")


# Sigmoid Function
def Sigmoid(x):
    return 1 / (1 + math.exp(-x))


def NetworkFunction(I1, I2):

    global COUNT
    COUNT += 1

    print("Training set №", COUNT)
    print("Input data:")

    print("I1 = ", I1)
    print("I2 = ", I2)

    H1_input = I1 * w1 + I2 * w3
    H1_output = Sigmoid(H1_input)

    print("H1_input = ", H1_input)
    print("H1_output = ", H1_output)

    H2_input = I1 * w2 + I2 * w4
    H2_output = Sigmoid(H2_input)

    print("H2_input = ", H2_input)
    print("H2_output = ", H2_output)

    O1_input = H1_output * w5 + H2_output * w6
    O1_output = Sigmoid(O1_input)

    print("O1_input = ", O1_input)
    print("O1_output = ", O1_output)

    O1_ideal = I1 ^ I2  # ^ - выполняет операцию xor (исключающее или)

    print("O1_ideal = ", O1_ideal)

    Error = ((O1_ideal - O1_output) ** 2) / COUNT  # **2 - возведение во 2-ую степень

    global ErrorSum
    ErrorSum += Error

    print("Error = ", Error)

    print("Result = ", O1_output, ", error = ", 100 * Error, "%.")

NetworkFunction(I1_1, I2_0)
print()
NetworkFunction(I1_0, I2_1)
print()
NetworkFunction(I1_1, I2_1)
print()
NetworkFunction(I1_0, I2_0)
print()
print("Summary Error for 4 training sets: ", ErrorSum)
print("Average Error: ", ErrorSum / 4)