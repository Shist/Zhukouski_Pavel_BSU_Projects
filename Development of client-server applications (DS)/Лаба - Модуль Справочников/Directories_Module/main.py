import tkinter as tk
import tkinter.ttk as ttk
from tkinter import messagebox
import pymysql
from tkcalendar import DateEntry

DB = pymysql.connect(host='localhost',
                     user='root',
                     password='2051868',
                     db='projects_competition')

cur = DB.cursor()  # Курсор по БД-шке

projects_headings = ('Название проекта', 'ФИО лидера', 'Дата создания', 'Число разработчиков',
                     'Инвестиции (бел. руб.)', 'Описание')
developers_headings = ('ФИО разработчика', 'Дата рождения', 'Решённых задач', 'Рейтинг', 'Описание')

MainWindow = tk.Tk()
MainWindow.title("Жуковский Павел Сергеевич, 2021 год, 3 курс, 12 группа")
MainWindow.attributes("-fullscreen", True)
MainWindow["bg"] = "#DDA0DD"

ProjectsList = []
DevsList = []

operation_state = "none"

def UpdateProjectsList():
    global ProjectsList
    ProjectsList = []
    cur.execute("SELECT * FROM projects")
    query_result = cur.fetchall()
    for pr in query_result:
        ProjectsList.append(pr[1])
    ProjectsList.sort()

def UpdateDevelopersList():
    global DevsList
    DevsList = []
    cur.execute("SELECT * FROM developers")
    query_result = cur.fetchall()
    for dev in query_result:
        DevsList.append(dev[1])
    DevsList.sort()

UpdateProjectsList()
UpdateDevelopersList()

Var_OutputMenu = tk.StringVar(MainWindow)
Var_OutputMenu.set("Выбрать справочник")

Var_Edit_ProjectName_or_DevName = tk.StringVar(MainWindow)
Var_OutputMenu_Projects_or_Devs = tk.StringVar(MainWindow)
Var_Edit_Chosen_ProjectCreationDate_or_DevBirthDate = tk.StringVar(MainWindow)
Var_Edit_ProjectCreationDate_or_DevBirthDate = tk.StringVar(MainWindow)
Var_Edit_ProjectDevsAmount_or_DevSolvedPrCount = tk.StringVar(MainWindow)
Var_Edit_ProjectInvests_or_DevRating = tk.StringVar(MainWindow)

Var_Edit_LeaderFIO = tk.StringVar(MainWindow)
Var_OutputMenu_Devs = tk.StringVar(MainWindow)

def CheckProjectName(str):
    if str == "":
        messagebox.showerror("Ошибка ввода названия проекта", "Название проекта не может быть пустым!")
    else:
        if "Выбрать проект для" in str:
            messagebox.showerror("Ошибка ввода имени проекта", "Проект не может быть с таким дурацким именем!")
            return False
        cur.execute('SELECT EXISTS(SELECT * FROM projects WHERE prName = %s)', str)
        exist_or_not = cur.fetchall()[0][0]
        if exist_or_not == 1:
            messagebox.showerror("Ошибка ввода имени проекта", "Проект с таким именем уже есть в базе данных!")
            return False
        return True
    return False

def CheckIfProjectChosen(str):
    if "Выбрать проект для" in str:
        messagebox.showerror("Ошибка выбора проекта", "Вы не выбрали проект!")
    else:
        return True
    return False

def CheckLeaderFIOName(str):
    if str == "Выбрать лидера проекта":
        messagebox.showerror("Ошибка ввода ФИО лидера проекта", "Вы не выбрали ФИО лидера проекта!")
    else:
        return True
    return False

def CheckProjectCrDate(str):
    if str == "":
        messagebox.showerror("Ошибка выбора даты создания проекта", "Вы не выбрали дату создания проекта!")
    else:
        return True
    return False

def CheckDevsAmount(str):
    try:
        devs_num = int(str)
        if devs_num < 1:
            messagebox.showerror("Ошибка ввода числа разработчиков", "Вы ввели не положительное число разработчиков!")
            return False
        return True
    except ValueError:
        messagebox.showerror("Ошибка ввода числа разработчиков", "Вы ввели не целое число разработчиков!")
        return False

def CheckInvests(str):
    try:
        invests = float(str)
        if invests < 0.0:
            messagebox.showerror("Ошибка ввода инвестиций", "Вы ввели отрицательное значение инвестиций!")
            return False
        return True
    except ValueError:
        messagebox.showerror("Ошибка ввода инвестиций", "В поле для инвестиций вы ввели не число!")
        return False

def CheckDevName(str):
    if str == "":
        messagebox.showerror("Ошибка ввода ФИО разработчика", "ФИО разработчика не может быть пустым!")
    else:
        if str.count(' ') != 1 and str.count(' ') != 2:
            messagebox.showerror("Ошибка ввода ФИО разработчика", "ФИО разработчика должно состоять из двух или трёх слов!")
        else:
            str_without_spaces = str.replace(' ', '')
            if str_without_spaces.isalpha():
                words = str.split(' ')
                for word in words:
                    if not word[0].isupper():
                        messagebox.showerror("Ошибка ввода ФИО разработчика",
                                             "Каждое из двух или трёх слов ФИО разработчика должно начинаться с большой буквы!")
                        return False
                cur.execute('SELECT EXISTS(SELECT * FROM developers WHERE devFIO = %s)', str)
                exist_or_not = cur.fetchall()[0][0]
                if exist_or_not == 1:
                    messagebox.showerror("Ошибка ввода имени разработчика",
                                         "Разработчик с таким ФИО уже есть в базе данных!")
                    return False
                return True
            else:
                messagebox.showerror("Ошибка ввода ФИО разработчика",
                                     "В ФИО разработчика могут быть использованы только буквы!")
    return False

def CheckIfDevChosen(str):
    if "Выбрать разработчика для" in str:
        messagebox.showerror("Ошибка выбора разработчика", "Вы не выбрали разработчика!")
    else:
        return True
    return False

