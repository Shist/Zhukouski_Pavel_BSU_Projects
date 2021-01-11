using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Classes_C_sharp
{
    class My_array
    {
        private int[] a;
        public int n
        {
            get; private set;
        }
        public My_array(int aN)
        {

            n = aN;

            a = new int[n + 1];
        }
        private bool ok(int i)
        {
            return (i <= n) & (i >= -n);
        }
        public int this[int i]
        {
            get
            {
                if (ok(i))
                    return (i < 0 ? -a[-i] : a[i]);
                throw new ArgumentException
                (String.Format("Bad index: {0}", i));
            }
            set
            {
                if (ok(i))
                {
                    if (i < 0) a[-i] = -value;
                    else a[i] = value;
                    return;
                }
                throw new ArgumentException
                (String.Format("Bad index: {0}", i));
            }
        }
    }
}