from tkinter import *
from tkinter import messagebox
import sqlite3

CurrentID = 1
CurrentName = ""
CurrentPrice = 0.0
CurrentAmount = 0

CurrentGood = [0, "", 0.0, 0]

CurrentOrder = []

Window_SignIn = Tk()
Window_SignIn.withdraw()

Window_SignUp = Toplevel(Window_SignIn)
Window_SignUp.withdraw()

Window_OnlineShop = Toplevel(Window_SignUp)
Window_OnlineShop.withdraw()

Window_AccountInfo = Toplevel(Window_OnlineShop)
Window_AccountInfo.withdraw()

Window_PreparingOrder = Toplevel(Window_AccountInfo)
Window_PreparingOrder.withdraw()

SignIn_Email = StringVar()
SignIn_Password = StringVar()

SignUp_Email = StringVar()
SignUp_Password = StringVar()
SignUp_PasswordConfirm = StringVar()

AccountInfo_NewEmail = StringVar()
AccountInfo_NewPassword = StringVar()

HowManyWasTaken = StringVar()

MobilePhone = StringVar()

# --- БЛОК РАБОТЫ С БД ---
conn = sqlite3.connect("DataBase.db")  # Подключение к БД с именем DataBase.db
cursor = conn.cursor()
# --- БЛОК РАБОТЫ С БД ---


# --- БЛОК РАБОТЫ С GUI ---
def SignIn_ButtonToSignUp_Clicked():
    Window_SignIn.withdraw()
    Window_SignUp_PowerOn()

def SignIn_ButtonConfirm_Clicked():
    sql1 = f"SELECT * FROM ACCOUNTS WHERE email LIKE '{str(SignIn_Email.get())}'"
    cursor.execute(sql1)
    if cursor.fetchall():
        sql2 = f"SELECT password FROM ACCOUNTS WHERE email LIKE '{str(SignIn_Email.get())}'"
        cursor.execute(sql2)
        if str(SignIn_Password.get()) == cursor.fetchall()[0][0]:
            Window_SignIn.withdraw()
            Window_OnlineShop_PowerOn()
        else:
            messagebox.showinfo("Online Shop - Sign In", f"Incorrect password for this account!")
    else:
        messagebox.showinfo("Online Shop - Sign In", f"No email like {str(SignIn_Email.get())} in DB!")


def Window_SignIn_PowerOn():
    Window_SignIn.deiconify()
    Window_SignIn.geometry('1500x800')
    Window_SignIn.resizable(width=False, height=False)
    Window_SignIn["bg"] = "#98FB98"
    Window_SignIn.title("Online Shop - Sign In")

    SignIn_Lbl1 = Label(Window_SignIn, text="SIGN IN", font=("Arial Bold", 50), bg="#98FB98")
    SignIn_Lbl1.place(relx=0.5, rely=0.15, anchor="c")

    SignIn_Lbl2 = Label(Window_SignIn, text="Enter Email:", font=("Arial Bold", 36), bg="#98FB98")
    SignIn_Lbl2.place(relx=0.2, rely=0.3, anchor="c")

    SignIn_Lbl3 = Label(Window_SignIn, text="Enter Password:", font=("Arial Bold", 36), bg="#98FB98")
    SignIn_Lbl3.place(relx=0.17, rely=0.4, anchor="c")

    SignIn_EmailTxt = Entry(Window_SignIn, width=20, bd=5, font=("Arial Bold", 36), textvariable=SignIn_Email)
    SignIn_EmailTxt.place(relx=0.5, rely=0.3, anchor="c")

    SignIn_PasswordTxt = Entry(Window_SignIn, width=20, bd=5, font=("Arial Bold", 36), show='*',
                               textvariable=SignIn_Password)
    SignIn_PasswordTxt.place(relx=0.5, rely=0.4, anchor="c")

    SignIn_ButtonToSignUp = Button(Window_SignIn, text="Don't have account yet? Sign Up!", font=("Arial Bold", 8), bd=5,
                                   background="#3CB371", command=SignIn_ButtonToSignUp_Clicked)
    SignIn_ButtonToSignUp.place(relx=0.5, rely=0.5, anchor="c")

    SignIn_ButtonConfirm = Button(Window_SignIn, text="CONFIRM", font=("Arial Bold", 24), bd=10, background="#3CB371",
                                  command=SignIn_ButtonConfirm_Clicked)
    SignIn_ButtonConfirm.place(relx=0.5, rely=0.7, anchor="c")

    Window_SignIn.mainloop()


