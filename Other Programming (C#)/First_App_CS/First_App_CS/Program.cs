using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace First_App_CS
{
    class Program
    {
        static int Main(string[] args)
        {
            if (args.Length != 0)
            {
                Console.Write("Hello");
                foreach (string s in args)
                    Console.Write(", " + s);
                Console.WriteLine("!");
            }
            else
                Console.WriteLine("Hello, world!");
            return 0;
        }
    }
}