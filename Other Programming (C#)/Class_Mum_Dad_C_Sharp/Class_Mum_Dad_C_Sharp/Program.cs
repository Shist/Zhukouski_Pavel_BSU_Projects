using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace Class_Mum_Dad_C_Sharp
{
    class MyThread
    {
        static public int Amount;
        static public object for_sections = new object();
        public int Current_amount;
        public int Time;
        public int Amount_of_threads;
        string Name_of_thread;

        public MyThread(string name, int curr_am, int t)
        {
            Amount_of_threads = 0;
            Name_of_thread = name;
            Current_amount = curr_am;
            Time = t;
        }
        
        public void Run()
        {
            lock (for_sections)
                Console.WriteLine("Поток \"" + Name_of_thread + "\" начал свою работу...");
            while (Amount_of_threads < Current_amount && Amount > 0)
            {
                Thread.Sleep(Time);
                if (Amount <= 0)
                    break;
                Amount--;
                lock (for_sections)
                    Console.WriteLine(Name_of_thread + "(" + (Amount_of_threads + 1) + "/" + Current_amount + ")");
                Amount_of_threads++;
            }
            lock (for_sections)
            {
                Console.WriteLine("Поток \"" + Name_of_thread + "\" завершил свою работу...");
                if (Amount_of_threads == Current_amount)
                    Console.WriteLine("Завершение по причине: \"Закончились собственные повторения объекта.\"");
                if (Amount <= 0)
                    Console.WriteLine("Завершение по причине: \"Закончилось общее количество повторений для всех объектов.\"");
            }
        }

        static int Main(string[] args)
        {
            Console.WriteLine("Как и в программе на C++, реализована работа с 4 тредами...");
            Console.Write("Введите \"1\" для ручного ввода данных или \"2\" для автоматического: ");
            int key = Convert.ToInt32(Console.ReadLine());
            if (key == 1)
            {
                Console.Write("Введите желаемое максимальное количество повторений для всех тредов: ");
                Amount = Convert.ToInt32(Console.ReadLine());
                if (Amount <= 0)
                {
                    Console.WriteLine("Вы ввели некорректное число повторений для всех тредов");
                    return -2;
                }
                Console.WriteLine("Максимальное количество повторений равно " + Amount);
                string Name_of_thread;
                int Amount_of_repetitions;
                int Time_interval;
                Console.Write("Напишите имя для первого треда: ");
                Name_of_thread = Console.ReadLine();
                Console.Write("Укажите желаемое число повторений для первого треда: ");
                Amount_of_repetitions = Convert.ToInt32(Console.ReadLine());
                if (Amount_of_repetitions < 1)
                {
                    Console.WriteLine("Вы ввели некорректное число повторений для первого треда");
                    return -3;
                }
                Console.Write("Укажите интервал времени между повторениями в первом треде: ");
                Time_interval = Convert.ToInt32(Console.ReadLine());
                if (Time_interval < 1)
                {
                    Console.WriteLine("Введено некорректное время между повторениями для первого треда");
                    return -4;
                }
                MyThread mt_1 = new MyThread(Name_of_thread, Amount_of_repetitions, Time_interval);
                Console.Write("Напишите имя для второго треда: ");
                Name_of_thread = Console.ReadLine();
                Console.Write("Укажите желаемое число повторений для второго треда: ");
                Amount_of_repetitions = Convert.ToInt32(Console.ReadLine());
                if (Amount_of_repetitions < 1)
                {
                    Console.WriteLine("Вы ввели некорректное число повторений для второго треда");
                    return -5;
                }
                Console.Write("Укажите интервал времени между повторениями во втором треде: ");
                Time_interval = Convert.ToInt32(Console.ReadLine());
                if (Time_interval < 1)
                {
                    Console.WriteLine("Введено некорректное время между повторениями для второго треда");
                    return -6;
                }
                MyThread mt_2 = new MyThread(Name_of_thread, Amount_of_repetitions, Time_interval);
                Console.Write("Напишите имя для третьего треда: ");
                Name_of_thread = Console.ReadLine();
                Console.Write("Укажите желаемое число повторений для третьего треда: ");
                Amount_of_repetitions = Convert.ToInt32(Console.ReadLine());
                if (Amount_of_repetitions < 1)
                {
                    Console.WriteLine("Вы ввели некорректное число повторений для третьего треда");
                    return -7;
                }
                Console.Write("Укажите интервал времени между повторениями в третьем треде: ");
                Time_interval = Convert.ToInt32(Console.ReadLine());
                if (Time_interval < 1)
                {
                    Console.WriteLine("Введено некорректное время между повторениями для третьего треда");
                    return -8;
                }
                MyThread mt_3 = new MyThread(Name_of_thread, Amount_of_repetitions, Time_interval);
                Console.Write("Напишите имя для четвертого треда: ");
                Name_of_thread = Console.ReadLine();
                Console.Write("Укажите желаемое число повторений для четвертого треда: ");
                Amount_of_repetitions = Convert.ToInt32(Console.ReadLine());
                if (Amount_of_repetitions < 1)
                {
                    Console.WriteLine("Вы ввели некорректное число повторений для четвертого треда");
                    return -9;
                }
                Console.Write("Укажите интервал времени между повторениями в четвертом треде: ");
                Time_interval = Convert.ToInt32(Console.ReadLine());
                if (Time_interval < 1)
                {
                    Console.WriteLine("Введено некорректное время между повторениями для четвертого треда");
                    return -10;
                }
                MyThread mt_4 = new MyThread(Name_of_thread, Amount_of_repetitions, Time_interval);
                Thread new_Thrd = new Thread(mt_1.Run);
                Thread new_Thrd2 = new Thread(mt_2.Run);
                Thread new_Thrd3 = new Thread(mt_3.Run);
                Thread new_Thrd4 = new Thread(mt_4.Run);
                new_Thrd.Start();
                new_Thrd2.Start();
                new_Thrd3.Start();
                new_Thrd4.Start();
            }
            else if (key == 2)
            {
                Amount = 15;
                MyThread mt = new MyThread("1_Тред", 10, 200);
                MyThread mt2 = new MyThread("2_Тред", 10, 400);
                MyThread mt3 = new MyThread("3_Тред", 10, 8000);
                MyThread mt4 = new MyThread("4_Тред", 10, 1100);
                Thread new_Thrd = new Thread(mt.Run);
                Thread new_Thrd2 = new Thread(mt2.Run);
                Thread new_Thrd3 = new Thread(mt3.Run);
                Thread new_Thrd4 = new Thread(mt4.Run);
                new_Thrd.Start();
                new_Thrd2.Start();
                new_Thrd3.Start();
                new_Thrd4.Start();
            }
            else
            {
                Console.WriteLine("Вы ввели некорректное значение для ключа...");
                return -1;
            }
            return 0;
        }
    }
}
