import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

public class Login_Password
{
    public static boolean Users_Search(String[] User_names, String Login)
    {
        for (int i = 0; i < User_names.length; i++)
            if (User_names[i].equals(Login))
                return true;
        return false;
    }

    public static void main(String[] args) throws IOException
    {
        Scanner users_info_scan = new Scanner(new FileReader("users.info.txt"));
        if (!users_info_scan.hasNext())
            System.out.print("Файл с данным логинов и паролей пуст!");
        else
        {
            int users_amount = users_info_scan.nextInt(); // Считываем количество пользователей и их паролей
            if (users_amount > 10)
                System.out.print("Слишком много пользователей! Файл ограничен сверху: не более 10 пользователей.");
            else
            {
                users_info_scan.nextLine(); // Избавляемся от \n
                String[] User_names = new String[users_amount]; // Массив, хранящий информацию об именах пользователей
                String[] User_passwords = new String[users_amount]; // Массив, хранящий информацию о паролях пользователей
                for (int i = 0; i < users_amount; i++)
                {
                    String[] User_data = new String[2];
                    User_data = users_info_scan.nextLine().split("-");
                    User_names[i] = User_data[0];
                    User_passwords[i] = User_data[1];
                }
                Scanner scan = new Scanner(System.in);
                int remaining_number_of_attempts = 3; // Количество попыток ввода
                boolean check = false;
                while (remaining_number_of_attempts != 0)
                {
                    System.out.println("Оставшееся количество попыток для корректного ввода: " + remaining_number_of_attempts);
                    System.out.print("Пожалуйста, введите логин: ");
                    String Login = scan.nextLine();
                    if (Login.length() == 0)
                    { // Проверка на пустоту логина
                        System.out.println("Введён пустой логин!");
                        remaining_number_of_attempts--;
                        continue;
                    }
                    if (Login.length() > 10)
                    { // Проверка на длину логина
                        System.out.println("Введён недопустимо длинный логин!");
                        remaining_number_of_attempts--;
                        continue;
                    }
                    if (Users_Search(User_names, Login))
                    { // Если пользователь с таким именем найден в базе данных, то запрашиваем пароль
                        System.out.println("Здравствуйте, " + Login + "!");
                        remaining_number_of_attempts = 3; // Снова даём три попытки
                        while (remaining_number_of_attempts != 0)
                        {
                            int True_Password_Index = 0;
                            for (int i = 0; i < User_names.length; i++)
                                if (User_names[i].equals(Login))
                                {
                                    True_Password_Index = i; // Запоминаем индекс нужного пароля
                                    break;
                                }
                            System.out.println("Оставшееся количество попыток для корректного ввода: " + remaining_number_of_attempts);
                            System.out.print("Пожалуйста, введите ваш пароль: ");
                            String Password = scan.nextLine();
                            if (Password.length() > 8)
                            { // Проверка на длину пароля
                                System.out.println("Введён недопустимо длинный пароль!");
                                remaining_number_of_attempts--;
                                continue;
                            }
                            if (User_passwords[True_Password_Index].equals(Password))
                            { // Если пароль подошёл
                                System.out.println("Пароль введён верно! Добро пожаловать в систему, " + Login + "!");
                                check = true;
                                remaining_number_of_attempts = 0;
                                break;
                            }
                            else
                            { // Иначе...
                                System.out.println("Введённ неверный пароль!");
                                remaining_number_of_attempts--;
                                continue;
                            }
                        }
                        if (remaining_number_of_attempts == 0)
                            break;
                    }
                    else
                    { // Иначе...
                        System.out.println("Введённый логин не найден в базе данных!");
                        remaining_number_of_attempts--;
                        continue;
                    }
                }
                if (!check)
                    System.out.println("Попытки закончились! Вход недоступен!");
            }
        }
    }
}