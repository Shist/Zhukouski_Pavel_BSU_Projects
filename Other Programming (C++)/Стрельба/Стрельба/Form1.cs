using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

namespace Стрельба
{
    public partial class Form1 : Form
    {
        int r = -1;
        int _2a = -1;
        int _2b = -1;
        int count = -1;
        int x = -1000;
        int y = -1000;
        bool isallinput = false;
        bool painting = false;
        Butt tir;
        public Form1()
        {
            tir = new Butt(150, 360, 240, 0, new Point(Width / 2, Height / 2));
            InitializeComponent();
            FormBorderStyle = FormBorderStyle.FixedToolWindow; // Фиксация окна (на всякий случай)
            MaximizeBox = false;
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
            int W = r.Width; // Длина (по иксу)
            int H = r.Height; // Ширина (по игрику)
            Point WN = new Point(0, 0); // Левая верхняя 
            Point WS = new Point(WN.X, WN.Y + H); // Левая нижняя
            Point ES = new Point(WN.X + W, WN.Y + H); // Правая нижняя 
            Point EN = new Point(WN.X + W, WN.Y); // Правая верхняя 
            Point Middle = new Point(WN.X + W / 2, WN.Y + H / 2);

            SolidBrush brush = new SolidBrush(Color.Gray);
            Pen pen = new Pen(Color.Black, 2);

            g.FillPie(brush, tir.Op_r, 90, 90); // Красим в серый весь нижний левый сектор
            g.FillRectangle(brush, Width / 2, (float)(Height - tir.Shirina) / 2, (float)tir.Dlina / 2, (float)tir.Shirina / 2); // Красим в серый весь правый верхний прямоугольник

            brush.Color = Color.White;

            g.FillPie(brush, tir.Op_r, 270, 90); // Закрашиваем в белый весь верхний правый сектор
            g.FillRectangle(brush, 0, Height / 2, (float)(Width - tir.Dlina) / 2, Height / 2); // Далее двумя прямоугольниками закрашиваем белым за пределами левого нижнего угла стрельбища
            g.FillRectangle(brush, (float)(Width - tir.Dlina) / 2, (float)(Height + tir.Shirina) / 2, (float)tir.Dlina / 2, (float)(Height - tir.Shirina) / 2);
            g.DrawLine(pen, tir.MiddleP.X + W / 2, tir.MiddleP.Y, tir.MiddleP.X - W / 2, tir.MiddleP.Y); // Рисуем ось Ox
            g.DrawLine(pen, tir.MiddleP.X, tir.MiddleP.Y + H / 2, tir.MiddleP.X, tir.MiddleP.Y - H / 2); // Рисуем ось Oy
            g.DrawEllipse(pen, tir.Op_r); // Рисиуем окружность
            g.DrawRectangle(pen, (float)(Width - tir.Dlina) / 2, (float)(Height - tir.Shirina) / 2, (float)tir.Dlina, (float)tir.Shirina); // Рисуем прямоугольник 

            brush.Color = Color.Black;
            Font font = new Font("Courier New", 15, FontStyle.Bold | FontStyle.Italic);
            StringFormat drawFormat = new System.Drawing.StringFormat();
            g.DrawString("Стрельба", font, brush, 0, 0, drawFormat); // Рисуем надпись "Стрельба" слева сверху

            for (int i = 0; i < tir.Hit.Count; i++)
            { // Красными круглешками закрашиваем выстрелы
                brush.Color = Color.Red;
                g.FillEllipse(brush, tir.Hit[i].X - 3, tir.Hit[i].Y - 3, 6, 6);
            }

            font.Dispose();
            brush.Dispose();
            font.Dispose();
        }

        private void tb_r_TextChanged(object sender, EventArgs e)
        { // Ввод радиуса
            try
            {
                if ((sender as TextBox).Text == "")
                {
                    isallinput = false;
                    r = -1;
                    return;
                }
                r = Convert.ToInt32((sender as TextBox).Text);
                if (r < 1) throw new FormatException();
                else
                {
                    if (r >= (Height - 10) / 2) throw new Exception();
                    if (r > 0 && _2a > 0 && _2b > 0 && count > 0) isallinput = true;
                }
            }
            catch (FormatException)
            {
                MessageBox.Show("Некорректные данные R, повторите ввод");
            }
            catch (Exception)
            {
                MessageBox.Show("Введенный радиус R слишком большой для данной формы");
            }
        }

