from mailmerge import MailMerge
import docx
import tkinter as tk
import tkinter.ttk as ttk
from tkinter import messagebox
from tkinter.filedialog import askopenfilename
from datetime import date
import random as rnd

LINE_SPACING_VALUES = [1, 1.15, 1.5, 2, 2.5, 3]

data = []
strings_amount_num = 0
sortFIOs_Reverse = False
sortNicks_Reverse = False
sortDates_Reverse = False
sortFinances_Reverse = False
word_file_name = ""

headings = ('ФИО', 'Кличка', 'Дата Рождения', 'Финансовый вклад (бел. руб.)')

RandomFIOs = ['Анисимов Соломон Авксентьевич', 'Кононов Виктор Валерьевич', 'Куликова Злата Георгиевна',
              'Горбачев Рудольф Арсениевич', 'Маркова Станислава Ивановна', 'Веселова Роза Ивановна',
              'Тимофеев Севастьян Ярославович', 'Семёнова Христина Тихоновна', 'Тарасов Леонтий Юрьевич',
              'Жданов Иван Данилович', 'Михеев Бронислав Алексеевич', 'Крылова Эдда Аркадьевна',
              'Михеев Бронислав Алексеевич', 'Крылова Эдда Аркадьевна', 'Комаров Тарас Куприянович',
              'Бобров Роман Данилович', 'Крылов Иван Парфениевич', 'Щукина Аурелиа Федосеевна',
              'Бондарев Сергей Даниилович', 'Осипова Ева Егоровна', 'Сазонов Демид Иванович', 'Морозов Дмитрий Михайлович',
              'Быков Степан Михайлович', 'Воробьева Анна Максимовна', 'Бирюкова София Львовна',
              'Никитин Семён Владимирович', 'Сергеев Захар Вячеславович', 'Соколов Тимур Иванович',
              'Емельянова Арина Львовна', 'Москвина Анна Матвеевна', 'Зотов Савва Арсентьевич', 'Сергеев Андрей Сергеевич',
              'Лобанов Александр Никитич', 'Смирнова Малика Адамовна', 'Мельников Максим Кириллович', 'Маслова Мария Георгиевна',
              'Карпов Михаил Матвеевич', 'Прохорова Ясмина Алиевна', 'Иванова Екатерина Егоровна', 'Тарасов Лука Алексеевич',
              'Морозова Василиса Святославовна', 'Давыдов Никита Михайлович', 'Гончарова Анастасия Никитична']
RandomFIOs_size = len(RandomFIOs)

RandomNicks = ['Peiascite', 'Cenna', 'Etestrial', 'Onst', 'Non', 'Tahamari', 'Ziche', 'Cel', 'Akannylar', 'Anerim',
               'Pto', 'Aberi', 'Thi', 'Avicthe', 'Vero', 'Filu', 'Rialent', 'Longi', 'Chistua', 'Menolobante',
               'PhilporusCh', 'Trema', 'Chro', 'OpaloP', 'Shakb', 'Glayi', 'Phre', 'Ubiqc', 'KilN', 'Evange',
               'Bedsw', 'BipPo', 'Dinoth', 'Adeno', 'Ebur', 'Preda', 'Nicot', 'Paron', 'Apor', 'Fovil']
RandomNicks_size = len(RandomNicks)

RandomDates = ['02.05.1984', '11.05.1987', '19.08.1988', '12.09.1988', '26.02.1990', '26.01.1992', '02.09.1995',
               '09.10.1995', '12.11.1997', '09.01.1998', '25.02.2001', '01.10.1983', '27.09.1984', '05.05.1986',
               '06.04.1988', '10.07.1992', '10.09.1996', '21.10.1958', '13.09.1962', '13.04.1963', '27.05.1983',
               '13.12.2007', '11.12.1959', '13.02.1984', '19.12.1988', '19.07.1993', '24.06.1997', '23.01.1956',
               '14.03.1972', '07.09.1982', '08.12.2000', '18.06.2010', '17.03.1975', '16.01.1976', '09.12.1984',
               '10.02.1992', '27.11.2005', '17.04.1958', '22.08.1964', '12.08.1974', '11.05.1977', '10.10.1987']
