using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Windows.Forms;

namespace KR_4
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
            foreach (Point p in Default_Points)
                RTextBox_SortePoints.Text += p.ToString() + "\n";
        }

        private void PrintCountedQuarter()
        {
            int QtFirst = 0, QtSecond = 0, QtThird = 0, QrFourth = 0, QtAxeAbsciss = 0, QtAxeOordinate = 0;

            foreach (Point p in Default_Points)
            {
                if (p.X == 0 && p.Y == 0)
                {
                    ++QtAxeAbsciss;
                    ++QtAxeOordinate;
                }
                else
                {
                    if (p.Y == 0)
                        ++QtAxeAbsciss;
                    else if (p.X == 0)
                        ++QtAxeOordinate;
                    else if (p.X > 0)
                    {
                        if (p.Y > 0)
                            ++QtFirst;
                        else
                            ++QrFourth;
                    }
                    else
                    {
                        if (p.Y > 0)
                            ++QtSecond;
                        else
                            ++QtThird;
                    }
                }     
            }

            StreamWriter writer = new StreamWriter("OUTPUT.TXT");

            Label_QtFirst.Text = "Число вершин в 1 четверти: " + QtFirst.ToString();
            writer.WriteLine("Число вершин в 1 четверти: " + QtFirst.ToString());

            Label_QtSecond.Text = "Число вершин в 2 четверти: " + QtSecond.ToString();
            writer.WriteLine("Число вершин в 2 четверти: " + QtSecond.ToString());

            Label_QtThird.Text = "Число вершин в 3 четверти: " + QtThird.ToString();
            writer.WriteLine("Число вершин в 3 четверти: " + QtThird.ToString());

            Label_QtFourth.Text = "Число вершин в 4 четверти: " + QrFourth.ToString();
            writer.WriteLine("Число вершин в 4 четверти: " + QrFourth.ToString());

            Label_QtAbsciss.Text = "Число вершин на оси абсцисс: " + QtAxeAbsciss.ToString();
            writer.WriteLine("Число вершин на оси абсцисс: " + QtAxeAbsciss.ToString());

            Label_QtOordinate.Text = "Число вершин на оси ординат: " + QtAxeOordinate.ToString();
            writer.WriteLine("Число вершин на оси ординат: " + QtAxeOordinate.ToString());

            writer.Close();
        }



        private void SetDefaults()
        {
            Field = new PictureField(PictureBox_Field);
        }


        /// <summary>
        /// Divides lin "strNumber1_strNumber2" into two numbers
        /// </summary>
        /// <param name="str">Line from stream</param>
        /// <returns>Point(Number1, Number2)</returns>
        private Point StrToPoint(string str)
        {
            string[] strCoord = str.Split(new char[] { ' ' });
            int X = int.Parse(strCoord[0]), 
                Y = int.Parse(strCoord[1]);

            return new Point(X, Y);
        }

        private void DownloadData()
        {
            string Path = "INPUT.TXT";

            try
            {
                StreamReader reader = new StreamReader(Path);
                using (reader)
                {
                    string Line;
                    while ((Line = reader.ReadLine()) != null)
                    {
                        Default_Points.Add(StrToPoint(Line));
                    }
                }

                //File is OK
                Label_OutputStatus.Text = "Успешно загружено.";
                Label_OutputStatus.ForeColor = Color.Green;
                reader.Close();
            }
            catch
            {
                //Notify user that there is an error in file
                Label_OutputStatus.Text = "Ошибка при чтении файла.";
                Label_OutputStatus.ForeColor = Color.Red;
            }
        }

        private void PictureBox_Field_Paint(object sender, PaintEventArgs e)
        {
            Field.DrawAxes(e);
            Field.DrawPoints(e, Default_Points);
        }

        private void Button_Decrease_Click(object sender, EventArgs e)
        {
            if (Field.ChangeMargin(5))
                Refresh();
        }

        private void Button_Encrease_Click(object sender, EventArgs e)
        {
            if (Field.ChangeMargin(-5))
             Refresh();
        }
    }

    public class PictureField
    {
        private int Field_Mid_X, Field_Mid_Y;

        private readonly int Point_Size = 5;
        private readonly int Limit = 250;
        //Set margin (to see points clearly)
        private int Margin_PixelSize = 20;

        Random rnd = new Random();
        private readonly int Color_Max = 255;

        //Maximum default pixel modal coordinate
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

        /// <summary>
        /// 
        /// </summary>
        /// <param name="forvalue"></param>
        /// <returns>Changed sucessfully</returns>
        /// 
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

        /// <summary>
        /// Draws a point on Form's
        /// PictureBox
        /// </summary>
        /// <param name="e"></param>
        /// <param name="p">Where does the point have to be drown</param>
        public void DrawPoints(PaintEventArgs e, List<Point> L_points)
        {
            //e.Graphics.DrawRectangle(pen, new Rectangle(p, new Size(new Point(1, 1))));
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

        //Draws main two axes
        public void DrawAxes(PaintEventArgs e)
        {
            SolidBrush myBrush = new SolidBrush(Color.Black);
            Pen myPen = new Pen(myBrush);

            //Abscissa
            e.Graphics.DrawLine(myPen, new Point(Margin, MidY), new Point(Pic_Width - Margin, MidY));
            e.Graphics.DrawLine(myPen, new Point(Margin, MidY), new Point(Pic_Width - Margin, MidY));
            DrawTriangle(e, new Point(MidX, Margin));

            //Ordinate
            e.Graphics.DrawLine(myPen, new Point(MidX, Margin), new Point(MidX, Pic_Height - Margin)); //+Y => down
            DrawTriangle(e, new Point(Pic_Width - Margin, MidY), false);

            myPen.Dispose();
            myBrush.Dispose();
        }

        /// <summary>
        /// Draws triangle at the end
        /// of the axe
        /// </summary>
        /// <param name="e"></param>
        /// <param name="Top">Main coordinate</param>
        /// <param name="NormalRotation">is 90 degree. NormalRotation == false means abscissa's triangle</param>
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
               points = new Point[]{ Top, LeftCorner, RightCorner };
            }
            else
            {
                Point UpCorner = new Point(Top.X - Triangle_Size, Top.Y - Triangle_Size / 2),
                      DownCorner = new Point(Top.X - Triangle_Size, Top.Y + Triangle_Size / 2);
                points = new Point[]{ Top, UpCorner, DownCorner};
            }
            e.Graphics.DrawPolygon(pen, points);

            myBrush.Dispose();
            pen.Dispose();
        }
    }


    public class PointComparer : IComparer<Point>
    {
        private double Dist_To_Begin(Point p)
        {
            return (Math.Pow(p.X, 2) + Math.Pow(p.Y, 2));
        }

        public int Compare(Point p1, Point p2)
        {
            double d1 = Dist_To_Begin(p1), d2 = Dist_To_Begin(p2);
            if (d1 < d2)
                return -1;
            else if (d1 > d2)
                return 1;
            else
                return 0;
        }
    }
}
