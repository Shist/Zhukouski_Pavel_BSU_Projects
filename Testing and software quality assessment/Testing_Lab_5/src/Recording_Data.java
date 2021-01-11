public class Recording_Data
{ // Запись данных
    public static String Print_Array(int[] arr)
    { // Выводит один массив
        String str = "";
        for (int i = 0; i < arr.length; i++)
        {
            str += arr[i];
            if (i != arr.length - 1)
                str += " ";
        }
        return str;
    }
}