import java.io.*;
import java.util.Scanner;

public class Triangles
{
    public static int Perimeter(int a, int b, int c)
    {
        int perimeter = 0;
        perimeter = a + b + c;
        return perimeter;
    }

    public static double Square(int a, int b, int c)
    {
        double p_p = 0.0; // poluperimeter
        double square = 0.0;
        p_p = (double)(a + b + c) / 2;
        square = Math.sqrt(p_p*(p_p - (double)a)*(p_p - (double)b)*(p_p - (double)c));
        return square;
    }

    public static String Triangle_View(int a, int b, int c)
    {
        if (a == b && b == c)
            return "равносторонний";
        else if (a == b || b == c || a == c)
            return "равнобедренный";
        else
            return "разносторонний";
    }

    public static boolean Is_Int_Digit(String x)
    {
        for (int i = 0; i < x.length(); i++)
        {
            if (x.charAt(i) < 48 || x.charAt(i) > 57)
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
        String begin_str = scan_in.nextLine();
        int tests_amount = scan_in.nextInt();
        if (tests_amount != 0)
        {
            scan_in.nextLine(); // Избавляемся от \n
            scan_in.nextLine(); // Избавляемся от пустой строки
        }
        PrintWriter out = new PrintWriter(new FileWriter("results.txt"));
        int [] a_b_c = new int[3];
        out.println(begin_str + " " + tests_amount);
        out.println();
        while (tests_amount != 0)
        {
            int i = 0;
            String test_num = scan_in.nextLine();
            out.println(test_num);
            String input_str = scan_in.nextLine();
            out.println("Входные данные: " + input_str);
            out.println("Ожидаемые результаты:");
            String Test_Mes = scan_in.nextLine();
            out.println(Test_Mes);
            out.println("||||||||||||||||||||||||||||||||||||||||||");
            String[] edges = input_str.split(" ");
            if (edges.length != 3)
            {
                Result_Mes = "введено неверное количество сторон для треугольника";
            }
            else if (edges.length == 3)
            {
                if (!(Is_Int_Digit(edges[0]) && Is_Int_Digit(edges[1]) && Is_Int_Digit(edges[2])))
                {
                    Result_Mes = "введены некорректные входные данные";
                }
                else
                {
                    a_b_c[0] = Integer.parseInt(edges[0]);
                    a_b_c[1] = Integer.parseInt(edges[1]);
                    a_b_c[2] = Integer.parseInt(edges[2]);
                    if (a_b_c[0] > 32767 || a_b_c[1] > 32767 || a_b_c[2] > 32767)
                    {
                        Result_Mes = "введены слишком большие значения сторон (больше двух байтов)";
                    }
                    else if (a_b_c[0] >= a_b_c[1] + a_b_c[2] || a_b_c[1] >= a_b_c[0] + a_b_c[2] || a_b_c[2] >= a_b_c[0] + a_b_c[1])
                    {
                        Result_Mes = "такого треугольника не существует";
                    }
                    else
                    {
                        String Result_Tr_View = Triangle_View(a_b_c[0], a_b_c[1], a_b_c[2]);
                        int Result_Per = Perimeter(a_b_c[0], a_b_c[1], a_b_c[2]);
                        double Result_Sq = Square(a_b_c[0], a_b_c[1], a_b_c[2]);
                        Result_Mes = (Result_Tr_View + ", P = " + Result_Per + ", S = " + Result_Sq);
                    }
                }
            }
            out.println("Результат работы программы:");
            out.println(Result_Mes);
            out.print("Вывод: ");
            if (Test_Mes.equals(Result_Mes))
            {
                out.print("ТЕСТ УСПЕШНО ПРОЙДЕН");
                success_tests++;
            }
            else
            {
                out.print("ТЕСТ УПАЛ");
                failed_tests++;
            }
            out.println();
            out.println();
            out.println();
            tests_amount--;
            if (tests_amount != 0)
            {
                scan_in.nextLine(); // Избавляемся от \n
            }
        }
        out.print("ИТОГ: Всего успешных тестов " + success_tests + " из " + (success_tests + failed_tests));
        out.close();
    }
}