def SignUp_ButtonToSignIn_Clicked():
    Window_SignUp.withdraw()
    Window_SignIn_PowerOn()


def SignUp_ButtonConfirm_Clicked():
    if '@' in str(SignUp_Email.get()):
        if 7 < len((str(SignUp_Password.get()))) < 17:
            if str(SignUp_Password.get()) == str(SignUp_PasswordConfirm.get()):
                cursor.execute(f"""INSERT INTO ACCOUNTS VALUES ('{str(SignUp_Email.get())}', '{str(SignUp_Password.get())}')""")
                conn.commit()
                messagebox.showinfo("Online Shop - Sign Up", "Account created successfully and added to DB!")
                Window_SignUp.withdraw()
                Window_SignIn_PowerOn()
            else:
                messagebox.showinfo("Online Shop - Sign Up", f"Passwords do not match!")
        else:
            messagebox.showinfo("Online Shop - Sign Up", f"Password must be from 8 to 16 characters!")
    else:
        messagebox.showinfo("Online Shop - Sign Up", f"Entered email {str(SignUp_Email.get())} is not valid!")

def Window_SignUp_PowerOn():
    Window_SignUp.deiconify()
    Window_SignUp.geometry('1500x800')
    Window_SignUp.resizable(width=False, height=False)
    Window_SignUp["bg"] = "#DDA0DD"
    Window_SignUp.title("Online Shop - Sign Up")

    SignUp_Lbl1 = Label(Window_SignUp, text="SIGN UP", font=("Arial Bold", 50), bg="#DDA0DD")
    SignUp_Lbl1.place(relx=0.5, rely=0.1, anchor="c")

    SignUp_Lbl2 = Label(Window_SignUp, text="Enter Email:", font=("Arial Bold", 36), bg="#DDA0DD")
    SignUp_Lbl2.place(relx=0.2, rely=0.25, anchor="c")

    SignUp_Lbl3 = Label(Window_SignUp, text="Enter Password:", font=("Arial Bold", 36), bg="#DDA0DD")
    SignUp_Lbl3.place(relx=0.17, rely=0.35, anchor="c")

    SignUp_Lbl4 = Label(Window_SignUp, text="Confirm Password:", font=("Arial Bold", 36), bg="#DDA0DD")
    SignUp_Lbl4.place(relx=0.15, rely=0.45, anchor="c")

    SignUp_EmailTxt = Entry(Window_SignUp, width=20, bd=5, font=("Arial Bold", 36), textvariable=SignUp_Email)
    SignUp_EmailTxt.place(relx=0.5, rely=0.25, anchor="c")

    SignUp_PasswordTxt = Entry(Window_SignUp, width=20, bd=5, font=("Arial Bold", 36), show='*',
                               textvariable=SignUp_Password)
    SignUp_PasswordTxt.place(relx=0.5, rely=0.35, anchor="c")

    SignUp_PasswordConfirmTxt = Entry(Window_SignUp, width=20, bd=5, font=("Arial Bold", 36), show='*',
                                      textvariable=SignUp_PasswordConfirm)
    SignUp_PasswordConfirmTxt.place(relx=0.5, rely=0.45, anchor="c")

    SignUp_ButtonToSignIn = Button(Window_SignUp, text="Already have account? Sign In!", font=("Arial Bold", 8), bd=5,
                                   background="#DA70D6", command=SignUp_ButtonToSignIn_Clicked)
    SignUp_ButtonToSignIn.place(relx=0.5, rely=0.55, anchor="c")

    SignUp_ButtonConfirm = Button(Window_SignUp, text="CONFIRM", font=("Arial Bold", 24), bd=10, background="#DA70D6",
                                  command=SignUp_ButtonConfirm_Clicked)
    SignUp_ButtonConfirm.place(relx=0.5, rely=0.7, anchor="c")

    Window_SignUp.mainloop()


