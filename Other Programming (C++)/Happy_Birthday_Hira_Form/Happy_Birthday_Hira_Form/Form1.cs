using System;
using System.Drawing;
using System.Windows.Forms;
using System.Media;

namespace Happy_Birthday_Hira_Form
{
    public partial class Form : System.Windows.Forms.Form
    {
        private void playSimpleSound()
        {
            SoundPlayer Music = new SoundPlayer("Music.wav");
            Music.Play();
        }

        public Form()
        {
            InitializeComponent();
            BackgroundImage = Image.FromFile("Happy Birthday.jpg");
            ImageAnimator.Animate(BackgroundImage, OnFrameChanged);
        }

        private void OnFrameChanged(object sender, EventArgs e)
        {
            if (InvokeRequired)
            {
                BeginInvoke((Action)(() => OnFrameChanged(sender, e)));
                return;
            }
            ImageAnimator.UpdateFrames();
            Invalidate(false);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Made for HIRA by Shist Degurechaff", "AUTHOR INFO", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            playSimpleSound();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            MessageBox.Show("С Днём Рождения, Хира! Хочу пожелать тебе всего наилучшего. И хотя ты почти ничего обо мне не знаешь, я считаю тебя дорогим" +
                " мне человеком. Возможно ты этого не замечаешь, но ты уникальная личность. Твоя сила воли порой просто поражает. " +
                "Хочу, чтобы ты провела еще один год с улыбкой на улице. Знай, мне очень приятно, если ты все же дочитаешь это скромное поздравление. " +
                "Пожалуйста, не держи на меня зла X)", "Поздравление", MessageBoxButtons.OK);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }
    }
}