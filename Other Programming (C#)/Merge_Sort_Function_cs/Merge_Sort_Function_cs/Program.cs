using System;

namespace Merge_Sort_Function_cs
{
    class Program
    {
        public static void Merge(int[] arr, int first, int last)
        { // Функция, сливающая массивы
            int middle, start, final, j;
            int[] temp_arr = new int[arr.Length];
            middle = (first + last) / 2; // Вычисление центрального элемента
            start = first; // Начало левой части
            final = middle + 1; // Начало правой части
            for (j = first; j <= last; j++) // Выполнять от начала до конца
            {
                if ((start <= middle) && ((final > last) || (arr[start] < arr[final])))
                {
                    temp_arr[j] = arr[start];
                    start++;
                }
                else
                {
                    temp_arr[j] = arr[final];
                    final++;
                }
            }
            for (j = first; j <= last; j++)
            {
                arr[j] = temp_arr[j]; // Возвращение результата в список
            }
        }

        public static void Merge_Sort(int[] arr, int first, int last)
        { // Рекурсивная процедура сортировки
            if (first < last)
            {
                Merge_Sort(arr, first, (first + last) / 2); // Cортировка левой части
                Merge_Sort(arr, (first + last) / 2 + 1, last); // Cортировка правой части
                Merge(arr, first, last); // Cлияние двух частей
            }
        }

        public static void Arr_Output(int[] arr)
        { // Вывод массива
            for (int i = 0; i < arr.Length; i++)
            {
                if (i == arr.Length - 1)
                {
                    Console.WriteLine(arr[i] + ".");
                    break;
                }
                Console.Write(arr[i] + ", ");
            }
        }

        static void Main(string[] args)
        {
            int[] arr = { 13, 4, 41, 31, 24, 523, 126, 421, 241, 317 };
            Console.WriteLine("Исходный массив:");
            Arr_Output(arr);
            Console.WriteLine("Исходный массив, отсортированный методом слияния:");
            Merge_Sort(arr, 0, arr.Length - 1);
            Arr_Output(arr);
        }
    }
}