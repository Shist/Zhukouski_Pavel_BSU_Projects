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
            if (tr.Insert(43)) Console.WriteLine("43 вставлено успешно!"); else Console.WriteLine("43 не удалось вставить!");
            if (tr.Insert(143)) Console.WriteLine("143 вставлено успешно!"); else Console.WriteLine("143 не удалось вставить!");
            if (tr.Insert(42)) Console.WriteLine("42 вставлено успешно!"); else Console.WriteLine("42 не удалось вставить!");
            if (tr.Insert(43)) Console.WriteLine("43 вставлено успешно!"); else Console.WriteLine("43 не удалось вставить!");
            if (tr.Insert(45)) Console.WriteLine("45 вставлено успешно!"); else Console.WriteLine("45 не удалось вставить!");

            if (tr.Delete(45)) Console.WriteLine("45 удалено успешно!"); else Console.WriteLine("45 не удалось удалить!");
            if (tr.Delete(145)) Console.WriteLine("145 удалено успешно!"); else Console.WriteLine("145 не удалось удалить!");
            if (tr.Delete(43)) Console.WriteLine("43 удалено успешно!"); else Console.WriteLine("43 не удалось удалить!");
            if (tr.Delete(43)) Console.WriteLine("43 удалено успешно!"); else Console.WriteLine("43 не удалось удалить!");

        }
    }
}
