from decimal import Decimal
from tkinter import *
from tkinter import messagebox

Window_Calculator = Tk()
Window_Calculator.withdraw()

FirstNum_Label = StringVar()
SecondNum_Label = StringVar()

Calculator_Output = Text(Window_Calculator, height=8.5, width=55, bd=5, font=("Times New Roman", 24), wrap=NONE)
Calculator_Output.place(relx=0.68, rely=0.75, anchor="c")
hor_scroll = Scrollbar(command=Calculator_Output.xview, width=25, orient=HORIZONTAL)
hor_scroll.pack(side=BOTTOM, ipadx=0.1, ipady=0.8, fill=X)
hor_scroll.place(x=573, y=770, height=25, width=893)
vert_scroll = Scrollbar(command=Calculator_Output.yview, width=25, orient=VERTICAL)
vert_scroll.pack(side=RIGHT, ipadx=0.1, ipady=0.8, fill=Y)
vert_scroll.place(x=1470, y=433, height=335, width=25)
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

def Sum_Button_Clicked():
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
                    Sum = FirstNum + SecondNum
                    Calculator_Output.insert(INSERT, "▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉\n")
                    Calculator_Output.insert(INSERT, "Первое число: " + str(FirstNum) + "\n")
                    Calculator_Output.insert(INSERT, "Второе число: " + str(SecondNum) + "\n")
                    Sum = CalcOutputFormat(Sum)
                    SecondNumStr = str(SecondNum)
                    if SecondNum < 0:
                        SecondNumStr = "({0})".format(SecondNumStr)
                    Calculator_Output.insert(INSERT, "Сумма: " + str(FirstNum) + " + " + SecondNumStr + " = " + Sum + "\n")
                else:
                    messagebox.showerror("Калькулятор", "Во втором числе введена буква \"e\"")
            else:
                messagebox.showerror("Калькулятор", "Второе число введено некорректно")
        else:
            messagebox.showerror("Калькулятор", "Во первом числе введена буква \"e\"")
    else:
        messagebox.showerror("Калькулятор", "Первое число введено некорректно")

def Diff_Button_Clicked():
    FirstNumInput = FirstNum_Label.get().replace(',', '.')
    FirstNumInput = FromStrToNumConvert(FirstNumInput)
    if Is_num(FirstNumInput):
        FirstNum = Decimal(FirstNumInput)
        SecondNumInput = SecondNum_Label.get().replace(',', '.')
        SecondNumInput = FromStrToNumConvert(SecondNumInput)
        if Is_num(SecondNumInput):
            SecondNum = Decimal(SecondNumInput)
            Diff = FirstNum - SecondNum
            Calculator_Output.insert(INSERT, "▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉\n")
            Calculator_Output.insert(INSERT, "Первое число: " + str(FirstNum) + "\n")
            Calculator_Output.insert(INSERT, "Второе число: " + str(SecondNum) + "\n")
            Diff = CalcOutputFormat(Diff)
            SecondNumStr = str(SecondNum)
            if SecondNum < 0:
                SecondNumStr = "({0})".format(SecondNumStr)
            Calculator_Output.insert(INSERT, "Разность: " + str(FirstNum) + " - " + SecondNumStr + " = " + Diff + "\n")
        else:
            messagebox.showerror("Калькулятор", "Второе число введено некорректно")
    else:
        messagebox.showerror("Калькулятор", "Первое число введено некорректно")

def Mult_Button_Clicked():
    FirstNumInput = FirstNum_Label.get().replace(',', '.')
    FirstNumInput = FromStrToNumConvert(FirstNumInput)
    if Is_num(FirstNumInput):
        FirstNum = Decimal(FirstNumInput)
        SecondNumInput = SecondNum_Label.get().replace(',', '.')
        SecondNumInput = FromStrToNumConvert(SecondNumInput)
        if Is_num(SecondNumInput):
            SecondNum = Decimal(SecondNumInput)
            Mult = FirstNum * SecondNum
            Calculator_Output.insert(INSERT, "▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉\n")
            Calculator_Output.insert(INSERT, "Первое число: " + str(FirstNum) + "\n")
            Calculator_Output.insert(INSERT, "Второе число: " + str(SecondNum) + "\n")
            Mult = CalcOutputFormat(Mult)
            FirstNumStr = str(FirstNum)
            if FirstNum < 0:
                FirstNumStr = "({0})".format(FirstNumStr)
            SecondNumStr = str(SecondNum)
            if SecondNum < 0:
                SecondNumStr = "({0})".format(SecondNumStr)
            Calculator_Output.insert(INSERT, "Произведение: " + FirstNumStr + " * " + SecondNumStr + " = " + Mult + "\n")
        else:
            messagebox.showerror("Калькулятор", "Второе число введено некорректно")
    else:
        messagebox.showerror("Калькулятор", "Первое число введено некорректно")