        private void tb_2a_TextChanged(object sender, EventArgs e)
        { // Ввод длины
            try
            {
                if ((sender as TextBox).Text == "")
                {
                    isallinput = false;
                    _2a = -1;
                    return;
                }
                _2a = Convert.ToInt32((sender as TextBox).Text);
                if (_2a < 1) throw new FormatException();
                else
                {
                    if (_2a >= Width - 10) throw new Exception();
                    if (r > 0 && _2a > 0 && _2b > 0 && count > 0) isallinput = true;
                }
            }
            catch (FormatException)
            {
                MessageBox.Show("Некорректные данные _2a, повторите ввод");
            }
            catch (Exception)
            {
                MessageBox.Show("Введенная длина прямоугольника слишком большая для данной формы");
            }
        }

        private void tb_2b_TextChanged(object sender, EventArgs e)
        { // Ввод ширины
            try
            {
                if ((sender as TextBox).Text == "")
                {
                    isallinput = false;
                    _2b = -1;
                    return;
                }
                _2b = Convert.ToInt32((sender as TextBox).Text);
                if (_2b < 1) throw new FormatException();
                else
                {
                    if (_2b >= Height - 10) throw new Exception();
                    if (r > 0 && _2a > 0 && _2b > 0 && count > 0) isallinput = true;
                }
            }
            catch (FormatException)
            {
                MessageBox.Show("Некорректные данные _2a, повторите ввод");
            }
            catch (Exception)
            {
                MessageBox.Show("Введенная длина прямоугольника слишком большая для данной формы");
            }
        }
        
