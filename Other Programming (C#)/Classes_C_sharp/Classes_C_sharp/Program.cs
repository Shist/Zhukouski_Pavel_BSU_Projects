using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Classes_C_sharp
{

    class Program
    {
        static void Main(string[] args)
        {
            Temperature a = new Temperature(24.7), b;
            Console.WriteLine("Первая температура: {0}", a);
            Console.WriteLine("Введите второе значение: ");
            while (true)
            {
                try
                {
                    b = Temperature.Parse(Console.ReadLine());
                    break;
                }
                catch (Exception)
                {
                    Console.WriteLine("Вы ошиблись, повторите ввод!");
                    continue;
                }
            }
            Console.WriteLine("Вторая температура: {0}", b);
            Console.WriteLine("Сумма двух температур: {0}", a + b);
            Console.WriteLine("Разность двух температур: {0}", a - b);
            Console.WriteLine("Вторая температура со знаком \"минус\": {0}", -b);
            Console.WriteLine("Проверка на равенство: {0}", a == b);
            Console.WriteLine("Проверка на неравенство: {0}", a != b);
            Console.WriteLine("Проверка на Equals: {0}", a.Equals(b));
            Console.WriteLine("Проверка на хеш-коды: {0} {1}",
            a.GetHashCode(), b.GetHashCode());
        }
    }
}