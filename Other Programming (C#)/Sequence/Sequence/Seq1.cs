using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Sequence
{
    class Seq1 : Interface1
    {
        private int _current;
        public int First()
        {
            _current = 1;
            return _current;
        }
        public int Current()
        {
            return _current;
        }
        public int Next()
        {
            if (_current == Int32.MaxValue)
                _current = 1;
            else
                _current++;
            return _current;
        }
    }
}