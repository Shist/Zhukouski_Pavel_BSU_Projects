using System;
using System.IO;

namespace Rectangles_by_Andrey_Petrov
{
    class MyPair
    {
        public long first;
        public char second;
        public MyPair(long f, char s)
        {
            first = f;
            second = s;
        }
    }

    class Program
    {
        public static void Merge(MyPair[] arr, long first, long last)
        {
            long middle, start, final, j;
            MyPair[] temp_arr = new MyPair[arr.Length];
            middle = (first + last) / 2;
            start = first;
            final = middle + 1;
            for (j = first; j <= last; j++)
            {
                if ((start <= middle) && ((final > last) || (arr[start].first < arr[final].first)))
                {
                    temp_arr[j] = new MyPair(arr[start].first, arr[start].second);
                    start++;
                }
                else
                {
                    temp_arr[j] = new MyPair(arr[final].first, arr[final].second);
                    final++;
                }
            }
            for (j = first; j <= last; j++)
            {
                arr[j].first = temp_arr[j].first;
                arr[j].second = temp_arr[j].second;
            }
        }

        public static void Merge_Sort(MyPair[] arr, long first, long last)
        {
            if (first < last)
            {
                Merge_Sort(arr, first, (first + last) / 2);
                Merge_Sort(arr, (first + last) / 2 + 1, last);
                Merge(arr, first, last);
            }
        }

        static void Main(string[] args)
        {
            StreamReader reader = new StreamReader("rect.in");
            StreamWriter writer = new StreamWriter("rect.out");
            long Xmax = 0;
            long Ymax = 0;
            long N = 0;
            string[] temp_str = reader.ReadLine().Split();
            Xmax = Convert.ToInt64(temp_str[0]);
            Ymax = Convert.ToInt64(temp_str[1]);
            N = Convert.ToInt64(temp_str[2]);
            long left_top_X = 0;
            long right_bottom_Y = 0;
            long right_bottom_X = 0;
            long left_top_y = 0;
            long end_X = 0;
            long end_Y = 0;
            long end_Num = 0;
            long counts = 0;
            long additional_coord = 0;
            MyPair[] rect_arr = new MyPair[2 * N];
            long i = 0;
            for (long t = 0; t < N; t++, i += 2)
            {
                string[] new_str = reader.ReadLine().Split();
                left_top_X = Convert.ToInt64(new_str[0]);
                right_bottom_Y = Convert.ToInt64(new_str[1]);
                right_bottom_X = Convert.ToInt64(new_str[2]);
                left_top_y = Convert.ToInt64(new_str[3]);
                long cur_crds = 0;
                long FirstDestination = 0;
                long SecondDestination = 0;
                if (left_top_y == 0)
                    cur_crds = int.MaxValue;
                else
                {
                    FirstDestination = left_top_X * Ymax;
                    SecondDestination = left_top_y * Xmax;
                    if (SecondDestination > FirstDestination)
                        cur_crds = (left_top_y - 1 + FirstDestination) / left_top_y;
                    else
                        cur_crds = Xmax - SecondDestination / left_top_X + Ymax;
                }
                rect_arr[i] = new MyPair(cur_crds, '[');
                if (right_bottom_Y == 0)
                    cur_crds = int.MaxValue;
                else
                {
                    FirstDestination = right_bottom_X * Ymax;
                    SecondDestination = right_bottom_Y * Xmax;
                    if (SecondDestination > FirstDestination)
                        cur_crds = FirstDestination / right_bottom_Y;
                    else
                        cur_crds = Xmax - (right_bottom_X - 1 + SecondDestination) / right_bottom_X + Ymax;
                }
                rect_arr[i + 1] = new MyPair(cur_crds, ']');
            }
            Merge_Sort(rect_arr, 0, 2 * N - 1);
            foreach (MyPair rect in rect_arr)
            {
                if (rect.second == '[')
                    counts++;
                else
                    counts--;
                if (counts > end_Num)
                {
                    end_Num = counts;
                    additional_coord = rect.first;
                }
            }
            if (additional_coord > Xmax)
            {
                end_X = Xmax;
                end_Y = Xmax + Ymax - additional_coord;
            }
            else
            {
                end_X = additional_coord;
                end_Y = Ymax;
            }
            writer.Write(end_Num + " " + end_X + " " + end_Y);
            reader.Close();
            writer.Close();
        }
    }
}