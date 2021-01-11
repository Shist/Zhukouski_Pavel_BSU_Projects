using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Classes_C_sharp
{
    class Point3D : Point2D
    {
        public double z { get; set; }
        public Point3D(double aX, double aY, double aZ) :
        base(aX, aY)
        {
            z = aZ;
        }
        public Point3D() :
        this(0, 0, 0)
        { }
    }
}
// Операция is проверяет, принадлежит ли объект указанному классу
// или его потомкам, а операция as приводит объект к указанному
// классу.