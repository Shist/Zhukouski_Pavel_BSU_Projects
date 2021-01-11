using System;
using System.IO;

namespace Palindrome
{
    class Program
    {
        public static int Max_from_two(int a, int b)
        {
            if (a > b)
                return a;
            else
                return b;
        }

        public static string Reverse_str(string str)
        {
            string result_str = "";
            for (int i = str.Length - 1; i >= 0; i--)
                result_str += str[i];
            return result_str;
        }

        static void Main(string[] args)
        {
            StreamReader reader = new StreamReader("input.txt");
            StreamWriter writer = new StreamWriter("output.txt");
            string str = reader.ReadLine();
            int L = str.Length;
            int[][] F = new int[L][];
            int i = 0;
            int j = 0;
            for (i = L - 1; i >= 0; i--) // По строкам снизу вверх
            { // Матрица для двумерного ДП
                F[i] = new int[L];
                for (j = 0; j < L; j++) // По столбцам слева направо
                {
                    if (i == j) // По диагонали единички (База ДП)
                        F[i][j] = 1;
                    else if (i == j - 1) // Проходимся по парам символов (База ДП)
                        if (str[i] == str[j]) // Если в паре одинаковые символы, то...
                            F[i][j] = 2;
                        else // Если же в паре символы разные, то...
                            F[i][j] = 1;
                    else if (i < j) // Формула для общего случая (ДП)
                        if (str[i] == str[j])
                            F[i][j] = F[i + 1][j - 1] + 2;
                        else
                            F[i][j] = Max_from_two(F[i][j - 1], F[i + 1][j]);
                    else
                        F[i][j] = 0; // В остальных местах нолики
                }
            }
            string result_str = "";
            string half_result_str = "";
            i = 0;
            j = L - 1;
            while (i < j)
            {
                if (str[i] == str[j])
                {
                    half_result_str += str[i];
                    i++;
                    j--;
                }
                else
                {
                    if (F[i][j - 1] > F[i + 1][j])
                        j--;
                    else
                        i++;
                }
            }
            if (F[0][L - 1] % 2 != 0) // Если итоговая строка должна быть нечетной длины
                result_str = half_result_str + str[i] + Reverse_str(half_result_str); // Добавляем также центральный элементик
            else
                result_str = half_result_str + Reverse_str(half_result_str); // Иначе без центрального элементика
            writer.WriteLine(F[0][L - 1]);
            writer.Write(result_str);
            reader.Close();
            writer.Close();
        }
    }
}