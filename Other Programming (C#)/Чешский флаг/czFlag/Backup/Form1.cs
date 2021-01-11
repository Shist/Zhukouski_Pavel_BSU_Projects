
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace czFlag
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        protected override void  OnPaint(PaintEventArgs e)
        {
 	        base.OnPaint(e);
            DrawFlag(ClientRectangle, e.Graphics);
        }

        private void DrawFlag(Rectangle r, Graphics g)
        {
            const int PROPX = 2, PROPY =3;
            g.Clear(Color.Gray);
            
            int H = r.Height, W = r.Width;
            Point WN = new Point(0,0);
        	if (PROPX * r.Width > PROPY * r.Height) // широкое поле
            {
                W = H*PROPY/PROPX;
                WN.X = (r.Width - W)/2;
            }
            else if (PROPX * r.Width < PROPY * r.Height) // высокое поле
            {
                H = W*PROPX/PROPY;
                WN.Y = (r.Height - H)/2;
            }
            Point WS = new Point(WN.X, WN.Y + H);
            Point ES = new Point(WN.X + W, WN.Y + H);
            Point C = new Point(WN.X + W / 2, WN.Y + H / 2);
            Point D = new Point(WN.X + W, WN.Y + H/2);

            Point [] red_part = new Point[4];
            Point[] blue_part = new Point[3];
            red_part[0] = WS; red_part[1] = C; red_part[2] = D; red_part[3] = ES;
            blue_part[0] = WS; blue_part[1] = C; blue_part[2] = WN;



            SolidBrush brush = new SolidBrush(Color.White);
            Pen pen = new Pen(brush);
            g.FillRectangle(brush, WN.X, WN.Y, W, H);
            pen.Color = Color.Red;
            g.DrawLine(pen, WS, C);
            g.DrawLine(pen, D, C);
            pen.Color = Color.Blue;
            g.DrawLine(pen, WN, C); 
            brush.Color = Color.Red;
            g.FillPolygon(brush, red_part);
            brush.Color = Color.Blue;
            g.FillPolygon(brush, blue_part);
            brush.Color = Color.Black;
            Font font = new Font("Courier New", 15, FontStyle.Bold | FontStyle.Italic);
            StringFormat drawFormat = new System.Drawing.StringFormat();
            g.DrawString("Чехия", font, brush, 0, 0, drawFormat);
            brush.Dispose();
            pen.Dispose();
            font.Dispose();
            


        }

        private void Form1_Resize(object sender, EventArgs e)
        {
            Invalidate();
        }


    }
}
