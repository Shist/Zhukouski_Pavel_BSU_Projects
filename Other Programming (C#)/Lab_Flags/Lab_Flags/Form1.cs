using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab_Flags
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        bool num_flag = true; // true - первый флаг; false - второй флаг

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);
            if (num_flag)
            {
                DrawFlag_1(ClientRectangle, e.Graphics);
            }
            else
            {
                DrawFlag_2(ClientRectangle, e.Graphics);
            }
        }

        protected override void OnKeyDown(KeyEventArgs e)
        { // При нажатии любой кнопки мы меняем флаг на другой
            base.OnKeyDown(e);
            if (num_flag)
            {
                num_flag = false;
            }
            else
            {
                num_flag = true;
            }
            Invalidate();
        }

        private void DrawFlag_1(Rectangle r, Graphics g)
        {
            g.Clear(Color.Gray); // Ставим серый фон
            const int PROPX = 2, PROPY = 3; // С помощью этих параметров задаем пропорции самого флага
            int H = r.Height;
            int W = r.Width;
            Point WN = new Point(0, 0);
            if (PROPX * r.Width > PROPY * r.Height) // Широкое поле
            {
                W = H * PROPY / PROPX;
                WN.X = (r.Width - W) / 2;
            }
            else if (PROPX * r.Width < PROPY * r.Height) // Высокое поле
            {
                H = W * PROPX / PROPY;
                WN.Y = (r.Height - H) / 2;
            }
            SolidBrush brush = new SolidBrush(Color.Yellow); // Кисть (по умолчанию ставим желтый цвет)
            Pen pen = new Pen(brush); // Ручка
            g.FillRectangle(brush, WN.X, WN.Y, W, H); // Рисуем сначала желтый фон флага
            Point A = new Point(WN.X, WN.Y + H); // Точка слева снизу
            Point B = new Point(WN.X + W * 2 / 3, WN.Y); // Точка вверху (ближе к середине)
            Point C = new Point(WN.X + W * 1 / 3, WN.Y + H); // Точка внизу (ближе к середине)
            Point D = new Point(WN.X + W, WN.Y); // Точка справа вверху
            Point E = new Point(WN.X + W, WN.Y + H); // Точка справа внизу
            Point[] red_part = new Point[3]; // Красный треугольник (массив из трёх точек)
            Point[] green_part = new Point[3]; // Зеленый треугольник (массив из трёх точек)
            red_part[0] = C;
            red_part[1] = D;
            red_part[2] = E;
            green_part[0] = A;
            green_part[1] = B;
            green_part[2] = WN;
            brush.Color = Color.Red; // Ставим цвет кисти на красный
            g.FillPolygon(brush, red_part); // Зарисовываем красную часть
            brush.Color = Color.Green; // Ставим цвет кисти на зелёный
            g.FillPolygon(brush, green_part); // Зарисовываем зелёную часть
            brush.Color = Color.Black; // Ставим цвет на чёрный, чтобы подписать название страны
            Font font = new Font("Courier New", 15, FontStyle.Bold | FontStyle.Italic); // Шрифт
            StringFormat drawFormat = new System.Drawing.StringFormat(); // Формат рисования (строчный)
            g.DrawString("Республика Конго", font, brush, 0, 0, drawFormat); // Рисуем название страны
            brush.Dispose(); // Отключаем кисть
            pen.Dispose(); // Отключаем ручку
            font.Dispose(); // Отключаем шрифт
        }

        private void DrawFlag_2(Rectangle r, Graphics g)
        {
            g.Clear(Color.Gray); // Ставим серый фон
            const int PROPX = 2, PROPY = 3; // С помощью этих параметров задаем пропорции самого флага
            int H = r.Height;
            int W = r.Width;
            Point WN = new Point(0, 0);
            if (PROPX * r.Width > PROPY * r.Height) // Широкое поле
            {
                W = H * PROPY / PROPX;
                WN.X = (r.Width - W) / 2;
            }
            else if (PROPX * r.Width < PROPY * r.Height) // Высокое поле
            {
                H = W * PROPX / PROPY;
                WN.Y = (r.Height - H) / 2;
            }
            SolidBrush brush = new SolidBrush(Color.White); // Кисть (по умолчанию ставим желтый цвет)
            Pen pen = new Pen(brush); // Ручка
            g.FillRectangle(brush, WN.X, WN.Y, W, H); // Рисуем сначала белый фон флага
            Point A = new Point(WN.X, WN.Y + H * 1 / 5); // Точка слева сверху (ближе к середине)
            Point B = new Point(WN.X, WN.Y + H * 1 / 10); // Точка слева сверху (ближе к верху)
            Point C = new Point(WN.X + W, WN.Y + H * 1 / 10); // Точка справа сверху (ближе к верху)
            Point D = new Point(WN.X + W, WN.Y + H * 1 / 5); // Точка справа сверху (блиэе к середине)
            Point[] red_part_1 = new Point[4]; // Верхняя красная полоса
            red_part_1[0] = A;
            red_part_1[1] = B;
            red_part_1[2] = C;
            red_part_1[3] = D;
            brush.Color = Color.Red; // Ставим цвет кисти на красный
            g.FillPolygon(brush, red_part_1); // Зарисовываем верхнуюю красную полосу
            Point E = new Point(WN.X, WN.Y + H * 9 / 10); // Точка слева снизу (ближе к низу)
            Point F = new Point(WN.X, WN.Y + H * 4 / 5); // Точка слева снизу (ближе к середине)
            Point G = new Point(WN.X + W, WN.Y + H * 4 / 5); // Точка справа снизу (ближе к середине)
            Point J = new Point(WN.X + W, WN.Y + H * 9 / 10); // Точка справа снизу (ближе к низу)
            Point[] red_part_2 = new Point[4]; // Нижняя красная полоса
            red_part_2[0] = E;
            red_part_2[1] = F;
            red_part_2[2] = G;
            red_part_2[3] = J;
            g.FillPolygon(brush, red_part_2); // Зарисовываем нижнюю красную полосу
            g.FillEllipse(brush, WN.X + W / 6, WN.Y + H / 4, H / 2, H / 2); // Рисуем большой красный круг в центре
            brush.Color = Color.White; // Временно возвращаем кисти белый цвет...
            g.FillEllipse(brush, WN.X + W * 29 / 120, WN.Y + H * 3 / 10, H * 2 / 5, H * 2 / 5); // Рисуем малый белый круг в центре, чтобы получился полумесяц
            brush.Color = Color.Red; // Снова возвращаем кисти красный цвет
            int CounterBig = 0; // Начинаем рисовать звезду
            double Fi = Math.PI * 72 / 180;
            Point[] Corner = new Point[10];
            Point[] Small = new Point[10];
            for (int i = 0; i < 5; i++)
            {
                double newX = (WN.X + W * 57 / 100) - ((H / 4) / 2) * Math.Sin(Fi * i + 0.25);
                double newY = (WN.Y + H / 2) - ((H / 4) / 2) * Math.Cos(Fi * i + 0.25);
                Corner[CounterBig] = new Point((int)newX, (int)newY);
                CounterBig += 2;
            }
            for (int i = 0; i < 5; i++)
            {
                double newX = (WN.X + W * 57 / 100) + ((H / 4) / 5) * Math.Sin(Fi * i + 0.25);
                double newY = (WN.Y + H / 2) + ((H / 4) / 5) * Math.Cos(Fi * i + 0.25);
                Small[i] = new Point((int)newX, (int)newY);
            }
            Corner[1] = Small[3];
            Corner[3] = Small[4];
            Corner[5] = Small[0];
            Corner[7] = Small[1];
            Corner[9] = Small[2];
            g.FillPolygon(brush, Corner);
            brush.Color = Color.Black; // Ставим цвет на чёрный, чтбы подписать название страны
            Font font = new Font("Courier New", 15, FontStyle.Bold | FontStyle.Italic); // Шрифт
            StringFormat drawFormat = new System.Drawing.StringFormat(); // Формат рисования (строчный)
            g.DrawString("Турецкая Республика Северного Кипра", font, brush, 0, 0, drawFormat); // Рисуем название страны
            brush.Dispose(); // Отключаем кисть
            pen.Dispose(); // Отключаем ручку
            font.Dispose(); // Отключаем шрифт
        }

        protected override void OnResize(EventArgs e)
        {
            base.OnResize(e);
            Invalidate(); // Эта вещь нам нужла для того, чтобы при изменении размеров окна флаг оставался нормальным
        }
    }
}
