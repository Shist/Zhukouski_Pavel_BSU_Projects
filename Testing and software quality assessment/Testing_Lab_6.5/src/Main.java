public class Main
{
    public static String main(int test_num) throws Exception
    { // Функция main() вернут отсортированный массив в виде строки
        String input_str = Reading_Data.Read_Data(test_num); // Считываем строку с массивом
        if (input_str.length() > 8 && input_str.substring(0, 8).equals("Mistake!"))
            return input_str; // Если какое-то сообщение об ошибке, то возвращаем его
        String[] str_arr = input_str.split(" "); // Разбиваем строку на элементы
        int[] arr = new int[2]; // Создаем массив для наших элементов
        for (int i = 0; i < 2; i++) // Заполняем массив нашими числами
            arr[i] = Integer.parseInt(str_arr[i]);
        int result = 0;
        String str = "";
        if (arr[0] >= 0)
        {
            if (arr[1] >= 0)
            {
                if ((arr[0] - arr[1]) >= 0)
                {
                    result = 0;
                    str = Integer.toString(result);
                    str += ", выражение: 0";
                }
                else if ((arr[0] - arr[1]) < 0)
                {
                    result = 2*arr[0] - 2*arr[1];
                    str = Integer.toString(result);
                    str += ", выражение: 2a-2b";
                }
            }
            else if (arr[1] < 0)
            {
                if ((arr[0] - arr[1]) >= 0)
                {
                    result = 2*arr[1];
                    str = Integer.toString(result);
                    str += ", выражение: 2b";
                }
                /*else if ((arr[0] - arr[1]) < 0)
                {
                    result = 2*arr[0];
                    str = Integer.toString(result);
                    str += ", выражение: 2a";
                }*/
            }
        }
        else if (arr[0] < 0)
        {
            if (arr[1] >= 0)
            {
                /*if ((arr[0] - arr[1]) >= 0)
                {
                    result = (-2)*arr[0];
                    str = Integer.toString(result);
                    str += ", выражение: -2a";
                }*/
                if ((arr[0] - arr[1]) < 0)
                {
                    result = (-2)*arr[1];
                    str = Integer.toString(result);
                    str += ", выражение: -2b";
                }
            }
            else if (arr[1] < 0)
            {
                if ((arr[0] - arr[1]) >= 0)
                {
                    result = (-2)*arr[0] + 2*arr[1];
                    str = Integer.toString(result);
                    str += ", выражение -2a-2b";
                }
                else if ((arr[0] - arr[1]) < 0)
                {
                    result = 0;
                    str = Integer.toString(result);
                    str += ", выражение: 0";
                }
            }
        }
        return str;
    }
}