def OnlineShop_ButtonSignOut_Clicked():
    Window_OnlineShop.withdraw()
    Window_SignIn_PowerOn()

def OnlineShop_ButtonAccountInfo_Clicked():
    Window_OnlineShop.withdraw()
    Window_AccountInfo_PowerOn()

def OnlineShop_ButtonConfirmOrder_Clicked():
    Window_OnlineShop.withdraw()
    Window_PreParingOrder_PowerOn()

def OnlineShop_ButtonPreviousGood_Clicked():
    Window_OnlineShop.withdraw()
    global CurrentID
    CurrentID -= 1
    Window_OnlineShop_PowerOn()

def OnlineShop_ButtonNextGood_Clicked():
    Window_OnlineShop.withdraw()
    global CurrentID
    CurrentID += 1
    Window_OnlineShop_PowerOn()

def OnlineShop_ButtonTakeToBasket_Clicked():
    global CurrentID
    global CurrentName
    global CurrentPrice
    global CurrentGood
    global CurrentOrder
    CurrentGood[0] = CurrentID
    CurrentGood[1] = CurrentName
    CurrentGood[2] = CurrentPrice
    CurrentGood[3] = int(HowManyWasTaken.get())
    CurrentOrder.append(CurrentGood.copy())
    Window_OnlineShop.withdraw()
    Window_OnlineShop_PowerOn()

