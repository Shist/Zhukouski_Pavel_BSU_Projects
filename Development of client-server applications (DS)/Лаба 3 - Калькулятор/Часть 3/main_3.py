from decimal import Decimal
from tkinter import *
from tkinter import messagebox, ttk

Window_Calculator = Tk()
Window_Calculator.withdraw()

FirstNum_Label = StringVar(Window_Calculator, value="0.0")
SecondNum_Label = StringVar(Window_Calculator, value="0.0")
ThirdNum_Label = StringVar(Window_Calculator, value="0.0")
FourthNum_Label = StringVar(Window_Calculator, value="0.0")

FirstOperation_Info = StringVar()
SecondOperation_Info = StringVar()
ThirdOperation_Info = StringVar()

RoundType_Info = StringVar()

Calculator_Output = Text(Window_Calculator, height=4.0, width=55, bd=5, font=("Times New Roman", 24), wrap=NONE)
Calculator_Output.place(relx=0.68, rely=0.86, anchor="c")
hor_scroll = Scrollbar(command=Calculator_Output.xview, width=25, orient=HORIZONTAL)
hor_scroll.pack(side=BOTTOM, ipadx=0.1, ipady=0.8, fill=X)
hor_scroll.place(x=573, y=770, height=25, width=893)
vert_scroll = Scrollbar(command=Calculator_Output.yview, width=25, orient=VERTICAL)
vert_scroll.pack(side=RIGHT, ipadx=0.1, ipady=0.8, fill=Y)
vert_scroll.place(x=1470, y=608, height=158, width=25)
Calculator_Output.config(xscrollcommand=hor_scroll.set, yscrollcommand=vert_scroll.set)

def Is_num(input_str):
    try:
        float(input_str)
        return True
    except ValueError:
        return False

def CalcOutputFormat(input_num):
    num_str = str(input_num)
    int_part_str = num_str
    fract_part_str = ""
    for i in range(len(num_str)):
        if num_str[i] == '.':
            int_part_str = num_str[:i]
            fract_part_str = num_str[i:i + 7].rstrip('0')
            if fract_part_str == ".":
                fract_part_str = ""
            break
    int_part_str = int_part_str[::-1]
    int_parts = [(int_part_str[i:i + 3]) for i in range(0, len(int_part_str), 3)]
    int_parts.reverse()
    for i in range(len(int_parts)):
        int_parts[i] = int_parts[i][::-1]
    result = ' '.join(int_parts) + fract_part_str
    return result

def FromStrToNumConvert(input_str):
    int_part_str = input_str
    negative = False
    fract_part_str = ""
    for i in range(len(input_str)):
        if input_str[i] == '.':
            int_part_str = input_str[:i]
            if int_part_str[0] == '-':
                negative = True
                int_part_str = int_part_str[1:]
            fract_part_str = input_str[i:len(input_str)].rstrip('0')
            if fract_part_str == ".":
                fract_part_str = ""
            break
    new_int_part_str = ""
    j = 0
    for i in range(len(int_part_str) - 1, -1, -1):
        j += 1
        if j % 4 == 0 and int_part_str[i] == ' ':
            continue
        new_int_part_str = int_part_str[i] + new_int_part_str
    result = new_int_part_str + fract_part_str
    if negative:
        result = '-' + result
    return result

def Clean_Button_Clicked():
    Calculator_Output.delete("0.0", END)

def Sum_Function(FirstNum, SecondNum):
    Sum = Decimal(FirstNum + SecondNum)
    return Sum

def Diff_Function(FirstNum, SecondNum):
    Diff = Decimal(FirstNum - SecondNum)
    return Diff

def Mult_Function(FirstNum, SecondNum):
    Mult = Decimal(FirstNum * SecondNum)
    return Mult

def Div_Function(FirstNum, SecondNum):
    if SecondNum == 0:
        return "error"
    Div = round(FirstNum / SecondNum, 11)
    Div *= 10000000000
    Div = Decimal(int(Div + Decimal(0.5 if Div > 0 else -0.5)))
    Div /= 10000000000
    Div = Decimal(Div)
    return Div

def Math_Round(num):
    return str(int(num + (Decimal(0.5) if num > Decimal(0.0) else Decimal(-0.5))))

def Book_Round(num):
    return str(round(num))

def Trunct_round(num):
    return str(int(num))

