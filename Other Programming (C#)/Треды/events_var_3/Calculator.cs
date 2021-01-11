using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Numerics;

namespace events
{
    public class CalcFinishEventArgs : EventArgs
    {
        public int PrimeFib { get; }
        public int A { get; }
        public int B { get; }

        public CalcFinishEventArgs(int primeFib, int a, int b)
        {
            PrimeFib = primeFib;
            A = a;
            B = b;
        }
    }
    public class Calculator
    {
        Random random = new Random();
        private bool active;
        private Thread thread;
        public int Pause { get; set; }

        public delegate void CalcFinishEventHandler(object sender, CalcFinishEventArgs e);
        public event CalcFinishEventHandler CalcFinish;

        private int maxN = 1000000;

        public Calculator(int time, Demonstrator dem)
        {
            Pause = time;
            dem.StopEvent += Demonstrator_StopEvent;
            dem.StartEvent += Demonstrator_StartEvent;
            Start();
        }

        private void Demonstrator_StartEvent(object sender, EventArgs e)
        {
            Start();
        }

        private void Demonstrator_StopEvent(object sender, EventArgs e)
        {
            if (thread.IsAlive)
            {
                thread.Abort();
                active = false;
                thread.Join();
            }
        }

        private void Start()
        {
            active = true;
            thread = new Thread(Fibonacci);
            thread.Start();
        }

        private static int Counter(int diapason_start, int diapason_end)
        {
            int result_num = 0;
            int sum = 0;
            int perv = 1;
            int vtor = 1;
            while (diapason_end >= sum)
            {
                sum = perv + vtor;
                if (isPrime(sum))
                {
                    result_num = sum;
                }
                perv = vtor;
                vtor = sum;
            }
            return result_num;
        }

        private static bool isPrime(long x)
        {
            if (x == 1)
                return false;
            for (long i = 2; i * i <= x; i++)
                if ((x % i) == 0) return false;
            return true;
        }

        private void Fibonacci()
        {
            while (active)
            {
                int b = random.Next(3, maxN);
                int a = random.Next(2, b - 1);
                int fib = Counter(a, b);

                CalcFinish?.Invoke(this, new CalcFinishEventArgs(fib, a, b));
                Thread.Sleep(Pause);
            }
        }
    }
}
