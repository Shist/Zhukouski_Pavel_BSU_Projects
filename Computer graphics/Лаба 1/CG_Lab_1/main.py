# Вариант 8
# RGB <--> XYZ <--> HSV
from tkinter import *
from tkinter import messagebox, colorchooser
import colorsys

MainWindow = Tk()
MainWindow.title("Жуковский Павел, 3 курс, 12 группа, Вариант 8, RGB <--> XYZ <--> HSV")
MainWindow.attributes("-fullscreen", True)
MainWindow["bg"] = "#FFDEAD"

varR = DoubleVar()
varR.set(0.0)
varG = DoubleVar()
varG.set(0.0)
varB = DoubleVar()
varB.set(0.0)

varX = DoubleVar()
varX.set(0.0)
varY = DoubleVar()
varY.set(0.0)
varZ = DoubleVar()
varZ.set(0.0)

varH = DoubleVar()
varH.set(0.0)
varS = DoubleVar()
varS.set(0.0)
varV = DoubleVar()
varV.set(0.0)

labWarning = Label(text="Предупреждение:\nбыло совершено округление",
                   font=("Times New Roman", "24"),
                   bg="#FFDEAD",
                   fg="#FF0000")
labWarning.pack()
labWarning.place(relx=0.28, rely=0.1)
labWarning.place_forget()

btnExit = Button(text="Выход",
                 bg="#DAA520",
                 fg="#000000",
                 font=("Times New Roman", "36"),
                 bd=10,
                 command=MainWindow.quit)
btnExit.pack()
btnExit.place(relx=0.03, rely=0.82)

labAuthor = Label(text="Жуковский Павел, 3 курс, 12 группа",
                  font=("Times New Roman", "24"),
                  bg="#FFDEAD")
labAuthor.pack()
labAuthor.place(relx=0.01, rely=0.01)

labVariant = Label(text="Вариант 8, RGB <--> XYZ <--> HSV",
                   font=("Times New Roman", "24"),
                   bg="#FFDEAD")
labVariant.pack()
labVariant.place(relx=0.01, rely=0.06)

labChosenColor = Label(text="Выбранный цвет:",
                  font=("Times New Roman", "28"),
                  bg="#FFDEAD")
labChosenColor.pack()
labChosenColor.place(relx=0.04, rely=0.14)

canvas = Canvas(width=800,
                height=500,
                bg="#000000",
                highlightbackground="#DAA520")
canvas.place(relx=0.03, rely=0.2)

colorDialog = colorchooser.Chooser(MainWindow)

def openColorDialog():
    global varR
    global varG
    global varB
    global varX
    global varY
    global varZ
    global varH
    global varS
    global varV
    color = colorDialog.show()
    messagebox.showinfo("Заметка", "Выбранный вами цвет: " + color[1] + "\n" +
                                "R = " + str(color[0][0]) + " , G = " + str(color[0][1]) + " , B = " + str(color[0][2]))
    varR.set(int(color[0][0]))
    varG.set(int(color[0][1]))
    varB.set(int(color[0][2]))
    xyz_list = FromRgbToXYZ(varR.get(), varG.get(), varB.get())
    varX.set(xyz_list[0])
    varY.set(xyz_list[1])
    varZ.set(xyz_list[2])
    hsv_list = FromRgbToHSV(varR.get(), varG.get(), varB.get())
    varH.set(hsv_list[0])
    varS.set(hsv_list[1])
    varV.set(hsv_list[2])
    canvas.config(bg=color[1])

btnChooseColor = Button(text="Выбрать цвет из палитры",
                        bg="#DAA520",
                        fg="#000000",
                        font=("Times New Roman", "36"),
                        bd=10,
                        command=openColorDialog)
btnChooseColor.pack()
btnChooseColor.place(relx=0.17, rely=0.82)

