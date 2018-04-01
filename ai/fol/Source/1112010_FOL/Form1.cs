using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace _1112010_FOL
{
    public partial class Form1 : Form
    {
        //Stack<Predic> KB = new Stack<Predic>();
        List<string> ans = new List<string>();
        List<string> KB = new List<string>();
        List<string> tmpO = new List<string>();
        int count_hs = 0;   //bien dem he so cho moi lan lap

        public Form1()
        {
            InitializeComponent();
        }

        private void bt_add_KB_Click(object sender, EventArgs e)
        {
            if (tb_add_KB.Text.Length < 1)
                return;
            lb_KB.Items.Add(tb_add_KB.Text);
            tb_add_KB.Clear();
        }

        private void bt_del_KB_Click(object sender, EventArgs e)
        {
            int index;
            if (lb_KB.SelectedIndex < 0)
                return;
            index = lb_KB.SelectedIndex;
            lb_KB.Items.RemoveAt(index);
            if (lb_KB.Items.Count > index)
                lb_KB.SelectedIndex = index;
            else
                lb_KB.SelectedIndex = -1;
        }

        private void bt_add_query_Click(object sender, EventArgs e)
        {
            if (tb_add_query.Text.Length < 1)
                return;
            lb_query.Items.Add(tb_add_query.Text);
            createKB();
            createKB();
            ans.Clear();
            List<string> O = new List<string>();
            if (FOL_BC_ASK(processString(tb_add_query.Text)))
                lb_query.Items.Add("TRUE");
            else
                lb_query.Items.Add("FALSE");
            tb_add_query.Clear();
        }

        private void bt_del_query_Click(object sender, EventArgs e)
        {
            int index;
            if (lb_query.SelectedIndex < 0)
                return;
            index = lb_query.SelectedIndex;
            lb_query.Items.RemoveAt(index);
            if (lb_query.Items.Count > index)
                lb_query.SelectedIndex = index;
            else
                lb_query.SelectedIndex = -1;
        }

        private void tb_add_KB_TextChanged(object sender, EventArgs e)
        {
            if (tb_add_KB.Text.Length < 1)
                return;
            if (tb_add_KB.Text[tb_add_KB.Text.Length - 1] == '\n')
            {
                lb_KB.Items.Add(tb_add_KB.Text);
                tb_add_KB.Clear();
            }
        }

        private void tb_add_query_TextChanged(object sender, EventArgs e)
        {
            if (tb_add_query.Text.Length < 1)
                return;
            if (tb_add_query.Text[tb_add_query.Text.Length - 1] == '\n')
            {
                lb_query.Items.Add(tb_add_query.Text);
                createKB();
                ans.Clear();
                List<string> O = new List<string>();
                if (FOL_BC_ASK(processString(tb_add_query.Text)))
                    lb_query.Items.Add("TRUE");
                else
                    lb_query.Items.Add("FALSE");
                tb_add_query.Clear();
            }
        }

        //ham xu li chuoi
        //bo dau ',' o dau string
        //bo dau '\r' va '\n'
        string processString(string x)
        {
            string tmp = "";
            int index = 0;
            if (x.Length > 0 && x[0] == ',')
                index = 1;
            for (int i = index; i < x.Length; i++)
            {
                if (x[i] == '\r' || x[i] == '\n')
                    break;
                tmp += x[i];
            }

            return tmp;
        }

        //tao du lieu KB tu listBox KB
        private void createKB()
        {
            KB.Clear();
            int i;

            for (i = 0; i < lb_KB.Items.Count; i++)
            {
                KB.Add(processString(lb_KB.Items[i].ToString()));
            }
        }

        //ham cap nhat ket qua vao listBox query
        void printRes(string goals, List<string> O)
        {
            bool flag = false;
            string tmp = "";
            List<string> tmp1 = new List<string>();
            List<string> tmp2 = new List<string>();
            List<string> tmp3 = new List<string>();

            for (int i = 0; i < goals.Length; i++)
            {
                if (goals[i] == '(')
                {
                    flag = true;
                    continue;
                }
                if (goals[i] == ')' || goals[i] == ',')
                {
                    tmp1.Add(tmp);
                    tmp = "";
                    continue;
                }
                if (flag == true)
                    tmp += goals[i];
            }

            int j, index;
            for (int i = 0; i < O.Count; i++)
            {
                tmp = "";
                for (j = 0; j < O[i].Length; j++)
                {
                    if (O[i][j] == '/')
                        break;
                    tmp += O[i][j];
                }
                tmp2.Add(tmp);
                tmp = "";
                index = j + 1;
                for (j = index; j < O[i].Length; j++)
                    tmp += O[i][j];
                tmp3.Add(tmp);
            }

            flag = false;
            tmp = "";
            for (int i = 0; i < tmp1.Count; i++)
            {
                tmp = tmp.Insert(0,tmp1[i]);
                for (j = 0; j < tmp2.Count; j++)
                {
                    if (tmp == tmp2[j])
                        tmp = tmp3[j];
                }
                if (tmp1[i][0] >= 65 && tmp1[i][0] <= 90)
                    lb_query.Items.Add(tmp1[i] + '=' + tmp);
                tmp = "";
            }
        }

        //thuat toan suy dien lui
        private bool FOL_BC_ASK(string goals)
        {
            bool flag;
            List<string> O = new List<string>();
            Stack<string> Open1 = new Stack<string>();  //chua muc gia tri dich can dat duoc
            Stack<List<string>> Open2 = new Stack<List<string>>();
            List<string> Close1 = new List<string>();   //tap cac phep the cho dich Open1
            List<List<string>> Close2 = new List<List<string>>();
            Open1.Push(goals);
            Open2.Push(O);

            while (Open1.Count != 0)
            {
                Close1.Add(Open1.Pop());
                Close2.Add(Open2.Pop());

                //neu dich rong thi tra ve ket qua thanh cong
                if (Close1[Close1.Count - 1].Length == 0)
                {
                    count_hs = 0;
                    printRes(goals,Close2[Close2.Count-1]);
                    return true;
                }

                string q1;

                q1 = SUBST(Close2[Close2.Count - 1], first(Close1[Close1.Count - 1]));

                for (int i = 0; i < KB.Count; i++)
                {
                    List<string> O1 = new List<string>();
                    //cap nhat cac phep the cho danh sach O1
                    for (int j = 0; j < Close2[Close2.Count-1].Count; j++)
                    {
                        string tmp = Close2[Close2.Count - 1][j];
                        O1.Add(tmp);
                    }
                    //kiem tra dang chuan va dong nhat
                    if (checkfirst(KB[i], q1) && unify(first(KB[i]), q1, ref O1))
                    {
                        for(int k=0; k<tmpO.Count; k++)
                            O1.Add(tmpO[k]);
                        tmpO.Clear();
                        string tmp = REST(Close1[Close1.Count-1]);
                        string tmp2 = REST(KB[i]);
                        if (count_hs > 0)
                        {
                            if (tmp2 != "")
                            {
                                add_count(ref tmp2);
                                add_O_count(q1, tmp2, ref O1);
                            }
                        }
                        if (tmp != "")
                            tmp = processString(tmp2 + tmp);
                        else
                            tmp = processString(tmp2);

                        flag = true;

                        if (flag)
                        {
                            Open1.Push(tmp);
                            Open2.Push(union(Close2[Close2.Count - 1], O1));
                        }
                    }
                }
                count_hs++;
            }

            count_hs = 0;
            return false;
        }

        //ham them chi so cho bien
        void add_count(ref string x)
        {
            bool flag = false;
            for (int i = 0; i < x.Length; i++)
            {
                if (x[i] >= 65 && x[i] <= 90)
                    flag = true;
                if (flag == true && i + 1 < x.Length && (x[i + 1] == ',' || x[i + 1] == ')'))
                {
                    flag = false;
                    x = x.Insert(i + 1, (count_hs + 1).ToString());
                    i += (count_hs + 1).ToString().Length;
                }
            }
            if (flag == true)
                x += (count_hs + 1).ToString();
        }

        //ham kiem tra ten ve dau cua vi tu co giong nhau
        bool checkfirst(string q, string q1)
        {
            int i;
            string tmp1 = "", tmp2 = "";

            for (i = 0; i < q.Length; i++)
            {
                if (q[i] == '(')
                    break;
                tmp1 += q[i];
            }

            for (i = 0; i < q1.Length; i++)
            {
                if (q1[i] == '(')
                    break;
                tmp2 += q1[i];
            }

            if (tmp1 == tmp2)
                return true;

            return false;
        }

        //ham hoi 2 danh sach
        List<string> union(List<string> O, List<string> O1)
        {
            List<string> tmp = new List<string>();

            for (int i = 0; i < O.Count; i++)
                tmp.Add(O[i]);

            for (int i = 0; i < O1.Count; i++)
                if (not_in(O, O1[i]))
                    tmp.Add(O1[i]);

            return tmp;
        }
        //kiem tra khong nam trong
        bool not_in(List<string> O, string check)
        {
            for (int i = 0; i < O.Count; i++)
                if (O[i] == check)
                    return false;
            return true;
        }
        //kiem tra nam trong danh sach hay khong
        bool in_list(List<string> O, string check, ref string val)
        {
            for (int i = 0; i < O.Count; i++)
            {
                for (int j = 0; j < O[i].Length; j++)
                {
                    if (O[i][j] == '/')
                    {
                        for (int k = j + 1; k < O[i].Length; k++)
                            val += O[i][k];
                        if (j < check.Length)
                            return false;
                        return true;
                    }
                    if (j >= check.Length)
                        break;
                    if (O[i][j] != check[j])
                        break;
                }
            }
            return false;
        }

        //ham kiem tra hang hay khong
        bool is_const(string src)
        {
            if (src.Length == 0)
                return false;
            if (src[0] >= 97 && src[0] <= 122)
            {
                for (int i = 0; i < src.Length; i++)
                    if (src[i] == '(' || src[i] == ',')
                        return false;
                return true;
            }
            return false;
        }

        //ham kiem tra la bien hay khong
        bool is_var(string src)
        {
            if (src.Length == 0)
                return false;
            if (src[0] >= 65 && src[0] <= 90)
            {
                for (int i = 0; i < src.Length; i++)
                    if (src[i] == '(' || src[i] == ',')
                        return false;
                return true;
            }
            return false;
        }
        //ham kiem tra la vi tu hay khong
        bool is_predic(string src)
        {
            if (src.Length == 0)
                return false;
            bool flag = false;
            if (src[0] >= 97 && src[0] <= 122)
            {
                for (int i = 0; i < src.Length; i++)
                {
                    if (src[i] == ')')
                        flag = true;
                    else if (src[i] == ':')
                        return false;
                    if (flag == true && src[i] == ',')
                        return false;
                }
                return flag;
            }
            return false;
        }
        //ham kiem tra xem co phai la danh sach hay khong
        bool is_list(string src)
        {
            for (int i = 0; i < src.Length; i++)
                if (src[i] == ',')
                    return true;
            return false;
        }
        //ham kiem tra xem co xuat hien trong chuoi con lai hay khong
        bool appear(string var, string q1)
        {
            if (var.Length > q1.Length)
                return false;

            for(int i=0; i<q1.Length; i++)
            {
                bool flag = true;
                if (var[0] == q1[i])
                {
                    int j;
                    for (j = i; j < var.Length; j++)
                    {
                        if (var[j] != q1[i + j])
                        {
                            flag = false;
                            break;
                        }
                    }
                    if (flag == true && (i + j >= q1.Length || q1[i + j] == ',' || q1[i + j] == ')'))
                    {
                        return true;
                    }
                }
            }
            return false;
        }

        //lay tham so cua vi tu
        string args(string x)
        {
            string tmp = "";
            int i;
            bool flag = false;

            for (i = 0; i < x.Length; i++)
            {
                if (x[i] == '(')
                {
                    flag = true;
                    continue;
                }
                else if (x[i] == ')')
                    flag = false;
                if (flag == true)
                    tmp += x[i];
            }

            return tmp;
        }

        //ham lay phan con lai cua vi tu
        string REST(string goal)
        {
            string tmp = "";
            bool flag = false;

            for (int i = 0; i < goal.Length; i++)
            {
                if (flag == true)
                {
                    tmp += goal[i];
                }
                if (goal[i] == ')')
                {
                    if (i + 1 < goal.Length && goal[i + 1] == ':')
                        i++;
                    flag = true;
                }
            }

            return tmp;
        }
        //ham lay phan con lai cua danh sach
        string REST_PRE(string goal)
        {
            string tmp = "";
            bool flag = false;

            for (int i = 0; i < goal.Length; i++)
            {
                if (flag == true)
                    tmp += goal[i];
                if (goal[i] == ',')
                    flag = true;
            }

            return tmp;
        }
        //ham them phep the vao danh sach
        void add_O_count(string q, string q1, ref List<string> O1)
        {
            string tmp = "";
            List<string> tmp1 = new List<string>();
            List<string> tmp2 = new List<string>();
            bool flag = false;
            if (count_hs == 0)
                return;
            
            for (int i = 0; i < q.Length; i++)
            {
                if (q[i] == '(')
                {
                    flag = true;
                    continue;
                }
                if (q[i] == ')' || q[i] == ',')
                {
                    tmp1.Add(tmp);
                    tmp = "";
                    continue;
                }
                if (flag == true)
                    tmp += q[i];
            }

            flag = false;
            for (int i = 0; i < q1.Length; i++)
            {
                if (q1[i] == '(')
                {
                    flag = true;
                    continue;
                }
                if (q1[i] == ')' || q1[i] == ',')
                {
                    tmp2.Add(tmp);
                    tmp = "";
                    continue;
                }
                if (flag == true)
                    tmp += q1[i];
            }

            for (int i = 0; i < tmp1.Count; i++)
            {
                if (tmp1[i][0] >= 65 && tmp1[i][0] <= 90)
                    O1.Add(tmp1[i] + '/' + tmp2[i]);
                else
                    O1.Add(tmp2[i] + '/' + tmp1[i]);
            }
        }
        //ham dong nhat tong quat
        private bool unify(string q, string q1, ref List<string> O1)
        {
            if (q == q1)
                return true;
            else if (is_var(q1))
            {
                if (is_var(q))
                    q1 += count_hs.ToString();
                return unify_var(q1, q, ref O1);
            }
            else if (is_var(q))
            {
                if (count_hs != 0)
                    add_count(ref q);
                return unify_var(q, q1, ref O1);
            }
            else if (is_predic(q) && is_predic(q1))
            {
                if (checkfirst(q, q1))
                    return unify(args(q), args(q1), ref O1);
                else
                    return false;
            }
            else if (is_list(q) && is_list(q1))
            {
                int count = 0;
                for (int i = 0; i < q.Length; i++)
                {
                    if (q[i] == '(')
                        count++;
                }
                if (count == 0)
                {
                    if (unify(firstlist(q), firstlist(q1), ref O1))
                        return unify(REST_PRE(q), REST_PRE(q1), ref O1);
                }
                else
                {
                    if (unify(first(q), first(q1), ref O1))
                        return unify(REST(q), REST(q1), ref O1);
                }
                return false;
            }
            return false;
        }
        //ham dong nhat bien
        private bool unify_var(string var, string q1, ref List<string> O1)
        {
            string val = "";

            if (in_list(O1, var, ref val))
                return unify(val, q1, ref O1);
            else if (in_list(O1, q1, ref val))
                return unify(var, val, ref O1);
            else if (appear(var, q1))
                return false;
            val = var;
            if (is_var(val) && is_var(q1))
                q1 += count_hs.ToString();
            tmpO.Add(val + '/' + q1);
            return true;
        }
        //ham the
        private string SUBST(List<string> O, string first)
        {
            string tmp1 = "", tmp2 = "", res = first;

            int i, j, index;
            for (i = 0; i < O.Count; i++)
            {
                tmp1 = "";
                tmp2 = "";
                for (j = 0; j < O[i].Length; j++)
                {
                    if (O[i][j] == '/')
                        break;
                    tmp1 += O[i][j];
                }
                index = j;
                for (j = index + 1; j < O[i].Length; j++)
                    tmp2 += O[i][j];
                res = replace(res,tmp1, tmp2);
            }

            return res;
        }

        //ham hoan doi chuoi
        string replace(string res, string src, string des)
        {
            string tmp = "";
            bool flag = true;

            for (int i = 0; i < res.Length; i++)
            {
                if (src[0] != res[i])
                    tmp += res[i];
                else
                {
                    flag = true;
                    int j;
                    for (j = 0; j < src.Length; j++)
                    {
                        if (i+j < res.Length && src[j] != res[i+j])
                        {
                            flag = false;
                            break;
                        }
                    }
                    if (res[i + j] != ',' && res[i + j] != ')')
                        flag = false;
                    if (flag == true)
                    {
                        tmp += des;
                        i += j-1;
                    }
                    else
                        tmp += res[i];
                }
            }

            return tmp;
        }

        //ham tim lay vi tu don dau tien
        private string first(string goals)
        {
            string tmp = "";

            for (int i = 0; i < goals.Length; i++)
            {
                tmp += goals[i];
                if (goals[i] == ')')
                    break;
            }

                return tmp;
        }

        //ham lay phan tu dau tien trong danh sach
        private string firstlist(string goals)
        {
            string tmp = "";

            for (int i = 0; i < goals.Length; i++)
            {
                if (goals[i] == ',')
                    break;
                tmp += goals[i];
            }

            return tmp;
        }
    }
}
