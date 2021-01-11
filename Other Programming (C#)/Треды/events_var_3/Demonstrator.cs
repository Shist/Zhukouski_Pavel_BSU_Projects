using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

namespace events
{
    public class DisplayEventArgs : EventArgs
    {
        public string Result { get; }
        public DisplayEventArgs(string str)
        {
            Result = str;
        }
    }

    public class ShootEventArgs : EventArgs
    {
        public int X { get; }
        public int Y { get; }
        public ShootEventArgs(int x, int y)
        {
            X = x;
            Y = y;
        }
    }

    public class Demonstrator
    {
        Random ShootRandom = new Random();
        private bool ShootActive;
        private Thread ShootThread;
        public int ShootPause { get; set; }
        public int TargetSize { get; set; }
        private int MaxX;
        private int MaxY;

        public Calculator calculator;

        public Demonstrator(int time, int targetSize, int maxX, int maxY)
        {
            ShootPause = time;
            TargetSize = targetSize;
            MaxX = maxX;
            MaxY = maxY;
            Start();
        }

        public delegate void DisplayEventHandler(object sender, DisplayEventArgs e);
        public event DisplayEventHandler DisplayEvent;

        public delegate void ShootEventHandler(object sender, ShootEventArgs e);
        public event ShootEventHandler ShootEvent;

        public delegate void StopShootEventHandler(object sender, EventArgs e);
        public event ShootEventHandler StopShootEvent;

        public delegate void StopEventHandler(object sender, EventArgs e);
        public event StopEventHandler StopEvent;

        public delegate void StartEventHandler(object sender, EventArgs e);
        public event StartEventHandler StartEvent;

        public void CalcInit(int time)
        {
            if (calculator == null || calculator.Pause != time)
            {
                // в начале, и при необходимости задать новое время ожидания
                calculator = new Calculator(time, this);
                calculator.CalcFinish += Calculator_CalcFinish;
            }
            else
            {
                StartEvent(this, new EventArgs());
            }
        }

        private void Calculator_CalcFinish(object sender, CalcFinishEventArgs e)
        {
            if (e.PrimeFib >= e.A && e.PrimeFib <= e.B)
            {
                string str = String.Format("В диапазоне [{0}, {1}] самым простым числом Фибоначчи является число {2}", e.A, e.B, e.PrimeFib);
                DisplayEvent(this, new DisplayEventArgs(str));
            }
            else
            {
                string str = String.Format("В выбранном диапазоне [" + e.A + ", " + e.B + "] вообще не существует простых чисел из ряда Фибоначчи...");
                DisplayEvent(this, new DisplayEventArgs(str));
            }
        }

        public void StopCalc()
        {
            // null-condition
            StopEvent?.Invoke(this, new EventArgs());
        }

        private void Start()
        {
            ShootActive = true;
            ShootThread = new Thread(Shooting);
            ShootThread.Start();
        }

        private void Shooting()
        {
            while (ShootActive)
            {
                int x = ShootRandom.Next(-MaxX/2, MaxX/2);
                int y = ShootRandom.Next(-MaxY/2, MaxY/2);

                ShootEvent?.Invoke(this, new ShootEventArgs(x, y));
                Thread.Sleep(ShootPause);
            }
        }

        public void StopShooting()
        {
            if (ShootThread.IsAlive)
            {
                ShootThread.Abort();
                ShootActive = false;
                ShootThread.Join();
            }
        }
    }
}