def FromRGBtoColorHex(R, G, B):
    return '#%02x%02x%02x' % (int(R.get()), int(G.get()), int(B.get()))

def g(x):
    if x >= 0.04045:
        return ((x + 0.055)/1.055) ** 2.4
    else:
        return x/12.92

def FromRgbToXYZ(R, G, B):
    xyz_list = []
    Rn = g(R / 255)*100
    Gn = g(G / 255)*100
    Bn = g(B / 255)*100
    X = Bn * 0.180437 + Gn * 0.357576 + Rn * 0.412456
    Y = Bn * 0.072175 + Gn * 0.715152 + Rn * 0.212673
    Z = Bn * 0.950304 + Gn * 0.119192 + Rn * 0.0193339
    if X > 100.0 or Y > 100.0 or Z > 100.0:
        labWarning.place(relx=0.28, rely=0.1)
    else:
        labWarning.place_forget()
    xyz_list.append(X)
    xyz_list.append(Y)
    xyz_list.append(Z)
    return xyz_list

def FromXYZtoRgb(X, Y, Z):
    X /= 100
    Y /= 100
    Z /= 100
    R = 3.2404542 * X - 1.5371385 * Y - 0.4985314 * Z
    G = -0.9692660 * X + 1.8760108 * Y + 0.0415560 * Z
    B = 0.0556434 * X - 0.2040259 * Y + 1.0572252 * Z
    R *= 255
    G *= 255
    B *= 255
    rgb_list = [R, G, B]
    if rgb_list[0] > 255.0 or rgb_list[1] > 255.0 or rgb_list[2] > 255.0:
        labWarning.place(relx=0.28, rely=0.1)
    else:
        labWarning.place_forget()
    return rgb_list

def FromRgbToHSV(R, G, B):
    hsv_list = list(colorsys.rgb_to_hsv(R, G, B))
    hsv_list[0] *= 100
    hsv_list[1] *= 100
    hsv_list[2] *= (100 / 255)
    return hsv_list

def FromHSVtoRgb(H, S, V):
    H /= 100
    S /= 100
    V /= (100/255)
    rgb_list = list(colorsys.hsv_to_rgb(H, S, V))
    return rgb_list

def changeColorFromRGB(scaleInfo):
    global canvas
    global varR
    global varG
    global varB
    global varX
    global varY
    global varZ
    global varH
    global varS
    global varV
    xyz_list = FromRgbToXYZ(varR.get(), varG.get(), varB.get())
    varX.set(xyz_list[0])
    varY.set(xyz_list[1])
    varZ.set(xyz_list[2])
    hsv_list = FromRgbToHSV(varR.get(), varG.get(), varB.get())
    varH.set(hsv_list[0])
    varS.set(hsv_list[1])
    varV.set(hsv_list[2])
    canvas.config(bg=FromRGBtoColorHex(varR, varG, varB))

def changeColorFromXYZ(scaleInfo):
    global canvas
    global varR
    global varG
    global varB
    global varX
    global varY
    global varZ
    global varH
    global varS
    global varV
    rgb_list = FromXYZtoRgb(varX.get(), varY.get(), varZ.get())
    varR.set(rgb_list[0])
    varG.set(rgb_list[1])
    varB.set(rgb_list[2])
    hsv_list = FromRgbToHSV(varR.get(), varG.get(), varB.get())
    varH.set(hsv_list[0])
    varS.set(hsv_list[1])
    varV.set(hsv_list[2])
    canvas.config(bg=FromRGBtoColorHex(varR, varG, varB))

def changeColorFromHSV(scaleInfo):
    global canvas
    global varR
    global varG
    global varB
    global varX
    global varY
    global varZ
    global varH
    global varS
    global varV
    rgb_list = FromHSVtoRgb(varH.get(), varS.get(), varV.get())
    varR.set(rgb_list[0])
    varG.set(rgb_list[1])
    varB.set(rgb_list[2])
    xyz_list = FromRgbToXYZ(varR.get(), varG.get(), varB.get())
    varX.set(xyz_list[0])
    varY.set(xyz_list[1])
    varZ.set(xyz_list[2])
    canvas.config(bg=FromRGBtoColorHex(varR, varG, varB))

