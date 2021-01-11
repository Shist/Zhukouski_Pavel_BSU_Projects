using System;

namespace Fraction_C_sharp
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                Console.Write("Введите числитель первой дроби: ");
                int a = int.Parse(Console.ReadLine());
                Console.Write("Введите знаменатель первой дроби: ");
                int b = int.Parse(Console.ReadLine());
                Fraction f1 = new Fraction(a, b);
                Console.Write("Введите числитель второй дроби: ");
                a = int.Parse(Console.ReadLine());
                Console.Write("Введите знаменатель третьейй дроби: ");
                b = int.Parse(Console.ReadLine());
                Fraction f2 = new Fraction(a, b);
                Console.WriteLine("Первая дробь: " + f1.ToString());
                Console.WriteLine("Вторая дробь: " + f2.ToString());
                Console.WriteLine("Первая дробь в рациональном виде: " + f1.SeeDouble());
                Console.WriteLine("Вторая дробь в рациональном виде: " + f2.SeeDouble());
                f1 = -f1;
                f2 = -f2;
                Console.WriteLine("Первая дробь с унарным минусом: " + f1.ToString());
                Console.WriteLine("Вторая дробь с унарным минусом: " + f2.ToString());
                Console.WriteLine("Первая дробь с унарным минусом в рациональном виде: " + f1.SeeDouble());
                Console.WriteLine("Вторая дробь с унарным минусом в рациональном виде: " + f2.SeeDouble());
                f1 = -f1;
                f2 = -f2;
                Console.WriteLine("Сумму дробей можно представить в виде дроби: " + (f1 + f2));
                Console.WriteLine("Сумма дробей в рациональном виде равна: " + (f1 + f2).SeeDouble());
                Console.WriteLine("Разность дробей можно представить в виде дроби: " + (f1 - f2));
                Console.WriteLine("Разность дробей в рациональном виде равна: " + (f1 - f2).SeeDouble());
                Console.WriteLine("Произведение дробей можно представить в виде дроби: " + (f1 * f2));
                Console.WriteLine("Произведение дробей в рациональном виде равна: " + (f1 * f2).SeeDouble());
                Console.WriteLine("Частность дробей можно представить в виде дроби: " + (f1 / f2));
                Console.WriteLine("Частность дробей в рациональном (или иррациональном) виде равна: " + (f1 / f2).SeeDouble());
                if (f1 == f2)
                {
                    Console.WriteLine("Дроби равны");
                }
                if (f1 != f2)
                {
                    Console.WriteLine("Дроби не равны");
                }
                if (f1 > f2)
                {
                    Console.WriteLine("Первая дробь больше второй");
                }
                if (f1 < f2)
                {
                    Console.WriteLine("Первая дробь меньше второй");
                }
            }
            catch (Exception e) // Ловим все исключения :D
            {
                Console.WriteLine(e.Message);
            }
        }
    }
}