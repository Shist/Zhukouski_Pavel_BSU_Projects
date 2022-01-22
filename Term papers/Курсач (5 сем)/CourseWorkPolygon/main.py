# Python program to translate
# speech to text and text to speech


import speech_recognition as sr
import pyttsx3
import pyaudio
from pulseapi import RobotPulse

import math

from pulseapi import RobotPulse, pose, position

from commands import ref

robot = RobotPulse("http://192.168.1.52:8081")

# Initialize the recognizer
r = sr.Recognizer()


# Function to convert text to
# speech
def SpeakText(command):
    # Initialize the engine
    engine = pyttsx3.init()
    engine.say(command)
    engine.runAndWait()


# Loop infinitely for user to
# speak
command_lst = []
if __name__ == '__main__':

    while True:

        # Exception handling to handle
        # exceptions at the runtime
        try:

            # use the microphone as source for input.
            with sr.Microphone() as source2:

                # wait for a second to let the recognizer
                # adjust the energy threshold based on
                # the surrounding noise level
                r.adjust_for_ambient_noise(source2, duration=0.2)

                print("Program\nYou can start speaking. You have only 10 seconds on fraze. Start...\n")

                # listens for the user's input
                audio2 = r.listen(source2, 10, 5)

                print("Program\nOK, I got it, take me some time to translate with google translate on the net...\n")

                # Using google to recognize audio
                MyText = r.recognize_google(audio2)
                MyText = MyText.lower()
                if "stop" in MyText:
                    ref["stop"]()
                elif "activate" in MyText:
                    ref["activate"]()
                elif "run" in command_lst and "square" in MyText:
                    command_lst = []
                    ref["circle"]()
                elif "run" in command_lst and "home" in MyText:
                    command_lst = []
                    ref["home"]()
                elif "start" in MyText:
                    command_lst.append("run")

                # Result = "Did you say " + str(MyText)
                print("Program\nI heard: \"" + MyText + "\"\n")
                # SpeakText(MyText)

        except sr.RequestError as e:
            print("Could not request results; {0}".format(e))

        except sr.UnknownValueError:
            print("unknown error occured")