def CheckDevBirthDate(str):
    if str == "":
        messagebox.showerror("Ошибка выбора даты рождения", "Вы не выбрали дату рождения разработчика!")
    else:
        return True
    return False

def CheckDevSolvedPrCount(str):
    try:
        tasks_num = int(str)
        if tasks_num < 1:
            messagebox.showerror("Ошибка ввода числа решённых задач разработчика", "Вы ввели не положительное число решённых задач!")
            return False
        return True
    except ValueError:
        messagebox.showerror("Ошибка ввода числа решённых задач разработчика", "Вы ввели не целое число решённых задач!")
        return False

def CheckDevRating(str):
    try:
        rating = float(str)
        if rating < 0.0:
            messagebox.showerror("Ошибка ввода рейтинга", "Вы ввели отрицательное значение рейтинга разработчика!")
            return False
        if rating > 10.0:
            messagebox.showerror("Ошибка ввода рейтинга", "Вы ввели значение рейтинга, превышающее максимальное! (> 10.0)")
            return False
        return True
    except ValueError:
        messagebox.showerror("Ошибка ввода рейтинга", "В поле для рейтинга разработчика вы ввели не число!")
        return False

def Select_Data():
    if Var_OutputMenu.get() == "Проекты":
        for row in Table_Projects_output.get_children():
            Table_Projects_output.delete(row)
        cur.execute("SELECT * FROM projects")
        query_result = cur.fetchall()
        devFIOs_list = []
        i = 0
        for str in query_result:
            i += 1
            if i == 16:
                a = 5
            if str[2] is None:
                cur.execute("SELECT prOldLeaderFIO FROM projects WHERE prID = %s", str[0])
            else:
                cur.execute("SELECT devFIO FROM developers WHERE devID = %s", str[2])
            devFIO = ''.join(cur.fetchall()[0])
            devFIOs_list.append(devFIO)
        i = 0
        for str in query_result:
            dsc_text = str[6].replace('\n', ' ')
            Table_Projects_output.insert('', tk.END,
                                         values=tuple([str[1], devFIOs_list[i], str[3], str[4], str[5], dsc_text]))
            i += 1
    elif Var_OutputMenu.get() == "Разработчики":
        for row in Table_Developers_output.get_children():
            Table_Developers_output.delete(row)
        cur.execute("SELECT * FROM developers")
        query_result = cur.fetchall()
        for str in query_result:
            dsc_text = str[5].replace('\n', ' ')
            Table_Developers_output.insert('', tk.END, values=tuple([str[1], str[2], str[3], str[4], dsc_text]))

def Start_Any_Operation():
    OutputMenu_ChooseDir["state"] = "disabled"
    Btn_Select_Data["state"] = "disabled"
    Btn_Add_Data["state"] = "disabled"
    Btn_Edit_Data["state"] = "disabled"
    Btn_Delete_Data["state"] = "disabled"
    Btn_Cancel.place(relx=0.12, rely=0.93, anchor="c")
    if Var_OutputMenu.get() == "Проекты":
        Table_Projects_output.place_forget()
        Table_Projects_output_scroll.place_forget()
        Lbl_Enter_Project_Name.place(relx=0.188, rely=0.27, anchor="c")
        Lbl_Enter_Project_LeaderFIO.place(relx=0.17, rely=0.37, anchor="c")
        Lbl_Enter_Project_CreationDate.place(relx=0.16, rely=0.47, anchor="c")
        Lbl_Enter_Project_DevsAmount.place(relx=0.168, rely=0.57, anchor="c")
        Lbl_Enter_Project_Investments.place(relx=0.175, rely=0.67, anchor="c")
        Lbl_Enter_Project_Description.place(relx=0.187, rely=0.77, anchor="c")
        TxtEdit_Enter_ProjectCreationDate_or_DevBirthDate.place(relx=0.353, rely=0.47, anchor="c")
        TxtEdit_Enter_ProjectDevsAmount_or_DevSolvedPrCount.place(relx=0.47, rely=0.57, anchor="c")
        TxtEdit_Enter_ProjectInvestments_or_DevRating.place(relx=0.47, rely=0.67, anchor="c")
        Text_Enter_Project_or_Dev_Description.place(relx=0.481, rely=0.79, anchor="c")
        Description_scroll.place(relx=0.305, rely=0.73, height=107, width=25)
        Lbl_Enter_Description_Additional.place(relx=0.19, rely=0.82, anchor="c")
    elif Var_OutputMenu.get() == "Разработчики":
        Table_Developers_output.place_forget()
        Table_Developers_output_scroll.place_forget()
        Lbl_Enter_Dev_Name.place(relx=0.184, rely=0.3, anchor="c")
        Lbl_Enter_Dev_BirthDate.place(relx=0.205, rely=0.42, anchor="c")
        Lbl_Enter_Dev_SolvedPrCount.place(relx=0.159, rely=0.54, anchor="c")
        Lbl_Enter_Dev_Rating.place(relx=0.246, rely=0.66, anchor="c")
        Lbl_Enter_Dev_Description.place(relx=0.158, rely=0.77, anchor="c")
        Lbl_Enter_Description_Additional.place(relx=0.16, rely=0.82, anchor="c")
        TxtEdit_Enter_ProjectCreationDate_or_DevBirthDate.place(relx=0.353, rely=0.42, anchor="c")
        TxtEdit_Enter_ProjectDevsAmount_or_DevSolvedPrCount.place(relx=0.47, rely=0.54, anchor="c")
        TxtEdit_Enter_ProjectInvestments_or_DevRating.place(relx=0.47, rely=0.66, anchor="c")
        Text_Enter_Project_or_Dev_Description.place(relx=0.481, rely=0.78, anchor="c")
        Description_scroll.place(relx=0.305, rely=0.719, height=107, width=25)

def Update_option_menu(curr_menu, new_list, var_str):
    new_menu = curr_menu["menu"]
    new_menu.delete(0, "end")
    for str in new_list:
        new_menu.add_command(label=str, command=lambda value=str: var_str.set(value))