RandomDates_size = len(RandomDates)

RandomFinances = ['5', '8', '35', '20', '25', '30', '135', '40', '45', '230', '55', '60', '185', '70', '75', '291', '85']
RandomFinances_size = len(RandomFinances)

DATA_LIMIT = min(RandomFIOs_size, RandomNicks_size, RandomDates_size, RandomFinances_size)

MainWindow = tk.Tk()
MainWindow.title("Жуковский Павел Сергеевич, 2021 год, 3 курс, 12 группа")
MainWindow.attributes("-fullscreen", True)
MainWindow["bg"] = "#FFDEAD"

StringsNum_Info = tk.StringVar()
TeamName_Info = tk.StringVar()
LeaderFIO_Info = tk.StringVar()
LeaderPhone_Info = tk.StringVar()
LeaderBirthDate_Info = tk.StringVar()
ChosenFile = ""

def isInt(s):
    try:
        int(s)
        return True
    except ValueError:
        return False

def GenerateBtn_Clicked():
    strings_amount_Str = StringsNum_Info.get()
    if strings_amount_Str:
        if isInt(strings_amount_Str):
            global strings_amount_num
            strings_amount_num = int(strings_amount_Str)
            if strings_amount_num >= 0:
                if strings_amount_num != 0:
                    for row in table.get_children():
                        table.delete(row)
                    global data
                    data = []
                    for i in range(strings_amount_num):
                        one_str_data = [rnd.choice(RandomFIOs), rnd.choice(RandomNicks), rnd.choice(RandomDates), rnd.choice(RandomFinances)]
                        data.append(one_str_data)
                    for str in data:
                        table.insert('', tk.END, values=tuple(str))
                else:
                    messagebox.showerror("Ошибка ввода количества строк", "Количество строк в таблице не может быть нулевым!")
            else:
                messagebox.showerror("Ошибка ввода количества строк", "Вы ввели отрицательное количество строк!")
        else:
            messagebox.showerror("Ошибка ввода количества строк", "Вы ввели не целое число!")
    else:
        messagebox.showerror("Ошибка ввода количества строк", "Вы ничего не ввели!")

def SortFIOsBtn_Clicked():
    global data
    global sortFIOs_Reverse
    global sortNicks_Reverse
    global sortDates_Reverse
    global sortFinances_Reverse
    if not sortFIOs_Reverse:
        data.sort()
        sortFIOs_Reverse = True
    else:
        data.sort(reverse=True)
        sortFIOs_Reverse = False
    for row in table.get_children():
        table.delete(row)
    for str in data:
        table.insert('', tk.END, values=tuple(str))
    sortNicks_Reverse = False
    sortDates_Reverse = False
    sortFinances_Reverse = False

def SortByNicks(one_str_data):
    return one_str_data[1]

def SortNicksBtn_Clicked():
    global data
    global sortFIOs_Reverse
    global sortNicks_Reverse
    global sortDates_Reverse
    global sortFinances_Reverse
    if not sortNicks_Reverse:
        data.sort(key=SortByNicks)
        sortNicks_Reverse = True
    else:
        data.sort(key=SortByNicks, reverse=True)
        sortNicks_Reverse = False
    for row in table.get_children():
        table.delete(row)
    for str in data:
        table.insert('', tk.END, values=tuple(str))
    sortFIOs_Reverse = False
    sortDates_Reverse = False
    sortFinances_Reverse = False

def SortByDates(one_str_data):
    curr_date = one_str_data[2].split('.')[::-1]
    return date(int(curr_date[0]), int(curr_date[1]), int(curr_date[2]))

def SortDatesBtn_Clicked():
    global data
    global sortFIOs_Reverse
    global sortNicks_Reverse
    global sortDates_Reverse
    global sortFinances_Reverse
    if not sortDates_Reverse:
        data.sort(key=SortByDates)
        sortDates_Reverse = True
    else:
        data.sort(key=SortByDates, reverse=True)
        sortDates_Reverse = False
    for row in table.get_children():
        table.delete(row)
    for str in data:
        table.insert('', tk.END, values=tuple(str))
    sortFIOs_Reverse = False
    sortNicks_Reverse = False
    sortFinances_Reverse = False

