namespace Zhukovskiy_13_Group
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
            this.Label_Margin = new System.Windows.Forms.Label();
            this.Button_Decrease = new System.Windows.Forms.Button();
            this.Button_Encrease = new System.Windows.Forms.Button();
            this.Group_Info = new System.Windows.Forms.GroupBox();
            this.On_Parabola = new System.Windows.Forms.Label();
            this.Lower_Zone = new System.Windows.Forms.Label();
            this.Higher_Zone = new System.Windows.Forms.Label();
            this.Group_SortedPoints = new System.Windows.Forms.GroupBox();
            this.RTextBox_SortePoints = new System.Windows.Forms.RichTextBox();
            this.Label_OutputStatus = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.PictureBox_Field)).BeginInit();
            this.Group_Info.SuspendLayout();
            this.Group_SortedPoints.SuspendLayout();
            this.SuspendLayout();
            // 
            // PictureBox_Field
            // 
            this.PictureBox_Field.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.PictureBox_Field.Location = new System.Drawing.Point(3, 37);
            this.PictureBox_Field.Name = "PictureBox_Field";
            this.PictureBox_Field.Size = new System.Drawing.Size(723, 512);
            this.PictureBox_Field.TabIndex = 0;
            this.PictureBox_Field.TabStop = false;
            this.PictureBox_Field.Paint += new System.Windows.Forms.PaintEventHandler(this.PictureBox_Field_Paint);
            // 
            // Label_Margin
            // 
            this.Label_Margin.AutoSize = true;
            this.Label_Margin.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Label_Margin.Location = new System.Drawing.Point(297, 4);
            this.Label_Margin.Name = "Label_Margin";
            this.Label_Margin.Size = new System.Drawing.Size(97, 25);
            this.Label_Margin.TabIndex = 1;
            this.Label_Margin.Text = "Масштаб";
            // 
            // Button_Decrease
            // 
            this.Button_Decrease.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Button_Decrease.Location = new System.Drawing.Point(251, -1);
            this.Button_Decrease.Name = "Button_Decrease";
            this.Button_Decrease.Size = new System.Drawing.Size(40, 35);
            this.Button_Decrease.TabIndex = 2;
            this.Button_Decrease.Text = "<";
            this.Button_Decrease.UseVisualStyleBackColor = true;
            this.Button_Decrease.Click += new System.EventHandler(this.Button_Decrease_Click);
            // 
            // Button_Encrease
            // 
            this.Button_Encrease.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Button_Encrease.Location = new System.Drawing.Point(410, -1);
            this.Button_Encrease.Name = "Button_Encrease";
            this.Button_Encrease.Size = new System.Drawing.Size(38, 35);
            this.Button_Encrease.TabIndex = 3;
            this.Button_Encrease.Text = ">";
            this.Button_Encrease.UseVisualStyleBackColor = true;
            this.Button_Encrease.Click += new System.EventHandler(this.Button_Encrease_Click);
            // 
            // Group_Info
            // 
            this.Group_Info.Controls.Add(this.On_Parabola);
            this.Group_Info.Controls.Add(this.Lower_Zone);
            this.Group_Info.Controls.Add(this.Higher_Zone);
            this.Group_Info.Controls.Add(this.Group_SortedPoints);
            this.Group_Info.Controls.Add(this.Label_OutputStatus);
            this.Group_Info.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Group_Info.Location = new System.Drawing.Point(732, 9);
            this.Group_Info.Name = "Group_Info";
            this.Group_Info.Size = new System.Drawing.Size(238, 540);
            this.Group_Info.TabIndex = 4;
            this.Group_Info.TabStop = false;
            this.Group_Info.Text = "Панель информации";
            // 
            // On_Parabola
            // 
            this.On_Parabola.AutoSize = true;
            this.On_Parabola.Location = new System.Drawing.Point(6, 131);
            this.On_Parabola.Name = "On_Parabola";
            this.On_Parabola.Size = new System.Drawing.Size(98, 17);
            this.On_Parabola.TabIndex = 11;
            this.On_Parabola.Text = "На параболе:";
            // 
            // Lower_Zone
            // 
            this.Lower_Zone.AutoSize = true;
            this.Lower_Zone.Location = new System.Drawing.Point(6, 87);
            this.Lower_Zone.Name = "Lower_Zone";
            this.Lower_Zone.Size = new System.Drawing.Size(117, 17);
            this.Lower_Zone.TabIndex = 10;
            this.Lower_Zone.Text = "Ниже параболы:";
            // 
            // Higher_Zone
            // 
            this.Higher_Zone.AutoSize = true;
            this.Higher_Zone.Location = new System.Drawing.Point(6, 47);
            this.Higher_Zone.Name = "Higher_Zone";
            this.Higher_Zone.Size = new System.Drawing.Size(120, 17);
            this.Higher_Zone.TabIndex = 9;
            this.Higher_Zone.Text = "Выше параболы:";
            // 
            // Group_SortedPoints
            // 
            this.Group_SortedPoints.Controls.Add(this.RTextBox_SortePoints);
            this.Group_SortedPoints.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Group_SortedPoints.Location = new System.Drawing.Point(0, 175);
            this.Group_SortedPoints.Name = "Group_SortedPoints";
            this.Group_SortedPoints.Size = new System.Drawing.Size(238, 332);
            this.Group_SortedPoints.TabIndex = 8;
            this.Group_SortedPoints.TabStop = false;
            this.Group_SortedPoints.Text = "Отсортированные точки";
            // 
            // RTextBox_SortePoints
            // 
            this.RTextBox_SortePoints.Location = new System.Drawing.Point(6, 26);
            this.RTextBox_SortePoints.Name = "RTextBox_SortePoints";
            this.RTextBox_SortePoints.ReadOnly = true;
            this.RTextBox_SortePoints.Size = new System.Drawing.Size(226, 245);
            this.RTextBox_SortePoints.TabIndex = 4;
            this.RTextBox_SortePoints.Text = "";
            // 
            // Label_OutputStatus
            // 
            this.Label_OutputStatus.AutoSize = true;
            this.Label_OutputStatus.Location = new System.Drawing.Point(6, 510);
            this.Label_OutputStatus.Name = "Label_OutputStatus";
            this.Label_OutputStatus.Size = new System.Drawing.Size(134, 17);
            this.Label_OutputStatus.TabIndex = 0;
            this.Label_OutputStatus.Text = "Label_OutputStatus";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(982, 553);
            this.Controls.Add(this.Group_Info);
            this.Controls.Add(this.Button_Encrease);
            this.Controls.Add(this.Button_Decrease);
            this.Controls.Add(this.Label_Margin);
            this.Controls.Add(this.PictureBox_Field);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "Form1";
            this.Text = "Парабола в системе координат (вариант 1-1)";
            ((System.ComponentModel.ISupportInitialize)(this.PictureBox_Field)).EndInit();
            this.Group_Info.ResumeLayout(false);
            this.Group_Info.PerformLayout();
            this.Group_SortedPoints.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox PictureBox_Field;
        private System.Windows.Forms.Label Label_Margin;
        private System.Windows.Forms.Button Button_Decrease;
        private System.Windows.Forms.Button Button_Encrease;
        private System.Windows.Forms.GroupBox Group_Info;
        private System.Windows.Forms.Label Label_OutputStatus;
        private System.Windows.Forms.GroupBox Group_SortedPoints;
        private System.Windows.Forms.RichTextBox RTextBox_SortePoints;
        private System.Windows.Forms.Label On_Parabola;
        private System.Windows.Forms.Label Lower_Zone;
        private System.Windows.Forms.Label Higher_Zone;
    }
}

