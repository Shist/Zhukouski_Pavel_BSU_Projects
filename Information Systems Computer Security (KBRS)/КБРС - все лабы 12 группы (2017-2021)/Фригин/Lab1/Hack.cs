using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Reflection.Metadata;
using System.Runtime.InteropServices.ComTypes;

namespace Lab1
{
    public class Hack
    {
         string defaultAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

         Dictionary<char,double> defaultFreaquance = new Dictionary<char, double>();

        private const int lCount = 3;
        public  int  GetKeyLength(string text)
        {
            var stringWithoutSpace = text.Replace(" ",null);
            var lGramLength = stringWithoutSpace.Length / lCount;

            var LGram = Enumerable.Range(0, lCount)
                .Select(_ => stringWithoutSpace.Where((c,i)=> (i+1)%(_+1) == 0)).ToList();

            double currentIndex = 0;
            double prevIndex = 0;
            double actualIndex = 0;

                var prevlGram = stringWithoutSpace.Where((c, index) => (index + 1) % (1) == 0);
                var prevlgramCount = prevlGram.Count();

                var currentlGram = stringWithoutSpace.Where((c, index) => (index + 1) % (1 + 1) == 0);
                var currentgramCount = currentlGram.Count();

                var actuallGram = stringWithoutSpace.Where((c, index) => (index + 1) % (1 + 2) == 0);
                var actualgramCount = actuallGram.Count();

                foreach (var c in defaultAlphabet)
                {
                    var prevlGramCharCount = prevlGram.Count(_ => _ == c);
                    prevIndex += (double) prevlGramCharCount * (prevlGramCharCount - 1) / prevlgramCount / (prevlgramCount - 1);

                    var currentlGramCharCount = currentlGram.Count(_ => _ == c);
                    currentIndex += (double) currentlGramCharCount * (currentlGramCharCount - 1) / currentgramCount / (currentgramCount - 1);

                    var actuallGramCharCount = actuallGram.Count(_ => _ == c);
                    actualIndex += (double) actuallGramCharCount * (actuallGramCharCount - 1) / actualgramCount / (actualgramCount - 1);
                }

                for (var i = 4; i < 50; i++)
                {
                    prevIndex = currentIndex;
                    currentIndex = actualIndex;

                    actuallGram = stringWithoutSpace.Where((c, index) => (index + 1) % i == 0);
                    actualgramCount = actuallGram.Count();
                    actualIndex = 0;

                    foreach (var c in defaultAlphabet)
                    {
                        var actuallGramCharCount = actuallGram.Count(_ => _ == c);
                        actualIndex += (double) actuallGramCharCount * (actuallGramCharCount - 1) / actualgramCount / (actualgramCount - 1);
                    }

                    if (prevIndex * 1.01 < currentIndex && currentIndex > actualIndex * 1.01)
                    {
                        return i;
                    }
            }

            return 0;
        }

        public  Hack(string alphabet, Dictionary<char, double> freaquance )
        {
            defaultAlphabet = alphabet;
            defaultFreaquance = freaquance;
        }

        public  Dictionary<char,double> CountFreq(string text)
        {
            var dic = defaultAlphabet.ToDictionary(_ => _, _ => 0);
            var escaped = 0;

            foreach (var t in text)
            {
                if (dic.ContainsKey(t))
                {
                    dic[t]++;
                }
                else
                {
                    escaped++;
                }
            }

            var textLen = text.Length - escaped;

            return dic.ToDictionary(_=>_.Key,_ => (double)_.Value / (double)textLen);
        }


        public  char FindKeyChar(string text)
        {
            var shifts = new Dictionary<int,int>();
            var countFreq = CountFreq(text);
            var listFrequense = defaultFreaquance.ToList();
            foreach (var cfreq in countFreq)
            {
                var i = 0;
                
                while (i < listFrequense.Count - 1)
                {
                    if(!(Math.Abs(cfreq.Value-listFrequense[i].Value) > Math.Abs(cfreq.Value - listFrequense[i+1].Value)))
                    {
                        var shift = cfreq.Key - listFrequense[i].Key;
                        if(shifts.ContainsKey(shift))
                        {
                            shifts[shift]++;
                        }
                        else
                        {
                            shifts[shift] = 0;
                        }
                        break;
                    }

                    i += 1;
                }
            }

            return defaultAlphabet[shifts.Max(_ => _.Value)];
        }
        public  string FindKey(string text)
        {
            var length = GetKeyLength(text);
            var parts = Enumerable.Range(1, length+1).Select(_ => new string(text.Where((c, index) => (index+1) % _ == 0).ToArray())).ToList();

            return string.Join("", parts.Select(FindKeyChar));
        }
    }
}