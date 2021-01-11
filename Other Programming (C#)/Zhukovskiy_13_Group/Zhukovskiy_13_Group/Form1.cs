// ВАРИАНТ 1-1 (Жуковский Павел из 13-ой группы)
// Честно скажу, многие идеи для создания основы формы я взял у Вани Калинчука, решение пробного варианта которого вы сбросили к нам в облако.
// Так что передаю ему спасибо, ну а вам...
// Приятной проверки, Сергей Иванович!
using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Windows.Forms;

namespace Zhukovskiy_13_Group
{
    public partial class Form1 : Form
    {
        private PictureField Field;

        List<Point> Default_Points = new List<Point>();

        public Form1()
        {
            InitializeComponent();
            SetDefaults();
            DownloadData();
            PrintCountedQuarter();
            PrintSortedPoints();
        }

        private void PrintSortedPoints()
        {
            Default_Points.Sort(new PointComparer());

            StreamWriter writer = new StreamWriter("OUTPUT.TXT");

            writer.WriteLine("Точки, отсортированные по координате y:");

            foreach (Point p in Default_Points)
            {
                RTextBox_SortePoints.Text += p.ToString() + "\n";
                writer.WriteLine("{ " + p.X + " ; " + p.Y + " }");
            }

            writer.Close();
        }

        private void PrintCountedQuarter()
        {
            int Higher_Par = 0, Lower_Par = 0, On_Par = 0;

            foreach (Point p in Default_Points)
            {
                int y = a * p.X * p.X + b * p.X + c; // Если бы мы подставили абсциссу точки в уравнение, то y был бы таким
                if (y < p.Y)
                    Higher_Par++;
                else if (y > p.Y)
                    Lower_Par++;
                else
                    On_Par++;
            }

            StreamWriter writer = new StreamWriter("OUTPUT.TXT");

            Higher_Zone.Text = "Число точек выше параболы: " + Higher_Par.ToString();

            Lower_Zone.Text = "Число точек ниже параболы: " + Lower_Par.ToString();

            On_Parabola.Text = "Число точек на параболе: " + On_Par.ToString();

            writer.Close();
        }

        private void SetDefaults()
        {
            Field = new PictureField(PictureBox_Field);
        }
        
        private Point StrToPoint(string str)
        {
            string[] strCoord = str.Split(new char[] { ' ' });

            int X = int.Parse(strCoord[0]),
                Y = int.Parse(strCoord[1]);

            return new Point(X, Y);
        }

        int a;
        int b;
        int c;
        bool check_input = false;
        int h = 209;
        int w = 271;

        private void DownloadData()
        {
            string Path = "INPUT.TXT";

            try
            {
                StreamReader reader = new StreamReader(Path);
                using (reader)
                {
                    string Line;
                    bool check = true;
                    if (check)
                    {
                        check = false;
                        Line = reader.ReadLine();
                        for (int i = 0; i <= Line.Length; i++)
                        {
                            if (i == 0)
                                a = Convert.ToInt32(Line[i] - '0');
                            if (a == 0)
                                check_input = true;
                            if (i == 2)
                                b = Convert.ToInt32(Line[i] - '0');
                            if (i == 4)
                                c = Convert.ToInt32(Line[i] - '0');
                        }
                    }
                    while ((Line = reader.ReadLine()) != null)
                    {
                        Default_Points.Add(StrToPoint(Line));
                    }
                }

                if (check_input)
                {
                    Label_OutputStatus.Text = "Коэффициент a равен нулю!";
                    Label_OutputStatus.ForeColor = Color.Red;
                }
                else
                {
                    // Проверка на то, успешно ли прочитался входной файл
                    Label_OutputStatus.Text = "Успешно загружено.";
                    Label_OutputStatus.ForeColor = Color.Green;
                    reader.Close();
                }
            }
            catch
            {
                // На случай, если возникнет ошибка
                Label_OutputStatus.Text = "Ошибка при чтении файла.";
                Label_OutputStatus.ForeColor = Color.Red;
            }
        }

        private void PictureBox_Field_Paint(object sender, PaintEventArgs e)
        {
            Field.DrawAxes(e); // Рисуем оси
            Field.DrawPoints(e, Default_Points); // Рисуем точки

            Color color;

            color = Color.Black;

            Pen pen = new Pen(color, 2);

            for (int i = -100; i < 100; i++)
            {
                int x = i;
                int y = a * x * x + b * x + c;
                int x2 = x + 1;
                int y2 = a * x2 * x2 + b * x2 + c;
                e.Graphics.DrawLine(pen, w - x, h - y, w - x2, h - y2);
            }
        }

        private void Button_Decrease_Click(object sender, EventArgs e)
        {
            if (Field.ChangeMargin(10))
                Refresh();
        }

        private void Button_Encrease_Click(object sender, EventArgs e)
        {
            if (Field.ChangeMargin(-10))
                Refresh();
        }
    }

    public class PictureField
    {
        private int Field_Mid_X, Field_Mid_Y;

        private readonly int Point_Size = 5;
        private readonly int Limit = 100;
        private int Margin_PixelSize = 20;

        Random rnd = new Random();
        private readonly int Color_Max = 255;
        
        private readonly int MAXCOORDSIZE = 1000;

        public int MidX { get => Field_Mid_X; }
        public int MidY { get => Field_Mid_Y; }

        public int Pic_Width { get => My_PictureBox.Width; }
        public int Pic_Height { get => My_PictureBox.Height; }

        private PictureBox My_PictureBox;

        public int Margin
        {
            get => Margin_PixelSize;
        }

        public bool ChangeMargin(int forvalue)
        {
            Margin_PixelSize += forvalue;
            if (Margin_PixelSize < 0)
            {
                Margin_PixelSize = 0;
                return false;
            }
            else if (Margin_PixelSize > Limit)
            {
                Margin_PixelSize = Limit;
                return false;
            }
            return true;
        }

        public PictureField(PictureBox picture)
        {
            My_PictureBox = picture;
            Field_Mid_X = picture.Width / 2;
            Field_Mid_Y = picture.Height / 2;
        }

        private Point Normalize(Point p)
        {
            return new Point(MidX + (Pic_Width / 2 - Margin) * p.X / MAXCOORDSIZE,
                             MidY - (Pic_Height / 2 - Margin) * p.Y / MAXCOORDSIZE);
        }

        public void DrawPoints(PaintEventArgs e, List<Point> L_points)
        {
            foreach (Point p in L_points)
            {
                e.Graphics.FillEllipse(new SolidBrush(RandomColor), new Rectangle(Normalize(p), new Size(new Point(Point_Size, Point_Size))));
            }
        }

        //Generate a color in RGB
        private Color RandomColor
        {
            get => Color.FromArgb(rnd.Next(Color_Max), rnd.Next(Color_Max), rnd.Next(Color_Max));
        }

        //Рисует оси
        public void DrawAxes(PaintEventArgs e)
        {
            SolidBrush myBrush = new SolidBrush(Color.Black);
            Pen myPen = new Pen(myBrush);

            //Абсцисса
            e.Graphics.DrawLine(myPen, new Point(Margin, MidY), new Point(Pic_Width - Margin, MidY));
            e.Graphics.DrawLine(myPen, new Point(Margin, MidY), new Point(Pic_Width - Margin, MidY));
            DrawTriangle(e, new Point(MidX, Margin));

            //Ордината
            e.Graphics.DrawLine(myPen, new Point(MidX, Margin), new Point(MidX, Pic_Height - Margin)); //+Y => down
            DrawTriangle(e, new Point(Pic_Width - Margin, MidY), false);

            myPen.Dispose();
            myBrush.Dispose();
        }

        // Рисует стрелочки на осях
        private void DrawTriangle(PaintEventArgs e, Point Top, bool NormalRotation = true)
        {
            SolidBrush myBrush = new SolidBrush(Color.Black);
            Pen pen = new Pen(myBrush);
            Point[] points;

            const int Triangle_Size = 10;

            if (NormalRotation)
            {
                Point LeftCorner = new Point(Top.X - Triangle_Size / 2, Top.Y + Triangle_Size),
                      RightCorner = new Point(Top.X + Triangle_Size / 2, Top.Y + Triangle_Size);
                points = new Point[] { Top, LeftCorner, RightCorner };
            }
            else
            {
                Point UpCorner = new Point(Top.X - Triangle_Size, Top.Y - Triangle_Size / 2),
                      DownCorner = new Point(Top.X - Triangle_Size, Top.Y + Triangle_Size / 2);
                points = new Point[] { Top, UpCorner, DownCorner };
            }

            e.Graphics.DrawPolygon(pen, points);

            myBrush.Dispose();
            pen.Dispose();
        }
    }

    // Сортировка точек
    public class PointComparer : IComparer<Point>
    {
        public int Compare(Point p1, Point p2)
        {
            if (p1.Y < p2.Y)
                return -1;
            else if (p2.Y > p2.Y)
                return 1;
            else
                return 0;
        }
    }
}