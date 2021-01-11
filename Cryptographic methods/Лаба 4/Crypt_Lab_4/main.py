from impl import BasicCalculation

if __name__ == "__main__":
    Input = open("OpenedText", "r")
    Data = Input.read()

    PrimeNumbersSize = input("Enter the size of the prime numbers you want to get:\n")
    result = BasicCalculation(Data, int(PrimeNumbersSize))

    print("Calculations have done. Here are the results...")
    print("Value of public key: ", result[1])
    print("Value of private key: ", result[2])
    print("This text on ASCII language: ", result[0][0])
    print("Edited version of this text: ", result[0][1])
    print("The text after encryption: ", result[0][2])
    print("The text after decryption (must be the same to edited version): ", result[0][3])
    print("This text on ASCII language again (must be the same to original variant): ", result[0][4])
    print("Text itself:\n", result[0][5])