def Finish_Any_Operation():
    global operation_state
    operation_state = "none"
    UpdateProjectsList()
    UpdateDevelopersList()
    Update_option_menu(OutputMenu_Choose_Dev, DevsList, Var_OutputMenu_Devs)
    OutputMenu_ChooseDir["state"] = "normal"
    Btn_Select_Data["state"] = "normal"
    Btn_Add_Data["state"] = "normal"
    Btn_Edit_Data["state"] = "normal"
    Btn_Delete_Data["state"] = "normal"
    Btn_Cancel.place_forget()
    Lbl_Add_Data.place_forget()
    Lbl_Edit_Data.place_forget()
    Lbl_Delete_Data.place_forget()
    TxtEdit_Enter_ProjectName_or_DevName.place_forget()
    Var_Edit_ProjectName_or_DevName.set("")
    OutputMenu_Choose_Dev.place_forget()
    OutputMenu_Choose_Project_or_Dev.place_forget()
    TxtEdit_Enter_ProjectCreationDate_or_DevBirthDate.place_forget()
    Var_Edit_ProjectCreationDate_or_DevBirthDate.set("")
    Btn_Choose_Date.place_forget()
    TxtEdit_Enter_ProjectDevsAmount_or_DevSolvedPrCount.place_forget()
    Var_Edit_ProjectDevsAmount_or_DevSolvedPrCount.set("")
    TxtEdit_Enter_ProjectInvestments_or_DevRating.place_forget()
    Var_Edit_ProjectInvests_or_DevRating.set("")
    Description_scroll.place_forget()
    Btn_Add_Data_Commit.place_forget()
    Btn_Edit_Data_Commit.place_forget()
    Btn_Delete_Data_Commit.place_forget()
    TxtEdit_Enter_ProjectDevsAmount_or_DevSolvedPrCount["state"] = "normal"
    TxtEdit_Enter_ProjectInvestments_or_DevRating["state"] = "normal"
    Text_Enter_Project_or_Dev_Description["state"] = "normal"
    Text_Enter_Project_or_Dev_Description.place_forget()
    Text_Enter_Project_or_Dev_Description.delete(1.0, tk.END)
    Lbl_Enter_Description_Additional.place_forget()
    if Var_OutputMenu.get() == "Проекты":
        Update_option_menu(OutputMenu_Choose_Project_or_Dev, ProjectsList, Var_OutputMenu_Projects_or_Devs)
        Lbl_Enter_Project_Name.place_forget()
        Lbl_Enter_Project_LeaderFIO.place_forget()
        Lbl_Enter_Project_CreationDate.place_forget()
        Lbl_Enter_Project_DevsAmount.place_forget()
        Lbl_Enter_Project_Investments.place_forget()
        Lbl_Enter_Project_Description.place_forget()
        TxtEdit_LeaderFIO.place_forget()
        Var_Edit_LeaderFIO.set("")
        TxtEdit_LeaderFIO["state"] = "normal"
        for row in Table_Projects_output.get_children():
            Table_Projects_output.delete(row)
        Table_Projects_output_scroll.place(relx=0.003, rely=0.14, height=727, width=25)
        Table_Projects_output.place(relx=0.02, rely=0.14)
    elif Var_OutputMenu.get() == "Разработчики":
        Update_option_menu(OutputMenu_Choose_Project_or_Dev, DevsList, Var_OutputMenu_Projects_or_Devs)
        Lbl_Enter_Dev_Name.place_forget()
        Lbl_Enter_Dev_BirthDate.place_forget()
        Lbl_Enter_Dev_SolvedPrCount.place_forget()
        Lbl_Enter_Dev_Rating.place_forget()
        Lbl_Enter_Dev_Description.place_forget()
        for row in Table_Developers_output.get_children():
            Table_Developers_output.delete(row)
        Table_Developers_output_scroll.place(relx=0.003, rely=0.14, height=727, width=25)
        Table_Developers_output.place(relx=0.02, rely=0.14)

CalWindow = tk.Toplevel(MainWindow)
CalWindow.title("Выбрать дату из календаря")
CalWindow.geometry("500x300")
CalWindow.resizable(width=False, height=False)
CalWindow["bg"] = "#DDA0DD"
CalWindow.withdraw()

def Close_Cal_Window():
    Btn_Choose_Date["state"] = "normal"
    Btn_Add_Data_Commit["state"] = "normal"
    Btn_Edit_Data_Commit["state"] = "normal"
    Btn_Cancel["state"] = "normal"
    date_data_list = Var_Edit_Chosen_ProjectCreationDate_or_DevBirthDate.get().split("/")
    if len(date_data_list[1]) == 1:
        date_data_list[1] = '0' + date_data_list[1]
    if len(date_data_list[0]) == 1:
        date_data_list[0] = '0' + date_data_list[0]
    Var_Edit_ProjectCreationDate_or_DevBirthDate.set(date_data_list[1] + '.' + date_data_list[0] + '.20' + date_data_list[2])
    CalWindow.withdraw()

CalWindow.protocol("WM_DELETE_WINDOW", Close_Cal_Window)

def Choose_Date():
    Btn_Choose_Date["state"] = "disabled"
    Btn_Add_Data_Commit["state"] = "disabled"
    Btn_Edit_Data_Commit["state"] = "disabled"
    Btn_Cancel["state"] = "disabled"
    CalWindow.deiconify()
    Lbl_Choose_Date_From_Calendar = tk.Label(CalWindow, text='Выберите дату:',
                                             font=("Arial Bold", 28), bg="#DDA0DD")
    Lbl_Choose_Date_From_Calendar.place(relx=0.5, rely=0.1, anchor="c")
    cal = DateEntry(CalWindow, font=("Arial Bold", 28), width=15, background='#BA55D3', borderwidth=7, state="readonly",
                    textvariable=Var_Edit_Chosen_ProjectCreationDate_or_DevBirthDate)
    cal.place(relx=0.5, rely=0.3, anchor="c")
    Btn_Confirm_Chosen_Date = tk.Button(CalWindow, text="Подтвердить дату", font=("Arial Bold", 24), bd=10,
                                        background="#BA55D3", command=Close_Cal_Window, width=20)
    Btn_Confirm_Chosen_Date.place(relx=0.5, rely=0.7, anchor="c")

