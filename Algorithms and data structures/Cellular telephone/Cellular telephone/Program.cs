using System;
using System.IO; // Для ввода/вывода
using System.Linq; // Для метода Sum()
using System.Collections.Generic; // Для List

namespace Cellular_telephone
{
    class Program
    { // Двумерное ДП
        static void Main(string[] args)
        {
            long MAX = int.MaxValue;
            StreamReader reader = new StreamReader("in.txt");
            StreamWriter writer = new StreamWriter("out.txt");
            int N = Convert.ToInt32(reader.ReadLine()); // Число клавиш на клавиатуре телефона
            int M = Convert.ToInt32(reader.ReadLine()); // Число букв алфавита
            List<long> use_of_letter = new List<long>(M + 1); // Массив с коэффициентами использования букв
            use_of_letter.Add(0);
            use_new_key_or_not.Add(false);
            for (int i = 1; i < M + 1; i++)
            {
                use_of_letter.Add(Convert.ToInt32(reader.ReadLine())); // Считываем данные об использовании каждой буквы алфавита и помещаем в массив
                use_new_key_or_not.Add(false);
            }
            if (N >= M) // Если кнопок больше, чем букв
                writer.Write(use_of_letter.Sum()); // То просто выводим сумму коэффициентов использования букв
            else
            {
                List<List<long>> Min_Sum_Key_Letter_ = new List<List<long>>(N + 1); // В матрице будем хранить все суммы
                long Letter_num_for_key_ = 1;
                for (int i = 0; i < N + 1; i++)
                {
                    Min_Sum_Key_Letter_.Add(new List<long>(M + 1));
                    int free_keys_left = i - 1;
                    for (int j = 0; j < M + 1; j++)
                    {
                        if (j == 0 && i != 0)
                        { // БАЗА ДП (1)
                            Min_Sum_Key_Letter_[i].Add(0); // Если кнопки есть, но нет букв, то сумма равна нулю
                        }
                        else if (i == 0)
                        { // БАЗА ДП (2)
                            Min_Sum_Key_Letter_[i].Add(MAX); // Если нет кнопок, то сумма равна бесконености
                        }
                        else if (j == 1)
                        {
                            Min_Sum_Key_Letter_[i].Add(use_of_letter[j]);
                            Letter_num_for_key_++;
                        }
                        else // i != 0, j != 0
                        {
                            long a = Min_Sum_Key_Letter_[i][j - 1] + Letter_num_for_key_ * use_of_letter[j]; // Ставим новую букву на текущую клавишу
                            long b = Min_Sum_Key_Letter_[i - 1][j - 1] + use_of_letter[j]; // Выбираем новую клавишу
                            if (j != M)
                            { // Если буква не последняя, ...
                                if (b < a && free_keys_left != 0 && // Если выгоднее перейти на новую клавишу и у нас они еще есть, ...
                                b + Letter_num_for_key_ * use_of_letter[j + 1] < // И если для следующей клавишы сумма будет хорошая, то...
                                Min_Sum_Key_Letter_[i - 1][j] + use_of_letter[j + 1])
                                { // Если перешли на новую клавишу
                                    free_keys_left--;
                                    Min_Sum_Key_Letter_[i].Add(b);
                                    Letter_num_for_key_ = 2;
                                }
                                else
                                { // Если остались на текущей клавише
                                    Min_Sum_Key_Letter_[i].Add(a);
                                    Letter_num_for_key_++;
                                }
                            }
                            else
                                Min_Sum_Key_Letter_[i].Add(b);
                        }
                    }
                    Letter_num_for_key_ = 1;
                }
                writer.Write(Min_Sum_Key_Letter_[N][M]);
            }
            writer.Close();
        }
    }
}