using System;
using System.IO;

namespace Disks
{
    class Program
    {
        static void Main(string[] args)
        {
            System.Threading.Thread.CurrentThread.CurrentCulture = new System.Globalization.CultureInfo("en-US");
            StreamReader reader = new StreamReader("in.txt");
            StreamWriter writer = new StreamWriter("out.txt");
            int N = Convert.ToInt32(reader.ReadLine()); // Число дисков
            double[] radius_diska = new double[N]; // Тут храним радиусы дисков
            double[] sum = new double[N]; // А тут храним сумму для ответа в каждом новом диске
            radius_diska[0] = Convert.ToDouble(reader.ReadLine()); // Считываем данные об радиусе первого диска
            sum[0] = radius_diska[0]; // база ДП
            double max_x = 0.0; // В этой переменной будем хранить максимальное расстояние между какими-то двумя дисками
            for (int i = 1; i < N; i++)
            {
                radius_diska[i] = Convert.ToDouble(reader.ReadLine()); // Считываем данные об радиусах дисков
                for (int j = 0; j < i; j++) // Для каждого диска, идущего перед текущим, подсчитываем расстояние до него
                    if (max_x < sum[j] + 2*Math.Sqrt(radius_diska[i] * radius_diska[j]))
                        max_x = sum[j] + 2*Math.Sqrt(radius_diska[i] * radius_diska[j]);
                sum[i] = max_x;
                max_x = 0.0;
            }
            sum[N - 1] += radius_diska[N - 1];
            writer.Write("{0:0.00000}", sum[N - 1]);
            reader.Close();
            writer.Close();
        }
    }
}