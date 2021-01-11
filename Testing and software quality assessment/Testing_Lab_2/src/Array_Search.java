import java.io.*;
import java.util.Scanner;
import java.util.concurrent.atomic.AtomicInteger;

public class Array_Search
{
    public static boolean Arr_Binary_Search(int[] arr, int key)
    { // Функция, проверяющая то, существует ли вообще элемент в массиве arr по заданному ключу key
        boolean check = false;
        int left = 0; // Задаем левую и правую границы поиска
        int right = arr.length - 1;
        int search = -1; // Найденный индекс элемента равен -1 (элемент не найден)
        while (left <= right) // Пока левая граница не "перескочит" правую
        {
            int mid = (left + right) / 2; // Ищем середину отрезка
            if (key == arr[mid])
            {  // Если ключевое поле равно искомому, то...
                search = mid;     // Мы нашли требуемый элемент,
                break;            // Выходим из цикла
            }
            if (key < arr[mid])     // Если искомое ключевое поле меньше найденной середины
                right = mid - 1;  // Смещаем правую границу, продолжим поиск в левой части
            else                  // Иначе
                left = mid + 1;   // Смещаем левую границу, продолжим поиск в правой части
        }
        if (search != -1) // Если индекс элемента не равен -1, то он существует
        {
            check = true;
        }
        return check;
    }

    public static int Find_Index_of_Key(int[] arr, int key)
    { // Функция, которая находит индекс элемента массива arr, значение которого совпадает со значением key
        int left = 0; // Задаем левую и правую границы поиска
        int right = arr.length - 1;
        int search = -1; // Найденный индекс элемента равен -1 (элемент не найден)
        while (left <= right) // Пока левая граница не "перескочит" правую
        {
            int mid = (left + right) / 2; // Ищем середину отрезка
            if (key == arr[mid])
            {  // Если ключевое поле равно искомому, то...
                search = mid;     // Мы нашли требуемый элемент,
                break;            // Выходим из цикла
            }
            if (key < arr[mid])     // Если искомое ключевое поле меньше найденной середины
                right = mid - 1;  // Смещаем правую границу, продолжим поиск в левой части
            else                  // Иначе
                left = mid + 1;   // Смещаем левую границу, продолжим поиск в правой части
        }
        return search;
    }

    public static boolean Arr_is_Ordered_or_Not(int[] arr)
    {
        boolean check = true;
        for (int i = 0; i < arr.length; i++)
        {
            for (int j = i; j < arr.length; j++)
            {
                if (arr[i] > arr[j])
                {
                    check = false;
                    break;
                }
            }
        }
        return check;
    }

    public static boolean Is_Int_Digit(String x)
    { // Функция, проверяющая, является ли строка целым числом
        for (int i = 0; i < x.length(); i++)
        {
            if ((x.charAt(i) < 48 || x.charAt(i) > 57) && x.charAt(i) != 45)
                return false;
        }
        return true;
    }

