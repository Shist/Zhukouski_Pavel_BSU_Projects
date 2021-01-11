namespace events
{
    partial class EventsForm
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
            this.btStartStop = new System.Windows.Forms.Button();
            this.tbResult = new System.Windows.Forms.TextBox();
            this.tbTime = new System.Windows.Forms.TextBox();
            this.btShootStop = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btStartStop
            // 
            this.btStartStop.Location = new System.Drawing.Point(184, 31);
            this.btStartStop.Name = "btStartStop";
            this.btStartStop.Size = new System.Drawing.Size(75, 23);
            this.btStartStop.TabIndex = 0;
            this.btStartStop.Text = "Stop";
            this.btStartStop.UseVisualStyleBackColor = true;
            this.btStartStop.Click += new System.EventHandler(this.btStartStop_Click);
            // 
            // tbResult
            // 
            this.tbResult.Location = new System.Drawing.Point(59, 92);
            this.tbResult.Multiline = true;
            this.tbResult.Name = "tbResult";
            this.tbResult.Size = new System.Drawing.Size(464, 137);
            this.tbResult.TabIndex = 1;
            // 
            // tbTime
            // 
            this.tbTime.Location = new System.Drawing.Point(59, 31);
            this.tbTime.Name = "tbTime";
            this.tbTime.Size = new System.Drawing.Size(100, 22);
            this.tbTime.TabIndex = 2;
            this.tbTime.Visible = false;
            // 
            // btShootStop
            // 
            this.btShootStop.Location = new System.Drawing.Point(1299, 30);
            this.btShootStop.Name = "btShootStop";
            this.btShootStop.Size = new System.Drawing.Size(75, 23);
            this.btShootStop.TabIndex = 3;
            this.btShootStop.Text = "Stop";
            this.btShootStop.UseVisualStyleBackColor = true;
            this.btShootStop.Click += new System.EventHandler(this.btShootStop_Click);
            // 
            // EventsForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1475, 713);
            this.Controls.Add(this.btShootStop);
            this.Controls.Add(this.tbTime);
            this.Controls.Add(this.tbResult);
            this.Controls.Add(this.btStartStop);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "EventsForm";
            this.Text = "Треды";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.EventsForm_FormClosing);
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.MainPaint);
            this.Resize += new System.EventHandler(this.MainResize);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btStartStop;
        private System.Windows.Forms.TextBox tbResult;
        private System.Windows.Forms.TextBox tbTime;
        private System.Windows.Forms.Button btShootStop;
    }
}

