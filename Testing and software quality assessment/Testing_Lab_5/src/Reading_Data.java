import java.io.FileReader;
import java.util.Scanner;

public class Reading_Data
{ // Чтение данных
    public static boolean Is_Int_Digit(String x)
    { // Функция, проверяющая, является ли строка целым числом
        for (int i = 0; i < x.length(); i++)
        {
            if ((x.charAt(i) < 48 || x.charAt(i) > 57) && x.charAt(i) != 45)
                return false;
        }
        return true;
    }
    public static String Read_Data(int test_num) throws Exception
    { // Читает одну строку
        Scanner scan_in = new Scanner(new FileReader("tests.txt"));
        String input_str = scan_in.nextLine();
        while (test_num != 1)
        {
            input_str = scan_in.nextLine();
            test_num--;
        }
        String[] str_arr = input_str.split(" ");
        boolean IntDigit_Check = true;
        boolean Is_Not_To_Big = true;
        for (int i = 0; i < str_arr.length; i++)
        { // Смотрим для каждого символа, является ли он вообще целым числом а также то, не слишком ли оно большое
            if (!Is_Int_Digit(str_arr[i]))
            {
                IntDigit_Check = false;
                break;
            }
            if (Integer.parseInt(str_arr[i]) > 32767 || Integer.parseInt(str_arr[i]) < -32768)
            {
                Is_Not_To_Big = false;
                break;
            }
        }
        if (!IntDigit_Check) // Если нашелся хотя бы один некорректный символ, то...
            return "Mistake! Incorrect input entered.";
        if (!Is_Not_To_Big) // Если нашелся хотя бы один элемент, больший 32767 или меньший -32768, то...
            return "Mistake! Key values that are too large or too small have been entered.";
        if (str_arr.length < 2) // В нашей входной строке должно быть хотя бы одно число
            return "Mistake! An invalid number of numbers was entered in the input string. There must be at least two.";
        return input_str;
    }
}