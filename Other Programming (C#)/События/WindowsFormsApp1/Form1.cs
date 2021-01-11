using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    
    public partial class Form1 : Form
    {

        #region calculator
        class CalculatorEventArgs:EventArgs
        {
            private int result, arg1, arg2;

            public int Result { get => result; private set => result = value; }
            public int Arg1 { get => arg1; private set => arg1 = value; }
            public int Arg2 { get => arg2; private set => arg2 = value; }

            public CalculatorEventArgs(int _result, int _arg1, int _arg2)
            {
                Result = _result;
                Arg1 = _arg1;
                Arg2 = _arg2;
            }
        }

        static int arg1, arg2;

        class Calculator
        {
            private int rest_time;
            private bool is_work = true;
            public delegate void CalculatorStateHendler(object sender, CalculatorEventArgs e);
            public event CalculatorStateHendler CalculationsEnded;
            public Calculator(int _rest_time)
            {
                rest_time = _rest_time;
            }

            async public void Numerator()
            {
               while (is_work)
               {
                    Random rand = new Random();
                    do
                    {
                        arg1 = rand.Next() % 999998 + 2;
                        rand = new Random();
                        arg2 = rand.Next() % 999998 + 2;
                    }
                    while (arg1 == arg2);
                    if (arg1 > arg2)
                    {
                        int tmp = arg1;
                        arg1 = arg2;
                        arg2 = tmp;
                    }
                    int result= await Task.Run(()=>Counter(arg1,arg2));
                    CalculationsEnded?.Invoke(this, new CalculatorEventArgs(result, arg1, arg2));
                    await Task.Run(() => Thread.Sleep(rest_time));
               }
            }
            public void StopCalculation()
            {
                is_work = false;
            }
             public void RestartCalculation()
            {
                is_work = true;
                Numerator();
            }
            private int Counter(int diapason_start, int diapason_end)
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

            public bool isPrime(long x)
            {
                for (long i = 2; i < Math.Sqrt(x); i++)
                    if ((x % i) == 0) return false;
                return true;

            }


        }
        #endregion

        public delegate void DemonstraterStateHendler();
        public event DemonstraterStateHendler BringToCloseCalculation;
        public event DemonstraterStateHendler Restartcalculating;
        Calculator calc;
        public int time;

        public Form1()
        {
            InitializeComponent();
        }

        private void Show(object sender, CalculatorEventArgs e)
        {
            if (e.Result >= arg1 && e.Result <= arg2)
            {
                listBox1.Items.Insert(0, "Наибольшее простое число из ряда Фибоначчи в диапазоне [" + e.Arg1 + ", " + e.Arg2 + "] равно: " + e.Result);
            }
            else
            {
                listBox1.Items.Insert(0, "В выбранном диапазоне [" + e.Arg1 + ", " + e.Arg2 + "] вообще не существует простых чисел из ряда Фибоначчи...");
            }
            Invalidate();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (button2.Text == "Стоп")
            {
                if (BringToCloseCalculation != null)
                {
                    BringToCloseCalculation();
                    button2.Text = "Продолжить";
                }
            }
            else
            {
                if (Restartcalculating != null)
                {
                    Restartcalculating();
                    button2.Text = "Стоп";
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                time = Convert.ToInt32(textBox1.Text);
                calc = new Calculator(time);
                BringToCloseCalculation += calc.StopCalculation;
                calc.CalculationsEnded += Show;
                Restartcalculating += calc.RestartCalculation;
                label1.Enabled = false;
                textBox1.Enabled = false;
                button1.Enabled = false;
                label1.Visible = false;
                textBox1.Visible = false;
                button1.Visible = false;
                button2.Enabled = true;
                button2.Visible = true;
                Restartcalculating?.Invoke();
            }
            catch (Exception)
            {
                MessageBox.Show("Неверный формат ввода");
            }
        }
    }
}