def Div_Button_Clicked():
    FirstNumInput = FirstNum_Label.get().replace(',', '.')
    FirstNumInput = FromStrToNumConvert(FirstNumInput)
    if Is_num(FirstNumInput):
        FirstNum = Decimal(FirstNumInput)
        SecondNumInput = SecondNum_Label.get().replace(',', '.')
        SecondNumInput = FromStrToNumConvert(SecondNumInput)
        if Is_num(SecondNumInput):
            SecondNum = Decimal(SecondNumInput)
            if SecondNum == 0:
                messagebox.showerror("Калькулятор", "Второе число равно нулю, деление невозможно")
            else:
                Div = round(FirstNum / SecondNum, 7)
                Div *= 1000000
                Div = Decimal(int(Div + Decimal(0.5 if Div > 0 else -0.5)))
                Div /= 1000000
                Calculator_Output.insert(INSERT, "▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉\n")
                Calculator_Output.insert(INSERT, "Первое число: " + str(FirstNum) + "\n")
                Calculator_Output.insert(INSERT, "Второе число: " + str(SecondNum) + "\n")
                Div = Decimal(Div)
                Div = CalcOutputFormat(Div)
                FirstNumStr = str(FirstNum)
                if FirstNum < 0:
                    FirstNumStr = "({0})".format(FirstNumStr)
                SecondNumStr = str(SecondNum)
                if SecondNum < 0:
                    SecondNumStr = "({0})".format(SecondNumStr)
                Calculator_Output.insert(INSERT, "Деление: " + FirstNumStr + " / " + SecondNumStr + " = " + Div + "\n")
        else:
            messagebox.showerror("Калькулятор", "Второе число введено некорректно")
    else:
        messagebox.showerror("Калькулятор", "Первое число введено некорректно")

def Window_Calculator_PowerOn():
    Window_Calculator.deiconify()
    Window_Calculator.geometry('1500x800')
    Window_Calculator.resizable(width=False, height=False)
    Window_Calculator["bg"] = "#FEE28A"
    Window_Calculator.title("Калькулятор")

    Calculator_Lbl1 = Label(Window_Calculator, text="Жуковский Павел Сергеевич, 3 курс, 12 группа, 2020 год",
                            font=("Arial Bold", 14), bg="#FEE28A")
    Calculator_Lbl1.place(relx=0.17, rely=0.015, anchor="c")

    Calculator_Lbl2 = Label(Window_Calculator, text="КАЛЬКУЛЯТОР", font=("Arial Bold", 50), bg="#FEE28A")
    Calculator_Lbl2.place(relx=0.5, rely=0.1, anchor="c")

    Clean_Button = Button(Window_Calculator, text="Очистить вывод", font=("Arial Bold", 18), bd=10,
                        background="#CC9B00", command=Clean_Button_Clicked)
    Clean_Button.place(relx=0.88, rely=0.49, anchor="c")

    Calculator_Lbl3 = Label(Window_Calculator, text="Введите первое число:", font=("Arial Bold", 36), bg="#FEE28A")
    Calculator_Lbl3.place(relx=0.2, rely=0.25, anchor="c")

    Calculator_Lbl4 = Label(Window_Calculator, text="Введите второе число:", font=("Arial Bold", 36), bg="#FEE28A")
    Calculator_Lbl4.place(relx=0.2015, rely=0.35, anchor="c")

    FirstNum_Txt = Entry(Window_Calculator, width=30, bd=5, font=("Arial Bold", 36), textvariable=FirstNum_Label)
    FirstNum_Txt.place(relx=0.68, rely=0.25, anchor="c")

    SecondNum_Txt = Entry(Window_Calculator, width=30, bd=5, font=("Arial Bold", 36), textvariable=SecondNum_Label)
    SecondNum_Txt.place(relx=0.68, rely=0.35, anchor="c")

    Sum_Button = Button(Window_Calculator, text="Сложить два числа", font=("Arial Bold", 24), bd=10,
                        background="#CC9B00", command=Sum_Button_Clicked)
    Sum_Button.place(relx=0.2, rely=0.55, anchor="c")

    Diff_Button = Button(Window_Calculator, text="Отнять от первого числа второе", font=("Arial Bold", 18), bd=10,
                        background="#CC9B00", command=Diff_Button_Clicked)
    Diff_Button.place(relx=0.2, rely=0.67, anchor="c")

    Mult_Button = Button(Window_Calculator, text="Перемножить два числа", font=("Arial Bold", 18), bd=10,
                         background="#CC9B00", command=Mult_Button_Clicked)
    Mult_Button.place(relx=0.2, rely=0.79, anchor="c")

    Div_Button = Button(Window_Calculator, text="Разделить первое число на второе", font=("Arial Bold", 18), bd=10,
                         background="#CC9B00", command=Div_Button_Clicked)
    Div_Button.place(relx=0.2, rely=0.91, anchor="c")

    Calculator_Lbl5 = Label(Window_Calculator, text="ВЫВОД", font=("Arial Bold", 36), bg="#FEE28A")
    Calculator_Lbl5.place(relx=0.47, rely=0.5, anchor="c")

    Window_Calculator.mainloop()

Window_Calculator_PowerOn()