        private void tb_count_TextChanged(object sender, EventArgs e)
        { // Ввод количества патронов (изначально)
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
                    if (r > 0 && _2a > 0 && _2b > 0 && count > 0) isallinput = true;
                }
            }
            catch (Exception)
            {
                MessageBox.Show("Некорректные данные \"количества\", повторите ввод");
            }
        }

        // СТАРТ
        private void button1_Click(object sender, EventArgs e)
        {
            if (isallinput)
            {
                #region disable
                label1.Visible = false;
                label2.Visible = false;
                label3.Visible = false;
                label4.Visible = false;
                label5.Visible = false;
                label6.Visible = false;
                label7.Visible = false;
                label8.Visible = false;
                tb_r.Visible = false;
                tb_2a.Visible = false;
                tb_2b.Visible = false;
                tb_count.Visible = false;
                button1.Visible = false;

                label1.Enabled = false;
                label2.Enabled = false;
                label3.Enabled = false;
                label4.Enabled = false;
                label5.Enabled = false;
                label6.Enabled = false;
                label7.Enabled = false;
                label8.Enabled = false;
                tb_r.Enabled = false;
                tb_2a.Enabled = false;
                tb_2b.Enabled = false;
                tb_count.Enabled = false;
                button1.Enabled = false;

                label16.Enabled = true;
                label16.Visible = true;
                tb_x.Enabled = true;
                tb_x.Visible = true;
                tb_y.Enabled = true;
                tb_y.Visible = true;
                button4.Enabled = true;
                button4.Visible = true;
                #endregion
                tir = new Butt(r, _2a, _2b, count, new Point(Width / 2, Height / 2));
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
                label10.Text = tir.Nomissing.ToString();
                label12.Text = tir.Missing.ToString();
                label14.Text = (tir.Shooting_nomber - (tir.Nomissing + tir.Missing)).ToString();
                Invalidate();
            }
            else
            {
                MessageBox.Show("Боеприпасы окончились, пополните обойму или начните сначала");
                #region enable
                painting = false;
                label15.Enabled = true;
                tb_reload.Enabled = true;
                button2.Enabled = true;
                button3.Enabled = true;
                label15.Visible = true;
                tb_reload.Visible = true;
                button2.Visible = true;
                button3.Visible = true;
                button4.Enabled = false;
                #endregion
            }
        }

        // Изменить размеры мишени (перезапустить игру)
        private void button3_Click(object sender, EventArgs e)
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
                        label15.Enabled = false;
                        label16.Enabled = false;
                        tb_reload.Enabled = false;
                        button2.Enabled = false;
                        button3.Enabled = false;
                        label15.Visible = false;
                        label16.Visible = false;
                        tb_reload.Visible = false;
                        button2.Visible = false;
                        button3.Visible = false;
                        label16.Enabled = true;
                        label16.Visible = true;
                        tb_x.Enabled = true;
                        tb_x.Visible = true;
                        tb_y.Enabled = true;
                        tb_y.Visible = true;
                        button4.Enabled = true;
                        #endregion
                        tir.Shooting_nomber += count;
                        label14.Text = (tir.Shooting_nomber - (tir.Nomissing + tir.Missing)).ToString();
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

        private void Form1_Resize(object sender, EventArgs e)
        {
            tir.ChangeMidllepoint(new Point(Width / 2, Height / 2));
            Invalidate();
        }

        private void button4_Click(object sender, EventArgs e)
        { // Стрельнуть по координатам
            try
            {
                if ((tb_x as TextBox).Text == "")
                {
                    x = -1000;
                    return;
                }
                x = Convert.ToInt32((tb_x as TextBox).Text);
                if (x >= Width / 2 || x <= (-1) * (Width / 2)) throw new Exception("Введенная координата x слишком большая для данной формы");
                if ((tb_y as TextBox).Text == "")
                {
                    y = -1000;
                    return;
                }
                y = Convert.ToInt32((tb_y as TextBox).Text);
                if (y >= Height / 2 || y <= (-1) * (Height / 2)) throw new Exception("Введенная координата y слишком большая для данной формы");
                if (!painting) return;
                if (tir.Shot(new Point(tir.MiddleP.X + x, tir.MiddleP.Y - y)))
                {
                    label10.Text = tir.Nomissing.ToString();
                    label12.Text = tir.Missing.ToString();
                    label14.Text = (tir.Shooting_nomber - (tir.Nomissing + tir.Missing)).ToString();
                    Invalidate();
                }
                else
                {
                    MessageBox.Show("Боеприпасы окончились, пополните обойму или начните сначала");
                    #region enable
                    painting = false;
                    label15.Enabled = true;
                    tb_reload.Enabled = true;
                    button2.Enabled = true;
                    button3.Enabled = true;
                    label15.Visible = true;
                    tb_reload.Visible = true;
                    button2.Visible = true;
                    button3.Visible = true;
                    button4.Enabled = false;
                    #endregion
                }
            }
            catch (FormatException)
            {
                MessageBox.Show("Некорректные данные x или y, повторите ввод");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
    }

    class Butt // Стрельбище
    {
        double radius = 100; // Радиус окружности
        double _2a = 100; // Длина прямоугольника (2a)
        double _2b = 100; // Ширина прямоугольника (2b)
        int shooting_nomber; // Патроны
        int missing = 0; // Промахи
        int nomissing = 0; // Попадания
        Point middleP; // Центральная точка
        List<Point> hit; // Список выстрелов
        Rectangle op_r; // Прямоугольник, окаймляющий окружность

        #region properties
        public double Radius { get => radius; private set => radius = value; }
        public double Dlina { get => _2a; private set => _2a = value; }
        public double Shirina { get => _2b; private set => _2b = value; }
        public Point MiddleP { get => middleP; private set => middleP = value; }
        public List<Point> Hit { get => hit; private set => hit = value; }
        public int Missing { get => missing; private set => missing = value; }
        public int Nomissing { get => nomissing; private set => nomissing = value; }
        public Rectangle Op_r { get => op_r; private set => op_r = value; }
        public int Shooting_nomber { get => shooting_nomber; set => shooting_nomber = value; }
        #endregion

        public Butt(double r, double dl, double sh, int sh_nom, Point Mid)
        {
            Radius = r;
            _2a = dl;
            _2b = sh;
            Shooting_nomber = sh_nom;
            Hit = new List<Point>();
            MiddleP = Mid;
            Op_r = new Rectangle(Mid.X - (int)r, Mid.Y - (int)r, 2 * (int)r, 2 * (int)r);
        }

        public bool Shot(Point A)
        {
            if (Hit.Count < Shooting_nomber)
            {
                Hit.Add(A);
                if (ishitting(A))
                {
                    Nomissing++;
                }
                else
                {
                    Missing++;
                }
                return true;
            }
            else
            {
                return false;
            }

        }

        private bool ishitting(Point A) // Проверка на попадание точки А в мишень
        {
            double dist = Math.Sqrt(Math.Pow((A.X - MiddleP.X), 2) + Math.Pow((A.Y - MiddleP.Y), 2)); // Расстояние от точки до центра
            if (dist >= Radius && // Если это расстояние больше радиуса окружности...
                A.X >= MiddleP.X && A.X <= (MiddleP.X + _2a / 2) &&
                A.Y >= (MiddleP.Y - _2b / 2) && A.Y <= MiddleP.Y) return true;
            if (dist <= Radius && // Если это расстояние меньше радиуса окружности...
                A.X >= (MiddleP.X - _2a / 2) && A.X <= MiddleP.X &&
                A.Y >= MiddleP.Y && A.Y <= (MiddleP.Y + _2b / 2)) return true;
            return false;
        }

        public void ChangeMidllepoint(Point A) // Если нужно будет поменять размеры поля
        {
            Point Del = new Point(A.X - MiddleP.X, A.Y - MiddleP.Y);
            MiddleP = A;
            Op_r = new Rectangle(MiddleP.X - (int)Radius, MiddleP.Y - (int)Radius, 2 * (int)Radius, 2 * (int)Radius);
            for (int i = 0; i < Hit.Count; i++)
            {
                Hit[i] = new Point(Hit[i].X + Del.X, Hit[i].Y + Del.Y);
            }
        }
    }
}