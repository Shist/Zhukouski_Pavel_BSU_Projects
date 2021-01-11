using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Obiem_Chilindra
{
    /// <summary>
    /// расчет объема цилиндра по радиусу и высоте \n
    /// единственный класс содержащий приватные поля и
    /// публичный метод Main
    /// </summary>
    class Program
    {
        /// <summary>
        /// R - радиус цилиндра
        /// h - высота цилиндра
        /// V - рассчитанный объем цилиндра
        /// </summary>
        private static double R, h, V;
        private static string s;
        public static void Main()
        {
            Console.WriteLine("Введите радиус основания цилиндра:");
            s = Console.ReadLine();
            R = Double.Parse(s);
            Console.WriteLine("Введите высоту цилиндра:");
            s = Console.ReadLine();
            h = Double.Parse(s);
            V = Math.PI * R * R * h;
            Console.WriteLine("Объем цилиндра равен: {0:#.###}", V);
        }
    }
}