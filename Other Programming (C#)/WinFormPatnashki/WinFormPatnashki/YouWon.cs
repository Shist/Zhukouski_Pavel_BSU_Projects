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
    public partial class YouWon : Form
    {
        private string actor_name;
        public YouWon()
        {
            InitializeComponent();
        }

        public string Actor_name { get => actor_name; private set => actor_name = value; }

        private void button1_Click(object sender, EventArgs e)
        {
            Actor_name = textBox1.Text;
            this.Hide();
        }
    }
}
