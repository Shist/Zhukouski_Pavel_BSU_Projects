using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.RegularExpressions;

namespace Sajora_Projects
{
    class Program
    {
        static void Main(string[] args)
        {
            int correct_taxi = 0;
            string input_str = Console.ReadLine();
            int kol_vo_taxi = int.Parse(input_str);
            Regex reg_1 = new Regex(@"^(([1-7]T[AB]X|7TEX)[ ]([0-9]{4}))$");
            Regex reg_2 = new Regex(@"^(([1-7]T[AB]X|7TEX)[ ][0][0][0][0])$");
            for (int i = 0; i < kol_vo_taxi; i++)
            {
                string temp_str = Console.ReadLine();
                if (reg_1.IsMatch(temp_str) && !reg_2.IsMatch(temp_str))
                {
                    correct_taxi++;
                }
            }
            Console.Write(correct_taxi);
        }
    }
}