def Window_OnlineShop_PowerOn():
    Window_OnlineShop.deiconify()
    Window_OnlineShop.geometry('1500x800')
    Window_OnlineShop.resizable(width=False, height=False)
    Window_OnlineShop["bg"] = "#F0E68C"
    Window_OnlineShop.title("Online Shop - Catalog")

    cursor.execute("""SELECT COUNT(*) as count FROM GOODS""")
    GoodsWholeAmount = cursor.fetchall()[0][0]

    PreviousGoodButtonState = "normal"
    NextGoodButtonState = "normal"

    if CurrentID == 1:
        PreviousGoodButtonState = "disabled"
    if CurrentID == GoodsWholeAmount:
        NextGoodButtonState = "disabled"
    cursor.execute(f"""SELECT * FROM GOODS WHERE ID LIKE {CurrentID}""")
    GoodInfo = cursor.fetchall()[0]
    global CurrentName
    CurrentName = GoodInfo[1]
    global CurrentPrice
    CurrentPrice = GoodInfo[2]
    global CurrentAmount
    CurrentAmount = GoodInfo[3]

    TextForBasket = []
    global CurrentOrder
    k = 0
    for GoodSort in CurrentOrder:
        k += 1
        TextForBasket.append(str(k) + ") " + GoodSort[1] + " ( " + "ID = " + str(GoodSort[0]) + " ), " +
                             str(GoodSort[3]) + " items, whole price - " + str(GoodSort[2]*GoodSort[3]) + "$\n")

    OnlineShop_Lbl1 = Label(Window_OnlineShop, text="GOOD's SHOP", font=("Arial Bold", 50), bg="#F0E68C")
    OnlineShop_Lbl1.place(relx=0.2, rely=0.08, anchor="c")

    OnlineShop_ButtonAccountInfo = Button(Window_OnlineShop, text="ACCOUNT INFORMATION", font=("Arial Bold", 24), bd=10,
                                          background="#DAA520", command=OnlineShop_ButtonAccountInfo_Clicked)
    OnlineShop_ButtonAccountInfo.place(relx=0.65, rely=0.08, anchor="c")

    OnlineShop_ButtonSignOut = Button(Window_OnlineShop, text="SIGN OUT", font=("Arial Bold", 24), bd=10,
                                      background="#DAA520", command=OnlineShop_ButtonSignOut_Clicked)
    OnlineShop_ButtonSignOut.place(relx=0.9, rely=0.08, anchor="c")

    OnlineShop_Lb_ID = Label(Window_OnlineShop, text="Good's ID", font=("Arial Bold", 24), bg="#FFA500", padx=50,
                              pady=20, relief="solid")
    OnlineShop_Lb_ID.place(relx=0.1, rely=0.35, anchor="c")

    OnlineShop_Lb_ID_Value = Label(Window_OnlineShop, text=str(CurrentID), font=("Arial Bold", 12), bg="#F0E68C",
                                   padx=50, pady=20)
    OnlineShop_Lb_ID_Value.place(relx=0.1, rely=0.443, anchor="c")

    OnlineShop_Lb_Name = Label(Window_OnlineShop, text="Good's Name", font=("Arial Bold", 24), bg="#FFA500", padx=50,
                              pady=20, relief="solid")
    OnlineShop_Lb_Name.place(relx=0.28, rely=0.35, anchor="c")

    OnlineShop_Lb_Name_Value = Label(Window_OnlineShop, text=str(CurrentName), font=("Arial Bold", 12), bg="#F0E68C",
                                     padx=50, pady=20)
    OnlineShop_Lb_Name_Value.place(relx=0.28, rely=0.443, anchor="c")

    OnlineShop_Lb_Price = Label(Window_OnlineShop, text="Price", font=("Arial Bold", 24), bg="#FFA500", padx=50,
                              pady=20, relief="solid")
    OnlineShop_Lb_Price.place(relx=0.438, rely=0.35, anchor="c")

    OnlineShop_Lb_Price_Value = Label(Window_OnlineShop, text=str(CurrentPrice)+"$", font=("Arial Bold", 12),
                                      bg="#F0E68C", padx=50, pady=20)
    OnlineShop_Lb_Price_Value.place(relx=0.44, rely=0.443, anchor="c")

    OnlineShop_Lb_Amount = Label(Window_OnlineShop, text="Amount in stock", font=("Arial Bold", 24), bg="#FFA500",
                                 padx=50, pady=20, relief="solid")
    OnlineShop_Lb_Amount.place(relx=0.607, rely=0.35, anchor="c")

    OnlineShop_Lb_Amount_Value = Label(Window_OnlineShop, text=str(CurrentAmount), font=("Arial Bold", 12),
                                       bg="#F0E68C", padx=50, pady=20)
    OnlineShop_Lb_Amount_Value.place(relx=0.61, rely=0.443, anchor="c")

    OnlineShop_Lb_Take = Label(Window_OnlineShop, text="Take some?", font=("Arial Bold", 24), bg="#00BFFF",
                                 padx=50, pady=20, relief="solid")
    OnlineShop_Lb_Take.place(relx=0.85, rely=0.35, anchor="c")

    OnlineShop_SpinBox = Spinbox(Window_OnlineShop, from_=1, to=CurrentAmount, width=5, bg="#00FFFF", bd=10,
                                 textvariable=HowManyWasTaken)
    OnlineShop_SpinBox.place(relx=0.78, rely=0.45, anchor="c")

    OnlineShop_ButtonTakeToBasket = Button(Window_OnlineShop, text="TAKE TO BASKET", font=("Arial Bold", 12), bd=10,
                                          background="#00FFFF", command=OnlineShop_ButtonTakeToBasket_Clicked)
    OnlineShop_ButtonTakeToBasket.place(relx=0.88, rely=0.45, anchor="c")

    OnlineShop_ButtonConfirmOrder = Button(Window_OnlineShop, text="CONFIRM AND GO TO THE ORDER PREPARING",
                                           font=("Arial Bold", 24), bd=10, background="#DAA520",
                                           command=OnlineShop_ButtonConfirmOrder_Clicked)
    OnlineShop_ButtonConfirmOrder.place(relx=0.3, rely=0.9, anchor="c")

    OnlineShop_Lbl2 = Label(Window_OnlineShop, text="PREVIOUS GOOD", font=("Arial Bold", 36), bg="#F0E68C")
    OnlineShop_Lbl2.place(relx=0.15, rely=0.58, anchor="c")

    OnlineShop_Lbl3 = Label(Window_OnlineShop, text="NEXT GOOD", font=("Arial Bold", 36), bg="#F0E68C")
    OnlineShop_Lbl3.place(relx=0.45, rely=0.58, anchor="c")

    OnlineShop_ButtonPreviousGood = Button(Window_OnlineShop, text="<--", font=("Arial Bold", 40), bd=10,
                                           background="#BDB76B", state=PreviousGoodButtonState,
                                           command=OnlineShop_ButtonPreviousGood_Clicked)
    OnlineShop_ButtonPreviousGood.place(relx=0.15, rely=0.7, anchor="c")

    OnlineShop_ButtonNextGood = Button(Window_OnlineShop, text="-->", font=("Arial Bold", 40), bd=10,
                                           background="#BDB76B", state=NextGoodButtonState,
                                       command=OnlineShop_ButtonNextGood_Clicked)
    OnlineShop_ButtonNextGood.place(relx=0.45, rely=0.7, anchor="c")

    OnlineShop_Lbl_Basket = Label(Window_OnlineShop, text="BASKET:", font=("Arial Bold", 36), bg="#F0E68C")
    OnlineShop_Lbl_Basket.place(relx=0.8, rely=0.55, anchor="c")

    OnlineShop_BasketInfoTxt = Text(Window_OnlineShop, height=7, width=35, bd=5, font=("Times New Roman", 24))
    OnlineShop_BasketInfoTxt.place(relx=0.79, rely=0.77, anchor="c")

    for i in range(len(TextForBasket)):
        OnlineShop_BasketInfoTxt.insert(INSERT, TextForBasket[i])

    Window_OnlineShop.mainloop()


