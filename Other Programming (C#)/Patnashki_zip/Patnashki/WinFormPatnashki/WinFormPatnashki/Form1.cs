using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WinFormPatnashki
{
    
    public partial class Form1 : Form
    {
        private DateTime t1;
        private GameEngine game;

        public DateTime T1 { get => t1; set => t1 = value; }

        //initialize
        public Form1()
        {
            InitializeComponent();
            timer1.Stop();
            game = new GameEngine(4, 4);
            textBox1.Text = "0";
            textBox2.Text = "0";
            timer1.Interval = 1000;
            int count = 1;
            for (int i = 0; i < 16; i++)
            {
                (tableLayoutPanel1.Controls["button" + Convert.ToString(count)]).Enabled = false;
                count++;
            }

        }

        private void tableLayoutPanel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
        //All button
        private void button14_Click(object sender, EventArgs e)
        {
            if (sender is Button)
            {
                int position = Convert.ToInt32((sender as Button).Tag);
                game.Change(position);
                refresh_buttons();
                if (game.iswin())
                {
                    int count = 1;
                    for (int i = 0; i < 16; i++)
                    {
                        (tableLayoutPanel1.Controls["button" + Convert.ToString(count)]).Enabled = false;
                        count++;
                    }
                    timer1.Stop();
                    MessageBox.Show("Вы выйграли!!!");
                }
            }
        }
        //timer
        private void timer1_Tick(object sender, EventArgs e)
        {
            T1=T1.AddSeconds(1);
            textBox2.Text = T1.TimeOfDay.ToString();
        }
        //start game button
        private void button17_Click(object sender, EventArgs e)
        {
            T1 = new DateTime(1, 1, 1, 0, 0, 0);
            int count = 1;
            timer1.Start();
            for (int i = 0; i < 16; i++)
            {
                (tableLayoutPanel1.Controls["button" + Convert.ToString(count)] as Button).Enabled = true;
                count++;
            }
            game.StartGame();
            refresh_buttons();
           
        }
        //reload game button
        private void reloadButton_Click(object sender, EventArgs e)
        {
            T1 = new DateTime(1, 1, 1, 0, 0, 0);
            timer1.Start();
            int count = 1;
            for (int i = 0; i < 16; i++)
            {
                tableLayoutPanel1.Controls["button" + Convert.ToString(count)].Enabled = true;
                count++;
            }
            game.ReloadGame();
            refresh_buttons();

        }
        private void refresh_buttons()
        {
            int count = 0;
            for (int i = 0; i < game.Coord_size.Item1; i++)
                for (int j = 0; j < game.Coord_size.Item2; j++)
                {
                    count++;
                    string temp = "button" + Convert.ToString(count);

                    if (game.Mass[i, j]==0) tableLayoutPanel1.Controls[temp].Visible = false;
                    else
                    {
                        tableLayoutPanel1.Controls[temp].Visible = true;
                        tableLayoutPanel1.Controls[temp].Text = Convert.ToString(game.Mass[i, j]);
                    }
                }
            textBox1.Text = Convert.ToString(game.Motion_count);
        }
    }
}
