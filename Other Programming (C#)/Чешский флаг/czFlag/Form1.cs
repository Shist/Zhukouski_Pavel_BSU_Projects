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
            Point A = new Point(WN.X + W / 2, WN.Y + 4 / 5 * H);
            Point B = new Point(WN.X + 3 / 5 * W, WN.Y + 3 / 5 * H);
            Point C = new Point(WN.X + 7 / 10 * W, WN.Y + 1 / 5 * H);
            Point D = new Point(WN.X + 3 / 10 * W, WN.Y + 1 / 5 * H);
            Point E = new Point(WN.X + 2 / 5 * W, WN.Y + 3 / 5 * H);
            Point F = new Point(WN.X + W / 2, WN.Y + 2 / 5 * H);
            Point G = new Point(WN.X + 7 / 20 * W, WN.Y + 11 / 20 * H);

            Point[] yellow_part_1 = new Point[3];
            Point[] yellow_part_2 = new Point[3];
            Point[] red_part_1 = new Point[3];
            Point[] red_part_2 = new Point[3];

            yellow_part_1[0] = A; yellow_part_1[1] = C; yellow_part_1[2] = D;
            yellow_part_2[0] = B; yellow_part_2[1] = D; yellow_part_2[2] = E;
            red_part_1[0] = C; red_part_1[1] = D; red_part_1[2] = F;
            red_part_2[0] = D; red_part_2[1] = E; red_part_2[2] = G;



            SolidBrush brush = new SolidBrush(Color.Red);
            Pen pen = new Pen(brush);
            g.FillRectangle(brush, WN.X, WN.Y, W, H);
            brush.Color = Color.Yellow;
            g.FillPolygon(brush, yellow_part_1);
            g.FillPolygon(brush, yellow_part_2);
            brush.Color = Color.Red;
            g.FillPolygon(brush, red_part_1);
            g.FillPolygon(brush, red_part_2);
            brush.Color = Color.Black;
            Font font = new Font("Courier New", 15, FontStyle.Bold | FontStyle.Italic);
            StringFormat drawFormat = new System.Drawing.StringFormat();
            g.DrawString("Вьетнам", font, brush, 0, 0, drawFormat);
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