def SortByFinances(one_str_data):
    return int(one_str_data[3])

def SortFinancesBtn_Clicked():
    global data
    global sortFIOs_Reverse
    global sortNicks_Reverse
    global sortDates_Reverse
    global sortFinances_Reverse
    if not sortFinances_Reverse:
        data.sort(key=SortByFinances)
        sortFinances_Reverse = True
    else:
        data.sort(key=SortByFinances, reverse=True)
        sortFinances_Reverse = False
    for row in table.get_children():
        table.delete(row)
    for str in data:
        table.insert('', tk.END, values=tuple(str))
    sortFIOs_Reverse = False
    sortNicks_Reverse = False
    sortDates_Reverse = False

def ChooseTemplateBtn_Clicked():
    global word_file_name
    global ChosenFile
    word_file_name = askopenfilename()
    if word_file_name.endswith('docx'):
        Lbl_ChosenFileInfo.config(text="Выбранный файл шаблона: " + word_file_name)
    else:
        messagebox.showerror("Ошибка выбора файла шаблона", "Вы нажали отмену либо выбрали какой-то файл, но это не файл шаблона!")

def CheckTeamName(str):
    if str == "":
        messagebox.showerror("Ошибка ввода имени команды", "Имя команды не может быть пустым!")
    else:
        return True
    return False

def CheckLeaderFIO(str):
    if str == "":
        messagebox.showerror("Ошибка ввода ФИО главы команды", "ФИО главы команды не может быть пустым!")
    else:
        if str.count(' ') != 2:
            messagebox.showerror("Ошибка ввода ФИО главы команды", "ФИО главы команды должно состоять из трёх слов!")
        else:
            str_without_spaces = str.replace(' ', '')
            if str_without_spaces.isalpha():
                uppers_amount = [l for l in str if l.isupper()]
                words = str.split(' ')
                if len(uppers_amount) == 3 and words[0][0].isupper() and words[1][0].isupper() and words[2][0].isupper():
                    return True
                else:
                    messagebox.showerror("Ошибка ввода ФИО главы команды",
                                     "Каждое из трёх слов ФИО должно начинаться с большой буквы!")
            else:
                messagebox.showerror("Ошибка ввода ФИО главы команды",
                                     "В ФИО могут быть использованы только буквы!")
    return False

def CheckLeaderPhone(str):
    if str == "":
        messagebox.showerror("Ошибка ввода мобильного телефона главы команды", "Мобильный телефон главы команды не может быть пустым!")
    else:
        if (str.replace('+', '')).isdigit():
            return True
        else:
            messagebox.showerror("Ошибка ввода мобильного телефона главы команды",
                                 "Мобильный телефон введён некорректно!")
    return False

def CheckLeaderBirthDate(str):
    try:
        curr_date = str.split('.')[::-1]
        date_check = date(int(curr_date[0]), int(curr_date[1]), int(curr_date[2]))
        return True
    except ValueError:
        messagebox.showerror("Ошибка ввода даты рождения главы команды",
                             "Дата рождения введена некорректно!")

