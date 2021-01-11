using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using System.Threading.Tasks;

namespace Free_Zone_CS
{
    class Program
    {
        static void ScanF(string x)
        {
            Console.WriteLine("Сканирование сообщения: \"" + x + "\"");
        }

        static void CantHelp()
        {
            Console.WriteLine("Извини, ни чем не могу помочь.");
        }

        static void Main(string[] args)
        {
            string a = Console.ReadLine();
            ScanF(a);
            CantHelp();
        }
    }
}