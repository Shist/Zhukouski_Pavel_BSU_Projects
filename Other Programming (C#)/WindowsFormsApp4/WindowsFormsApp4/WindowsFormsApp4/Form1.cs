using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp4
{
    public partial class Form1 : Form
    {
        bool f = false;

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Поздравляю, ты дурак!");
            Close();
        }

        private void button2_MouseMove(object sender, MouseEventArgs e)
        {
            if(!f)
            {
                int ox = e.X, oy = e.Y;
                ox += button2.Location.X;
                oy += button2.Location.Y;
                int bx = button2.Location.X;
                int by = button2.Location.Y;
                Point nw = button2.Location;
                nw.X = (button2.Location.X + button2.Width / 2);
                nw.Y = (button2.Location.Y + button2.Height / 2);
                nw.X = nw.X + (nw.X - ox) / 2 - button2.Width / 2;
                nw.Y = nw.Y + (nw.Y - oy) / 2 - button2.Height / 2;
                if (nw.Y < 0 || nw.Y > Height-100) nw.Y = (Height-50)/2;
                if (nw.X < 0 || nw.X > Width-120) nw.X = (Width-60)/2;

                button2.Location = nw;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (f)
            {
                MessageBox.Show("Поздравляю, ты читер!");
                Close();
            }
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            if (textBox1.Text == "bsu") f = true;
        }
    }
}
