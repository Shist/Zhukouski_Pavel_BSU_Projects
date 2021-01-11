from tkinter import *

Main_Form = Tk()
Main_Form.deiconify()
Main_Form.attributes('-fullscreen', True)
Main_Form.resizable(width=False, height=False)
Main_Form["bg"] = "#000000"
Main_Form.title("Hira, Happy Birthday To You!!!")

L_Sign = Label(Main_Form, text="Programmed for Hira by Shist, 14.11.2020", font=("Times New Roman", 18), fg="#808080", bg="#000000")
L_Sign.place(relx=0.135, rely=0.015, anchor="c")

L_H1 = Label(Main_Form, text="H", font=("Arial", 72), fg="#FF00FF", bg="#000000")
L_H1.place(relx=0.17, rely=0.2, anchor="c")

L_A1 = Label(Main_Form, text="A", font=("Arial", 72), fg="#FF0000", bg="#000000")
L_A1.place(relx=0.22, rely=0.2, anchor="c")

L_P1 = Label(Main_Form, text="P", font=("Arial", 72), fg="#FFFF00", bg="#000000")
L_P1.place(relx=0.27, rely=0.2, anchor="c")

L_P2 = Label(Main_Form, text="P", font=("Arial", 72), fg="#00FF00", bg="#000000")
L_P2.place(relx=0.32, rely=0.2, anchor="c")

L_Y1 = Label(Main_Form, text="Y", font=("Arial", 72), fg="#00FFFF", bg="#000000")
L_Y1.place(relx=0.37, rely=0.2, anchor="c")

L_B = Label(Main_Form, text="B", font=("Arial", 72), fg="#0000FF", bg="#000000")
L_B.place(relx=0.48, rely=0.2, anchor="c")

L_I1 = Label(Main_Form, text="I", font=("Arial", 72), fg="#FF00FF", bg="#000000")
L_I1.place(relx=0.53, rely=0.2, anchor="c")

L_R1 = Label(Main_Form, text="R", font=("Arial", 72), fg="#FF0000", bg="#000000")
L_R1.place(relx=0.58, rely=0.2, anchor="c")

L_T1 = Label(Main_Form, text="T", font=("Arial", 72), fg="#FFFF00", bg="#000000")
L_T1.place(relx=0.63, rely=0.2, anchor="c")

L_H2 = Label(Main_Form, text="H", font=("Arial", 72), fg="#00FF00", bg="#000000")
L_H2.place(relx=0.68, rely=0.2, anchor="c")

L_D = Label(Main_Form, text="D", font=("Arial", 72), fg="#00FFFF", bg="#000000")
L_D.place(relx=0.73, rely=0.2, anchor="c")

L_A2 = Label(Main_Form, text="A", font=("Arial", 72), fg="#0000FF", bg="#000000")
L_A2.place(relx=0.78, rely=0.2, anchor="c")

L_Y2 = Label(Main_Form, text="Y", font=("Arial", 72), fg="#FF00FF", bg="#000000")
L_Y2.place(relx=0.83, rely=0.2, anchor="c")

L_T2 = Label(Main_Form, text="T", font=("Arial", 72), fg="#FF0000", bg="#000000")
L_T2.place(relx=0.2, rely=0.35, anchor="c")

L_O1 = Label(Main_Form, text="O", font=("Arial", 72), fg="#FFFF00", bg="#000000")
L_O1.place(relx=0.25, rely=0.35, anchor="c")

L_Y3 = Label(Main_Form, text="Y", font=("Arial", 72), fg="#00FF00", bg="#000000")
L_Y3.place(relx=0.36, rely=0.35, anchor="c")

L_O2 = Label(Main_Form, text="O", font=("Arial", 72), fg="#00FFFF", bg="#000000")
L_O2.place(relx=0.41, rely=0.35, anchor="c")

L_U = Label(Main_Form, text="U", font=("Arial", 72), fg="#0000FF", bg="#000000")
L_U.place(relx=0.46, rely=0.35, anchor="c")

L_Comma = Label(Main_Form, text=",", font=("Arial", 72), fg="#FF00FF", bg="#000000")
L_Comma.place(relx=0.49, rely=0.35, anchor="c")

L_H3 = Label(Main_Form, text="H", font=("Arial", 72), fg="#FF0000", bg="#000000")
L_H3.place(relx=0.58, rely=0.35, anchor="c")

L_I2 = Label(Main_Form, text="I", font=("Arial", 72), fg="#FFFF00", bg="#000000")
L_I2.place(relx=0.63, rely=0.35, anchor="c")

L_R = Label(Main_Form, text="R", font=("Arial", 72), fg="#00FF00", bg="#000000")
L_R.place(relx=0.68, rely=0.35, anchor="c")

L_A3 = Label(Main_Form, text="A", font=("Arial", 72), fg="#00FFFF", bg="#000000")
L_A3.place(relx=0.73, rely=0.35, anchor="c")

L_EP1 = Label(Main_Form, text="!", font=("Arial", 72), fg="#0000FF", bg="#000000")
L_EP1.place(relx=0.77, rely=0.35, anchor="c")

L_EP2 = Label(Main_Form, text="!", font=("Arial", 72), fg="#FF00FF", bg="#000000")
L_EP2.place(relx=0.8, rely=0.35, anchor="c")

L_EP3 = Label(Main_Form, text="!", font=("Arial", 72), fg="#FF0000", bg="#000000")
L_EP3.place(relx=0.83, rely=0.35, anchor="c")

def B_Clicked():
    B['state'] = 'disabled'
    B.place_forget()
    L.place(relx=0.5, rely=0.65, anchor="c")

B = Button(Main_Form, text="CONGRATULATORY LETTER", font=("Times New Roman", 36), bd=70, background="#6A5ACD", command=B_Clicked)
B.place(relx=0.6, rely=0.7, anchor="c")

L = Label(Main_Form, text="And again 14th November has come, I continue wondering how quickly time flies. Traditionally,\n"
                          "I've prepared a small congratulatory program for you. I'd like to say some words as a\n"
                          "congratulation to you, Hira. You have achieved a lot of success both in study and in life,\n"
                          "I never cease to be amazed at you. Despite the difficult times, both in university and in the\n"
                          "world, I wish you to remain as cheerful and never give up. I'll make sure that my friends are\n"
                          "happy, and you're not exception, Hira, Happy Birthday To You!\n\n\t\t\t\t\t\t\t(c) Shist",
          font=("Arial", 24), fg="#6A5ACD", bg="#000000")

B_Exit = Button(Main_Form, text="EXIT", font=("Times New Roman", 24), bd=20, background="#C0C0C0", command=Main_Form.destroy)
B_Exit.place(relx=0.1, rely=0.9, anchor="c")

Main_Form.mainloop()