def Calculation_Button_Clicked():
    FirstNumInput = FirstNum_Label.get().replace(',', '.')
    FirstNumInput = FromStrToNumConvert(FirstNumInput)
    if Is_num(FirstNumInput):
        if 'e' not in FirstNumInput:
            FirstNum = Decimal(FirstNumInput)
            SecondNumInput = SecondNum_Label.get().replace(',', '.')
            SecondNumInput = FromStrToNumConvert(SecondNumInput)
            if Is_num(SecondNumInput):
                if 'e' not in SecondNumInput:
                    SecondNum = Decimal(SecondNumInput)
                    ThirdNumInput = ThirdNum_Label.get().replace(',', '.')
                    ThirdNumInput = FromStrToNumConvert(ThirdNumInput)
                    if Is_num(ThirdNumInput):
                        if 'e' not in ThirdNumInput:
                            ThirdNum = Decimal(ThirdNumInput)
                            FourthNumInput = FourthNum_Label.get().replace(',', '.')
                            FourthNumInput = FromStrToNumConvert(FourthNumInput)
                            if Is_num(FourthNumInput):
                                if 'e' not in FourthNumInput:
                                    FourthNum = Decimal(FourthNumInput)
                                    Calculator_Output.insert(INSERT, "▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉\n")
                                    Calculator_Output.insert(INSERT,
                                                             "Первое число: " + str(FirstNum) + "\n")
                                    Calculator_Output.insert(INSERT,
                                                             "Второе число: " + str(SecondNum) + "\n")
                                    Calculator_Output.insert(INSERT,
                                                             "Третье число: " + str(ThirdNum) + "\n")
                                    Calculator_Output.insert(INSERT,
                                                             "Четвёртое число: " + str(FourthNum) + "\n")
                                    Result_Num = Calculation_Function(FirstNum, SecondNum, ThirdNum,
                                                                      FourthNum, FirstOperation_Info.get(),
                                                                      SecondOperation_Info.get(),
                                                                      ThirdOperation_Info.get())
                                    if isinstance(Result_Num, str):
                                        Calculator_Output.insert(INSERT, Result_Num + "\n")
                                    else:
                                        Result_Num_str = CalcOutputFormat(Result_Num)
                                        Calculator_Output.insert(INSERT, "Вычисления:\n")
                                        FirstNumStr = str(FirstNum)
                                        SecondNumStr = str(SecondNum)
                                        ThirdNumStr = str(ThirdNum)
                                        FourthNumStr = str(FourthNum)
                                        if SecondNum < 0:
                                            SecondNumStr = "({0})".format(SecondNumStr)
                                        if ThirdNum < 0:
                                            ThirdNumStr = "({0})".format(ThirdNumStr)
                                        if FourthNum < 0:
                                            FourthNumStr = "({0})".format(FourthNumStr)
                                        Calculator_Output.insert(INSERT, FirstNumStr + " "
                                                                 + FirstOperation_Info.get() + " ( " +
                                                                 SecondNumStr + " " + SecondOperation_Info.get() +
                                                                 " " + ThirdNumStr + " ) " +
                                                                 ThirdOperation_Info.get() + " " + FourthNumStr +
                                                                 " = " + Result_Num_str + "\n")
                                        if RoundType_Info.get() == "Математическое":
                                            Calculator_Output.insert(INSERT, "Результат после математического "
                                                                             "округления: " +
                                                                     CalcOutputFormat(Math_Round(Result_Num))
                                                                     + "\n")
                                        elif RoundType_Info.get() == "Бухгалтерское":
                                            Calculator_Output.insert(INSERT, "Результат после бухгалтерского "
                                                                             "округления: " +
                                                                     CalcOutputFormat(Book_Round(Result_Num))
                                                                     + "\n")
                                        else:
                                            Calculator_Output.insert(INSERT, "Результат после усечения " +
                                                                     CalcOutputFormat(Trunct_round(Result_Num)) + "\n")
                                else:
                                    messagebox.showerror("Калькулятор", "Во четвёртом числе введена буква \"e\"")
                            else:
                                messagebox.showerror("Калькулятор", "Третье число введено некорректно")
                        else:
                            messagebox.showerror("Калькулятор", "Во третьем числе введена буква \"e\"")
                    else:
                        messagebox.showerror("Калькулятор", "Третье число введено некорректно")
                else:
                    messagebox.showerror("Калькулятор", "Во втором числе введена буква \"e\"")
            else:
                messagebox.showerror("Калькулятор", "Второе число введено некорректно")
        else:
            messagebox.showerror("Калькулятор", "Во первом числе введена буква \"e\"")
    else:
        messagebox.showerror("Калькулятор", "Первое число введено некорректно")

