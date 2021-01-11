using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Classes_C_sharp
{
    public class DescTemperature : IComparer
    {
        public int Compare(Object x, Object y)
        {
            if ((x is Temperature) && (y is Temperature))
            {
                Temperature tx = (Temperature)x;
                Temperature ty = (Temperature)y;
                return (ty.CompareTo(tx));
            }
            throw new ArgumentException(
            "objects are not a Temperature");
        }
    }
}