def Add_Data():
    global operation_state
    operation_state = "add"
    Start_Any_Operation()
    Lbl_Add_Data.place(relx=0.34, rely=0.18, anchor="c")
    Btn_Add_Data_Commit.place(relx=0.47, rely=0.925, anchor="c")
    if Var_OutputMenu.get() == "Проекты":
        Var_OutputMenu_Devs.set("Выбрать лидера проекта")
        OutputMenu_Choose_Dev.place(relx=0.47, rely=0.37, anchor="c")
        TxtEdit_Enter_ProjectName_or_DevName.place(relx=0.47, rely=0.27, anchor="c")
        Btn_Choose_Date.place(relx=0.525, rely=0.47, anchor="c")
    elif Var_OutputMenu.get() == "Разработчики":
        TxtEdit_Enter_ProjectName_or_DevName.place(relx=0.47, rely=0.3, anchor="c")
        Btn_Choose_Date.place(relx=0.525, rely=0.42, anchor="c")

def Add_Data_Confirm():
    if Var_OutputMenu.get() == "Проекты":
        prName = Var_Edit_ProjectName_or_DevName.get()
        prLeaderFIO = Var_OutputMenu_Devs.get()
        prCrDate = Var_Edit_ProjectCreationDate_or_DevBirthDate.get()
        prDevAmount = Var_Edit_ProjectDevsAmount_or_DevSolvedPrCount.get()
        prInvests = Var_Edit_ProjectInvests_or_DevRating.get()
        prDescription = Text_Enter_Project_or_Dev_Description.get(1.0, tk.END)
        if CheckProjectName(prName):
            if CheckLeaderFIOName(prLeaderFIO):
                if CheckProjectCrDate(prCrDate):
                    if CheckDevsAmount(prDevAmount):
                        if CheckInvests(prInvests):
                            try:
                                cur.execute("SELECT devID FROM developers WHERE devFIO = %s", prLeaderFIO)
                                devID = cur.fetchall()[0][0]
                                prCrDateList = prCrDate.split('.')
                                day = prCrDateList[0]
                                month = prCrDateList[1]
                                year = prCrDateList[2]
                                prCrDate = year + '-' + month + '-' + day
                                if prDescription == "\n":
                                    prDescription = "No additional information"
                                cur.execute(
                                    'INSERT INTO projects (prName, prLeaderID, prCreationDate, prDevsAmount, prInvests, prDescript, prOldLeaderFIO)'
                                    'VALUES (%s, %s, %s, %s, %s, %s, %s)',
                                    (prName, devID, prCrDate, prDevAmount, prInvests, prDescription, prLeaderFIO))
                                messagebox.showinfo("Успешное добавление записи в базу данных",
                                                    "Добавление записи о проекте в базу данных проведено успешно!")
                                DB.commit()
                                Finish_Any_Operation()
                            except:
                                DB.rollback()
                                messagebox.showerror("Ошибка при добавлении данных в базу",
                                                    "По неизвестной причине не удалось добавить данные в БД!")
    elif Var_OutputMenu.get() == "Разработчики":
        devName = Var_Edit_ProjectName_or_DevName.get()
        devBirthDate = Var_Edit_ProjectCreationDate_or_DevBirthDate.get()
        devSolvedPrCount = Var_Edit_ProjectDevsAmount_or_DevSolvedPrCount.get()
        devRating = Var_Edit_ProjectInvests_or_DevRating.get()
        devDescription = Text_Enter_Project_or_Dev_Description.get(1.0, tk.END)
        if CheckDevName(devName):
            if CheckDevBirthDate(devBirthDate):
                if CheckDevSolvedPrCount(devSolvedPrCount):
                    if CheckDevRating(devRating):
                        try:
                            devBirthDateList = devBirthDate.split('.')
                            day = devBirthDateList[0]
                            month = devBirthDateList[1]
                            year = devBirthDateList[2]
                            devBirthDate = year + '-' + month + '-' + day
                            if devDescription == "\n":
                                devDescription = "No additional information"
                            cur.execute(
                                'INSERT INTO developers (devFIO, devBirthDate, devSolvedPrCount, devRating, devDescript)'
                                'VALUES (%s, %s, %s, %s, %s)',
                                (devName, devBirthDate, devSolvedPrCount, devRating, devDescription))
                            messagebox.showinfo("Успешное добавление записи в базу данных",
                                                "Добавление записи о разработчике в базу данных проведено успешно!")
                            DB.commit()
                            Finish_Any_Operation()
                        except:
                            DB.rollback()
                            messagebox.showerror("Ошибка при добавлении данных в базу",
                                                 "По неизвестной причине не удалось добавить данные в БД!")

def Edit_Data():
    global operation_state
    operation_state = "edit"
    Start_Any_Operation()
    Lbl_Edit_Data.place(relx=0.34, rely=0.18, anchor="c")
    Btn_Edit_Data_Commit.place(relx=0.47, rely=0.925, anchor="c")
    if Var_OutputMenu.get() == "Проекты":
        Var_OutputMenu_Projects_or_Devs.set("Выбрать проект для изменений")
        Var_OutputMenu_Devs.set("Выбрать лидера проекта")
        OutputMenu_Choose_Project_or_Dev.place(relx=0.47, rely=0.27, anchor="c")
        OutputMenu_Choose_Dev.place(relx=0.47, rely=0.37, anchor="c")
        Btn_Choose_Date.place(relx=0.525, rely=0.47, anchor="c")
    elif Var_OutputMenu.get() == "Разработчики":
        Var_OutputMenu_Projects_or_Devs.set("Выбрать разработчика для изменений")
        OutputMenu_Choose_Project_or_Dev.place(relx=0.47, rely=0.3, anchor="c")
        Btn_Choose_Date.place(relx=0.525, rely=0.42, anchor="c")

