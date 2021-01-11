using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Calculator
{
    public partial class Form1 : Form
    {
        double a;
        double b;
        double c;
        int count;
        bool sgn = true;

        private void calculate()
        {
            switch (count)
            {
                case 1:
                    {
                        b = Convert.ToDouble(textBoxResult.Text);
                        c = a + b;
                        textBoxResult.Text = c.ToString();
                        break;
                    }
                case 2:
                    {
                        b = Convert.ToDouble(textBoxResult.Text);
                        c = a * b;
                        textBoxResult.Text = c.ToString();
                        break;
                    }
                case 3:
                    {
                        b = Convert.ToDouble(textBoxResult.Text);
                        c = a / b;
                        textBoxResult.Text = c.ToString();
                        break;
                    }
                case 4:
                    {
                        b = Convert.ToDouble(textBoxResult.Text);
                        c = a - b;
                        textBoxResult.Text = c.ToString();
                        break;
                    }
                default:
                    break;
            }
        }

        public Form1()
        {
            InitializeComponent();
        }

        private void buttonMul_Click(object sender, EventArgs e)
        {
            a = Convert.ToDouble(textBoxResult.Text);
            textBoxResult.Clear();
            count = 2;
            label3.Text = a.ToString() + "*";
            sgn = true;
        }

        private void buttonDev_Click(object sender, EventArgs e)
        {
            a = Convert.ToDouble(textBoxResult.Text);
            textBoxResult.Clear();
            count = 3;
            label3.Text = a.ToString() + "/";
            sgn = true;
        }

        private void buttonSum_Click(object sender, EventArgs e)
        {
            a = Convert.ToDouble(textBoxResult.Text);
            textBoxResult.Clear();
            count = 1;
            label3.Text = a.ToString() + "+";
            sgn = true;
        }

        private void buttonSub_Click(object sender, EventArgs e)
        {
            a = Convert.ToDouble(textBoxResult.Text);
            textBoxResult.Clear();
            count = 4;
            label3.Text = a.ToString() + "-";
            sgn = true;
        }

        public static double sum(double a, double b) // Сумма
        {
            return a + b;
        }
        public static double dev(double a, double b) // Деление
        {
            return a / b;
        }
        public static double sub(double a, double b) // вычитание
        {
            return a - b;
        }
        public static double mul(double a, double b) // умножение
        {
            return a * b;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            textBoxResult.Text = textBoxResult.Text + 1;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            textBoxResult.Text = textBoxResult.Text + 2;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            textBoxResult.Text = textBoxResult.Text + 3;
        }

        private void button4_Click(object sender, EventArgs e)
        {
            textBoxResult.Text = textBoxResult.Text + 4;
        }

        private void button5_Click(object sender, EventArgs e)
        {
            textBoxResult.Text = textBoxResult.Text + 5;
        }

        private void button6_Click(object sender, EventArgs e)
        {
            textBoxResult.Text = textBoxResult.Text + 6;
        }

        private void button7_Click(object sender, EventArgs e)
        {
            textBoxResult.Text = textBoxResult.Text + 7;
        }
        private void button8_Click(object sender, EventArgs e)
        {
            textBoxResult.Text = textBoxResult.Text + 8;
        }
        private void button9_Click(object sender, EventArgs e)
        {
            textBoxResult.Text = textBoxResult.Text + 9;
        }
        private void button0_Click(object sender, EventArgs e)
        {
            textBoxResult.Text = textBoxResult.Text + 0;
        }

        private void buttonComma_Click(object sender, EventArgs e)
        {
            textBoxResult.Text = textBoxResult.Text + ",";
        }

        private void buttonQually_Click(object sender, EventArgs e)
        {
            calculate();
            label3.Text = "";
        }

        private void ButtonC_Click(object sender, EventArgs e)
        {
            textBoxResult.Text = "";
            label3.Text = "";
        }

        private void button16_Click(object sender, EventArgs e)
        {
            int lenght = textBoxResult.Text.Length - 1;
            string text = textBoxResult.Text;
            textBoxResult.Clear();
            for (int i = 0; i < lenght; i++)
                textBoxResult.Text = textBoxResult.Text + text[i];
        }

        private void buttonNeg_Click(object sender, EventArgs e)
        {
            if (sgn == true)
            {
                textBoxResult.Text = "-" + textBoxResult.Text;
                sgn = false;
            }
            else if (sgn == false)
            {
                textBoxResult.Text = textBoxResult.Text.Replace("-", "+");
                sgn = true;
            }
        }

    }
}
