﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;
using System.IO;

namespace AvansApplication
{
    public class Avans
    {
        public string FIO;
        public string Address;
        public int Salary;
    }

    public class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("*******");
            Console.WriteLine("*АВАНС*");
            Console.WriteLine("*******");
            Console.WriteLine("ВРЕМЯ {0}", DateTime.Now);
            var avansList = new List<Avans>();
            while (true)
            {
                Avans p = new Avans();
                Console.Write("Введите фамилию: ");
                p.FIO = Console.ReadLine();
                if (p.FIO == "q")
                    break;
                Console.Write("Введите адресс: ");
                p.Address = Console.ReadLine();
                Console.Write("Введите зарплату: ");
                p.Salary = int.Parse(Console.ReadLine());
                avansList.Add(p);
            }
            Console.WriteLine("-----------");
            foreach (Avans a in avansList)
            {
                Console.WriteLine(a.FIO);
            }
            Console.WriteLine("-----------");
            // Сохранение списка в файл.
            SaveAvansListToFile(avansList);
            // Ждем ENTER.
            Console.ReadLine();
            // Чтение списка из файла.
            avansList = LoadAvansListFromFile();
            // Печать списка:
            PrintAvansList(avansList);
            // Сортировка списка по имени FIO.
            avansList.Sort(AvansComparer);
            // Поиск элемента по имени FIO. Получаем индекс.
            int i = avansList.FindIndex(IsAvansWithGivenFIO);
            // Поиск элемента по имени FIO с использованием анонимной функции, определенной по месту.
            i = avansList.FindIndex(delegate (Avans p) { return p.FIO == "Petrov"; });
            // Поиск с помощью бинарного поиска. Применим лишь для сортированного списка.
            Avans b = new Avans();
            b.FIO = "Petrov";
            i = avansList.BinarySearch(b, new AvansComparerObject());
            // Удаление элемента по индексу.
            avansList.RemoveAt(i);
            // Печать списка:
            PrintAvansList(avansList);
            // Сохранение списка в файл.
            SaveAvansListToFile(avansList);
            // Ждем ENTER.
            Console.ReadLine();
            Console.WriteLine("ВРЕМЯ {0}", DateTime.Now);
        }

        public static int AvansComparer(Avans a, Avans b)
        {
            // Функция сравнения должна возвращать:
            // -1, если a < b
            // 0, если a == b
            // 1, если a > b
            // Для сравнение строк есть готовая функция String.Compare(a, b).
            return String.Compare(a.FIO, b.FIO);
        }

        public static bool IsAvansWithGivenFIO(Avans p)
        {
            return p.FIO == "Petrov";
        }

        public static void PrintAvansList(List<Avans> avansList)
        {
            Console.WriteLine("-----------");
            foreach (Avans a in avansList)
            {
                Console.Write(a.FIO);
                Console.Write(", ");
                Console.WriteLine(a.Salary);
            }
            int summa = 0;
            foreach (Avans a in avansList)
            {
                summa = summa + a.Salary;
            }
            Console.WriteLine(String.Format("-- Summa: {0} --", summa));
            Console.WriteLine("-----------");
        }

        public static void SaveAvansListToFile(List<Avans> avansList)
        {
            XmlSerializer x = new XmlSerializer(typeof(List<Avans>));
            using (FileStream f = File.Create(@"C:\Users\user\Documents\Avanses.xml"))
            {
                x.Serialize(f, avansList);
            }
        }

        public static List<Avans> LoadAvansListFromFile()
        {
            List<Avans> result;
            XmlSerializer x = new XmlSerializer(typeof(List<Avans>));
            using (FileStream f = File.OpenRead(@"C:\Users\user\Documents\Avanses.xml"))
            {
                result = (List<Avans>)x.Deserialize(f);
            }
            return result;
        }
    }

    public class AvansComparerObject : IComparer<Avans>
    {
        public int Compare(Avans a, Avans b)
        {
            return String.Compare(a.FIO, b.FIO);
        }
    }
}
