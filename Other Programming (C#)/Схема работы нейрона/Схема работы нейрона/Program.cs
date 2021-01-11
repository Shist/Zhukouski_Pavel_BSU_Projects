using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Схема_работы_нейрона
{
    class Program
    {
        static void Neuron (double x)
        {
            switch (x)
            {
                case 1.0:
                    {
                        Console.WriteLine("Результат работы нейрона:");
                        Console.WriteLine("В данной ситуации есть очень серьёзные проблемы!");
                        Console.WriteLine();
                        break;
                    }
                case 0.75:
                    {
                        Console.WriteLine("Результат работы нейрона:");
                        Console.WriteLine("В данной ситуации есть серьёзные проблемы!");
                        Console.WriteLine();
                        break;
                    }
                case 0.50:
                    {
                        Console.WriteLine("Результат работы нейрона:");
                        Console.WriteLine("В данной ситуации есть проблемы!");
                        Console.WriteLine();
                        break;
                    }
                case 0.25:
                    {
                        Console.WriteLine("Результат работы нейрона:");
                        Console.WriteLine("В данной ситуации есть небольшие проблемы!");
                        Console.WriteLine();
                        break;
                    }
                case 0.0:
                    {
                        Console.WriteLine("Результат работы нейрона:");
                        Console.WriteLine("Ситуация в норме!");
                        Console.WriteLine();
                        break;
                    }
                default:
                    {
                        Console.WriteLine("Некорректный ввод данных!");
                        Console.WriteLine();
                        break;
                    }
            }
        }

        static void Main(string[] args)
        {
            Console.WriteLine("**********************************");
            Console.WriteLine("***PROGRAM СХЕМА РАБОТЫ НЕЙРОНА***");
            Console.WriteLine("**********************************");
            Console.WriteLine("***Для выхода из программы введите exit***");
            while (true)
            {
                Console.WriteLine("Введите состояние (от 0,0 до 1,0 с точностью 0,25):");
                string str = Console.ReadLine();
                if (str == "exit")
                    break;
                double x = Convert.ToDouble(str);
                Neuron(x);
            }
        }
    }
}
