namespace _1112010_FOL
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.tb_add_KB = new System.Windows.Forms.TextBox();
            this.bt_add_KB = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.tb_add_query = new System.Windows.Forms.TextBox();
            this.bt_add_query = new System.Windows.Forms.Button();
            this.lb_KB = new System.Windows.Forms.ListBox();
            this.label3 = new System.Windows.Forms.Label();
            this.bt_del_KB = new System.Windows.Forms.Button();
            this.bt_del_query = new System.Windows.Forms.Button();
            this.lb_query = new System.Windows.Forms.ListBox();
            this.label4 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // tb_add_KB
            // 
            this.tb_add_KB.Location = new System.Drawing.Point(12, 25);
            this.tb_add_KB.Multiline = true;
            this.tb_add_KB.Name = "tb_add_KB";
            this.tb_add_KB.Size = new System.Drawing.Size(222, 95);
            this.tb_add_KB.TabIndex = 0;
            this.tb_add_KB.TextChanged += new System.EventHandler(this.tb_add_KB_TextChanged);
            // 
            // bt_add_KB
            // 
            this.bt_add_KB.Location = new System.Drawing.Point(240, 47);
            this.bt_add_KB.Name = "bt_add_KB";
            this.bt_add_KB.Size = new System.Drawing.Size(75, 23);
            this.bt_add_KB.TabIndex = 1;
            this.bt_add_KB.Text = "Add";
            this.bt_add_KB.UseVisualStyleBackColor = true;
            this.bt_add_KB.Click += new System.EventHandler(this.bt_add_KB_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(9, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(46, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "New KB";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(9, 125);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(60, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "New Query";
            // 
            // tb_add_query
            // 
            this.tb_add_query.Location = new System.Drawing.Point(12, 141);
            this.tb_add_query.Multiline = true;
            this.tb_add_query.Name = "tb_add_query";
            this.tb_add_query.Size = new System.Drawing.Size(222, 95);
            this.tb_add_query.TabIndex = 4;
            this.tb_add_query.TextChanged += new System.EventHandler(this.tb_add_query_TextChanged);
            // 
            // bt_add_query
            // 
            this.bt_add_query.Location = new System.Drawing.Point(240, 163);
            this.bt_add_query.Name = "bt_add_query";
            this.bt_add_query.Size = new System.Drawing.Size(75, 23);
            this.bt_add_query.TabIndex = 5;
            this.bt_add_query.Text = "Add";
            this.bt_add_query.UseVisualStyleBackColor = true;
            this.bt_add_query.Click += new System.EventHandler(this.bt_add_query_Click);
            // 
            // lb_KB
            // 
            this.lb_KB.FormattingEnabled = true;
            this.lb_KB.Location = new System.Drawing.Point(321, 25);
            this.lb_KB.Name = "lb_KB";
            this.lb_KB.Size = new System.Drawing.Size(291, 95);
            this.lb_KB.TabIndex = 7;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(318, 9);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(21, 13);
            this.label3.TabIndex = 8;
            this.label3.Text = "KB";
            // 
            // bt_del_KB
            // 
            this.bt_del_KB.Location = new System.Drawing.Point(240, 76);
            this.bt_del_KB.Name = "bt_del_KB";
            this.bt_del_KB.Size = new System.Drawing.Size(75, 23);
            this.bt_del_KB.TabIndex = 9;
            this.bt_del_KB.Text = "Delete";
            this.bt_del_KB.UseVisualStyleBackColor = true;
            this.bt_del_KB.Click += new System.EventHandler(this.bt_del_KB_Click);
            // 
            // bt_del_query
            // 
            this.bt_del_query.Location = new System.Drawing.Point(240, 192);
            this.bt_del_query.Name = "bt_del_query";
            this.bt_del_query.Size = new System.Drawing.Size(75, 23);
            this.bt_del_query.TabIndex = 10;
            this.bt_del_query.Text = "Delete";
            this.bt_del_query.UseVisualStyleBackColor = true;
            this.bt_del_query.Click += new System.EventHandler(this.bt_del_query_Click);
            // 
            // lb_query
            // 
            this.lb_query.FormattingEnabled = true;
            this.lb_query.Location = new System.Drawing.Point(321, 141);
            this.lb_query.Name = "lb_query";
            this.lb_query.Size = new System.Drawing.Size(291, 95);
            this.lb_query.TabIndex = 11;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(318, 125);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(35, 13);
            this.label4.TabIndex = 12;
            this.label4.Text = "Query";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(624, 322);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.lb_query);
            this.Controls.Add(this.bt_del_query);
            this.Controls.Add(this.bt_del_KB);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.lb_KB);
            this.Controls.Add(this.bt_add_query);
            this.Controls.Add(this.tb_add_query);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.bt_add_KB);
            this.Controls.Add(this.tb_add_KB);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox tb_add_KB;
        private System.Windows.Forms.Button bt_add_KB;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox tb_add_query;
        private System.Windows.Forms.Button bt_add_query;
        private System.Windows.Forms.ListBox lb_KB;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button bt_del_KB;
        private System.Windows.Forms.Button bt_del_query;
        private System.Windows.Forms.ListBox lb_query;
        private System.Windows.Forms.Label label4;
    }
}