def Edit_Data_Confirm():
    if Var_OutputMenu.get() == "Проекты":
        prName = Var_OutputMenu_Projects_or_Devs.get()
        prLeaderFIO = Var_OutputMenu_Devs.get()
        prCrDate = Var_Edit_ProjectCreationDate_or_DevBirthDate.get()
        prDevAmount = Var_Edit_ProjectDevsAmount_or_DevSolvedPrCount.get()
        prInvests = Var_Edit_ProjectInvests_or_DevRating.get()
        prDescription = Text_Enter_Project_or_Dev_Description.get(1.0, tk.END)
        if CheckIfProjectChosen(prName):
            if CheckLeaderFIOName(prLeaderFIO):
                if CheckProjectCrDate(prCrDate):
                    if CheckDevsAmount(prDevAmount):
                        if CheckInvests(prInvests):
                            try:
                                cur.execute("SELECT prID FROM projects WHERE prName = %s", prName)
                                prID = cur.fetchall()[0][0]
                                cur.execute("SELECT devID FROM developers WHERE devFIO = %s", prLeaderFIO)
                                devID = cur.fetchall()[0][0]
                                prCrDateList = prCrDate.split('.')
                                day = prCrDateList[0]
                                month = prCrDateList[1]
                                year = prCrDateList[2]
                                prCrDate = year + '-' + month + '-' + day
                                if prDescription == "\n":
                                    prDescription = "No additional information"
                                cur.execute('UPDATE projects SET prName = %s, prLeaderID = %s, prCreationDate = %s, prDevsAmount = %s,'
                                    'prInvests = %s, prDescript = %s, prOldLeaderFIO = %s WHERE prID = %s',
                                    (prName, devID, prCrDate, prDevAmount, prInvests, prDescription, prLeaderFIO, prID))
                                messagebox.showinfo("Успешное редактирование записи в базе данных",
                                                    "Редактирование записи о проекте в базе данных проведено успешно!")
                                DB.commit()
                                Finish_Any_Operation()
                            except:
                                DB.rollback()
                                messagebox.showerror("Ошибка при редактировании данных в базу",
                                                    "По неизвестной причине не удалось редактировать данные в БД!")
    elif Var_OutputMenu.get() == "Разработчики":
        devName = Var_OutputMenu_Projects_or_Devs.get()
        devBirthDate = Var_Edit_ProjectCreationDate_or_DevBirthDate.get()
        devSolvedPrCount = Var_Edit_ProjectDevsAmount_or_DevSolvedPrCount.get()
        devRating = Var_Edit_ProjectInvests_or_DevRating.get()
        devDescription = Text_Enter_Project_or_Dev_Description.get(1.0, tk.END)
        if CheckIfDevChosen(devName):
            if CheckDevBirthDate(devBirthDate):
                if CheckDevSolvedPrCount(devSolvedPrCount):
                    if CheckDevRating(devRating):
                        try:
                            cur.execute("SELECT devID FROM developers WHERE devFIO = %s", devName)
                            devID = cur.fetchall()[0][0]
                            devBirthDateList = devBirthDate.split('.')
                            day = devBirthDateList[0]
                            month = devBirthDateList[1]
                            year = devBirthDateList[2]
                            devBirthDate = year + '-' + month + '-' + day
                            if devDescription == "\n":
                                devDescription = "No additional information"
                            cur.execute(
                                'UPDATE developers SET devFIO = %s, devBirthDate = %s, devSolvedPrCount = %s,'
                                'devRating = %s, devDescript = %s WHERE devID = %s',
                                (devName, devBirthDate, int(devSolvedPrCount), float(devRating), devDescription, devID))
                            messagebox.showinfo("Успешное редактирование записи в базе данных",
                                                "Редактирование записи о разработчике в базе данных проведено успешно!")
                            DB.commit()
                            Finish_Any_Operation()
                        except:
                            DB.rollback()
                            messagebox.showerror("Ошибка при редактировании данных в базе",
                                                 "По неизвестной причине не удалось редактировать данные в БД!")

def Delete_Data():
    global operation_state
    operation_state = "delete"
    Start_Any_Operation()
    Lbl_Delete_Data.place(relx=0.34, rely=0.18, anchor="c")
    Btn_Delete_Data_Commit.place(relx=0.47, rely=0.925, anchor="c")
    if Var_OutputMenu.get() == "Проекты":
        Var_OutputMenu_Projects_or_Devs.set("Выбрать проект для удаления")
        OutputMenu_Choose_Project_or_Dev.place(relx=0.47, rely=0.27, anchor="c")
        TxtEdit_LeaderFIO.place(relx=0.47, rely=0.37, anchor="c")
        TxtEdit_LeaderFIO["state"] = "readonly"
        TxtEdit_Enter_ProjectDevsAmount_or_DevSolvedPrCount["state"] = "readonly"
        TxtEdit_Enter_ProjectInvestments_or_DevRating["state"] = "readonly"
        Text_Enter_Project_or_Dev_Description["state"] = "disable"
    elif Var_OutputMenu.get() == "Разработчики":
        Var_OutputMenu_Projects_or_Devs.set("Выбрать разработчика для удаления")
        OutputMenu_Choose_Project_or_Dev.place(relx=0.47, rely=0.3, anchor="c")
        TxtEdit_Enter_ProjectDevsAmount_or_DevSolvedPrCount["state"] = "readonly"
        TxtEdit_Enter_ProjectInvestments_or_DevRating["state"] = "readonly"
        Text_Enter_Project_or_Dev_Description["state"] = "disable"