def AccountInfo_ButtonGoShopping_Clicked():
    Window_AccountInfo.withdraw()
    Window_OnlineShop_PowerOn()

def AccountInfo_ButtonSignOut_Clicked():
    Window_AccountInfo.withdraw()
    Window_SignIn_PowerOn()

def AccountInfo_ButtonConfirmNewEmail_Clicked():
    if '@' in str(AccountInfo_NewEmail.get()):
        sql = f"""UPDATE ACCOUNTS SET email = '{str(AccountInfo_NewEmail.get())}' WHERE email = '{str(SignIn_Email.get())}'"""
        cursor.execute(sql)
        conn.commit()
        messagebox.showinfo("Online Shop - Account Information",
                            "Email changed successfully! You need to sign in again.")
        Window_AccountInfo.withdraw()
        Window_SignIn_PowerOn()
    else:
        messagebox.showinfo("Online Shop - Sign Up", f"Entered email {str(AccountInfo_NewEmail.get())} is not valid!")

def AccountInfo_ButtonConfirmNewPassword_Clicked():
    if 7 < len((str(AccountInfo_NewPassword.get()))) < 17:
        sql = f"""UPDATE ACCOUNTS SET password = '{str(AccountInfo_NewPassword.get())}' WHERE email = '{str(SignIn_Email.get())}'"""
        cursor.execute(sql)
        conn.commit()
        messagebox.showinfo("Online Shop - Account Information",
                            "Password changed successfully! You need to sigh in again")
        Window_AccountInfo.withdraw()
        Window_SignIn_PowerOn()
    else:
        messagebox.showinfo("Online Shop - Sign Up", f"Password must be from 8 to 16 characters!")

def Chiphered_Password(size):
    return '*' * size

