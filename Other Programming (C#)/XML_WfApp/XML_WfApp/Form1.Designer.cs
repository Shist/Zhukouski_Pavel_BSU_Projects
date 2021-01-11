namespace XML_WfApp
{
    partial class fXML_Reader
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing) {
            if (disposing && (components != null)) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent() {
            this.rtbTextInfoOut = new System.Windows.Forms.RichTextBox();
            this.btnXMLReader = new System.Windows.Forms.Button();
            this.btnClearRtbTextInfoOut = new System.Windows.Forms.Button();
            this.btnJSONReader = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // rtbTextInfoOut
            // 
            this.rtbTextInfoOut.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.rtbTextInfoOut.Font = new System.Drawing.Font("Verdana", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.rtbTextInfoOut.Location = new System.Drawing.Point(178, 11);
            this.rtbTextInfoOut.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.rtbTextInfoOut.Name = "rtbTextInfoOut";
            this.rtbTextInfoOut.ReadOnly = true;
            this.rtbTextInfoOut.Size = new System.Drawing.Size(701, 615);
            this.rtbTextInfoOut.TabIndex = 0;
            this.rtbTextInfoOut.Text = "";
            // 
            // btnXMLReader
            // 
            this.btnXMLReader.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnXMLReader.Font = new System.Drawing.Font("Verdana", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.btnXMLReader.Location = new System.Drawing.Point(11, 31);
            this.btnXMLReader.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.btnXMLReader.Name = "btnXMLReader";
            this.btnXMLReader.Size = new System.Drawing.Size(150, 73);
            this.btnXMLReader.TabIndex = 1;
            this.btnXMLReader.Text = "XML-file";
            this.btnXMLReader.UseVisualStyleBackColor = true;
            this.btnXMLReader.Click += new System.EventHandler(this.btnXMLReader_Click);
            // 
            // btnClearRtbTextInfoOut
            // 
            this.btnClearRtbTextInfoOut.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnClearRtbTextInfoOut.Font = new System.Drawing.Font("Verdana", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.btnClearRtbTextInfoOut.Location = new System.Drawing.Point(11, 223);
            this.btnClearRtbTextInfoOut.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.btnClearRtbTextInfoOut.Name = "btnClearRtbTextInfoOut";
            this.btnClearRtbTextInfoOut.Size = new System.Drawing.Size(150, 73);
            this.btnClearRtbTextInfoOut.TabIndex = 2;
            this.btnClearRtbTextInfoOut.Text = "Clear";
            this.btnClearRtbTextInfoOut.UseVisualStyleBackColor = true;
            this.btnClearRtbTextInfoOut.Click += new System.EventHandler(this.btnClearRtbTextInfoOut_Click);
            // 
            // btnJSONReader
            // 
            this.btnJSONReader.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnJSONReader.Font = new System.Drawing.Font("Verdana", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.btnJSONReader.Location = new System.Drawing.Point(11, 124);
            this.btnJSONReader.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.btnJSONReader.Name = "btnJSONReader";
            this.btnJSONReader.Size = new System.Drawing.Size(150, 73);
            this.btnJSONReader.TabIndex = 3;
            this.btnJSONReader.Text = "JSON-file";
            this.btnJSONReader.UseVisualStyleBackColor = true;
            this.btnJSONReader.Click += new System.EventHandler(this.btnJSONReader_Click);
            // 
            // fXML_Reader
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(890, 609);
            this.Controls.Add(this.btnJSONReader);
            this.Controls.Add(this.btnClearRtbTextInfoOut);
            this.Controls.Add(this.btnXMLReader);
            this.Controls.Add(this.rtbTextInfoOut);
            this.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.MinimumSize = new System.Drawing.Size(906, 597);
            this.Name = "fXML_Reader";
            this.Text = "XML Reader";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.RichTextBox rtbTextInfoOut;
        private System.Windows.Forms.Button btnXMLReader;
        private System.Windows.Forms.Button btnClearRtbTextInfoOut;
        private System.Windows.Forms.Button btnJSONReader;
    }
}