def Delete_Data_Confirm():
    if Var_OutputMenu.get() == "Проекты":
        prName = Var_OutputMenu_Projects_or_Devs.get()
        if CheckIfProjectChosen(prName):
            try:
                cur.execute("DELETE FROM projects WHERE prName = %s", prName)
                messagebox.showinfo("Успешное удаление записи из базы данных",
                                    "Удаление записи о проекте из базы данных проведено успешно!")
                DB.commit()
                Finish_Any_Operation()
            except:
                DB.rollback()
                messagebox.showerror("Ошибка при удалении данных из базы",
                                     "По неизвестной причине не удалось удалить данные в БД!")
    elif Var_OutputMenu.get() == "Разработчики":
        devName = Var_OutputMenu_Projects_or_Devs.get()
        if CheckIfDevChosen(devName):
            try:
                cur.execute("DELETE FROM developers WHERE devFIO = %s", devName)
                messagebox.showinfo("Успешное удаление записи из базы данных",
                                    "Удаление записи о разработчике из базы данных проведено успешно!")
                DB.commit()
                Finish_Any_Operation()
            except:
                DB.rollback()
                messagebox.showerror("Ошибка при удалении данных из базы",
                                     "По неизвестной причине не удалось удалить данные в БД!")

def Project_or_Dev_For_Delete_Chosen(*args):
    global operation_state
    if operation_state == "delete":
        pr_or_dev_Name = Var_OutputMenu_Projects_or_Devs.get()
        if Var_OutputMenu.get() == "Проекты":
            if "Выбрать проект для" not in pr_or_dev_Name:
                cur.execute("SELECT * FROM projects WHERE prName = %s", pr_or_dev_Name)
                pr_info = cur.fetchall()
                leader_id = pr_info[0][2]
                cur.execute("SELECT devFIO FROM developers WHERE devID = %s", leader_id)
                Var_Edit_LeaderFIO.set(cur.fetchall()[0][0])
                Var_Edit_ProjectCreationDate_or_DevBirthDate.set(str(pr_info[0][3]))
                Var_Edit_ProjectDevsAmount_or_DevSolvedPrCount.set(str(pr_info[0][4]))
                Var_Edit_ProjectInvests_or_DevRating.set(pr_info[0][5])
                Text_Enter_Project_or_Dev_Description["state"] = "normal"
                Text_Enter_Project_or_Dev_Description.delete(1.0, tk.END)
                Text_Enter_Project_or_Dev_Description.insert(tk.END, pr_info[0][6])
                Text_Enter_Project_or_Dev_Description["state"] = "disable"
        elif Var_OutputMenu.get() == "Разработчики":
            if "Выбрать разработчика для" not in pr_or_dev_Name:
                cur.execute("SELECT * FROM developers WHERE devFIO = %s", pr_or_dev_Name)
                pr_or_dev_info = cur.fetchall()
                Var_Edit_ProjectCreationDate_or_DevBirthDate.set(str(pr_or_dev_info[0][2]))
                Var_Edit_ProjectDevsAmount_or_DevSolvedPrCount.set(str(pr_or_dev_info[0][3]))
                Var_Edit_ProjectInvests_or_DevRating.set(pr_or_dev_info[0][4])
                Text_Enter_Project_or_Dev_Description["state"] = "normal"
                Text_Enter_Project_or_Dev_Description.delete(1.0, tk.END)
                Text_Enter_Project_or_Dev_Description.insert(tk.END, pr_or_dev_info[0][5])
                Text_Enter_Project_or_Dev_Description["state"] = "disable"

Var_OutputMenu_Projects_or_Devs.trace("w", Project_or_Dev_For_Delete_Chosen)

Lbl_FIO = tk.Label(MainWindow, text="Жуковский Павел Сергеевич, 3 курс, 12 группа, 2021 год",
                   font=("Arial Bold", 18), bg="#DDA0DD")
Lbl_FIO.place(relx=0.215, rely=0.025, anchor="c")

Lbl_Start = tk.Label(MainWindow, text='Лабораторная "Модуль справочников v202102"\n\n'
                                      'Сделано для Баровика Дмитрия Валентиновича\n\n'
                                      'Язык программирования: Python\n\n'
                                      'Технологии: Tkinter, pymysql\n\n'
                                      'Среда разработки: PyCharm\n\n'
                                      'Разработчик программы: Жуковский Павел Сергеевич\n'
                                      '3 курс, 12 группа, 2021 год',
                     font=("Times New Roman", 32), bg="#DDA0DD")
Lbl_Start.place(relx=0.33, rely=0.5, anchor="c")

def Dir_Chosen(*args):
    Lbl_Start.place_forget()
    if Var_OutputMenu.get() == "Проекты":
        UpdateProjectsList()
        Update_option_menu(OutputMenu_Choose_Project_or_Dev, ProjectsList, Var_OutputMenu_Projects_or_Devs)
        OutputMenu_Choose_Project_or_Dev.config(font=("Times New Roman", 24), width=29)
        Lbl_Dir_Developers.place_forget()
        Table_Developers_output_scroll.place_forget()
        Table_Developers_output.place_forget()
        for row in Table_Projects_output.get_children():
            Table_Projects_output.delete(row)
        Lbl_Dir_Projects.place(relx=0.34, rely=0.1, anchor="c")
        Table_Projects_output_scroll.place(relx=0.003, rely=0.14, height=727, width=25)
        Table_Projects_output.place(relx=0.02, rely=0.14)
    elif Var_OutputMenu.get() == "Разработчики":
        UpdateDevelopersList()
        Update_option_menu(OutputMenu_Choose_Project_or_Dev, DevsList, Var_OutputMenu_Projects_or_Devs)
        OutputMenu_Choose_Project_or_Dev.config(font=("Times New Roman", 18), width=39)
        Lbl_Dir_Projects.place_forget()
        Table_Projects_output_scroll.place_forget()
        Table_Projects_output.place_forget()
        for row in Table_Developers_output.get_children():
            Table_Developers_output.delete(row)
        Lbl_Dir_Developers.place(relx=0.34, rely=0.1, anchor="c")
        Table_Developers_output_scroll.place(relx=0.003, rely=0.14, height=727, width=25)
        Table_Developers_output.place(relx=0.02, rely=0.14)
    Btn_Select_Data["state"] = "normal"
    Btn_Add_Data["state"] = "normal"
    Btn_Edit_Data["state"] = "normal"
    Btn_Delete_Data["state"] = "normal"

