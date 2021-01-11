using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Поздравление
{
    class Program
    {
        static void Main(string[] args)
        {
            long a = 0;
            while (a <= 1300000000)
            {
                if (a == 100000000)
                    Console.Write("Андрей");
                if (a == 200000000)
                    Console.Write(", ");
                if (a == 400000000)
                    Console.Write("с ");
                if (a == 600000000)
                    Console.Write("днём ");
                if (a == 800000000)
                    Console.Write("рождения");
                if (a == 1000000000)
                    Console.WriteLine("!!!");
                if (a == 1300000000)
                    Console.WriteLine("(с) Полярник");
                a+=2;
            }
        }
    }
}
