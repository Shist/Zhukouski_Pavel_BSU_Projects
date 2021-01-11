using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Вы_дурак
{
    public partial class Form1 : Form
    {
        bool chit_code = false; // Проверка на правильность чит-кода

        public Form1()
        {
            InitializeComponent();
        }

        private void label1_Click(object sender, EventArgs e) // Надпись "Вы дурак?"
        {

        }

        private void button1_Click(object sender, EventArgs e) // Кнопка "Да"
        {
            MessageBox.Show("Поздравляю, вы дурак"); // Если пользователь тыкает "да", то выводим это сообщение
            Application.Exit(); // И выходим из приложения
        }

        private void button2_MouseMove(object sender, MouseEventArgs e) // Кнопка "Нет"
        {
            
        }

        private void button2_Click(object sender, EventArgs e) // Кнопка "Нет"
        {
            if (chit_code) // Если кнопка "Нет" нажата после введения правильного чит-кода
            {
                MessageBox.Show("Вы не дурак...");
                Application.Exit(); // Выходим из приложения
            }
            else
            {
                MessageBox.Show("Неплохая попытка"); // Если пользователь вдруг попал по кнопке "Нет" до правильного ввода чит-кода
            }
        }

        private void label2_Click(object sender, EventArgs e) // Надпись "Введите чит-код:"
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e) // Поле для чит-кода
        {
            if (textBox1.Text == "10")
            {
                chit_code = true;
            }
            else
            {
                chit_code = false;
            }
        }

        private void button2_MouseMove_1(object sender, MouseEventArgs e)
        {
            if (!chit_code)
            {
                int ox = e.X;
                int oy = e.Y;
                ox += button2.Location.X;
                oy += button2.Location.Y;
                Point nw = button2.Location; // В центре кнопки "Нет" создаем точку и в зависимости от расстояния до нее двигаем кнопку и эту точку
                nw.X = (button2.Location.X + button2.Width / 2);
                nw.Y = (button2.Location.Y + button2.Height / 2);
                nw.X = nw.X + (nw.X - ox) / 2 - button2.Width / 2;
                nw.Y = nw.Y + (nw.Y - oy) / 2 - button2.Height / 2;
                if (nw.Y < 0 || nw.Y > Height - 80) nw.Y = Height / 2; // Проверка на верхние и нижние границы фомры
                if (nw.X < 0 || nw.X > Width - 100) nw.X = Width / 2; // Проверка на правые и левые границы фомры
                button2.Location = nw;
            }
        }
    }
}