Lbl_ChooseDir = tk.Label(MainWindow, text="Выберите интересующий вас справочник:",
                         font=("Arial Bold", 18), bg="#DDA0DD")
Lbl_ChooseDir.place(relx=0.83, rely=0.07, anchor="c")

OutputMenu_ChooseDir = tk.OptionMenu(MainWindow, Var_OutputMenu, "Проекты", "Разработчики")
OutputMenu_ChooseDir.config(font=("Times New Roman", 28), bg="#BA55D3", bd=5, width=20)
OutputMenu_ChooseDir.place(relx=0.83, rely=0.14, anchor="c")

Var_OutputMenu.trace("w", Dir_Chosen)

Btn_Select_Data = tk.Button(MainWindow, text="Вывести все записи", font=("Arial Bold", 28), bd=10,
                            background="#BA55D3", command=Select_Data, width=20, state="disabled")
Btn_Select_Data.place(relx=0.83, rely=0.34, anchor="c")

Lbl_Add_Data = tk.Label(MainWindow, text='Добавление записи',
                        font=("Arial Bold", 36), bg="#DDA0DD")

Lbl_Edit_Data = tk.Label(MainWindow, text='Редактирование записи',
                         font=("Arial Bold", 36), bg="#DDA0DD")

Lbl_Delete_Data = tk.Label(MainWindow, text='Удаление записи',
                           font=("Arial Bold", 36), bg="#DDA0DD")

Lbl_Enter_Project_Name = tk.Label(MainWindow, text='Название проекта:',
                                  font=("Arial Bold", 28), bg="#DDA0DD")

Lbl_Enter_Dev_Name = tk.Label(MainWindow, text='ФИО разработчика:',
                                  font=("Arial Bold", 28), bg="#DDA0DD")

TxtEdit_Enter_ProjectName_or_DevName = tk.Entry(MainWindow, width=34, bd=5, font=("Arial Bold", 20),
                                                textvariable=Var_Edit_ProjectName_or_DevName)

OutputMenu_Choose_Project_or_Dev = tk.OptionMenu(MainWindow, Var_OutputMenu_Projects_or_Devs, *ProjectsList)
OutputMenu_Choose_Project_or_Dev.config(font=("Times New Roman", 24), bg="#BA55D3", bd=5, width=29)

Lbl_Enter_Project_LeaderFIO = tk.Label(MainWindow, text='ФИО лидера проекта:',
                                       font=("Arial Bold", 28), bg="#DDA0DD")

TxtEdit_LeaderFIO = tk.Entry(MainWindow, width=34, bd=5, font=("Arial Bold", 20),
                                    textvariable=Var_Edit_LeaderFIO)

OutputMenu_Choose_Dev = tk.OptionMenu(MainWindow, Var_OutputMenu_Devs, *DevsList)
OutputMenu_Choose_Dev.config(font=("Times New Roman", 24), bg="#BA55D3", bd=5, width=29)

Lbl_Enter_Project_CreationDate = tk.Label(MainWindow, text='Дата создания проекта:',
                                          font=("Arial Bold", 28), bg="#DDA0DD")

Lbl_Enter_Dev_BirthDate = tk.Label(MainWindow, text='Дата рождения:',
                                          font=("Arial Bold", 28), bg="#DDA0DD")

TxtEdit_Enter_ProjectCreationDate_or_DevBirthDate = tk.Entry(MainWindow, width=10, bd=5, font=("Arial Bold", 20),
                                                             textvariable=Var_Edit_ProjectCreationDate_or_DevBirthDate,
                                                             state="readonly")

Btn_Choose_Date = tk.Button(MainWindow, text="Выбрать дату", font=("Arial Bold", 22), bd=10,
                            background="#BA55D3", command=Choose_Date, width=18)

Lbl_Enter_Project_DevsAmount = tk.Label(MainWindow, text='Число разработчиков:',
                                        font=("Arial Bold", 28), bg="#DDA0DD")

Lbl_Enter_Dev_SolvedPrCount = tk.Label(MainWindow, text='Число решённых задач:',
                                        font=("Arial Bold", 28), bg="#DDA0DD")

TxtEdit_Enter_ProjectDevsAmount_or_DevSolvedPrCount = tk.Entry(MainWindow, width=34, bd=5, font=("Arial Bold", 20),
                                                               textvariable=Var_Edit_ProjectDevsAmount_or_DevSolvedPrCount)

Lbl_Enter_Project_Investments = tk.Label(MainWindow, text='Инвестиции проекта:',
                                         font=("Arial Bold", 28), bg="#DDA0DD")

Lbl_Enter_Dev_Rating = tk.Label(MainWindow, text='Рейтинг:',
                                         font=("Arial Bold", 28), bg="#DDA0DD")

TxtEdit_Enter_ProjectInvestments_or_DevRating = tk.Entry(MainWindow, width=34, bd=5, font=("Arial Bold", 20),
                                                         textvariable=Var_Edit_ProjectInvests_or_DevRating)

Lbl_Enter_Project_Description = tk.Label(MainWindow, text='Описание проекта:',
                                         font=("Arial Bold", 28), bg="#DDA0DD")

Lbl_Enter_Dev_Description = tk.Label(MainWindow, text='Описание разработчика:',
                                         font=("Arial Bold", 28), bg="#DDA0DD")

Lbl_Enter_Description_Additional = tk.Label(MainWindow, text='(не обязательно)',
                                            font=("Arial Bold", 24), bg="#DDA0DD")

Text_Enter_Project_or_Dev_Description = tk.Text(MainWindow, height=3, width=34, bd=5, font=("Times New Roman", 20))

Btn_Cancel = tk.Button(MainWindow, text="Отмена", font=("Arial Bold", 24), bd=5,
                                background="#BA55D3", command=Finish_Any_Operation, width=15)

Btn_Add_Data_Commit = tk.Button(MainWindow, text="Подтвердить добавление", font=("Arial Bold", 28), bd=10,
                                background="#BA55D3", command=Add_Data_Confirm, width=22)