def Window_AccountInfo_PowerOn():
    Window_AccountInfo.deiconify()
    Window_AccountInfo.geometry('1500x800')
    Window_AccountInfo.resizable(width=False, height=False)
    Window_AccountInfo["bg"] = "#F08080"
    Window_AccountInfo.title("Online Shop - Account Information")

    AccountInfo_Lbl1 = Label(Window_AccountInfo, text="ACCOUNT INFORMATION", font=("Arial Bold", 50), bg="#F08080")
    AccountInfo_Lbl1.place(relx=0.3, rely=0.08, anchor="c")

    AccountInfo_ButtonGoShopping = Button(Window_AccountInfo, text="GO SHOPPING", font=("Arial Bold", 24), bd=10,
                                          background="#DC143C", command=AccountInfo_ButtonGoShopping_Clicked)
    AccountInfo_ButtonGoShopping.place(relx=0.7, rely=0.08, anchor="c")

    AccountInfo_ButtonSignOut = Button(Window_AccountInfo, text="SIGN OUT", font=("Arial Bold", 24), bd=10,
                                       background="#DC143C", command=AccountInfo_ButtonSignOut_Clicked)
    AccountInfo_ButtonSignOut.place(relx=0.9, rely=0.08, anchor="c")

    AccountInfo_Lbl2 = Label(Window_AccountInfo, text="Current EMAIL", font=("Arial Bold", 50), bg="#F08080")
    AccountInfo_Lbl2.place(relx=0.25, rely=0.3, anchor="c")

    AccountInfo_Lbl3 = Label(Window_AccountInfo, text="Current PASSWORD", font=("Arial Bold", 50), bg="#F08080")
    AccountInfo_Lbl3.place(relx=0.7, rely=0.3, anchor="c")

    AccountInfo_Lbl4 = Label(Window_AccountInfo, text=str(SignIn_Email.get()), font=("Arial Bold", 36), bg="#F08080")
    AccountInfo_Lbl4.place(relx=0.25, rely=0.4, anchor="c")

    AccountInfo_Lbl5 = Label(Window_AccountInfo, text=Chiphered_Password(len(str(SignIn_Password.get()))),
                             font=("Arial Bold", 36), bg="#F08080")
    AccountInfo_Lbl5.place(relx=0.7, rely=0.4, anchor="c")

    AccountInfo_Lbl6 = Label(Window_AccountInfo, text="Change EMAIL?", font=("Arial Bold", 50), bg="#F08080")
    AccountInfo_Lbl6.place(relx=0.25, rely=0.6, anchor="c")

    AccountInfo_Lbl7 = Label(Window_AccountInfo, text="Change PASSWORD?", font=("Arial Bold", 50), bg="#F08080")
    AccountInfo_Lbl7.place(relx=0.7, rely=0.6, anchor="c")

    AccountInfo_NewEmailTxt = Entry(Window_AccountInfo, width=20, bd=5, font=("Arial Bold", 36),
                                    textvariable=AccountInfo_NewEmail)
    AccountInfo_NewEmailTxt.place(relx=0.25, rely=0.7, anchor="c")

    AccountInfo_NewPasswordTxt = Entry(Window_AccountInfo, width=20, bd=5, font=("Arial Bold", 36), show='*',
                                       textvariable=AccountInfo_NewPassword)
    AccountInfo_NewPasswordTxt.place(relx=0.7, rely=0.7, anchor="c")

    AccountInfo_ButtonConfirmNewEmail = Button(Window_AccountInfo, text="CONFIRM", font=("Arial Bold", 24), bd=10,
                                               background="#DC143C", command=AccountInfo_ButtonConfirmNewEmail_Clicked)
    AccountInfo_ButtonConfirmNewEmail.place(relx=0.25, rely=0.85, anchor="c")

    AccountInfo_ButtonConfirmNewPassword = Button(Window_AccountInfo, text="CONFIRM", font=("Arial Bold", 24), bd=10,
                                                  background="#DC143C",
                                                  command=AccountInfo_ButtonConfirmNewPassword_Clicked)
    AccountInfo_ButtonConfirmNewPassword.place(relx=0.7, rely=0.85, anchor="c")

    Window_AccountInfo.mainloop()


def PreparingOrder_ButtonGoShopping_Clicked():
    Window_PreparingOrder.withdraw()
    Window_OnlineShop_PowerOn()

def PreparingOrder_ButtonSignOut_Clicked():
    Window_PreparingOrder.withdraw()
    Window_SignIn_PowerOn()

def PreparingOrder_ButtonConfirmOrder_Clicked():
    if '+' in str(MobilePhone.get()) and len(str(MobilePhone.get())) == 13:
        messagebox.showinfo("Online Shop - Preparing Order", "Order successfully prepared! We will contact you soon!")
        global CurrentOrder
        CurrentOrder = []
        global CurrentID
        CurrentID = 1
        Window_PreparingOrder.withdraw()
        Window_OnlineShop_PowerOn()
    else:
        messagebox.showinfo("Online Shop - Preparing Order", "Invalid mobile phone entered!")

