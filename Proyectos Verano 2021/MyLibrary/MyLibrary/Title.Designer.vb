<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()>
Partial Class Title
    Inherits System.Windows.Forms.Form

    'Form reemplaza a Dispose para limpiar la lista de componentes.
    <System.Diagnostics.DebuggerNonUserCode()>
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Requerido por el Diseñador de Windows Forms
    Private components As System.ComponentModel.IContainer

    'NOTA: el Diseñador de Windows Forms necesita el siguiente procedimiento
    'Se puede modificar usando el Diseñador de Windows Forms.  
    'No lo modifique con el editor de código.
    <System.Diagnostics.DebuggerStepThrough()>
    Private Sub InitializeComponent()
        Me.Button1 = New System.Windows.Forms.Button()
        Me.Button_Iniciar = New System.Windows.Forms.Button()
        Me.SuspendLayout()
        '
        'Button1
        '
        Me.Button1.BackColor = System.Drawing.Color.Transparent
        Me.Button1.Location = New System.Drawing.Point(12, 57)
        Me.Button1.Name = "Button1"
        Me.Button1.Size = New System.Drawing.Size(1294, 526)
        Me.Button1.TabIndex = 0
        Me.Button1.UseVisualStyleBackColor = False
        '
        'Button_Iniciar
        '
        Me.Button_Iniciar.BackColor = System.Drawing.Color.MistyRose
        Me.Button_Iniciar.FlatAppearance.BorderColor = System.Drawing.Color.White
        Me.Button_Iniciar.FlatAppearance.BorderSize = 0
        Me.Button_Iniciar.FlatStyle = System.Windows.Forms.FlatStyle.Flat
        Me.Button_Iniciar.Font = New System.Drawing.Font("Segoe UI", 18.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Button_Iniciar.ForeColor = System.Drawing.Color.DarkSlateGray
        Me.Button_Iniciar.Location = New System.Drawing.Point(94, 407)
        Me.Button_Iniciar.Name = "Button_Iniciar"
        Me.Button_Iniciar.Size = New System.Drawing.Size(129, 56)
        Me.Button_Iniciar.TabIndex = 0
        Me.Button_Iniciar.Text = "Iniciar"
        Me.Button_Iniciar.UseVisualStyleBackColor = False
        '
        'Title
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(13.0!, 29.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.BackColor = System.Drawing.SystemColors.ActiveCaptionText
        Me.BackgroundImage = Global.MyLibrary.My.Resources.Resources.Background_Title
        Me.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center
        Me.ClientSize = New System.Drawing.Size(802, 511)
        Me.Controls.Add(Me.Button_Iniciar)
        Me.DoubleBuffered = True
        Me.Font = New System.Drawing.Font("Cascadia Code SemiBold", 11.0!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.Margin = New System.Windows.Forms.Padding(4)
        Me.Name = "Title"
        Me.Text = "MyLibrary"
        Me.ResumeLayout(False)

    End Sub

    Friend WithEvents Button1 As Button
    Friend WithEvents Button_Iniciar As Button
End Class
