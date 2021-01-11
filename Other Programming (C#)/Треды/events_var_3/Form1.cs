using System;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace events
{
    public partial class EventsForm : Form
    {
        public Demonstrator demonstrator;
        bool isRunning = false;

        public EventsForm()
        {
            InitializeComponent();
            demonstrator = new Demonstrator(1000, 150, 600, 600);
            demonstrator.CalcInit(200);
            isRunning = true;
            demonstrator.DisplayEvent += Demonstrator_DisplayEvent;
            demonstrator.ShootEvent += Demonstartor_ShootEvent;
            tbResult.ReadOnly = true;

            Hits = new Point[maxHitNum];
        }

        private void Demonstrator_DisplayEvent(object sender, DisplayEventArgs e)
        {
            tbResult.Invoke((MethodInvoker) delegate { tbResult.Text = e.Result; });
        }

        private void Demonstartor_ShootEvent(object sender, ShootEventArgs e)
        {
            if (curHitNum >= maxHitNum)
                return;
            Hits[curHitNum] = new Point(e.X, -e.Y);
            if (Gotcha(Hits[curHitNum]))
                luckyHitNum++;
            curHitNum++;
            Invalidate();
        }

        private void EventsForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            demonstrator.StopCalc();
        }

        private void btStartStop_Click(object sender, EventArgs e)
        {/*
            if (!isRunning)
            {
                int time = 1000;
                if (tbTime.Text != "")
                    time = Convert.ToInt32(tbTime.Text);
                demonstrator.CalcInit(time);
                btStartStop.Text = "Stop";
                tbTime.ReadOnly = true;
                isRunning = true;
            }*/
            if (isRunning)
            {
                demonstrator.StopCalc();
                //btStartStop.Text = "Start";
                isRunning = false;
                btStartStop.Enabled = false;
                //tbTime.ReadOnly = false;
            }
        }

        // //////////////////////////////////////////////////////////////////////////////////////////

        private int Bx;  // x центра мишени
        private int Ay;  // y центра мишени
        private int maxHitNum = 100000;
        private int curHitNum = 0;
        private Point[] Hits;  // координаты в расчете от центра мишени
        private int luckyHitNum = 0;

        int hitX;
        int hitY;

        private void MainPaint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);
            DrawTarget(ClientRectangle, e.Graphics);
        }

        private void MainResize(object sender, EventArgs e)
        {
            Invalidate();
        }

        private void DrawTarget(Rectangle r, Graphics g)
        {
            int By = 100 * demonstrator.TargetSize / 150;  // b
            int Ax = 200 * demonstrator.TargetSize / 150;  // a
            int R = demonstrator.TargetSize;
            Ay = r.Height / 2;
            Bx = 3 * r.Width / 4;

            // Hits * koef ot resize(width. height)

            g.Clear(Color.White);

            SolidBrush brush = new SolidBrush(Color.Gray);
            g.FillEllipse(brush, Bx - R, Ay - R, 2 * R, 2 * R);
            brush.Color = Color.White;
            g.FillRectangle(brush, 0, 0, r.Width, Ay);
            g.FillRectangle(brush, Bx, 0, Bx, r.Height);
            g.FillRectangle(brush, 0, Ay + By, r.Width, r.Height);
            g.FillRectangle(brush, 0, 0, Bx - Ax, r.Height);
            brush.Color = Color.Gray;
            g.FillRectangle(brush, Bx, Ay - By, Ax, By);
            brush.Color = Color.White;
            g.FillPie(brush, Bx - R, Ay - R, 2 * R, 2 * R, 0, -90);

            brush.Color = Color.Black;
            Pen pen = new Pen(brush);
            // Ox
            g.DrawLine(pen, new Point(0, Ay), new Point(r.Width, Ay));
            // Oy
            g.DrawLine(pen, new Point(Bx, 0), new Point(Bx, r.Height));
            // rect
            g.DrawLine(pen, new Point(Bx - Ax, Ay - By), new Point(Bx + Ax, Ay - By));
            g.DrawLine(pen, new Point(Bx - Ax, Ay + By), new Point(Bx + Ax, Ay + By));
            g.DrawLine(pen, new Point(Bx - Ax, Ay - By), new Point(Bx - Ax, Ay + By));
            g.DrawLine(pen, new Point(Bx + Ax, Ay - By), new Point(Bx + Ax, Ay + By));

            g.DrawEllipse(pen, Bx - R, Ay - R, 2 * R, 2 * R);

            for (int i = 0; i < curHitNum; i++)
            {
                SolidBrush br;
                if (Gotcha(Hits[i]))
                    br = new SolidBrush(Color.Red);
                else
                    br = new SolidBrush(Color.Blue);
                g.FillEllipse(br, Hits[i].X + Bx - 3, Hits[i].Y + Ay - 3, 6, 6);
            }

            Font font = new Font("Consolas", 12, FontStyle.Bold);
            StringFormat drawFormat = new System.Drawing.StringFormat();
            g.DrawString("Совершено выстрелов: " + curHitNum.ToString(), font, brush, 0 + 3 * Bx / 5, 25, drawFormat);
            g.DrawString("Промахов: " + (curHitNum - luckyHitNum).ToString(), font, brush, 0 + 3 * Bx / 5, 50, drawFormat);
            g.DrawString("Попаданий: " + luckyHitNum.ToString(), font, brush, 0 + 3 * Bx / 5, 75, drawFormat);

            brush.Dispose();
            font.Dispose();
        }

        public bool Gotcha(Point p)
        {
            int By = 100 * demonstrator.TargetSize / 150;  // b
            int Ax = 200 * demonstrator.TargetSize / 150;  // a
            int R = demonstrator.TargetSize;
            if (p.X + Bx < Bx && p.X + Bx > Bx - Ax && p.Y + Ay > Ay && p.Y + Ay < Ay + By &&
               (p.X + Bx - Bx) * (p.X + Bx - Bx) + (p.Y + Ay - Ay) * (p.Y + Ay - Ay) < R * R)
                return true;
            if (p.X + Bx > Bx && p.Y + Ay < Ay && p.X + Bx < Bx + Ax && p.Y + Ay > Ay - By &&
               (p.X + Bx - Bx) * (p.X + Bx - Bx) + (p.Y + Ay - Ay) * (p.Y + Ay - Ay) > R * R)
                return true;
            return false;
        }

        private void btShootStop_Click(object sender, EventArgs e)
        {
            if (isRunning)
            {
                demonstrator.StopCalc();
                btStartStop.Text = "Stop";
                btStartStop.Enabled = false;
                btShootStop.Enabled = false;
                isRunning = false;
                tbTime.ReadOnly = false;
            }
            else
            {
                btShootStop.Enabled = false;
            }
            demonstrator.StopShooting();
        }

        /*

private void RadiusMinused(object sender, EventArgs e)
{
if (R > 0)
R -= 1;
curHitNum = 0;
luckyHitNum = 0;
lError.Visible = false;
Invalidate();
}

private void AMinused(object sender, EventArgs e)
{
if (Ax > 0)
Ax -= 1;
curHitNum = 0;
luckyHitNum = 0;
lError.Visible = false;
Invalidate();
}

private void BMinused(object sender, EventArgs e)
{
if (By > 0)
By -= 1;
curHitNum = 0;
luckyHitNum = 0;
lError.Visible = false;
Invalidate();
}

private void MaxHitNumberMinused(object sender, EventArgs e)
{
if (maxHitNum > 0)
maxHitNum -= 1;
curHitNum = 0;
luckyHitNum = 0;
lError.Visible = false;
Invalidate();
}

private void RadiusPlused(object sender, EventArgs e)
{
R++;
curHitNum = 0;
luckyHitNum = 0;
lError.Visible = false;
Invalidate();
}

private void APlused(object sender, EventArgs e)
{
Ax++;
curHitNum = 0;
luckyHitNum = 0;
lError.Visible = false;
Invalidate();
}

private void BPlused(object sender, EventArgs e)
{
By++;
curHitNum = 0;
luckyHitNum = 0;
lError.Visible = false;
Invalidate();
}

private void MaxHitNumberPlused(object sender, EventArgs e)
{
maxHitNum++;
curHitNum = 0;
luckyHitNum = 0;
lError.Visible = false;
Invalidate();
}
*/
    }
}
