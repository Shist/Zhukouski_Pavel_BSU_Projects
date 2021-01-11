using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Часы
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Clock_Tick(object sender, EventArgs e)
        {
            timelbl.Text = DateTime.Now.ToLongTimeString();
            datelbl.Text = DateTime.Now.ToLongDateString();
        }

        private void timelbl_Click(object sender, EventArgs e)
        {
            MessageBox.Show(timelbl.Text);
        }

        private void datelbl_Click(object sender, EventArgs e)
        {
            MessageBox.Show(datelbl.Text);
        }
    }
}
