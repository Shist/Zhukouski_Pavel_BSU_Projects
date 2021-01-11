import java.util.ArrayList;
import java.util.Scanner;

public class Main
{ // Вариант 17 (работа со строками)
    public static void main(String[] args)
    {
        try
        {
            ArrayList<String> arr = new ArrayList<>(); // Создаём массив строк
            Scanner Scan = new Scanner(System.in);
            System.out.println("Введите строки, среди которых хотите искать наибольшие общие подстроки:");
            while (Scan.hasNextLine())
            {
                System.out.println("Можно ввести еще одну строку для сравнения. Чтобы закончить, нажмите ctrl+D");
                String str = Scan.nextLine();
                arr.add(str);
            }
            String lrg_sub_str; // В этой переменной будем хранить общую наибольшую подстроку
            if (arr.size() == 0)
                throw new IllegalArgumentException("Вы не ввели ни одной строки. Нечего сравнивать.");
            if (arr.size() == 1)
                throw new IllegalArgumentException("Вы ввели только одну строку. Сравнивать её не с чем.");
            System.out.println("Все веддённые строки:");
            for (int i = 0; i < arr.size(); i++)
            {
                System.out.println((i+1) + ") " + arr.get(i));
            }
            for (int i = 0; i < arr.size() - 1; i++)
            { // Для каждой строки
                for (int j = i + 1; j < arr.size(); j++)
                { // Сравниваем ее с каждой из оставшихся строк
                    lrg_sub_str = ""; // Наибольшую общую подстроку храним в этой переменной
                    int mn = Math.min(arr.get(i).length(), arr.get(j).length()); // Запоминаем минимальную длину среди двух строк
                    // Для решения задачи пользуемся методами строк "contains" и "substring"
                    for (int k = 1; k <= mn; k++)
                        for (int t = 0; t < arr.get(i).length() - k + 1; t++) // Для каждого символа (до конца одной из строк)
                            if (arr.get(j).contains(arr.get(i).substring(t, t + k)))
                                lrg_sub_str = arr.get(i).substring(t, t + k); // Если строка содержит подстроку, то запоминаем ее
                    if (lrg_sub_str == "") // Если общих подстрок нету
                        System.out.println("Строки " + (i+1) + ") и " + (j+1) + ") не имеют общих подстрок.");
                    else
                    {
                        System.out.println("Наибольшая общая подстрока среди " + (i+1) + ") и " + (j+1) + ") строчек:");
                        System.out.println(lrg_sub_str);
                    }
                }
            }
        }
        catch (IllegalArgumentException ex)
        {
            System.out.println("Ошибка! Было выброшено исключение. Описание ошибки:\n" + ex.getMessage());
        }
    }
}