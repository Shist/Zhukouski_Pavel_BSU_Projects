public class Main
{
    public static String main(int test_num) throws Exception
    { // Функция main() вернут отсортированный массив в виде строки
        String input_str = Reading_Data.Read_Data(test_num); // Считываем строку с массивом
        if (input_str.length() > 8 && input_str.substring(0, 8).equals("Mistake!"))
            return input_str; // Если какое-то сообщение об ошибке, то возвращаем его
        String[] str_arr = input_str.split(" "); // Разбиваем строку на элементы
        int[] arr = new int[str_arr.length]; // Создаем массив для наших элементов
        for (int i = 0; i < str_arr.length; i++) // Заполняем массив нашими числами
            arr[i] = Integer.parseInt(str_arr[i]);
        Bubble_Sort.Flag_Bubble_Sort(arr, arr.length); // Сортируем массив
        String str = Recording_Data.Print_Array(arr); // Печатаем массив
        return str;
    }
}