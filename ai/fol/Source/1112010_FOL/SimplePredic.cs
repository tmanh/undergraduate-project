using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace _1112010_FOL
{
    class SimplePredic
    {
        public string name = "";
        public Stack<string> para = new Stack<string>();

        public int create(int pos, string src)
        {
            name = "";
            para.Clear();

            int i = pos;
            int index = pos;
            string tmp = "";

            for(i=pos; i<src.Length; i++)
            {
                if(src[i] == '(')
                    break;
                name += src[i];
            }

            while (src[i] != ')')
            {
                index = i + 1;
                for (i = index; i < src.Length; i++)
                {
                    if (src[i] == ',' || src[i] == ')')
                        break;
                    tmp += src[i];
                }
                para.Push(tmp);
                tmp = "";
            }
            return i + 1;
        }
    }
}