def CreateDocBtn_Clicked():
    global data
    global word_file_name
    global TeamName_Info
    global LeaderFIO_Info
    global LeaderPhone_Info
    global LeaderBirthDate_Info
    if word_file_name.endswith('docx'):
        if CheckTeamName(TeamName_Info.get()):
            if CheckLeaderFIO(LeaderFIO_Info.get()):
                if CheckLeaderPhone(LeaderPhone_Info.get()):
                    if CheckLeaderBirthDate(LeaderBirthDate_Info.get()):

                        template_doc = MailMerge(word_file_name)

                        team_name = TeamName_Info.get()
                        leader_FIO = LeaderFIO_Info.get()
                        leader_phone = LeaderPhone_Info.get()
                        leader_birthdate = LeaderBirthDate_Info.get()

                        template_doc.merge(
                            TeamName=team_name,
                            LeaderFIO=leader_FIO,
                            LeaderPhone=leader_phone,
                            LeaderBirthdate=leader_birthdate
                        )

                        # list of data that will be substituted into the word template.
                        data_word_list = []

                        # Populating the list with data.
                        for row in data:
                            data_word_list.append(
                                {
                                    'FIO': row[0],
                                    'Nick': row[1],
                                    'Birthdate': row[2],
                                    'Finances': row[3],
                                },
                            )

                        template_doc.merge_rows('FIO', data_word_list)

                        template_doc.write('Result.docx')

                        template_doc.close()

                        new_doc = docx.Document('Result.docx')

                        new_doc.add_picture('python.png')

                        new_doc.save('Result.docx')

                        import os
                        os.system('start Result.docx')
    else:
        messagebox.showerror("Ошибка выбора файла шаблона", "Вы не выбрали файл шаблона!")

Lbl_FIO = tk.Label(MainWindow, text="Жуковский Павел Сергеевич, 3 курс, 12 группа, 2021 год",
                            font=("Arial Bold", 18), bg="#FFDEAD")
Lbl_FIO.place(relx=0.21, rely=0.02, anchor="c")

Lbl_EnterStrNum = tk.Label(MainWindow, text="Количество строк таблицы:", font=("Arial Bold", 28), bg="#FFDEAD")
Lbl_EnterStrNum.place(relx=0.19, rely=0.07, anchor="c")

TxtEdit_EnterStrNum = tk.Entry(MainWindow, width=10, bd=5, font=("Arial Bold", 28), textvariable=StringsNum_Info)
TxtEdit_EnterStrNum.place(relx=0.19, rely=0.15, anchor="c")

Btn_Generate = tk.Button(MainWindow, text="Сгенерировать таблицу", font=("Arial Bold", 28), bd=10,
                        background="#CC9B00", command=GenerateBtn_Clicked, width=20)
Btn_Generate.place(relx=0.19, rely=0.27, anchor="c")

Btn_SortFIO = tk.Button(MainWindow, text="Сортировать по ФИО", font=("Arial Bold", 28), bd=10,
                        background="#CC9B00", command=SortFIOsBtn_Clicked, width=20)
Btn_SortFIO.place(relx=0.19, rely=0.43, anchor="c")

Btn_SortNick = tk.Button(MainWindow, text="Сортировать по кличке", font=("Arial Bold", 28), bd=10,
                        background="#CC9B00", command=SortNicksBtn_Clicked, width=20)
Btn_SortNick.place(relx=0.19, rely=0.54, anchor="c")

Btn_SortDate = tk.Button(MainWindow, text="Сортировать по дате", font=("Arial Bold", 28), bd=10,
                        background="#CC9B00", command=SortDatesBtn_Clicked, width=20)
Btn_SortDate.place(relx=0.19, rely=0.65, anchor="c")

Btn_SortFinances = tk.Button(MainWindow, text="Сортировать по вкладу", font=("Arial Bold", 28), bd=10,
                        background="#CC9B00", command=SortFinancesBtn_Clicked, width=20)
Btn_SortFinances.place(relx=0.19, rely=0.76, anchor="c")

Btn_Exit = tk.Button(MainWindow, text="Выход", font=("Arial Bold", 28), bd=10,
                        background="#CC9B00", command=MainWindow.quit, width=20)
Btn_Exit.place(relx=0.19, rely=0.925, anchor="c")

Lbl_Project_Name = tk.Label(MainWindow, text="Участники командного конкурса", font=("Arial Bold", 36), bg="#FFDEAD")
Lbl_Project_Name.place(relx=0.7, rely=0.04, anchor="c")

Lbl_Team_Name = tk.Label(MainWindow, text="Название команды:", font=("Arial Bold", 18), bg="#FFDEAD")
Lbl_Team_Name.place(relx=0.572, rely=0.12, anchor="c")

TxtEdit_EnterTeamName = tk.Entry(MainWindow, width=34, bd=5, font=("Arial Bold", 20), textvariable=TeamName_Info)
TxtEdit_EnterTeamName.place(relx=0.82, rely=0.12, anchor="c")

