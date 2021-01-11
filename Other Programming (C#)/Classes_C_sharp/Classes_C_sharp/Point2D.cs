using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Classes_C_sharp
{
    class Point2D
    {
        public double x { get; set; }
        public double y { get; set; }
        public Point2D(double aX, double aY)
        {
            x = aX; y = aY;
        }
        public Point2D() : this(0, 0) { } // <--вон тот this - это обращение к другому конструктору
    }
}