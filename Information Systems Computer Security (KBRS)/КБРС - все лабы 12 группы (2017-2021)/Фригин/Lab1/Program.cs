using System;
using System.Collections.Generic;
using System.Linq;

namespace Lab1
{
    public class Program
    {
        static string Eng = new string(Enumerable.Range('A', 'Z' - 'A' - 1).Select(_ => (char)_).ToArray());
        static string Rus = new string(Enumerable.Range('А', 'Я' - 'А' - 1).Select(_ => (char)_).ToArray());

        static Dictionary<char,double> EngFreq = new Dictionary<char, double>
        {  {'a', 0.08167},
           {'b', 0.01492},
           {'c', 0.02782},
           {'d', 0.04253},
           {'e', 0.12702},
           {'f', 0.0228},
           {'g', 0.02015},
           {'h', 0.06094},
           {'i', 0.06966},
           {'j', 0.00153},
           {'k', 0.00772},
           {'l', 0.04025},
           {'m', 0.02406},
           {'n', 0.06749},
           {'o', 0.07507},
           {'p', 0.01929},
           {'q', 0.00095},
           {'r', 0.05987},
           {'s', 0.06327},
           {'t', 0.09056},
           {'u', 0.02758},
           {'v', 0.00978},
           {'w', 0.0236},
           {'x', 0.0015},
           {'y', 0.01974},
           {'z', 0.00074}
        };
        static Dictionary<char, double> RusFreq = new Dictionary<char, double>
        {
            {'а', 0.07821},
            {'б', 0.01732},
            {'в', 0.04491},
            {'г', 0.01698},
            {'д', 0.03103},
            {'е', 0.08567},
            {'ё', 0.0007},
            {'ж', 0.01082},
            {'з', 0.01647},
            {'и', 0.06777},
            {'й', 0.01041},
            {'к', 0.03215},
            {'л', 0.04813},
            {'м', 0.03139},
            {'н', 0.0685},
            {'о', 0.11394},
            {'п', 0.02754},
            {'р', 0.04234},
            {'с', 0.05382},
            {'т', 0.06443},
            {'у', 0.02882},
            {'ф', 0.00132},
            {'х', 0.00833},
            {'ц', 0.00333},
            {'ч', 0.01645},
            {'ш', 0.00775},
            {'щ', 0.00331},
            {'ъ', 0.00023},
            {'ы', 0.01854},
            {'ь', 0.02106},
            {'э', 0.0031},
            {'ю', 0.00544},
            {'я', 0.01979}
        };

        static void Main(string[] args)
        { 
            Console.WriteLine("Pick language 1:en,2:ru");

            if (int.TryParse(Console.ReadLine(), out var res))
            {
                Crypt crypt;
                Hack hack;
                if (res == 1)
                {
                    crypt = new Crypt(Eng);
                    hack  = new Hack(Eng,EngFreq);
                }
                else if (res == 2)
                {
                    crypt = new Crypt(Rus);
                    hack = new Hack(Rus, RusFreq);
                }
                else
                {
                    return;
                }
                Console.WriteLine("Print message");
                var message = Console.ReadLine().ToUpper();
                Console.WriteLine("Print key");
                var key = Console.ReadLine();

                var cryptText = crypt.Encrypt(message, key);
                var decryptText = crypt.Decrypt(cryptText, key?.ToUpper());
                Console.WriteLine($"Secret text: {cryptText}");
                Console.WriteLine($"Decrypt text: {decryptText}");

                Console.WriteLine("Find Key:");
                Console.WriteLine(hack.FindKey(cryptText));
            }
        }
    }
}
