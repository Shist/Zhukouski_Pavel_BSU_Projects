using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WinFormPatnashki
{
    class GameEngine
    {
        private int emptyblock_i;
        private int emptyblock_j;
        private Tuple<int, int> coord_size;//максимальные координаты
        //private int size;
        private int[,] mass;
        private int[,] reload;//матрица для перезагрузки
        private uint motion_count=0;//счтчик ходов


        //свойства
        public int[,] Mass
        {
            get => mass;
            private set => mass = value;
        }
        public Tuple<int, int> Coord_size
        {
            get => coord_size;
           private set => coord_size = value;
        }
        public uint Motion_count
        {
            get => motion_count;
            private set => motion_count = value;
        }
        
        public GameEngine(int i_max, int j_max)
        {
            //size = (i_max * j_max);
            Coord_size = new Tuple<int, int>(i_max, j_max);
            Mass = new int[i_max, j_max];
            StartGame();
        }

        public void StartGame()
        {
            int count = 1;
            for (int i = 0; i < Coord_size.Item1; i++)
            {
                for (int j = 0; j < Coord_size.Item2; j++)
                {
                    if (i == Coord_size.Item1 && j == Coord_size.Item2)
                        Mass[i, j] = 0;
                    Mass[i, j] = count;
                    count++;
                }
            }
            emptyblock_i = Coord_size.Item1-1;
            emptyblock_j = Coord_size.Item2-1;
#warning to change numbers of start moves 
            RundomStart(15);
            reload=new int[Coord_size.Item1, Coord_size.Item2];
            for (int i=0;i<Coord_size.Item1;i++)
                for(int j=0;j<Coord_size.Item2;j++)
                    reload[i,j] = Mass[i,j];
            Motion_count = 0;
        }
        public void ReloadGame()
        {
            for (int i = 0; i < Coord_size.Item1; i++)
                for (int j = 0; j < Coord_size.Item2; j++)
                {
                    Mass[i, j] = reload[i, j];
                    if (Mass[i, j] == 0)
                    {
                        emptyblock_i = i;
                        emptyblock_j = j;
                    }
                }
            Motion_count = 0;
        }
        public void Change(int aposition)
        {
            int i, j;
            i = aposition / Coord_size.Item1;
            j = aposition % Coord_size.Item1;
            if(Math.Abs(i-emptyblock_i)+Math.Abs(j-emptyblock_j)<2)
            {
                Mass[emptyblock_i, emptyblock_j] = Mass[i, j];
                Mass[i, j] = 0;
                emptyblock_i = i;
                emptyblock_j = j;
                Motion_count++;
            }
        }
        public bool iswin()
        {
            int count = 1;
            for(int i=0; i<Coord_size.Item1;i++)
                for(int j=0;j<Coord_size.Item2;j++)
                {
                    if (i == Coord_size.Item1 - 1 && j == Coord_size.Item2 - 1)
                    {
                        if (Mass[i, j] != 0) return false;
                    }
                    else
                    {
                        if (Mass[i, j] != count) return false;
                    }
                    count++;
                }
            return true;
        }
        private void RundomStart(int arepeats)
        {
            Random tmpRan = new Random();
            for (int i = 0; i < arepeats; i++)
            {
                int motion = tmpRan.Next(0, 4);
                switch (motion)
                {
                    case (0):
                        if (emptyblock_i != 0)
                            Change(emptyblock_j + ((emptyblock_i - 1) * Coord_size.Item1));
                        break;
                    case (1):
                        if (emptyblock_i != (Coord_size.Item1-1))
                            Change(emptyblock_j + ((emptyblock_i + 1) * Coord_size.Item1));
                        break;
                    case (2):
                        if (emptyblock_j != 0)
                            Change((emptyblock_j-1) + ((emptyblock_i) * Coord_size.Item1));
                        break;
                    case (3):
                        if (emptyblock_i != (Coord_size.Item2 - 1))
                            Change((emptyblock_j+1) + ((emptyblock_i) * Coord_size.Item1));
                        break;
                }
            }
        }
        
    }
}
