using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace Matrix_Multiplication_Order
{
    class Program
    {
        static void Main(string[] args)
        {
            StreamReader reader = new StreamReader("input.txt");
            StreamWriter writer = new StreamWriter("output.txt");
            int S = Convert.ToInt32(reader.Read()) - 48;
            Tuple<int, int>[] matrix = new Tuple<int, int>[S];
            int i = 0;
            while (i < S)
            {
                matrix[i] = Tuple.Create(Convert.ToInt32(reader.Read()) - 48, Convert.ToInt32(reader.Read()) - 48);
                i++;
            }
            reader.Close();
            writer.Close();
        }
    }
}
