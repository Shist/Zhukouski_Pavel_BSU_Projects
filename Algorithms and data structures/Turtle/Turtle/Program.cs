using System;
using System.IO;

namespace Turtle
{
    class Program
    {
        static long Obr_po_modul(long x, long p)
        {
            if (p % x == 0) return 1;
            else return p - Obr_po_modul(p % x, x) * p / x;
        }

        static void Main(string[] args)
        { // (M+N)! / (M!*N!)
            StreamReader reader = new StreamReader("input.txt");
            StreamWriter writer = new StreamWriter("output.txt");
            string[] nums = reader.ReadLine().Split(new char[] { ' ' });
            long N = Convert.ToInt32(nums[0]) - 1; // Считываем кол-во строк -1 (т.к. нужны клеточки, а не ребра)
            long M = Convert.ToInt32(nums[1]) - 1; // Считывем кол-во столбцов -1 (т.к. нужны клеточки, а не ребра)
            long fact_1 = 1;
            long fact_2 = 1;
            long p = 1000000007;
            for (long i = 1; i <= M; i++) // Скоратили числитель и знаменатель на N!
            { // Считаем факториалы по модулю (этого будет достаточно)
                fact_1 = (fact_1 * (N + i)) % p;
                fact_2 = (fact_2 * i) % p;
            }
            long obr_fact_2 = Obr_po_modul(fact_2, p);
            long answer = (fact_1 * obr_fact_2) % p;
            writer.Write(answer);
            reader.Close();
            writer.Close();
        }
    }
}