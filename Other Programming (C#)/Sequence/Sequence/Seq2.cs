using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Sequence
{
    class Seq2 : Interface1
    {
        private int _current;
        private Random rnd;
        private int _key;
        public Seq2(int key)
        {
            _key = key;
            rnd = new Random(key);
            _current = rnd.Next();
        }
        public int First()
        {
            rnd = new Random(_key);
            _current = rnd.Next();

            return _current;

        }
        public int Current()
        {
            return _current;
        }
        public int Next()
        {
            _current = rnd.Next();
            return _current;
        }
    }
}