labRGB = Label(text="RGB",
               font=("Times New Roman", "48"),
               bg="#FFDEAD")
labRGB.pack()
labRGB.place(relx=0.67, rely=0.01)

labRGB_R = Label(text="R",
               font=("Times New Roman", "36"),
               bg="#FFDEAD")
labRGB_R.pack()
labRGB_R.place(relx=0.57, rely=0.1)

scrollR = Scale(bg="#DAA520",
                activebackground="#B8860B",
                fg="#000000",
                highlightbackground="#DAA520",
                bd=3,
                orient=HORIZONTAL,
                sliderlength=20,
                length=256,
                width=20,
                to=255,
                relief="ridge",
                troughcolor="#FFF8DC",
                command=changeColorFromRGB,
                variable=varR)
scrollR.pack()
scrollR.place(relx=0.62, rely=0.103)

textR = Entry(MainWindow,
              width=4,
              bd=5,
              font=("Times New Roman", "32"),
              textvariable=varR,
              state="disabled")
textR.place(relx=0.93, rely=0.101)

btnSetR_Flag = True

def SetR_Foo():
    global varR
    global btnSetR_Flag
    if btnSetR_Flag:
        textR.config(state="normal")
        btnSetR.config(text="Подтвердить R")
        btnSetR_Flag = False
    else:
        changeColorFromRGB("SetR_Foo")
        textR.config(state="disabled")
        btnSetR.config(text="Задать точное R")
        btnSetR_Flag = True

btnSetR = Button(text="Задать точное R",
                        bg="#DAA520",
                        fg="#000000",
                        font=("Times New Roman", "14"),
                        bd=10,
                        command=SetR_Foo,
                        padx=5,
                        pady=5)
btnSetR.pack()
btnSetR.place(relx=0.81, rely=0.101)

labRGB_G = Label(text="G",
               font=("Times New Roman", "36"),
               bg="#FFDEAD")
labRGB_G.pack()
labRGB_G.place(relx=0.57, rely=0.18)

scrollG = Scale(bg="#DAA520",
                activebackground="#B8860B",
                fg="#000000",
                highlightbackground="#DAA520",
                bd=3,
                orient=HORIZONTAL,
                sliderlength=20,
                length=256,
                width=20,
                to=255,
                relief="ridge",
                troughcolor="#FFF8DC",
                command=changeColorFromRGB,
                variable=varG)
scrollG.pack()
scrollG.place(relx=0.62, rely=0.183)

textG = Entry(MainWindow,
              width=4,
              bd=5,
              font=("Times New Roman", "32"),
              textvariable=varG,
              state="disabled")
textG.place(relx=0.93, rely=0.176)

btnSetG_Flag = True

def SetG_Foo():
    global varG
    global btnSetG_Flag
    if btnSetG_Flag:
        textG.config(state="normal")
        btnSetG.config(text="Подтвердить G")
        btnSetG_Flag = False
    else:
        changeColorFromRGB("SetG_Foo")
        textG.config(state="disabled")
        btnSetG.config(text="Задать точное G")
        btnSetG_Flag = True

btnSetG = Button(text="Задать точное G",
                        bg="#DAA520",
                        fg="#000000",
                        font=("Times New Roman", "14"),
                        bd=10,
                        command=SetG_Foo,
                        padx=5,
                        pady=5)
btnSetG.pack()
btnSetG.place(relx=0.81, rely=0.176)

labRGB_B = Label(text="B",
               font=("Times New Roman", "36"),
               bg="#FFDEAD")
labRGB_B.pack()
labRGB_B.place(relx=0.57, rely=0.26)