    public static void main(String[] args) throws IOException
    {
        String Result_Mes = "";
        int success_tests = 0;
        int failed_tests = 0;
        Scanner scan_in = new Scanner(new FileReader("tests.txt"));
        PrintWriter out = new PrintWriter(new FileWriter("results.txt"));
        String begin_str = scan_in.nextLine();
        int tests_amount = scan_in.nextInt();
        out.println(begin_str + " " + tests_amount); // Пишем: "Общее количество тестов: (число тестов)"
        out.println(); // Отступ на следующую строку
        if (tests_amount != 0)
        {
            scan_in.nextLine(); // Избавляемся от \n
            scan_in.nextLine(); // Избавляемся от пустой строки
        }
        while (tests_amount != 0)
        {
            String test_num = scan_in.nextLine(); // Считываем "Тест №(...)"
            out.println(test_num); // Пишем: "Тест №(...)"
            String input_str = scan_in.nextLine(); // Считываем строку с данными (1-ое число - ключ, остальные - элементы массива)
            out.println("Входные данные: " + input_str); // Пишем: "Входные данные: (ключ и элементы массива)"
            String Test_Mes = scan_in.nextLine(); // Считываем строку с ожидаемыми результатами
            out.println("Ожидаемые результаты: " + Test_Mes); // Пишем строку с ожидаемыми результатами
            out.println("||||||||||||||||||||||||||||||||||||||||||");
            String[] key_and_elements = input_str.split(" "); // Создаем массив символов, состоящие из ключа и элементов массива
            if (key_and_elements.length < 2)
            { // В нашей входной строке должно быть как минимум 2 числа: ключ и хотя бы один элемент массива
                Result_Mes = "Введено неверное количество чисел во входной строке";
            }
            else
            { // Если во входной строке достаточно чисел для дальнейшей работы программы, то...
                boolean IntDigit_Check = true;
                boolean Is_Not_To_Big = true;
                for (int i = 0; i < key_and_elements.length; i++)
                { // Смотрим для каждого символа, является ли он вообще целым числом а также то, не слишком ли оно большое
                    if (!Is_Int_Digit(key_and_elements[i]))
                    {
                        IntDigit_Check = false;
                        break;
                    }
                    if (IntDigit_Check)
                    {
                        if (Integer.parseInt(key_and_elements[i]) > 32767 || Integer.parseInt(key_and_elements[i]) < -32768)
                        {
                            Is_Not_To_Big = false;
                            break;
                        }
                    }
                }
                if (!IntDigit_Check)
                { // Если нашелся хотя бы один некорректный символ, то...
                    Result_Mes = "Введены некорректные входные данные";
                }
                else if (!Is_Not_To_Big)
                { // Если нашелся хотя бы один элемент, больший 32767 или меньший -32768, то...
                    Result_Mes = "Введены слишком большие или слишком маленькие значения элементов с ключом";
                }
                else
                { // Если же все числа в введённой строке являются целыми числами, то идём дальше...
                    int key = Integer.parseInt(key_and_elements[0]); // Запоминаем ключ, по которому будет искать
                    int[] arr = new int[key_and_elements.length - 1]; // Создаем массив для наших элементов
                    for (int i = 1; i < key_and_elements.length; i++)
                    { // Заполняем массив нашими числами
                        arr[i - 1] = Integer.parseInt(key_and_elements[i]);
                    }
                    if (!Arr_is_Ordered_or_Not(arr)) // Проверяем, является ли введённый массив упорядоченным
                    { // Если наш массив НЕ является упорядоченным, то...
                        Result_Mes = "Введённый массив не является упорядоченным";
                    }
                    else
                    { // Если массив упорядочен, то работает дальше...
                        boolean index_found = Arr_Binary_Search(arr, key); // True - если нашли, False - если не нашли
                        int result_index = 0; // Находим индекс элемента result_index по ключу key в массиве arr
                        if (index_found)
                        { // Если элемент по ключу существует, то находим его индекс второй функцией...
                            result_index = Find_Index_of_Key(arr, key);
                            Result_Mes = "Result = true, I = " + result_index + ".";
                        }
                        else
                        {
                            Result_Mes = "Result = false, I = 0.";
                        }
                    }
                }
            }
            out.println("Результат работы программы:");
            out.println(Result_Mes); // Выводим результат в формате "Result = (...), I = (...)."
            out.print("Вывод: ");
            if (Test_Mes.equals(Result_Mes)) // Если результат совпал с ожидаемым из теста, то...
            {
                out.print("ТЕСТ УСПЕШНО ПРОЙДЕН");
                success_tests++;
            }
            else
            { // В противном случае...
                out.print("ТЕСТ УПАЛ");
                failed_tests++;
            }
            out.println();
            out.println();
            out.println();
            tests_amount--;
            if (tests_amount != 0)
            { // Если это был не последний тест, то...
                scan_in.nextLine(); // Избавляемся от \n
            }
        }
        out.print("ИТОГ: Всего успешных тестов " + success_tests + " из " + (success_tests + failed_tests));
        out.close();
    }
}