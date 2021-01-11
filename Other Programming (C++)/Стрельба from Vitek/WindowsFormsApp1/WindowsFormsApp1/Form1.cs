using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        int r1 = -1, r2 = -1, count = -1;
        bool isallinput = false;
        bool painting = false;
        Butt tir;
        public Form1()
        {
            tir = new Butt(120, 200, 0, new Point(Width / 2, Height / 2));
            InitializeComponent();
            FormBorderStyle = FormBorderStyle.FixedSingle;
        }
        protected override void OnPaint(PaintEventArgs e)
        {
            if (painting)
            {
                base.OnPaint(e);
                DrawShooting(ClientRectangle, e.Graphics);
            }
        }

        //Нарисовать мишень
        private void DrawShooting(Rectangle r, Graphics g)
        {
            g.Clear(Color.White);
            int H = r.Height, W = r.Width;
            Point WN = new Point(0, 0);//левая верхняя 
            Point WS = new Point(WN.X, WN.Y + H);//левая нижняя
            Point ES = new Point(WN.X + W, WN.Y + H);//правая нижняя 
            Point EN = new Point(WN.X + W, WN.Y);//правая верхняя 
            Point Middle = new Point(WN.X + W / 2, WN.Y + H / 2);

            SolidBrush brush = new SolidBrush(Color.Gray);
            Pen pen = new Pen(Color.Black, 2);

            g.FillPie(brush, tir.Op_r2, 0, 90);
            g.FillPie(brush, tir.Op_r1, 180, 90);
            brush.Color = Color.White;
            g.FillPie(brush, tir.Op_r1, 0, 90);
            g.DrawLine(pen, tir.MiddleP.X + W / 2, tir.MiddleP.Y, tir.MiddleP.X - W / 2, tir.MiddleP.Y);
            g.DrawLine(pen, tir.MiddleP.X, tir.MiddleP.Y + H / 2, tir.MiddleP.X, tir.MiddleP.Y - H / 2);
            g.DrawEllipse(pen, tir.Op_r1);

            brush.Color = Color.Black;
            Font font = new Font("Courier New", 15, FontStyle.Bold | FontStyle.Italic);
            StringFormat drawFormat = new System.Drawing.StringFormat();
            g.DrawString("Shooting", font, brush, 0, 0, drawFormat);

            for(int i=0;i<tir.Hit.Count;i++)
            {
                brush.Color = Color.Red;
                g.FillEllipse(brush, tir.Hit[i].X - 3, tir.Hit[i].Y - 3, 6, 6);
            }

            font.Dispose();
            brush.Dispose();
            font.Dispose();
        }

        //радиус1 изменение
        private void tb_r1_TextChanged(object sender, EventArgs e)
        { 
        try
            {
                if ((sender as TextBox).Text == "")
                {
                    isallinput = false;
                    r1 = -1;
                    return;
                }
                r1 = Convert.ToInt32((sender as TextBox).Text);
                if (r1 < 1) throw new FormatException();
                else
                {
                    if (r1 >= (Height - 10) / 2) throw new Exception();
                    if (r1 > 0 && r2 > 0 && count > 0) isallinput = true;    
                }
            }
            catch (FormatException)
            {
                MessageBox.Show("Некорректные данные r1, повторите ввод");
            }
            catch (Exception)
            {
                MessageBox.Show("Введенный радиус r1 слишком большой для данной формы");
            }
        }

        //радиус2 изменение
        private void tb_r2_TextChanged(object sender, EventArgs e)
        {
            try
            {
                if ((sender as TextBox).Text == "")
                {
                    isallinput = false;
                    r2 = -1;
                    return;
                }
                r2 = Convert.ToInt32((sender as TextBox).Text);
                if (r2 < 1) throw new FormatException();
                else
                {
                    if (r2 >= (Height - 10) / 2) throw new Exception();
                    if (r1 > 0 && r2 > 0 && count > 0) isallinput = true;
                }
            }
            catch (FormatException)
            {
                MessageBox.Show("Некорректные данные r2, повторите ввод");
            }
            catch (Exception)
            {
                MessageBox.Show("Введенный радиус r2 слишком большой для данной формы");
            }
        }

        //Количество патронов
        private void tb_count_TextChanged(object sender, EventArgs e)
        {
            try
            {
                if ((sender as TextBox).Text == "")
                {
                    isallinput = false;
                    count = -1;
                    return;
                }
                count = Convert.ToInt32((sender as TextBox).Text);
                if (count < 1) throw new FormatException();
                else
                {
                    if (r1 > 0 && r2 > 0 && count > 0) isallinput = true;
                }
            }
            catch (Exception)
            {
                MessageBox.Show("Некорректные данные \"количества\", повторите ввод");
            }
        }

        //начать игру
        private void button1_Click(object sender, EventArgs e)
        {
            if(isallinput)
            {
                #region disable
                label1.Visible = false;
                label2.Visible = false;
                label3.Visible = false;
                label4.Visible = false;
                label5.Visible = false;
                button1.Visible = false;
                tb_count.Visible = false;
                tb_r1.Visible = false;
                tb_r2.Visible = false;

                label1.Enabled = false;
                label2.Enabled = false;
                label3.Enabled = false;
                label4.Enabled = false;
                label5.Enabled = false;
                button1.Enabled = false;
                tb_count.Enabled = false;
                tb_r1.Enabled = false;
                tb_r2.Enabled = false;
                #endregion
                tir = new Butt(r1, r2, count, new Point(Width / 2, Height / 2));
                painting = isallinput;
                Invalidate();
            }
            else
            {
                MessageBox.Show("Перед тем, как начать, необходимо ввести все данные!");
            }
        }

        //Нажатие мыши
        private void Form1_MouseClick(object sender, MouseEventArgs e)
        {
            if (!painting) return;
            if (tir.Shot(e.Location))
            {
                label8.Text = tir.Nomissing.ToString();
                label9.Text = tir.Missing.ToString();
                label10.Text = (tir.Shooting_nomber - (tir.Nomissing + tir.Missing)).ToString();
                Invalidate();
            }
            else
            {
                MessageBox.Show("Боеприпасы окончились, пополните обойму или начните сначала");
                #region enable
                painting = false;
                label13.Enabled = true;
                label12.Enabled = true;
                tb_reload.Enabled = true;
                label13.Visible = true;
                label12.Visible = true;
                tb_reload.Visible = true;
                button2.Visible = true;
                button4.Visible = true;
                button4.Enabled = true;
                button2.Enabled = true;
                #endregion

            }
        }

        //Перезапустить игру
        private void button2_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start(Application.ExecutablePath); // Для запуска нового экземпляра приложения
            Close(); // выключить текущее приложение
        }

        //Добавить патроны
        private void tb_reload_Validating(object sender, CancelEventArgs e)
        {
            try
            {
                if ((sender as TextBox).Text == "")
                {
                    return;
                }
                count = Convert.ToInt32((sender as TextBox).Text);
                if (count < 1) throw new FormatException();
                else
                {
                    if (count > 0)
                    {
                        #region disable
                        painting = true;
                        label13.Enabled = false;
                        label12.Enabled = false;
                        tb_reload.Enabled = false;
                        label13.Visible = false;
                        label12.Visible = false;
                        tb_reload.Visible = false;
                        button2.Visible = false;
                        button2.Enabled = false;
                        button4.Visible = false;
                        button4.Enabled = false;
                        #endregion
                        tir.Shooting_nomber += count;
                        label10.Text = (tir.Shooting_nomber - (tir.Nomissing + tir.Missing)).ToString();
                        Invalidate();

                    }
                }
            }
            catch (Exception)
            {
                MessageBox.Show("Некорректные данные \"количества\", повторите ввод");
            }
            (sender as TextBox).Clear();
        }

        //Изменить размер
        private void Form1_Resize(object sender, EventArgs e)
        {
            tir.ChangeMidllepoint(new Point(Width / 2, Height / 2));
            Invalidate();
        }
    }
}