def Calculation_Function(A, B, C, D, OP1, OP2, OP3):
    if OP2 == "+":
        BC = Sum_Function(B, C)
    elif OP2 == "-":
        BC = Diff_Function(B, C)
    elif OP2 == "*":
        BC = Mult_Function(B, C)
    else:
        BC_str = Div_Function(B, C)
        if BC_str == "error":
            return "Произошла ошибка, 3-е число равно нулю, деление на него невозможно"
        BC = Decimal(BC_str)
    if OP3 == "*" or OP3 == "/":
        if OP3 == "+":
            BCD = Sum_Function(BC, D)
        elif OP3 == "-":
            BCD = Diff_Function(BC, D)
        elif OP3 == "*":
            BCD = Mult_Function(BC, D)
        else:
            BCD_str = Div_Function(BC, D)
            if BCD_str == "error":
                return "Произошла ошибка, 4-ое число равно нулю, деление на него невозможно"
            BCD = Decimal(BCD_str)
        if OP1 == "+":
            A_BCD = Sum_Function(A, BCD)
        elif OP1 == "-":
            A_BCD = Diff_Function(A, BCD)
        elif OP1 == "*":
            A_BCD = Mult_Function(A, BCD)
        else:
            A_BCD_str = Div_Function(A, BCD)
            if A_BCD_str == "error":
                return "Произошла ошибка, результат операций 2-ого, 3-его и 4-ого чисел равен нулю, деление на него невозможно"
            A_BCD = Decimal(A_BCD_str)
        return A_BCD
    else:
        if OP1 == "+":
            ABC = Sum_Function(A, BC)
        elif OP1 == "-":
            ABC = Diff_Function(A, BC)
        elif OP1 == "*":
            ABC = Mult_Function(A, BC)
        else:
            ABC_str = Div_Function(A, BC)
            if ABC_str == "error":
                return "Произошла ошибка, результат операций 2-ого и 3-его чисел равен нулю, деление на него невозможно"
            ABC = Decimal(ABC_str)
        if OP3 == "+":
            ABC_D = Sum_Function(ABC, D)
        elif OP3 == "-":
            ABC_D = Diff_Function(ABC, D)
        elif OP3 == "*":
            ABC_D = Mult_Function(ABC, D)
        else:
            ABC_D_str = Div_Function(ABC, D)
            if ABC_D_str == "error":
                return "Произошла ошибка, четвёртое число равно нулю, деление на него невозможно"
            ABC_D = Decimal(ABC_D_str)
        return ABC_D