scrollB = Scale(bg="#DAA520",
                activebackground="#B8860B",
                fg="#000000",
                highlightbackground="#DAA520",
                bd=3,
                orient=HORIZONTAL,
                sliderlength=20,
                length=256,
                width=20,
                to=255,
                relief="ridge",
                troughcolor="#FFF8DC",
                command=changeColorFromRGB,
                variable=varB)
scrollB.pack()
scrollB.place(relx=0.62, rely=0.263)

textB = Entry(MainWindow,
              width=4,
              bd=5,
              font=("Times New Roman", "32"),
              textvariable=varB,
              state="disabled")
textB.place(relx=0.93, rely=0.251)

btnSetB_Flag = True

def SetB_Foo():
    global varB
    global btnSetB_Flag
    if btnSetB_Flag:
        textB.config(state="normal")
        btnSetB.config(text="Подтвердить B")
        btnSetB_Flag = False
    else:
        changeColorFromRGB("SetB_Foo")
        textB.config(state="disabled")
        btnSetB.config(text="Задать точное B")
        btnSetB_Flag = True

btnSetB = Button(text="Задать точное B",
                        bg="#DAA520",
                        fg="#000000",
                        font=("Times New Roman", "14"),
                        bd=10,
                        command=SetB_Foo,
                        padx=5,
                        pady=5)
btnSetB.pack()
btnSetB.place(relx=0.81, rely=0.251)

labXYZ = Label(text="XYZ",
               font=("Times New Roman", "48"),
               bg="#FFDEAD")
labXYZ.pack()
labXYZ.place(relx=0.67, rely=0.33)

labXYZ_X = Label(text="X",
               font=("Times New Roman", "36"),
               bg="#FFDEAD")
labXYZ_X.pack()
labXYZ_X.place(relx=0.57, rely=0.42)

scrollX = Scale(bg="#DAA520",
                activebackground="#B8860B",
                fg="#000000",
                highlightbackground="#DAA520",
                bd=3,
                orient=HORIZONTAL,
                sliderlength=20,
                length=256,
                width=20,
                to=100,
                relief="ridge",
                troughcolor="#FFF8DC",
                command=changeColorFromXYZ,
                variable=varX)
scrollX.pack()
scrollX.place(relx=0.62, rely=0.423)

textX = Entry(MainWindow,
              width=4,
              bd=5,
              font=("Times New Roman", "32"),
              textvariable=varX,
              state="disabled")
textX.place(relx=0.93, rely=0.423)

btnSetX_Flag = True

def SetX_Foo():
    global varX
    global btnSetX_Flag
    if btnSetX_Flag:
        textX.config(state="normal")
        btnSetX.config(text="Подтвердить X")
        btnSetX_Flag = False
    else:
        changeColorFromXYZ("SetX_Foo")
        textX.config(state="disabled")
        btnSetX.config(text="Задать точное X")
        btnSetX_Flag = True

btnSetX = Button(text="Задать точное X",
                        bg="#DAA520",
                        fg="#000000",
                        font=("Times New Roman", "14"),
                        bd=10,
                        command=SetX_Foo,
                        padx=5,
                        pady=5)
btnSetX.pack()
btnSetX.place(relx=0.81, rely=0.423)

labXYZ_Y = Label(text="Y",
               font=("Times New Roman", "36"),
               bg="#FFDEAD")
labXYZ_Y.pack()
labXYZ_Y.place(relx=0.57, rely=0.5)

scrollY = Scale(bg="#DAA520",
                activebackground="#B8860B",
                fg="#000000",
                highlightbackground="#DAA520",
                bd=3,
                orient=HORIZONTAL,
                sliderlength=20,
                length=256,
                width=20,
                to=100,
                relief="ridge",
                troughcolor="#FFF8DC",
                command=changeColorFromXYZ,
                variable=varY)
scrollY.pack()
scrollY.place(relx=0.62, rely=0.503)

