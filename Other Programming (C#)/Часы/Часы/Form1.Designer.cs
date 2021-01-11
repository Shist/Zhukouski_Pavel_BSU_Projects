namespace Часы
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
            this.components = new System.ComponentModel.Container();
            this.Clock = new System.Windows.Forms.Timer(this.components);
            this.timelbl = new System.Windows.Forms.Label();
            this.datelbl = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // Clock
            // 
            this.Clock.Enabled = true;
            this.Clock.Tick += new System.EventHandler(this.Clock_Tick);
            // 
            // timelbl
            // 
            this.timelbl.AutoSize = true;
            this.timelbl.Font = new System.Drawing.Font("Arial Narrow", 72F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.timelbl.Location = new System.Drawing.Point(12, 9);
            this.timelbl.Name = "timelbl";
            this.timelbl.Size = new System.Drawing.Size(322, 137);
            this.timelbl.TabIndex = 0;
            this.timelbl.Text = "label1";
            this.timelbl.Click += new System.EventHandler(this.timelbl_Click);
            // 
            // datelbl
            // 
            this.datelbl.AutoSize = true;
            this.datelbl.Font = new System.Drawing.Font("Arial Narrow", 72F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.datelbl.Location = new System.Drawing.Point(12, 146);
            this.datelbl.Name = "datelbl";
            this.datelbl.Size = new System.Drawing.Size(322, 137);
            this.datelbl.TabIndex = 1;
            this.datelbl.Text = "label1";
            this.datelbl.Click += new System.EventHandler(this.datelbl_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1380, 362);
            this.Controls.Add(this.datelbl);
            this.Controls.Add(this.timelbl);
            this.Name = "Form1";
            this.Text = "В Р Е М Я";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Timer Clock;
        private System.Windows.Forms.Label timelbl;
        private System.Windows.Forms.Label datelbl;
    }
}