Btn_Edit_Data_Commit = tk.Button(MainWindow, text="Подтвердить изменение", font=("Arial Bold", 28), bd=10,
                                background="#BA55D3", command=Edit_Data_Confirm, width=22)

Btn_Delete_Data_Commit = tk.Button(MainWindow, text="Подтвердить удаление", font=("Arial Bold", 28), bd=10,
                                background="#BA55D3", command=Delete_Data_Confirm, width=22)

Btn_Add_Data = tk.Button(MainWindow, text="Добавить запись", font=("Arial Bold", 28), bd=10,
                         background="#BA55D3", command=Add_Data, width=20, state="disabled")
Btn_Add_Data.place(relx=0.83, rely=0.46, anchor="c")

Btn_Edit_Data = tk.Button(MainWindow, text="Редактировать запись", font=("Arial Bold", 28), bd=10,
                          background="#BA55D3", command=Edit_Data, width=20, state="disabled")
Btn_Edit_Data.place(relx=0.83, rely=0.58, anchor="c")

Btn_Delete_Data = tk.Button(MainWindow, text="Удалить запись", font=("Arial Bold", 28), bd=10,
                            background="#BA55D3", command=Delete_Data, width=20, state="disabled")
Btn_Delete_Data.place(relx=0.83, rely=0.7, anchor="c")

Lbl_Dir_Projects = tk.Label(MainWindow, text='Справочник "Проекты"',
                            font=("Arial Bold", 28), bg="#DDA0DD")

Lbl_Dir_Developers = tk.Label(MainWindow, text='Справочник "Разработчики"',
                              font=("Arial Bold", 28), bg="#DDA0DD")

Table_Projects_output = ttk.Treeview(MainWindow, height=35, show="headings", selectmode="browse")
Table_Projects_output["columns"] = projects_headings
Table_Projects_output["displaycolumns"] = projects_headings
Table_Projects_output.heading(projects_headings[0], text=projects_headings[0], anchor=tk.CENTER)
Table_Projects_output.column(projects_headings[0], width=180, anchor=tk.CENTER)
Table_Projects_output.heading(projects_headings[1], text=projects_headings[1], anchor=tk.CENTER)
Table_Projects_output.column(projects_headings[1], width=200, anchor=tk.CENTER)
Table_Projects_output.heading(projects_headings[2], text=projects_headings[2], anchor=tk.CENTER)
Table_Projects_output.column(projects_headings[2], width=85, anchor=tk.CENTER)
Table_Projects_output.heading(projects_headings[3], text=projects_headings[3], anchor=tk.CENTER)
Table_Projects_output.column(projects_headings[3], width=160, anchor=tk.CENTER)
Table_Projects_output.heading(projects_headings[4], text=projects_headings[4], anchor=tk.CENTER)
Table_Projects_output.column(projects_headings[4], width=135, anchor=tk.CENTER)
Table_Projects_output.heading(projects_headings[5], text=projects_headings[5], anchor=tk.CENTER)
Table_Projects_output.column(projects_headings[5], width=230, anchor=tk.CENTER)
Table_Projects_output.column('#' + str(1), minwidth=180, stretch=False)
Table_Projects_output.column('#' + str(2), minwidth=200, stretch=False)
Table_Projects_output.column('#' + str(3), minwidth=85, stretch=False)
Table_Projects_output.column('#' + str(4), minwidth=160, stretch=False)
Table_Projects_output.column('#' + str(5), minwidth=135, stretch=False)
Table_Projects_output.column('#' + str(6), minwidth=230, stretch=False)

Table_Developers_output = ttk.Treeview(MainWindow, height=35, show="headings", selectmode="browse")
Table_Developers_output["columns"] = developers_headings
Table_Developers_output["displaycolumns"] = developers_headings
Table_Developers_output.heading(developers_headings[0], text=developers_headings[0], anchor=tk.CENTER)
Table_Developers_output.column(developers_headings[0], width=300, anchor=tk.CENTER)
Table_Developers_output.heading(developers_headings[1], text=developers_headings[1], anchor=tk.CENTER)
Table_Developers_output.column(developers_headings[1], width=100, anchor=tk.CENTER)
Table_Developers_output.heading(developers_headings[2], text=developers_headings[2], anchor=tk.CENTER)
Table_Developers_output.column(developers_headings[2], width=160, anchor=tk.CENTER)
Table_Developers_output.heading(developers_headings[3], text=developers_headings[3], anchor=tk.CENTER)
Table_Developers_output.column(developers_headings[3], width=100, anchor=tk.CENTER)
Table_Developers_output.heading(developers_headings[4], text=developers_headings[4], anchor=tk.CENTER)
Table_Developers_output.column(developers_headings[4], width=330, anchor=tk.CENTER)
Table_Developers_output.column('#' + str(1), minwidth=300, stretch=False)
Table_Developers_output.column('#' + str(2), minwidth=100, stretch=False)
Table_Developers_output.column('#' + str(3), minwidth=160, stretch=False)
Table_Developers_output.column('#' + str(4), minwidth=100, stretch=False)
Table_Developers_output.column('#' + str(5), minwidth=330, stretch=False)

Table_Projects_output_scroll = tk.Scrollbar(MainWindow, command=Table_Projects_output.yview)

Table_Projects_output.configure(yscrollcommand=Table_Projects_output_scroll.set)

Table_Developers_output_scroll = tk.Scrollbar(MainWindow, command=Table_Developers_output.yview)

Table_Developers_output.configure(yscrollcommand=Table_Developers_output_scroll.set)

Description_scroll = tk.Scrollbar(MainWindow, command=Text_Enter_Project_or_Dev_Description.yview)

Text_Enter_Project_or_Dev_Description.configure(yscrollcommand=Description_scroll.set)

Btn_Exit = tk.Button(MainWindow, text="Выход", font=("Arial Bold", 28), bd=10,
                     background="#BA55D3", command=MainWindow.quit, width=20)
Btn_Exit.place(relx=0.83, rely=0.925, anchor="c")

MainWindow.mainloop()
