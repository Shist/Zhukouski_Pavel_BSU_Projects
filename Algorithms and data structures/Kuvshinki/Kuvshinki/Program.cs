using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace Kuvshinki
{
    class Program
    {
        static int Max_from_two(int a, int b)
        {
            int max = 0;
            if (a > b)
                max = a;
            else
                max = b;
            return max;
        }

        static void Sum_of_list(int x, int[] list_s_komarami, int[] final_arr)
        {
            if (final_arr[x - 3] == -1)
                Sum_of_list(x - 3, list_s_komarami, final_arr);
            if (final_arr[x - 2] == -1)
                Sum_of_list(x - 2, list_s_komarami, final_arr);
            final_arr[x] = Max_from_two(final_arr[x - 2], final_arr[x - 3]) + list_s_komarami[x];
        }

        static void Main(string[] args)
        {
            StreamReader reader = new StreamReader("input.txt");
            StreamWriter writer = new StreamWriter("output.txt");
            int N = Convert.ToInt32(reader.ReadLine());
            string str = reader.ReadLine();
            string temp_str = null;
            int[] list_s_komarami = new int[N];
            int[] final_arr = new int[N];
            int i = 0;
            for (i = 0; i < N; i++)
                final_arr[i] = -1;
            int j = 0;
            for (i = 0; i < str.Length; i++)
            {
                temp_str += str[i];
                if (str[i] == ' ' || i == str.Length - 1)
                {
                    list_s_komarami[j] = Convert.ToInt32(temp_str);
                    j++;
                    temp_str = null;
                }
            } // ДП с мемоизацией
            if (N > 0)
                final_arr[0] = list_s_komarami[0]; // Первый лист
            // final_arr[1] = -1; Второй лист
            if (N > 2)
                final_arr[2] = final_arr[0] + list_s_komarami[2]; // Третий лист
            if (N > 3)
                final_arr[3] = final_arr[0] + list_s_komarami[3]; // Четвёртый лист
            if (N > 4)
                final_arr[4] = final_arr[2] + list_s_komarami[4]; // Пятый лист
            if (N > 5)
                Sum_of_list(N - 1, list_s_komarami, final_arr);
            writer.Write(final_arr[N-1]);
            reader.Close();
            writer.Close();
        }
    }
}