namespace Calculator
{
    partial class Form1
    {
        /// <summary>
        /// Требуется переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Обязательный метод для поддержки конструктора - не изменяйте
        /// содержимое данного метода при помощи редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.buttonMul = new System.Windows.Forms.Button();
            this.buttonDev = new System.Windows.Forms.Button();
            this.buttonSum = new System.Windows.Forms.Button();
            this.buttonSub = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.textBoxResult = new System.Windows.Forms.TextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.button7 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.button5 = new System.Windows.Forms.Button();
            this.button6 = new System.Windows.Forms.Button();
            this.buttonNeg = new System.Windows.Forms.Button();
            this.button8 = new System.Windows.Forms.Button();
            this.buttonComma = new System.Windows.Forms.Button();
            this.button0 = new System.Windows.Forms.Button();
            this.button16 = new System.Windows.Forms.Button();
            this.button9 = new System.Windows.Forms.Button();
            this.ButtonC = new System.Windows.Forms.Button();
            this.buttonQually = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // buttonMul
            // 
            this.buttonMul.Location = new System.Drawing.Point(0, 50);
            this.buttonMul.Name = "buttonMul";
            this.buttonMul.Size = new System.Drawing.Size(100, 60);
            this.buttonMul.TabIndex = 2;
            this.buttonMul.TabStop = false;
            this.buttonMul.Text = "*";
            this.buttonMul.UseVisualStyleBackColor = true;
            this.buttonMul.Click += new System.EventHandler(this.buttonMul_Click);
            // 
            // buttonDev
            // 
            this.buttonDev.Location = new System.Drawing.Point(100, 50);
            this.buttonDev.Name = "buttonDev";
            this.buttonDev.Size = new System.Drawing.Size(100, 60);
            this.buttonDev.TabIndex = 3;
            this.buttonDev.TabStop = false;
            this.buttonDev.Text = "/";
            this.buttonDev.UseVisualStyleBackColor = true;
            this.buttonDev.Click += new System.EventHandler(this.buttonDev_Click);
            // 
            // buttonSum
            // 
            this.buttonSum.Location = new System.Drawing.Point(200, 50);
            this.buttonSum.Name = "buttonSum";
            this.buttonSum.Size = new System.Drawing.Size(100, 60);
            this.buttonSum.TabIndex = 4;
            this.buttonSum.TabStop = false;
            this.buttonSum.Text = "+";
            this.buttonSum.UseVisualStyleBackColor = true;
            this.buttonSum.Click += new System.EventHandler(this.buttonSum_Click);
            // 
            // buttonSub
            // 
            this.buttonSub.Location = new System.Drawing.Point(300, 50);
            this.buttonSub.Name = "buttonSub";
            this.buttonSub.Size = new System.Drawing.Size(100, 60);
            this.buttonSub.TabIndex = 5;
            this.buttonSub.TabStop = false;
            this.buttonSub.Text = "-";
            this.buttonSub.UseVisualStyleBackColor = true;
            this.buttonSub.Click += new System.EventHandler(this.buttonDev_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(691, 213);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(49, 17);
            this.label1.TabIndex = 6;
            this.label1.Text = "Число";
            // 
            // textBoxResult
            // 
            this.textBoxResult.BackColor = System.Drawing.SystemColors.Info;
            this.textBoxResult.Font = new System.Drawing.Font("Times New Roman", 12F, System.Drawing.FontStyle.Bold);
            this.textBoxResult.Location = new System.Drawing.Point(0, 0);
            this.textBoxResult.Multiline = true;
            this.textBoxResult.Name = "textBoxResult";
            this.textBoxResult.Size = new System.Drawing.Size(400, 50);
            this.textBoxResult.TabIndex = 7;
            this.textBoxResult.TabStop = false;
            this.textBoxResult.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxResult.UseWaitCursor = true;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(0, 110);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(100, 60);
            this.button1.TabIndex = 8;
            this.button1.TabStop = false;
            this.button1.Text = "1";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(100, 110);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(100, 60);
            this.button2.TabIndex = 9;
            this.button2.TabStop = false;
            this.button2.Text = "2";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(200, 110);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(100, 60);
            this.button3.TabIndex = 10;
            this.button3.TabStop = false;
            this.button3.Text = "3";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // button7
            // 
            this.button7.Location = new System.Drawing.Point(0, 230);
            this.button7.Name = "button7";
            this.button7.Size = new System.Drawing.Size(100, 60);
            this.button7.TabIndex = 11;
            this.button7.TabStop = false;
            this.button7.Text = "7";
            this.button7.UseVisualStyleBackColor = true;
            this.button7.Click += new System.EventHandler(this.button7_Click);
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(0, 170);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(100, 60);
            this.button4.TabIndex = 12;
            this.button4.TabStop = false;
            this.button4.Text = "4";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // button5
            // 
            this.button5.Location = new System.Drawing.Point(100, 170);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(100, 60);
            this.button5.TabIndex = 13;
            this.button5.TabStop = false;
            this.button5.Text = "5";
            this.button5.UseVisualStyleBackColor = true;
            this.button5.Click += new System.EventHandler(this.button5_Click);
            // 
            // button6
            // 
            this.button6.Location = new System.Drawing.Point(200, 170);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(100, 60);
            this.button6.TabIndex = 14;
            this.button6.TabStop = false;
            this.button6.Text = "6";
            this.button6.UseVisualStyleBackColor = true;
            this.button6.Click += new System.EventHandler(this.button6_Click);
            // 
            // buttonNeg
            // 
            this.buttonNeg.Location = new System.Drawing.Point(300, 230);
            this.buttonNeg.Name = "buttonNeg";
            this.buttonNeg.Size = new System.Drawing.Size(100, 60);
            this.buttonNeg.TabIndex = 15;
            this.buttonNeg.TabStop = false;
            this.buttonNeg.Text = "+-";
            this.buttonNeg.UseVisualStyleBackColor = true;
            this.buttonNeg.Click += new System.EventHandler(this.buttonNeg_Click);
            // 
            // button8
            // 
            this.button8.Location = new System.Drawing.Point(100, 230);
            this.button8.Name = "button8";
            this.button8.Size = new System.Drawing.Size(100, 60);
            this.button8.TabIndex = 16;
            this.button8.TabStop = false;
            this.button8.Text = "8";
            this.button8.UseVisualStyleBackColor = true;
            this.button8.Click += new System.EventHandler(this.button8_Click);
            // 
            // buttonComma
            // 
            this.buttonComma.Location = new System.Drawing.Point(0, 290);
            this.buttonComma.Name = "buttonComma";
            this.buttonComma.Size = new System.Drawing.Size(100, 60);
            this.buttonComma.TabIndex = 17;
            this.buttonComma.TabStop = false;
            this.buttonComma.Text = ",";
            this.buttonComma.UseVisualStyleBackColor = true;
            this.buttonComma.Click += new System.EventHandler(this.buttonComma_Click);
            // 
            // button0
            // 
            this.button0.Location = new System.Drawing.Point(100, 290);
            this.button0.Name = "button0";
            this.button0.Size = new System.Drawing.Size(100, 60);
            this.button0.TabIndex = 18;
            this.button0.TabStop = false;
            this.button0.Text = "0";
            this.button0.UseVisualStyleBackColor = true;
            this.button0.Click += new System.EventHandler(this.button0_Click);
            // 
            // button16
            // 
            this.button16.Location = new System.Drawing.Point(300, 110);
            this.button16.Name = "button16";
            this.button16.Size = new System.Drawing.Size(100, 60);
            this.button16.TabIndex = 19;
            this.button16.TabStop = false;
            this.button16.Text = "<-";
            this.button16.UseVisualStyleBackColor = true;
            this.button16.Click += new System.EventHandler(this.button16_Click);
            // 
            // button9
            // 
            this.button9.Location = new System.Drawing.Point(200, 230);
            this.button9.Name = "button9";
            this.button9.Size = new System.Drawing.Size(100, 60);
            this.button9.TabIndex = 20;
            this.button9.TabStop = false;
            this.button9.Text = "9";
            this.button9.UseVisualStyleBackColor = true;
            this.button9.Click += new System.EventHandler(this.button9_Click);
            // 
            // ButtonC
            // 
            this.ButtonC.Location = new System.Drawing.Point(300, 170);
            this.ButtonC.Name = "ButtonC";
            this.ButtonC.Size = new System.Drawing.Size(100, 60);
            this.ButtonC.TabIndex = 22;
            this.ButtonC.TabStop = false;
            this.ButtonC.Text = "C";
            this.ButtonC.UseVisualStyleBackColor = true;
            this.ButtonC.Click += new System.EventHandler(this.ButtonC_Click);
            // 
            // buttonQually
            // 
            this.buttonQually.Location = new System.Drawing.Point(200, 290);
            this.buttonQually.Name = "buttonQually";
            this.buttonQually.Size = new System.Drawing.Size(200, 60);
            this.buttonQually.TabIndex = 23;
            this.buttonQually.TabStop = false;
            this.buttonQually.Text = "=";
            this.buttonQually.UseVisualStyleBackColor = true;
            this.buttonQually.Click += new System.EventHandler(this.buttonQually_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(35, 15);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(0, 17);
            this.label2.TabIndex = 24;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F);
            this.label3.Location = new System.Drawing.Point(12, 15);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(0, 25);
            this.label3.TabIndex = 25;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(398, 347);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.buttonQually);
            this.Controls.Add(this.ButtonC);
            this.Controls.Add(this.button9);
            this.Controls.Add(this.button16);
            this.Controls.Add(this.button0);
            this.Controls.Add(this.buttonComma);
            this.Controls.Add(this.button8);
            this.Controls.Add(this.buttonNeg);
            this.Controls.Add(this.button6);
            this.Controls.Add(this.button5);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.button7);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.textBoxResult);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.buttonSub);
            this.Controls.Add(this.buttonSum);
            this.Controls.Add(this.buttonDev);
            this.Controls.Add(this.buttonMul);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonMul;
        private System.Windows.Forms.Button buttonDev;
        private System.Windows.Forms.Button buttonSum;
        private System.Windows.Forms.Button buttonSub;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBoxResult;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button7;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.Button button6;
        private System.Windows.Forms.Button buttonNeg;
        private System.Windows.Forms.Button button8;
        private System.Windows.Forms.Button buttonComma;
        private System.Windows.Forms.Button button0;
        private System.Windows.Forms.Button button16;
        private System.Windows.Forms.Button button9;
        private System.Windows.Forms.Button ButtonC;
        private System.Windows.Forms.Button buttonQually;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
    }
}

