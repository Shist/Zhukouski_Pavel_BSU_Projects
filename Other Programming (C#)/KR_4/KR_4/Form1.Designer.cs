namespace KR_4
{
    partial class Form1
    {
        /// <summary>
        /// Обязательная переменная конструктора.
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
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.PictureBox_Field = new System.Windows.Forms.PictureBox();
            this.Group_Info = new System.Windows.Forms.GroupBox();
            this.Label_OutputStatus = new System.Windows.Forms.Label();
            this.Label_QtOordinate = new System.Windows.Forms.Label();
            this.Label_QtAbsciss = new System.Windows.Forms.Label();
            this.Group_SortedPoints = new System.Windows.Forms.GroupBox();
            this.RTextBox_SortePoints = new System.Windows.Forms.RichTextBox();
            this.Label_QtFourth = new System.Windows.Forms.Label();
            this.Label_QtThird = new System.Windows.Forms.Label();
            this.Label_QtSecond = new System.Windows.Forms.Label();
            this.Label_QtFirst = new System.Windows.Forms.Label();
            this.Button_Decrease = new System.Windows.Forms.Button();
            this.Button_Encrease = new System.Windows.Forms.Button();
            this.Label_Margin = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.PictureBox_Field)).BeginInit();
            this.Group_Info.SuspendLayout();
            this.Group_SortedPoints.SuspendLayout();
            this.SuspendLayout();
            // 
            // PictureBox_Field
            // 
            this.PictureBox_Field.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.PictureBox_Field.Location = new System.Drawing.Point(16, 34);
            this.PictureBox_Field.Margin = new System.Windows.Forms.Padding(4);
            this.PictureBox_Field.Name = "PictureBox_Field";
            this.PictureBox_Field.Size = new System.Drawing.Size(657, 525);
            this.PictureBox_Field.TabIndex = 0;
            this.PictureBox_Field.TabStop = false;
            this.PictureBox_Field.Paint += new System.Windows.Forms.PaintEventHandler(this.PictureBox_Field_Paint);
            // 
            // Group_Info
            // 
            this.Group_Info.Controls.Add(this.Label_OutputStatus);
            this.Group_Info.Controls.Add(this.Label_QtOordinate);
            this.Group_Info.Controls.Add(this.Label_QtAbsciss);
            this.Group_Info.Controls.Add(this.Group_SortedPoints);
            this.Group_Info.Controls.Add(this.Label_QtFourth);
            this.Group_Info.Controls.Add(this.Label_QtThird);
            this.Group_Info.Controls.Add(this.Label_QtSecond);
            this.Group_Info.Controls.Add(this.Label_QtFirst);
            this.Group_Info.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Group_Info.Location = new System.Drawing.Point(681, 3);
            this.Group_Info.Margin = new System.Windows.Forms.Padding(4);
            this.Group_Info.Name = "Group_Info";
            this.Group_Info.Padding = new System.Windows.Forms.Padding(4);
            this.Group_Info.Size = new System.Drawing.Size(338, 556);
            this.Group_Info.TabIndex = 1;
            this.Group_Info.TabStop = false;
            this.Group_Info.Text = "Панель информации";
            // 
            // Label_OutputStatus
            // 
            this.Label_OutputStatus.AutoSize = true;
            this.Label_OutputStatus.Location = new System.Drawing.Point(8, 527);
            this.Label_OutputStatus.Name = "Label_OutputStatus";
            this.Label_OutputStatus.Size = new System.Drawing.Size(157, 20);
            this.Label_OutputStatus.TabIndex = 2;
            this.Label_OutputStatus.Text = "Label_OutputStatus";
            // 
            // Label_QtOordinate
            // 
            this.Label_QtOordinate.AutoSize = true;
            this.Label_QtOordinate.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Label_QtOordinate.Location = new System.Drawing.Point(8, 156);
            this.Label_QtOordinate.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.Label_QtOordinate.Name = "Label_QtOordinate";
            this.Label_QtOordinate.Size = new System.Drawing.Size(53, 20);
            this.Label_QtOordinate.TabIndex = 7;
            this.Label_QtOordinate.Text = "label3";
            // 
            // Label_QtAbsciss
            // 
            this.Label_QtAbsciss.AutoSize = true;
            this.Label_QtAbsciss.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Label_QtAbsciss.Location = new System.Drawing.Point(8, 131);
            this.Label_QtAbsciss.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.Label_QtAbsciss.Name = "Label_QtAbsciss";
            this.Label_QtAbsciss.Size = new System.Drawing.Size(53, 20);
            this.Label_QtAbsciss.TabIndex = 6;
            this.Label_QtAbsciss.Text = "label3";
            // 
            // Group_SortedPoints
            // 
            this.Group_SortedPoints.Controls.Add(this.RTextBox_SortePoints);
            this.Group_SortedPoints.Location = new System.Drawing.Point(7, 193);
            this.Group_SortedPoints.Name = "Group_SortedPoints";
            this.Group_SortedPoints.Size = new System.Drawing.Size(324, 324);
            this.Group_SortedPoints.TabIndex = 5;
            this.Group_SortedPoints.TabStop = false;
            this.Group_SortedPoints.Text = "Отсортированные точки";
            // 
            // RTextBox_SortePoints
            // 
            this.RTextBox_SortePoints.BackColor = System.Drawing.Color.White;
            this.RTextBox_SortePoints.Location = new System.Drawing.Point(6, 29);
            this.RTextBox_SortePoints.Name = "RTextBox_SortePoints";
            this.RTextBox_SortePoints.ReadOnly = true;
            this.RTextBox_SortePoints.Size = new System.Drawing.Size(312, 289);
            this.RTextBox_SortePoints.TabIndex = 4;
            this.RTextBox_SortePoints.Text = "";
            // 
            // Label_QtFourth
            // 
            this.Label_QtFourth.AutoSize = true;
            this.Label_QtFourth.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Label_QtFourth.Location = new System.Drawing.Point(8, 106);
            this.Label_QtFourth.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.Label_QtFourth.Name = "Label_QtFourth";
            this.Label_QtFourth.Size = new System.Drawing.Size(53, 20);
            this.Label_QtFourth.TabIndex = 3;
            this.Label_QtFourth.Text = "label3";
            // 
            // Label_QtThird
            // 
            this.Label_QtThird.AutoSize = true;
            this.Label_QtThird.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Label_QtThird.Location = new System.Drawing.Point(8, 81);
            this.Label_QtThird.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.Label_QtThird.Name = "Label_QtThird";
            this.Label_QtThird.Size = new System.Drawing.Size(53, 20);
            this.Label_QtThird.TabIndex = 2;
            this.Label_QtThird.Text = "label2";
            // 
            // Label_QtSecond
            // 
            this.Label_QtSecond.AutoSize = true;
            this.Label_QtSecond.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Label_QtSecond.Location = new System.Drawing.Point(8, 56);
            this.Label_QtSecond.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.Label_QtSecond.Name = "Label_QtSecond";
            this.Label_QtSecond.Size = new System.Drawing.Size(53, 20);
            this.Label_QtSecond.TabIndex = 1;
            this.Label_QtSecond.Text = "label1";
            // 
            // Label_QtFirst
            // 
            this.Label_QtFirst.AutoSize = true;
            this.Label_QtFirst.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Label_QtFirst.Location = new System.Drawing.Point(8, 31);
            this.Label_QtFirst.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.Label_QtFirst.Name = "Label_QtFirst";
            this.Label_QtFirst.Size = new System.Drawing.Size(119, 20);
            this.Label_QtFirst.TabIndex = 0;
            this.Label_QtFirst.Text = "Label_FieldRR";
            // 
            // Button_Decrease
            // 
            this.Button_Decrease.ImageAlign = System.Drawing.ContentAlignment.TopCenter;
            this.Button_Decrease.Location = new System.Drawing.Point(263, -1);
            this.Button_Decrease.Margin = new System.Windows.Forms.Padding(0);
            this.Button_Decrease.Name = "Button_Decrease";
            this.Button_Decrease.Size = new System.Drawing.Size(34, 31);
            this.Button_Decrease.TabIndex = 2;
            this.Button_Decrease.Text = "<";
            this.Button_Decrease.UseVisualStyleBackColor = true;
            this.Button_Decrease.Click += new System.EventHandler(this.Button_Decrease_Click);
            // 
            // Button_Encrease
            // 
            this.Button_Encrease.ImageAlign = System.Drawing.ContentAlignment.TopCenter;
            this.Button_Encrease.Location = new System.Drawing.Point(384, -1);
            this.Button_Encrease.Margin = new System.Windows.Forms.Padding(0);
            this.Button_Encrease.Name = "Button_Encrease";
            this.Button_Encrease.Size = new System.Drawing.Size(34, 31);
            this.Button_Encrease.TabIndex = 3;
            this.Button_Encrease.Text = ">";
            this.Button_Encrease.UseVisualStyleBackColor = true;
            this.Button_Encrease.Click += new System.EventHandler(this.Button_Encrease_Click);
            // 
            // Label_Margin
            // 
            this.Label_Margin.AutoSize = true;
            this.Label_Margin.Location = new System.Drawing.Point(300, 3);
            this.Label_Margin.Name = "Label_Margin";
            this.Label_Margin.Size = new System.Drawing.Size(86, 20);
            this.Label_Margin.TabIndex = 4;
            this.Label_Margin.Text = "Масштаб";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(10F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(1024, 568);
            this.Controls.Add(this.Label_Margin);
            this.Controls.Add(this.Button_Encrease);
            this.Controls.Add(this.Button_Decrease);
            this.Controls.Add(this.Group_Info);
            this.Controls.Add(this.PictureBox_Field);
            this.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "Form1";
            this.Text = "Система координат";
            ((System.ComponentModel.ISupportInitialize)(this.PictureBox_Field)).EndInit();
            this.Group_Info.ResumeLayout(false);
            this.Group_Info.PerformLayout();
            this.Group_SortedPoints.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox PictureBox_Field;
        private System.Windows.Forms.GroupBox Group_Info;
        private System.Windows.Forms.Label Label_QtFirst;
        private System.Windows.Forms.Label Label_QtFourth;
        private System.Windows.Forms.Label Label_QtThird;
        private System.Windows.Forms.Label Label_QtSecond;
        private System.Windows.Forms.RichTextBox RTextBox_SortePoints;
        private System.Windows.Forms.GroupBox Group_SortedPoints;
        private System.Windows.Forms.Label Label_QtOordinate;
        private System.Windows.Forms.Label Label_QtAbsciss;
        private System.Windows.Forms.Label Label_OutputStatus;
        private System.Windows.Forms.Button Button_Decrease;
        private System.Windows.Forms.Button Button_Encrease;
        private System.Windows.Forms.Label Label_Margin;
    }
}

