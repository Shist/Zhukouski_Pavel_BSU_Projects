using System;
using System.IO;

namespace Tree01
{
    public class Tree
    { // Класс "узел БПД"
        public class Item
        {
            public int info, max_l_way, max_r_way, max_result_summary_way, max_l_sum, max_r_sum, max_sum; // info - значение, хранящееся в узле
            public Item lSon, rSon, father; // lSon, rSon, father - ссылки на левого, правого сына и отца
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


        public bool Find(int x) // внешняя процедура поиска
        {
            Item p;
            return Find(x, out p);
        }

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

        public int root_to_delete = 0;
        public int current_max_result_summary_way = 0;
        public int current_max_result_sum = Int32.MinValue;
        public int centre_versh_to_delete = 0;
        public bool centre_versh_and_root_are_the_same = false;
        public bool centre_versh_exists = false;
        public int needed_steps_from_root_to_centre_versh = 0;
        public bool Obhod_2_special_propusk = false;
        public bool ne_opredelena_centre_versh_to_delete = true;

        public void Obhod_1(Item x)
        {
            if (x != null)
            {
                if (x.lSon != null)
                {
                    Obhod_1(x.lSon);
                }
                if (x.rSon != null)
                {
                    Obhod_1(x.rSon);
                }
                if (x.lSon != null)
                {
                    if (x.lSon.max_l_way > x.lSon.max_r_way)
                    {
                        x.max_l_way = x.lSon.max_l_way + 1;
                        x.max_l_sum = x.lSon.max_l_sum + x.info;
                    }
                    else if (x.lSon.max_l_way < x.lSon.max_r_way)
                    {
                        x.max_l_way = x.lSon.max_r_way + 1;
                        x.max_l_sum = x.lSon.max_r_sum + x.info;
                    }
                    else // Если у сына оба путя равны, то смотрим на суммы
                    {
                        if (x.lSon.max_l_sum >= x.lSon.max_r_sum)
                        {
                            x.max_l_way = x.lSon.max_l_way + 1;
                            x.max_l_sum = x.lSon.max_l_sum + x.info;
                        }
                        else if (x.lSon.max_l_sum < x.lSon.max_r_sum)
                        {
                            x.max_l_way = x.lSon.max_r_way + 1;
                            x.max_l_sum = x.lSon.max_r_sum + x.info;
                        }
                    }
                }
                else
                {
                    x.max_l_way = 0;
                    x.max_l_sum = x.info;
                }
                if (x.rSon != null)
                {
                    if (x.rSon.max_l_way > x.rSon.max_r_way)
                    {
                        x.max_r_way = x.rSon.max_l_way + 1;
                        x.max_r_sum = x.rSon.max_l_sum + x.info;
                    }
                    else if (x.rSon.max_l_way < x.rSon.max_r_way)
                    {
                        x.max_r_way = x.rSon.max_r_way + 1;
                        x.max_r_sum = x.rSon.max_r_sum + x.info;
                    }
                    else // Если у сына оба путя равны, то смотрим на суммы
                    {
                        if (x.rSon.max_l_sum >= x.rSon.max_r_sum)
                        {
                            x.max_r_way = x.rSon.max_l_way + 1;
                            x.max_r_sum = x.rSon.max_l_sum + x.info;
                        }
                        else if (x.rSon.max_l_sum < x.rSon.max_r_sum)
                        {
                            x.max_r_way = x.rSon.max_r_way + 1;
                            x.max_r_sum = x.rSon.max_r_sum + x.info;
                        }
                    }
                }
                else
                {
                    x.max_r_way = 0;
                    x.max_r_sum = x.info;
                }
                x.max_result_summary_way = x.max_l_way + x.max_r_way;
                x.max_sum = x.max_l_sum + x.max_r_sum - x.info;

                if (x.max_result_summary_way > current_max_result_summary_way)
                {
                    current_max_result_summary_way = x.max_result_summary_way;
                    current_max_result_sum = x.max_sum;
                    root_to_delete = x.info;
                    if (x.max_l_way == x.max_r_way)
                        centre_versh_and_root_are_the_same = true;
                    else
                        centre_versh_and_root_are_the_same = false;
                    if (x.max_result_summary_way % 2 != 0) // Если наибольший путь НЕЧЁТНОЙ длины
                        centre_versh_exists = false;
                    else
                        centre_versh_exists = true;
                }
                else if (x.max_result_summary_way == current_max_result_summary_way)
                {
                    if (x.max_sum > current_max_result_sum)
                    {
                        current_max_result_sum = x.max_sum;
                        root_to_delete = x.info;
                        if (x.max_l_way == x.max_r_way)
                            centre_versh_and_root_are_the_same = true;
                        else
                            centre_versh_and_root_are_the_same = false;
                        if (x.max_result_summary_way % 2 != 0) // Если наибольший путь НЕЧЁТНОЙ длины
                            centre_versh_exists = false;
                        else
                            centre_versh_exists = true;
                    }
                }
            }
        }

