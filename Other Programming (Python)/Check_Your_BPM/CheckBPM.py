from tkinter import *
import time

StartTime = time.time()
StartFlag = True

Taps_Count = 0

Main_Form = Tk()
Main_Form.deiconify()
Main_Form.geometry('450x300')
Main_Form.resizable(width=False, height=False)
Main_Form["bg"] = "#000000"
Main_Form.title("Check your BPM")

BPM_Value = StringVar(Main_Form, value="0")

Z_Start = False
X_Start = False

def entry_Z(event):
    global Z_Start
    global X_Start
    if not Z_Start:
        Button_Clicked()
        X.config(relief=RAISED)
        Z.config(relief=SUNKEN)
        Z_Start = True
        X_Start = False

def entry_X(event):
    global Z_Start
    global X_Start
    if not X_Start:
        Button_Clicked()
        Z.config(relief=RAISED)
        X.config(relief=SUNKEN)
        X_Start = True
        Z_Start = False

def Button_Clicked():
    global StartTime
    global StartFlag
    global Taps_Count
    if StartFlag:
        StartTime = time.time()
        time.sleep(1e-100)
        StartFlag = False
    Taps_Count += 1
    BPM_Entry.config(state=NORMAL)
    BPM_Entry.delete(0, END)
    BPM_Entry.insert(0, str(int(60.0 * (Taps_Count / float(time.time() - StartTime)))))
    BPM_Entry.update()
    BPM_Entry.config(state="readonly")

def Retry():
    global StartFlag
    global Taps_Count
    StartFlag = True
    Taps_Count = 0
    BPM_Entry.config(state=NORMAL)
    BPM_Entry.delete(0, END)
    BPM_Entry.insert(0, "0")
    BPM_Entry.update()
    BPM_Entry.config(state="readonly")
    X.config(relief=RAISED)
    Z.config(relief=RAISED)

BPM_Entry = Entry(Main_Form, width=4, bd=7, font=("Arial Bold", 36), textvariable=BPM_Value, state="readonly")
BPM_Entry.place(relx=0.25, rely=0.25, anchor="c")

BPM_Label = Label(Main_Form, text="BPM (1/1)", font=("Arial Bold", 24), bg="#000000", fg="#8A2BE2")
BPM_Label.place(relx=0.73, rely=0.22, anchor="c")

Z = Button(Main_Form, text="Z", font=("Arial Bold", 24), bd=10, background="#8A2BE2", command=Button_Clicked, state=DISABLED)
Z.place(relx=0.15, rely=0.75, anchor="c")
Main_Form.bind('<z>', entry_Z)
Main_Form.bind('<Z>', entry_Z)

X = Button(Main_Form, text="X", font=("Arial Bold", 24), bd=10, background="#8A2BE2", command=Button_Clicked, state=DISABLED)
X.place(relx=0.4, rely=0.75, anchor="c")
Main_Form.bind('<x>', entry_X)
Main_Form.bind('<X>', entry_X)

RetryButton = Button(Main_Form, text="Retry", font=("Arial Bold", 14), bd=10, background="#4B0082", command=Retry,
                     height=1, width=8, activebackground="#9370DB", activeforeground="#FFFFFF")
RetryButton.place(relx=0.8, rely=0.55, anchor="c")

CloseButton = Button(Main_Form, text="Exit", font=("Arial Bold", 14), bd=10, background="#4B0082", command=Main_Form.destroy,
                     height=1, width=8, activebackground="#9370DB", activeforeground="#FFFFFF")
CloseButton.place(relx=0.8, rely=0.85, anchor="c")

Main_Form.mainloop()