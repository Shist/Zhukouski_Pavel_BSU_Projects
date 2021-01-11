using System;
using System.Collections.Generic;
using System.IO;
namespace SortSharp
{
    class Program
    {
        static void Sort(LinkedList<int> deque, int N)
        {
            if (N == 0)
                throw new Exception("На ноль делить нельзя!");
            bool check = false;
            for (LinkedListNode<int> node = deque.First; node != null; node = node.Next)
                if (node.Value % N == 0)
                {
                    if (check)
                    {
                        LinkedListNode<int> node_to_delete = node;
                        node = node.Previous;
                        deque.Remove(node_to_delete.Value);
                    }
                    check = true;
                }
                else
                    check = false;
        }

        static void Main(string[] args)
        {
            StreamReader sr = new StreamReader(@"D:\1\БГУ\Лабы\SortSharp\SortSharp\input.txt");
            LinkedList<int> numbers = new LinkedList<int>();

            string line;

            while ((line = sr.ReadLine()) != null)
                numbers.AddLast(int.Parse(line));

            Console.WriteLine("Исходные числа в деке:");

            foreach (int num in numbers)
                Console.WriteLine(num);
            Console.WriteLine("Кол-во элементов в деке: {0} ", numbers.Count);

            Console.WriteLine("Введите число, на которое будем делить элементы дека:");
            int N = int.Parse(Console.ReadLine());

            try
            {
                Sort(numbers, N);
            }
            catch (Exception e)
            {
                Console.WriteLine("Ошибка! {0}", e);
            }

            Console.WriteLine("Итоговые числа в деке после удаления подряд идущих и деляющихся на {0}:", N);
            foreach (int num in numbers)
                Console.WriteLine(num);
            Console.WriteLine("Кол-во элементов в деке: {0} ", numbers.Count);
        }
    }
}