textY = Entry(MainWindow,
              width=4,
              bd=5,
              font=("Times New Roman", "32"),
              textvariable=varY,
              state="disabled")
textY.place(relx=0.93, rely=0.498)

btnSetY_Flag = True

def SetY_Foo():
    global varY
    global btnSetY_Flag
    if btnSetY_Flag:
        textY.config(state="normal")
        btnSetY.config(text="Подтвердить Y")
        btnSetY_Flag = False
    else:
        changeColorFromXYZ("SetY_Foo")
        textY.config(state="disabled")
        btnSetY.config(text="Задать точное Y")
        btnSetY_Flag = True

btnSetY = Button(text="Задать точное Y",
                        bg="#DAA520",
                        fg="#000000",
                        font=("Times New Roman", "14"),
                        bd=10,
                        command=SetY_Foo,
                        padx=5,
                        pady=5)
btnSetY.pack()
btnSetY.place(relx=0.81, rely=0.498)

labXYZ_Z = Label(text="Z",
               font=("Times New Roman", "36"),
               bg="#FFDEAD")
labXYZ_Z.pack()
labXYZ_Z.place(relx=0.57, rely=0.58)

scrollZ = Scale(bg="#DAA520",
                activebackground="#B8860B",
                fg="#000000",
                highlightbackground="#DAA520",
                bd=3,
                orient=HORIZONTAL,
                sliderlength=20,
                length=256,
                width=20,
                to=100,
                relief="ridge",
                troughcolor="#FFF8DC",
                command=changeColorFromXYZ,
                variable=varZ)
scrollZ.pack()
scrollZ.place(relx=0.62, rely=0.583)

textZ = Entry(MainWindow,
              width=4,
              bd=5,
              font=("Times New Roman", "32"),
              textvariable=varZ,
              state="disabled")
textZ.place(relx=0.93, rely=0.573)

btnSetZ_Flag = True

def SetZ_Foo():
    global varZ
    global btnSetZ_Flag
    if btnSetZ_Flag:
        textZ.config(state="normal")
        btnSetZ.config(text="Подтвердить Z")
        btnSetZ_Flag = False
    else:
        changeColorFromXYZ("SetZ_Foo")
        textZ.config(state="disabled")
        btnSetZ.config(text="Задать точное Z")
        btnSetZ_Flag = True

btnSetZ = Button(text="Задать точное Z",
                        bg="#DAA520",
                        fg="#000000",
                        font=("Times New Roman", "14"),
                        bd=10,
                        command=SetZ_Foo,
                        padx=5,
                        pady=5)
btnSetZ.pack()
btnSetZ.place(relx=0.81, rely=0.573)

labHSV = Label(text="HSV",
               font=("Times New Roman", "48"),
               bg="#FFDEAD")
labHSV.pack()
labHSV.place(relx=0.67, rely=0.65)

labHSV_H = Label(text="H",
               font=("Times New Roman", "36"),
               bg="#FFDEAD")
labHSV_H.pack()
labHSV_H.place(relx=0.57, rely=0.74)

scrollH = Scale(bg="#DAA520",
                activebackground="#B8860B",
                fg="#000000",
                highlightbackground="#DAA520",
                bd=3,
                orient=HORIZONTAL,
                sliderlength=20,
                length=256,
                width=20,
                to=100,
                relief="ridge",
                troughcolor="#FFF8DC",
                command=changeColorFromHSV,
                variable=varH)
scrollH.pack()
scrollH.place(relx=0.62, rely=0.743)

textH = Entry(MainWindow,
              width=4,
              bd=5,
              font=("Times New Roman", "32"),
              textvariable=varH,
              state="disabled")
textH.place(relx=0.93, rely=0.74)

btnSetH_Flag = True

