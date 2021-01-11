using System;
using System.Text.RegularExpressions;

namespace Belarusian_Taxi
{
    class Program
    {
        static void Main()
        {
            int n = int.Parse(Console.ReadLine());
            int result = 0;
            Regex reg = new Regex(@"^(([1-7]T[AB]X|7TEX)[ ]([0-9]{3}[1-9]|[0-9]{2}[1-9][0-9]|[0-9][1-9][0-9]{2}|[1-9][0-9]{3}))$", RegexOptions.Compiled);
            for (int i = 0; i < n; i++) if (reg.IsMatch(Console.ReadLine())) result++;
            Console.Write(result);
        }
    }
}