def Window_PreParingOrder_PowerOn():
    Window_PreparingOrder.deiconify()
    Window_PreparingOrder.geometry('1500x800')
    Window_PreparingOrder.resizable(width=False, height=False)
    Window_PreparingOrder["bg"] = "#87CEFA"
    Window_PreparingOrder.title("Online Shop - Preparing Order")

    PreparingOrder_Lbl1 = Label(Window_PreparingOrder, text="PREPARING ORDER", font=("Arial Bold", 50), bg="#87CEFA")
    PreparingOrder_Lbl1.place(relx=0.25, rely=0.08, anchor="c")

    PreparingOrder_ButtonGoShopping = Button(Window_PreparingOrder, text="GO SHOPPING", font=("Arial Bold", 24), bd=10,
                                             background="#1E90FF", command=PreparingOrder_ButtonGoShopping_Clicked)
    PreparingOrder_ButtonGoShopping.place(relx=0.7, rely=0.08, anchor="c")

    PreparingOrder_ButtonSignOut = Button(Window_PreparingOrder, text="SIGN OUT", font=("Arial Bold", 24), bd=10,
                                          background="#1E90FF", command=PreparingOrder_ButtonSignOut_Clicked)
    PreparingOrder_ButtonSignOut.place(relx=0.9, rely=0.08, anchor="c")

    PreparingOrder_Lbl2 = Label(Window_PreparingOrder, text="YOUR ORDER:", font=("Arial Bold", 50), bg="#87CEFA")
    PreparingOrder_Lbl2.place(relx=0.17, rely=0.25, anchor="c")

    PreparingOrder_OrderInfoTxt = Text(Window_PreparingOrder, height=7, width=59, bd=5, font=("Times New Roman", 24))
    PreparingOrder_OrderInfoTxt.place(relx=0.66, rely=0.35, anchor="c")

    TextForBasket = []
    global CurrentOrder
    k = 0
    WholePrice = 0.0
    for GoodSort in CurrentOrder:
        k += 1
        WholePrice += GoodSort[2] * GoodSort[3]
        TextForBasket.append(str(k) + ") " + GoodSort[1] + " ( " + "ID = " + str(GoodSort[0]) + " ), " +
                             str(GoodSort[3]) + " items, whole price - " + str(GoodSort[2] * GoodSort[3]) + "$\n")

    TextForBasket.append("WHOLE SUM: " + str(WholePrice) + "$")

    for i in range(len(TextForBasket)):
        PreparingOrder_OrderInfoTxt.insert(INSERT, TextForBasket[i])

    PreparingOrder_Lbl3 = Label(Window_PreparingOrder, text="Indicate your contacts and we will accept your order:",
                                font=("Arial Bold", 36), bg="#87CEFA")
    PreparingOrder_Lbl3.place(relx=0.4, rely=0.6, anchor="c")

    PreparingOrder_Lbl4 = Label(Window_PreparingOrder, text="Mobile Phone:", font=("Arial Bold", 36), bg="#87CEFA")
    PreparingOrder_Lbl4.place(relx=0.2, rely=0.7, anchor="c")

    PreparingOrder_MobilePhoneTxt = Entry(Window_PreparingOrder, width=13, bd=5, font=("Arial Bold", 36),
                                textvariable=MobilePhone)
    PreparingOrder_MobilePhoneTxt.place(relx=0.438, rely=0.7, anchor="c")

    PreparingOrder_Lbl5 = Label(Window_PreparingOrder, text="Address:", font=("Arial Bold", 36), bg="#87CEFA")
    PreparingOrder_Lbl5.place(relx=0.238, rely=0.8, anchor="c")

    PreparingOrder_AddressTxt = Text(Window_PreparingOrder, height=3, width=60, bd=5, font=("Times New Roman", 24))
    PreparingOrder_AddressTxt.place(relx=0.64, rely=0.85, anchor="c")

    PreparingOrder_ButtonConfirmOrder = Button(Window_PreparingOrder, text="CONFIRM ORDER", font=("Arial Bold", 24),
                                               bd=10, background="#1E90FF",
                                               command=PreparingOrder_ButtonConfirmOrder_Clicked)
    PreparingOrder_ButtonConfirmOrder.place(relx=0.15, rely=0.92, anchor="c")

    Window_PreparingOrder.mainloop()
# --- БЛОК РАБОТЫ С GUI ---


Window_SignIn_PowerOn()  # Запуск со стартовой страницы
