using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WinFormPatnashki
{
    public partial class DeleteGameForm : Form
    {
        private DateTime ans;
        public DeleteGameForm(GameResult tmpresult)
        {
            InitializeComponent();
            int count = 1;
            try
            {
                foreach (var x in tmpresult.ShowAll())
                {
                    string temp = "";
                    temp += count.ToString() + '\t' + x.User_name + ": " + x.Start_time + " " + x.Play_time + " " + x.Moving_number;
                    listBox1.Items.Add(temp);
                    monthCalendar1.AddAnnuallyBoldedDate(x.Start_time);
                    count++;
                    //monthCalendar1.MinDate = (tmpresult.ShowAll())[0].Start_time;
                }
            }
            catch (NullReferenceException) { }
            
        }

        public DateTime Ans { get => ans; set => ans = value; }

        private void monthCalendar1_DateChanged(object sender, DateRangeEventArgs e)
        {
            ans = (sender as MonthCalendar).SelectionStart;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.Hide();
        }
    }
}