def SetH_Foo():
    global varH
    global btnSetH_Flag
    if btnSetH_Flag:
        textH.config(state="normal")
        btnSetH.config(text="Подтвердить H")
        btnSetH_Flag = False
    else:
        changeColorFromHSV("SetH_Foo")
        textH.config(state="disabled")
        btnSetH.config(text="Задать точное H")
        btnSetH_Flag = True

btnSetH = Button(text="Задать точное H",
                        bg="#DAA520",
                        fg="#000000",
                        font=("Times New Roman", "14"),
                        bd=10,
                        command=SetH_Foo,
                        padx=5,
                        pady=5)
btnSetH.pack()
btnSetH.place(relx=0.81, rely=0.74)

labHSV_S = Label(text="S",
               font=("Times New Roman", "36"),
               bg="#FFDEAD")
labHSV_S.pack()
labHSV_S.place(relx=0.57, rely=0.82)

scrollS = Scale(bg="#DAA520",
                activebackground="#B8860B",
                fg="#000000",
                highlightbackground="#DAA520",
                bd=3,
                orient=HORIZONTAL,
                sliderlength=20,
                length=256,
                width=20,
                to=100,
                relief="ridge",
                troughcolor="#FFF8DC",
                command=changeColorFromHSV,
                variable=varS)
scrollS.pack()
scrollS.place(relx=0.62, rely=0.823)

textS = Entry(MainWindow,
              width=4,
              bd=5,
              font=("Times New Roman", "32"),
              textvariable=varS,
              state="disabled")
textS.place(relx=0.93, rely=0.815)

btnSetS_Flag = True

def SetS_Foo():
    global varS
    global btnSetS_Flag
    if btnSetS_Flag:
        textS.config(state="normal")
        btnSetS.config(text="Подтвердить S")
        btnSetS_Flag = False
    else:
        changeColorFromHSV("SetS_Foo")
        textS.config(state="disabled")
        btnSetS.config(text="Задать точное S")
        btnSetS_Flag = True

btnSetS = Button(text="Задать точное S",
                        bg="#DAA520",
                        fg="#000000",
                        font=("Times New Roman", "14"),
                        bd=10,
                        command=SetS_Foo,
                        padx=5,
                        pady=5)
btnSetS.pack()
btnSetS.place(relx=0.81, rely=0.815)

labHSV_V = Label(text="V",
               font=("Times New Roman", "36"),
               bg="#FFDEAD")
labHSV_V.pack()
labHSV_V.place(relx=0.57, rely=0.9)

scrollV = Scale(bg="#DAA520",
                activebackground="#B8860B",
                fg="#000000",
                highlightbackground="#DAA520",
                highlightcolor="#FFFFFF",
                bd=3,
                orient=HORIZONTAL,
                sliderlength=20,
                length=256,
                width=20,
                to=100,
                relief="ridge",
                troughcolor="#FFF8DC",
                command=changeColorFromHSV,
                variable=varV)
scrollV.pack()
scrollV.place(relx=0.62, rely=0.903)

textV = Entry(MainWindow,
              width=4,
              bd=5,
              font=("Times New Roman", "32"),
              textvariable=varV,
              state="disabled")
textV.place(relx=0.93, rely=0.89)

btnSetV_Flag = True

def SetV_Foo():
    global varV
    global btnSetV_Flag
    if btnSetV_Flag:
        textV.config(state="normal")
        btnSetV.config(text="Подтвердить V")
        btnSetV_Flag = False
    else:
        changeColorFromHSV("SetV_Foo")
        textV.config(state="disabled")
        btnSetV.config(text="Задать точное V")
        btnSetV_Flag = True

btnSetV = Button(text="Задать точное V",
                        bg="#DAA520",
                        fg="#000000",
                        font=("Times New Roman", "14"),
                        bd=10,
                        command=SetV_Foo,
                        padx=5,
                        pady=5)
btnSetV.pack()
btnSetV.place(relx=0.81, rely=0.89)

MainWindow.mainloop()