def Window_Calculator_PowerOn():
    Window_Calculator.deiconify()
    Window_Calculator.geometry('1500x800')
    Window_Calculator.resizable(width=False, height=False)
    Window_Calculator["bg"] = "#FEE28A"
    Window_Calculator.title("Калькулятор")

    Calculator_Lbl1 = Label(Window_Calculator, text="Жуковский Павел Сергеевич, 3 курс, 12 группа, 2020 год",
                            font=("Arial Bold", 14), bg="#FEE28A")
    Calculator_Lbl1.place(relx=0.17, rely=0.015, anchor="c")

    Calculator_Lbl2 = Label(Window_Calculator, text="КАЛЬКУЛЯТОР", font=("Arial Bold", 14), bg="#FEE28A")
    Calculator_Lbl2.place(relx=0.95, rely=0.015, anchor="c")

    Calculator_Lbl3 = Label(Window_Calculator, text="Введите первое число:", font=("Arial Bold", 36), bg="#FEE28A")
    Calculator_Lbl3.place(relx=0.225, rely=0.1, anchor="c")

    FirstNum_Txt = Entry(Window_Calculator, width=30, bd=5, font=("Arial Bold", 36), textvariable=FirstNum_Label)
    FirstNum_Txt.place(relx=0.7, rely=0.1, anchor="c")

    Calculator_Lbl4 = Label(Window_Calculator, text="Выберите первую операцию:", font=("Arial Bold", 18), bg="#FEE28A")
    Calculator_Lbl4.place(relx=0.26, rely=0.185, anchor="c")

    FirstOperation = ttk.Combobox(Window_Calculator, values=["+", "-", "*", "/"], font=("Arial Bold", 26), width=2,
                                  state='readonly', textvariable=FirstOperation_Info)
    FirstOperation.current(0)
    FirstOperation.place(relx=0.4, rely=0.185, anchor="c")

    Calculator_Lbl5 = Label(Window_Calculator, text="Введите второе число:", font=("Arial Bold", 36), bg="#FEE28A")
    Calculator_Lbl5.place(relx=0.225, rely=0.27, anchor="c")

    SecondNum_Txt = Entry(Window_Calculator, width=30, bd=5, font=("Arial Bold", 36), textvariable=SecondNum_Label)
    SecondNum_Txt.setvar("0")
    SecondNum_Txt.place(relx=0.7, rely=0.27, anchor="c")

    Calculator_Lbl6 = Label(Window_Calculator, text="Выберите вторую операцию:", font=("Arial Bold", 18), bg="#FEE28A")
    Calculator_Lbl6.place(relx=0.26, rely=0.355, anchor="c")

    SecondOperation = ttk.Combobox(Window_Calculator, values=["+", "-", "*", "/"], font=("Arial Bold", 26), width=2,
                                   state='readonly', textvariable=SecondOperation_Info)
    SecondOperation.current(0)
    SecondOperation.place(relx=0.4, rely=0.355, anchor="c")

    Calculator_Lbl7 = Label(Window_Calculator, text="Введите третье число:", font=("Arial Bold", 36), bg="#FEE28A")
    Calculator_Lbl7.place(relx=0.226, rely=0.44, anchor="c")

    ThirdNum_Txt = Entry(Window_Calculator, width=30, bd=5, font=("Arial Bold", 36), textvariable=ThirdNum_Label)
    ThirdNum_Txt.place(relx=0.7, rely=0.44, anchor="c")

    Calculator_Lbl8 = Label(Window_Calculator, text="Выберите третью операцию:", font=("Arial Bold", 18), bg="#FEE28A")
    Calculator_Lbl8.place(relx=0.26, rely=0.525, anchor="c")

    ThirdOperation = ttk.Combobox(Window_Calculator, values=["+", "-", "*", "/"], font=("Arial Bold", 26), width=2,
                                  state='readonly', textvariable=ThirdOperation_Info)
    ThirdOperation.current(0)
    ThirdOperation.place(relx=0.4, rely=0.525, anchor="c")

    Calculator_Lbl9 = Label(Window_Calculator, text="Введите четвёртое число:", font=("Arial Bold", 36), bg="#FEE28A")
    Calculator_Lbl9.place(relx=0.2, rely=0.61, anchor="c")

    FourthNum_Txt = Entry(Window_Calculator, width=30, bd=5, font=("Arial Bold", 36), textvariable=FourthNum_Label)
    FourthNum_Txt.place(relx=0.7, rely=0.61, anchor="c")

    Clean_Button = Button(Window_Calculator, text="Очистить вывод", font=("Arial Bold", 18), bd=10,
                        background="#CC9B00", command=Clean_Button_Clicked)
    Clean_Button.place(relx=0.88, rely=0.71, anchor="c")

    Calculator_Lbl10 = Label(Window_Calculator, text="ВЫВОД", font=("Arial Bold", 36), bg="#FEE28A")
    Calculator_Lbl10.place(relx=0.47, rely=0.72, anchor="c")

    Calculator_Lbl11 = Label(Window_Calculator, text="Выберите тип округления:", font=("Arial Bold", 28), bg="#FEE28A")
    Calculator_Lbl11.place(relx=0.18, rely=0.72, anchor="c")

    RoundingType = ttk.Combobox(Window_Calculator, values=["Математическое", "Бухгалтерское", "Усечение"],
                                font=("Arial Bold", 26), width=15, state='readonly', textvariable=RoundType_Info)
    RoundingType.current(0)
    RoundingType.place(relx=0.18, rely=0.8, anchor="c")

    Calculation_Button = Button(Window_Calculator, text="Провести расчёты", font=("Arial Bold", 28), bd=10,
                        background="#CC9B00", command=Calculation_Button_Clicked)
    Calculation_Button.place(relx=0.178, rely=0.915, anchor="c")

    Window_Calculator.mainloop()

Window_Calculator_PowerOn()