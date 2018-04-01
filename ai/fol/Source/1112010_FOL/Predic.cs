using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace _1112010_FOL
{
    class Predic
    {
        SimplePredic before = new SimplePredic();
        SimplePredic after = new SimplePredic();

        public void create(string src)
        {
            int index;
            index = before.create(0, src);
            if (index >= src.Length)
                return;
            after.create(index + 1, src);
        }

        public bool empty()
        {
            if (before.name == "" && before.para.Count == 0)
                return true;
            return false;
        }
    }
}
