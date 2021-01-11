# Python program to translate
# speech to text and text to speech


import speech_recognition as sr
import pyttsx3
import pyaudio
from tkinter import *



# Initialize the recognizer
r = sr.Recognizer()


# Function to convert text to
# speech
def SpeakText(command):
    # Initialize the engine
    engine = pyttsx3.init()
    engine.say(command)
    engine.runAndWait()

flag = True

def Start_Button_Clicked():
    # Loop infinitely for user to
    # speak

    global flag
    if flag:
        Output.insert(INSERT,
                  "Welcome to alpha version of program that tries to convert your voice into the text...\n\n")
    flag = False

    # Exception handling to handle
    # exceptions at the runtime
    try:

        # use the microphone as source for input.
        with sr.Microphone() as source2:

            # wait for a second to let the recognizer
            # adjust the energy threshold based on
            # the surrounding noise level
            r.adjust_for_ambient_noise(source2, duration=0.2)

            # listens for the user's input
            audio2 = r.listen(source2, 5, 5)

            Output.insert(INSERT,
                          "Program\nOK, I got it, take me some time to translate with google translate on the net...\n\n")

            # Using google to recognize audio
            MyText = r.recognize_google(audio2)
            MyText = MyText.lower()

            Output.insert(INSERT, "Program\nI heard: \"" + MyText + "\"\n\n")
            SpeakText(MyText)

            Output.insert(INSERT,
                          "Program\nYou can speak again. Remember, you have only 5 seconds on fraze. Start with button \"Say\"\n\n")

    except sr.RequestError as e:
        Output.insert(INSERT, "Could not request results; {0}\n\n".format(e))
        Output.insert(INSERT,
                      "Program\nYou can speak again. Remember, you have only 5 seconds on fraze. Start with button \"Say\"\n\n")

    except sr.UnknownValueError:
        Output.insert(INSERT, "Unknown error occured. Please, check your Internet connection or say louder.\n\n")
        Output.insert(INSERT,
                      "Program\nYou can speak again. Remember, you have only 5 seconds on fraze. Start with button \"Say\".\n\n")

MainWindow = Tk()
MainWindow.withdraw()

Output = Text(MainWindow, height=20, width=85, bd=5, font=("Times New Roman", 24), wrap=NONE)
Output.place(relx=0.52, rely=0.5, anchor="c")

hor_scroll = Scrollbar(command=Output.xview, width=25, orient=HORIZONTAL)
hor_scroll.pack(side=BOTTOM, ipadx=0.1, ipady=0.8, fill=X)
hor_scroll.place(x=92, y=770, height=25, width=1375)
vert_scroll = Scrollbar(command=Output.yview, width=25, orient=VERTICAL)
vert_scroll.pack(side=RIGHT, ipadx=0.1, ipady=0.8, fill=Y)
vert_scroll.place(x=1470, y=34, height=733, width=25)

Output.config(xscrollcommand=hor_scroll.set, yscrollcommand=vert_scroll.set)

Start_Button = Button(MainWindow, text="Say", font=("Arial Bold", 18), bd=10,
                        background="#00BFFF", command=Start_Button_Clicked)
Start_Button.place(relx=0.031, rely=0.1, anchor="c")

MainWindow.deiconify()
MainWindow.geometry('1500x800')
MainWindow.resizable(width=False, height=False)
MainWindow["bg"] = "#87CEEB"
MainWindow.title("Проект \"Голос в строку\": альфа-версия")
MainWindow.mainloop()