        public void Obhod_2(Item x)
        {
            if (x != null && ne_opredelena_centre_versh_to_delete)
            {
                if (Obhod_2_special_propusk)
                {
                    if (needed_steps_from_root_to_centre_versh == 0)
                    {
                        centre_versh_to_delete = x.info;
                        ne_opredelena_centre_versh_to_delete = false;
                    }
                    else
                    {
                        needed_steps_from_root_to_centre_versh--;
                        if (x.lSon != null && x.rSon != null)
                        {
                            if (x.max_l_way > x.max_r_way)
                            {
                                Obhod_2(x.lSon);
                                if (!ne_opredelena_centre_versh_to_delete)
                                    return;
                            }
                            if (x.max_l_way < x.max_r_way)
                            {
                                Obhod_2(x.rSon);
                                if (!ne_opredelena_centre_versh_to_delete)
                                    return;
                            }
                            if (x.max_l_way == x.max_r_way)
                            {
                                if (x.max_l_sum > x.max_r_sum)
                                {
                                    Obhod_2(x.lSon);
                                    if (!ne_opredelena_centre_versh_to_delete)
                                        return;
                                }
                                if (x.max_l_sum < x.max_r_sum)
                                {
                                    Obhod_2(x.rSon);
                                    if (!ne_opredelena_centre_versh_to_delete)
                                        return;
                                }
                            }
                        }
                        if (x.lSon != null)
                        {
                            Obhod_2(x.lSon);
                            if (!ne_opredelena_centre_versh_to_delete)
                                return;
                        }
                        if (x.rSon != null)
                        {
                            Obhod_2(x.rSon);
                            if (!ne_opredelena_centre_versh_to_delete)
                                return;
                        }
                    }
                }
                else
                {
                    if (x.info == root_to_delete) // Дошли до корня нашего поддерева
                    {
                        Obhod_2_special_propusk = true;
                        if (x.max_l_way > x.max_r_way)
                        {
                            needed_steps_from_root_to_centre_versh = (x.max_l_way - x.max_r_way) / 2;
                            needed_steps_from_root_to_centre_versh--;
                            Obhod_2(x.lSon);
                            if (!ne_opredelena_centre_versh_to_delete)
                                return;
                        }
                        if (x.max_l_way < x.max_r_way)
                        {
                            needed_steps_from_root_to_centre_versh = (x.max_r_way - x.max_l_way) / 2;
                            needed_steps_from_root_to_centre_versh--;
                            Obhod_2(x.rSon);
                            if (!ne_opredelena_centre_versh_to_delete)
                                return;
                        }
                    }
                    if (x.lSon != null)
                    {
                        Obhod_2(x.lSon);
                        if (!ne_opredelena_centre_versh_to_delete)
                            return;
                    }
                    if (x.rSon != null)
                    {
                        Obhod_2(x.rSon);
                        if (!ne_opredelena_centre_versh_to_delete)
                            return;
                    }
                }
            }
        }

        public void output(Item x, TextWriter y)
        { // Вывод
            y.WriteLine(x.info);
            if (x.lSon != null) output(x.lSon, y);
            if (x.rSon != null) output(x.rSon, y);
        }
    }

    class Tree01
    {
        static void Main(string[] args)
        {
            Tree my_tree = new Tree();
            StreamReader reader = new StreamReader("in.txt");
            StreamWriter writer = new StreamWriter("out.txt");
            string str;
            while ((str = reader.ReadLine()) != null)
            {
                int key = Convert.ToInt32(str);
                my_tree.Insert(key);
            }
            my_tree.Obhod_1(my_tree.root);
            if (!my_tree.centre_versh_and_root_are_the_same && my_tree.centre_versh_exists)
            {
                my_tree.Obhod_2(my_tree.root); // Во втором обходе определяем центральную вершину для удаления
                my_tree.Delete(my_tree.centre_versh_to_delete);
            }
            my_tree.Delete(my_tree.root_to_delete);
            my_tree.output(my_tree.root, writer);
            reader.Close();
            writer.Close();
        }
    }
}
// АЛГОРИТМ
// Нам потребуется один обратный обход в любом случае, и, возможно, нам понадобится ещё один прямой обход
// Для каждой вершины запоминать 2 расстояния: 1) максимальный путь до листа в левом направлении 2) максимальный путь до листа в правом направлении
// Также нужно запоминать 2 суммы: 1) сумма всех ключей до листа в левом направлении 2) сумма всех ключей до листа в правом направлении
// Для каждой вершины найти сумму полученных двух путей, и вершина с наибольшей суммой и будет являться корнем искомого наибольшего полупути
// Если оба путя для корня равны - значит, он по совместительству еще и центральная вершина в наибольшем полупути
// Если же оба пути не равны, однако сумма двух путей нечетна, то центральной вершины просто не существует
// А если четная, значит центральную вершину можно найти следующим образом:
// От большего из двух путей отнять меньший, потом поделить на два, и на это кол-во шагов пойти в ту сторону, где был больше путь (а если пути равны, то где больше сумма ключей)
// Там-то и наткнемся на центральную вершину
// Теперь удаляем сначала центральную вершину, потом корень (ну либо только корень)