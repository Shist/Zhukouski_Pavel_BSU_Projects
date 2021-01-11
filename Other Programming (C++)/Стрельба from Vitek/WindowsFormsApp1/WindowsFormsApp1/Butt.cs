using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.ComponentModel;
using System.Data;
using System.Drawing;


namespace WindowsFormsApp1
{
    class Butt
    {
        double radius1=100, radius2=100;
        int shooting_nomber;
        int missing=0, nomissing=0;
        Point middleP;
        List<Point> hit;
        Rectangle op_r1, op_r2;

        #region properties
        public double Radius1 { get => radius1; private set => radius1 = value; }
        public double Radius2 { get => radius2; private set => radius2 = value; }
        public Point MiddleP { get => middleP; private set => middleP = value; }
        public List<Point> Hit { get => hit; private set => hit = value; }
        public int Missing { get => missing; private set => missing = value; }
        public int Nomissing { get => nomissing; private set => nomissing = value; }
        public Rectangle Op_r1 { get => op_r1; private set => op_r1 = value; }
        public Rectangle Op_r2 { get => op_r2; private set => op_r2 = value; }
        public int Shooting_nomber { get => shooting_nomber; set => shooting_nomber = value; }
        #endregion

        public Butt(double r1,double r2, int sh_nom, Point Mid)
        {
            Radius1 = r1;
            Radius2 = r2;
            Shooting_nomber = sh_nom;
            Hit = new List<Point>();
            MiddleP = Mid;
            Op_r1 = new Rectangle(Mid.X - (int)r1, Mid.Y - (int)r1, 2 * (int)r1, 2 * (int)r1); 
            Op_r2= new Rectangle(Mid.X - (int)r2, Mid.Y - (int)r2, 2 * (int)r2, 2 * (int)r2); 
        }
        public bool Shot(Point A)
        {
            if(Hit.Count<Shooting_nomber)
            {
                Hit.Add(A);
                if (ishitting(A)) Nomissing++;
                else Missing++;
                return true;
            }
            else
            {
                return false;
            }

        }
        private bool ishitting(Point A)
        {
            double dist = Math.Sqrt(Math.Pow((A.X - MiddleP.X), 2) + Math.Pow((A.Y - MiddleP.Y), 2));
            if (dist <= Radius2 && dist >= Radius1 && A.X >= MiddleP.X && A.Y >= MiddleP.Y) return true;
            if (dist <= Radius1 && A.X <= MiddleP.X && A.Y <= MiddleP.Y) return true;
            return false;
        }
        public void ChangeMidllepoint(Point A)
        {
            Point Del=new Point(A.X-MiddleP.X, A.Y - MiddleP.Y);
            MiddleP = A;
            Op_r1 = new Rectangle(MiddleP.X - (int)Radius1, MiddleP.Y - (int)Radius1, 2 * (int)Radius1, 2 * (int)Radius1);
            Op_r2 = new Rectangle(MiddleP.X - (int)Radius2, MiddleP.Y - (int)Radius2, 2 * (int)Radius2, 2 * (int)Radius2);
            for (int i=0;i<Hit.Count;i++)
            {
                Hit[i] = new Point(Hit[i].X + Del.X, Hit[i].Y + Del.Y);
            }
        }
    }

}
