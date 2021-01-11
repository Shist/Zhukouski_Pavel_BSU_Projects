using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using System.Xml.Serialization;

namespace WinFormPatnashki
{
    
    public partial class Form1 : Form
    {
        private DateTime t1;
        private GameEngine game;
        private GameResult.ResultNode resultNode;
        private GameResult games_range;
        public DateTime T1 { get => t1; set => t1 = value; }

        //initialize
        public Form1()
        {
            InitializeComponent();
            timer1.Stop();
            пререзагрузкаToolStripMenuItem.Enabled = false;
            games_range = new GameResult();
            DeSerializeIt();
            game = new GameEngine(4, 4);
            toolStripTextBox2.Text = "0";
            toolStripTextBox5.Text = "0";
            timer1.Interval = 1000;
            int count = 1;
            for (int i = 0; i < 16; i++)
            {
                (tableLayoutPanel1.Controls["button" + Convert.ToString(count)]).Enabled = false;
                count++;
            }

        }

        private void tableLayoutPanel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
        //All button
        private void button14_Click(object sender, EventArgs e)
        {
            if (sender is Button)
            {
                int position = Convert.ToInt32((sender as Button).Tag);
                game.Change(position);
                refresh_buttons();
                if (game.iswin())
                {
                    int count = 1;
                    for (int i = 0; i < 16; i++)
                    {
                        (tableLayoutPanel1.Controls["button" + Convert.ToString(count)]).Enabled = false;
                        count++;
                    }
                    timer1.Stop();
                    resultNode.Moving_number = (int)game.Motion_count;
                    resultNode.Play_time = T1;
                    YouWon tmp = new YouWon();
                    tmp.ShowDialog();
                    resultNode.User_name=tmp.Actor_name;
                    games_range.InsertNewRecord(resultNode);
                    SerializeIt();
                    пререзагрузкаToolStripMenuItem.Enabled = false;

                }
            }
        }
        //timer
        private void timer1_Tick(object sender, EventArgs e)
        {
            T1=T1.AddSeconds(1);
            toolStripTextBox5.Text = T1.TimeOfDay.ToString();
        }

        private void refresh_buttons()
        {
            int count = 0;
            for (int i = 0; i < game.Coord_size.Item1; i++)
                for (int j = 0; j < game.Coord_size.Item2; j++)
                {
                    count++;
                    string temp = "button" + Convert.ToString(count);

                    if (game.Mass[i, j]==0) tableLayoutPanel1.Controls[temp].Visible = false;
                    else
                    {
                        tableLayoutPanel1.Controls[temp].Visible = true;
                        tableLayoutPanel1.Controls[temp].Text = Convert.ToString(game.Mass[i, j]);
                    }
                }
            toolStripTextBox2.Text = Convert.ToString(game.Motion_count);
        }

        // start game
        private void новаяИграToolStripMenuItem_Click(object sender, EventArgs e)
        {
            T1 = new DateTime(1, 1, 1, 0, 0, 0);
            пререзагрузкаToolStripMenuItem.Enabled = true;
            resultNode = new GameResult.ResultNode();
            int count = 1;
            timer1.Start();
            for (int i = 0; i < 16; i++)
            {
                (tableLayoutPanel1.Controls["button" + Convert.ToString(count)] as Button).Enabled = true;
                count++;
            }
            game.StartGame();
            refresh_buttons();
        }

        //перезагрузка
        private void пререзагрузкаToolStripMenuItem_Click(object sender, EventArgs e)
        {
            T1 = new DateTime(1, 1, 1, 0, 0, 0);
            timer1.Start();
            int count = 1;
            for (int i = 0; i < 16; i++)
            {
                tableLayoutPanel1.Controls["button" + Convert.ToString(count)].Enabled = true;
                count++;
            }
            game.ReloadGame();
            refresh_buttons();
        }

        private void menuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }

        private void продолжительностиСборкиToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string temp="";
            foreach (var x in games_range.ShowBestTime())
            {
                temp += x.User_name + ": \t" + x.Start_time + " \t" + x.Play_time.TimeOfDay.ToString() + " \t" + x.Moving_number + "\n";
            }
            if (temp != "")
            {
                MessageBox.Show(temp,"Лучшие результаты по времени");
            }
            else MessageBox.Show("Список пуст");
        }

        private void поПроToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string temp = "";
            foreach (var x in games_range.ShowBestMoveResult())
            {
                temp += x.User_name + ": \t" + x.Start_time + " \t" + x.Play_time.TimeOfDay.ToString() + " \t" + x.Moving_number + "\n";
            }
            if (temp != "")
            {
                MessageBox.Show(temp,"Лучшие результаты по количеству перемещений");
            }
            else MessageBox.Show("Список пуст");
        }

        private void последнихToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string temp = "";
            foreach (var x in games_range.ShowLastTen())
            {
                temp += x.User_name + ": \t" + x.Start_time + " \t" + x.Play_time.TimeOfDay.ToString() + " \t" + x.Moving_number + "\n";
            }
            if (temp != "")
            {
                MessageBox.Show(temp,"Последние 10 результатов");
            }
            else MessageBox.Show("Список пуст");
        }

        private void удалитьСуществующиеРекордыToolStripMenuItem_Click(object sender, EventArgs e)
        {

            DeleteGameForm deldate = new DeleteGameForm(games_range);
            deldate.ShowDialog();
            games_range.SearchAndRemove(deldate.Ans);
            SerializeIt();
        }
        /*
        #region binarySerialisation
        private void SerializeIt()
        {
            using (FileStream fs = new FileStream("Results.dat", FileMode.Create))
            {
                BinaryFormatter bf = new BinaryFormatter();
                bf.Serialize(fs, games_range);
            }
        }
        private void DeSerializeIt()
        {
            try
            {
                using (FileStream fs = new FileStream("Results.dat", FileMode.Open))
                {
                    BinaryFormatter bf = new BinaryFormatter();
                    games_range = (GameResult)bf.Deserialize(fs);
                }
            }
            catch (Exception){}  
        }
        #endregion*/

        #region XMLSerialisation
        private void SerializeIt()
        {
            using (FileStream fs = new FileStream("ResultsXML.xml", FileMode.Create))
            {
                XmlSerializer bf = new XmlSerializer(typeof(GameResult));
                bf.Serialize(fs, games_range);
            }
        }
        private void DeSerializeIt()
        {
            try
            {
                using (FileStream fs = new FileStream("ResultsXML.xml", FileMode.Open))
                {
                    XmlSerializer bf = new XmlSerializer(typeof(GameResult));
                    games_range = (GameResult)bf.Deserialize(fs);
                }
            }
            catch (Exception) { }
        }
        #endregion
        private void добавить15ЭлементовВРекордыToolStripMenuItem_Click(object sender, EventArgs e)
        {
            games_range.Add15items();
            SerializeIt();
        }
    }
}
