using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BinaryTree
{
    class Program
    {
        static void Main()
        {
            Tree tr = new Tree();
            int k;
            int m;
            Console.Write("Введите желаемое количество узлов в дереве: ");
            k = int.Parse(Console.ReadLine());
            for (int i = 1; i <= k; i++)
            {
                Console.Write("Введите значение " + i + " узла: ");
                m = int.Parse(Console.ReadLine());
                if (tr.Insert(m)) Console.WriteLine("Число " + m + " успешно вставлено в дерево!");
                else Console.WriteLine("Число " + m + " не удалось вставить в дерево, так как оно уже есть в нём!");
            }
            tr.Function_23();
            Console.ReadKey();
        }
    }
}
