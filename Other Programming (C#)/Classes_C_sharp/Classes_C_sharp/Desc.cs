using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Classes_C_sharp
{
    public class Desc : IComparer
    {
        public int Compare(object x, object y)
        {
            if ((x is IComparable) && (y is IComparable))
            {
                IComparable tx = (IComparable)x;
                IComparable ty = (IComparable)y;
                return (ty.CompareTo(tx));
            }
            throw new ArgumentException(@"objects don't implement the IComparable interface");
        }
    }
}