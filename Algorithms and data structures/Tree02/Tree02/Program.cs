using System;
using System.IO;

namespace Tree01
{
    public class Tree
    { // Класс "узел БПД"
        public class Item
        {
            public int info; // info - значение, хранящееся в узле
            public Item lSon, rSon, father; // lSon, rSon, father - ссылки на левого, правого сына и отца
            /// <param name="x">значение, хранящееся в узле</param>
            public Item(int x) // Конструктор узла БПД
            {
                info = x;
                lSon = rSon = father = null;
            }
        }

        public Item root; // ссылка на корень дерева

        public Tree() // конструктор дерева
        {
            root = null;
        }

        /// <param name="x">искомое значение</param>
        /// <param name="p">ели найдено - ссылка на соответствующий узел, иначе - ссылка на то место, где остановились</param>
        /// <returns>нашли или нет</returns>
        private bool Find(int x, out Item p) // внутренняя процедура поиска
        {
            p = root;
            Item q = p;
            while (q != null)
            {
                p = q;
                if (q.info == x)
                    return true;
                if (q.info < x)
                    q = q.rSon;
                else
                    q = q.lSon;
            }
            return false;
        }


        /// <param name="x">искомое значение</param>
        /// <returns>нашли или нет</returns>
        public bool Find(int x) // внешняя процедура поиска
        {
            Item p;
            return Find(x, out p);
        }

        /// <param name="x">вставляемое значение</param>
        /// <returns>смогли вставить или нет</returns>
        public bool Insert(int x) // втавка в БПД
        {
            Item r, p;
            if (root == null)
            {
                r = new Item(x);
                root = r;
                return true;
            }
            if (Find(x, out r))
                return false;
            p = new Item(x);
            p.father = r;
            if (r.info < x)
                r.rSon = p;
            else
                r.lSon = p;
            return true;
        }

        /// <param name="x">удаляемая вершина</param>
        private void deleteItem(Item x) // удалить вершину (оборвать все ссылки)
        {
            if (x.father == null)
                if (x.lSon != null)
                {
                    root = x.lSon;
                    x.lSon.father = null;
                }
                else
                {
                    root = x.rSon;
                    if (x.rSon != null)
                        x.rSon.father = null;
                }
            else
            if (x.father.lSon == x)
                if (x.lSon != null)
                {
                    x.father.lSon = x.lSon;
                    x.lSon.father = x.father;
                }
                else
                {
                    x.father.lSon = x.rSon;
                    if (x.rSon != null)
                        x.rSon.father = x.father;
                }
            else
                if (x.lSon != null)
            {
                x.father.rSon = x.lSon;
                x.lSon.father = x.father;
            }
            else
            {
                x.father.rSon = x.rSon;
                if (x.rSon != null)
                    x.rSon.father = x.father;
            }
            x.father = x.lSon = x.rSon = null;
        }

        /// <param name="x">удаляемое значение</param>
        /// <returns>смогли удалить или нет</returns>
        public bool Delete(int x) // Удалить вершину по значению
        {
            Item r, p;
            if (!Find(x, out r))
                return false;
            if ((r.lSon == null) || (r.rSon == null))
            {
                deleteItem(r);
                return true;
            }
            p = r.rSon;
            while (p.lSon != null)
                p = p.lSon;
            r.info = p.info;
            deleteItem(p);
            return true;
        }

        private int sum; // Здесь храним сумму значений всех узлов дерева
        private int count; // Здесь храним количество всех узлов дерева

        private void Obhod(Item x)
        { // С помощью этой функции считаем сумму значений всех узлов и их количество
            if (x != null)
            {
                sum += x.info;
                count++;
                if (x.lSon != null) Obhod(x.lSon);
                if (x.rSon != null) Obhod(x.rSon);
            }
        }

        public void output(Item x, TextWriter y/*, int lvl, int sr*/)
        { // Вывод
            y.WriteLine(/*"Значение вершины равно " + */x.info/* + ", ее уровень равен " + lvl*/);
            if (x.lSon != null) output(x.lSon, y/*, lvl + 1, sr*/);
            if (x.rSon != null) output(x.rSon, y/*, lvl + 1, sr*/);
        }
    }

    class Tree01
    {
        static void Main(string[] args)
        {
            Tree my_tree = new Tree();
            StreamReader reader = new StreamReader("input.txt");
            StreamWriter writer = new StreamWriter("output.txt");
            string str;
            int key_to_delete = 0;
            bool check = true;
            while ((str = reader.ReadLine()) != null)
            {
                if (str == "")
                    continue;
                if (check)
                {
                    key_to_delete = Convert.ToInt32(str);
                    check = false;
                }
                else
                {
                    int key = Convert.ToInt32(str);
                    my_tree.Insert(key);
                }
            }
            my_tree.Delete(key_to_delete);
            my_tree.output(my_tree.root, writer);
            reader.Close();
            writer.Close();
        }
    }
}
