using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ConsoleApplication1
{
    public class AlarmEventArgs : EventArgs
    {
        DateTime alarmTime;
        public AlarmEventArgs(DateTime time)
        {
            alarmTime = time;
        }

        public DateTime Time
        {
            get {return alarmTime;}
        }

    }

    public delegate void AlarmEventHandler(object sender, AlarmEventArgs ev);

    public class Alarm
    {
        private DateTime alarmTime;
        private int interval = 10;

        public event AlarmEventHandler AlarmEvent;

        public Alarm(DateTime time) : this(time, 10)
        {
        }

        public Alarm(DateTime time, int interval)
        {
            this.alarmTime = time;
            this.interval = interval;
            this.Active = true;
        }

        public bool Active
        {
            set;
            get;
        }

        public void Set()
        {
            while (true)
            {
                System.Threading.Thread.Sleep(2000);
                DateTime currentTime = DateTime.Now;
                // Test whether it is time for the alarm to go off.
                if (currentTime.Hour == alarmTime.Hour &&
                    currentTime.Minute == alarmTime.Minute)
                {
                    AlarmEventArgs args = new AlarmEventArgs(currentTime);
                    if (AlarmEvent != null)
                        AlarmEvent(this, args);
                    if (!Active)
                        return;
                    if (interval==0)
                        return;
                    alarmTime = alarmTime.AddMinutes(interval);
                }
            }
        }
    }

    class Program
    {
        static Alarm alarm;

        public static void Main()
        {
            DateTime wakeUpTime = DateTime.Now;
            wakeUpTime = wakeUpTime.AddMinutes(1);
            alarm = new Alarm(wakeUpTime, 1);
            alarm.AlarmEvent += new AlarmEventHandler(wakeUp);
            alarm.Set();
        }

        private static void wakeUp(object sender, AlarmEventArgs ev) {
            ConsoleKeyInfo s;
            Console.WriteLine("Звенит будильник! {0}", ev.Time.ToLocalTime());
            Console.WriteLine("Нажмите 1, если Вы проснулись (другая клавиша - продолжаете спать...)");
            s = Console.ReadKey();
            if (s.KeyChar == '1')
                alarm.Active = false;
        }

    }

  
}