Lbl_Leader_FIO = tk.Label(MainWindow, text="ФИО главы команды:", font=("Arial Bold", 18), bg="#FFDEAD")
Lbl_Leader_FIO.place(relx=0.5655, rely=0.2, anchor="c")

TxtEdit_EnterLeaderFIO = tk.Entry(MainWindow, width=34, bd=5, font=("Arial Bold", 20), textvariable=LeaderFIO_Info)
TxtEdit_EnterLeaderFIO.place(relx=0.82, rely=0.2, anchor="c")

Lbl_Leader_Telephone = tk.Label(MainWindow, text="Мобильный телефон главы команды:", font=("Arial Bold", 18), bg="#FFDEAD")
Lbl_Leader_Telephone.place(relx=0.508, rely=0.28, anchor="c")

TxtEdit_EnterLeaderPhone = tk.Entry(MainWindow, width=34, bd=5, font=("Arial Bold", 20), textvariable=LeaderPhone_Info)
TxtEdit_EnterLeaderPhone.place(relx=0.82, rely=0.28, anchor="c")

Lbl_Leader_BirthDate = tk.Label(MainWindow, text="Дата рождения главы команды:", font=("Arial Bold", 18), bg="#FFDEAD")
Lbl_Leader_BirthDate.place(relx=0.53, rely=0.36, anchor="c")

TxtEdit_EnterLeaderBirthDate = tk.Entry(MainWindow, width=10, bd=5, font=("Arial Bold", 20), textvariable=LeaderBirthDate_Info)
TxtEdit_EnterLeaderBirthDate.place(relx=0.703, rely=0.36, anchor="c")

Lbl_Leader_BirthDate_Format = tk.Label(MainWindow, text="(Формат даты: ДД.ММ.ГГГГ)", font=("Arial Bold", 18), bg="#FFDEAD")
Lbl_Leader_BirthDate_Format.place(relx=0.87, rely=0.36, anchor="c")

table = ttk.Treeview(MainWindow, height=15, show="headings", selectmode="browse")
table["columns"] = headings
table["displaycolumns"] = headings
table.heading(headings[0], text=headings[0], anchor=tk.W)
table.column(headings[0], width=400, anchor=tk.W)
table.heading(headings[1], text=headings[1], anchor=tk.W)
table.column(headings[1], width=150, anchor=tk.W)
table.heading(headings[2], text=headings[2], anchor=tk.CENTER)
table.column(headings[2], width=150, anchor=tk.CENTER)
table.heading(headings[3], text=headings[3], anchor=tk.E)
table.column(headings[3], width=180, anchor=tk.E)
table.column('#' + str(0), minwidth=700, stretch=0)
table.column('#' + str(1), minwidth=200, stretch=0)
table.column('#' + str(2), minwidth=300, stretch=0)
table.column('#' + str(3), minwidth=400, stretch=0)

table_scroll = tk.Scrollbar(MainWindow, command=table.yview)
table.configure(yscrollcommand=table_scroll.set)
table_scroll.place(relx=0.975, rely=0.43, height=328, width=25)
table.place(relx=0.4, rely=0.43)

Lbl_ChosenFileInfo = tk.Label(MainWindow, text="Выбранный файл шаблона: (пока не выбран)", font=("Arial Bold", 18), bg="#FFDEAD")
Lbl_ChosenFileInfo.place(relx=0.5, rely=0.84, anchor="c")

Btn_ChooseTemplate = tk.Button(MainWindow, text="Выбрать шаблон", font=("Arial Bold", 28), bd=15,
                        background="#CC9B00", command=ChooseTemplateBtn_Clicked, width=19)
Btn_ChooseTemplate.place(relx=0.545, rely=0.925, anchor="c")

Btn_ChooseTemplate = tk.Button(MainWindow, text="Создать документ", font=("Arial Bold", 28), bd=15,
                        background="#CC9B00", command=CreateDocBtn_Clicked, width=19)
Btn_ChooseTemplate.place(relx=0.845, rely=0.925, anchor="c")

MainWindow.mainloop()
