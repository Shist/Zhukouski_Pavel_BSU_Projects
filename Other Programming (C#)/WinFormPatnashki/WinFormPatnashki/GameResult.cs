using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WinFormPatnashki
{
    [Serializable]
    public class GameResult
    {
        [Serializable]
        public class ResultNode: IComparable<ResultNode>
        {
            public String user_name;
            public DateTime start_time;
            public DateTime play_time;
            public int moving_number;


            public ResultNode()
            {
                Start_time = DateTime.Now;
            }

            public ResultNode(string _name, DateTime _start_time, DateTime _play_time, int _moving_number)
            {
                user_name = _name;
                start_time = _start_time;
                play_time = _play_time;
                moving_number = _moving_number;
            }

            #region properties
            public string User_name { get => user_name; set => user_name = value; }
            public DateTime Start_time { get => start_time; set => start_time = value; }
            public DateTime Play_time { get => play_time; set => play_time = value; }
            public int Moving_number { get => moving_number; set => moving_number = value; }
            #endregion

            public int CompareTo(ResultNode other)
            {
                return (other.Start_time).CompareTo(this.start_time);
            }

        }

        public GameResult()
        {

        }

        public List<ResultNode> allrecords=new List<ResultNode>();

        private class PlayTimeCompare : IComparer<ResultNode>
        {
            int IComparer<ResultNode>.Compare(ResultNode x, ResultNode y)
            {
                return x.Play_time.CompareTo(y.Play_time);
            }
        }

        private class MoveCompare : IComparer<ResultNode>
        {
            public int Compare(ResultNode x, ResultNode y)
            {
                return x.Moving_number.CompareTo(y.Moving_number);
            }
        }

        public List<ResultNode> ShowBestTime()
        {
            List<ResultNode> temp=new List<ResultNode>();
            temp.AddRange(allrecords);
            temp.Sort(new PlayTimeCompare());
            try
            {
                temp.RemoveRange(10, temp.Count - 10);
            }
            catch(ArgumentOutOfRangeException ) { }
            catch (ArgumentException) { }
            return (temp);
        }

        public List<ResultNode> ShowBestMoveResult()
        {
            List<ResultNode> temp = new List<ResultNode>();
            temp.AddRange(allrecords);
            temp.Sort(new MoveCompare());
            try
            {
                temp.RemoveRange(10, temp.Count-10);
            }
            catch (Exception) { }
            return (temp);
        }

        public List<ResultNode> ShowLastTen()
        {
            List<ResultNode> temp = new List<ResultNode>();
            int endrenge = (allrecords.Count < 10) ? (allrecords.Count) : 10;
            temp = allrecords.GetRange(0, endrenge);
            return (temp);
        }

        public List<ResultNode> ShowAll()
        {
            return allrecords;
        }

        public void InsertNewRecord(ResultNode temp)
        {
            allrecords.Add(temp);
            allrecords.Sort();
        }
        
        public void Add15items()
        {
            InsertNewRecord(new ResultNode("player01", new DateTime(2019, 4, 10), new DateTime(0001, 1, 1, 0, 0, 20, 0), 40));
            InsertNewRecord(new ResultNode("player02", new DateTime(2019, 4, 11), new DateTime(0001, 1, 1, 0, 22, 0), 39));
            InsertNewRecord(new ResultNode("player03", new DateTime(2019, 4, 12), new DateTime(0001, 1, 1, 0, 15, 0), 42));
            InsertNewRecord(new ResultNode("player04", new DateTime(2019, 4, 14), new DateTime(0001, 1, 1, 3, 20, 0), 87));
            InsertNewRecord(new ResultNode("player05", new DateTime(2019, 4, 15), new DateTime(0001, 1, 1, 2, 20, 0), 79));
            InsertNewRecord(new ResultNode("player06", new DateTime(2019, 4, 16), new DateTime(0001, 1, 1, 1, 0, 0), 99));
            InsertNewRecord(new ResultNode("player07", new DateTime(2019, 4, 17), new DateTime(0001, 1, 1, 0, 25, 0), 124));
            InsertNewRecord(new ResultNode("player08", new DateTime(2019, 4, 18), new DateTime(0001, 1, 1, 0, 40, 0), 120));
            InsertNewRecord(new ResultNode("player09", new DateTime(2019, 4, 19), new DateTime(0001, 1, 1, 0, 13, 0), 19));
            InsertNewRecord(new ResultNode("player10", new DateTime(2019, 4, 21), new DateTime(0001, 1, 1, 0, 11, 0), 30));
            InsertNewRecord(new ResultNode("player11", new DateTime(2019, 4, 22), new DateTime(0001, 1, 1, 0, 7, 0), 7));
            InsertNewRecord(new ResultNode("player12", new DateTime(2019, 4, 23), new DateTime(0001, 1, 1, 0, 8, 0), 25));
            InsertNewRecord(new ResultNode("player13", new DateTime(2019, 4, 15), new DateTime(0001, 1, 1, 0, 12, 0), 20));
            InsertNewRecord(new ResultNode("player14", new DateTime(2019, 4, 17), new DateTime(0001, 1, 1, 0, 24, 0), 14));
            InsertNewRecord(new ResultNode("player15", new DateTime(2019, 4, 14), new DateTime(0001, 1, 1, 0, 12, 0), 12));
        }
        
        public void SearchAndRemove(DateTime latestDay)
        {
            
            int _of_region=allrecords.FindIndex(x => x.Start_time<=(latestDay));
            try
            {
                allrecords.RemoveRange(_of_region, (allrecords.Count-_of_region));
            }
            catch (Exception) { }
        }

    }
}
