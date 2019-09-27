<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form reemplaza a Dispose para limpiar la lista de componentes.
    <System.Diagnostics.DebuggerNonUserCode()> _
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
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.Suma = New System.Windows.Forms.RadioButton()
        Me.Resta = New System.Windows.Forms.RadioButton()
        Me.Division = New System.Windows.Forms.RadioButton()
        Me.Multiplicacion = New System.Windows.Forms.RadioButton()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.B = New System.Windows.Forms.TextBox()
        Me.A = New System.Windows.Forms.TextBox()
        Me.C = New System.Windows.Forms.TextBox()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.Button1 = New System.Windows.Forms.Button()
        Me.SuspendLayout()
        '
        'Suma
        '
        Me.Suma.AutoSize = True
        Me.Suma.Location = New System.Drawing.Point(12, 92)
        Me.Suma.Name = "Suma"
        Me.Suma.Size = New System.Drawing.Size(52, 17)
        Me.Suma.TabIndex = 0
        Me.Suma.TabStop = True
        Me.Suma.Text = "Suma"
        Me.Suma.UseVisualStyleBackColor = True
        '
        'Resta
        '
        Me.Resta.AutoSize = True
        Me.Resta.Location = New System.Drawing.Point(87, 92)
        Me.Resta.Name = "Resta"
        Me.Resta.Size = New System.Drawing.Size(53, 17)
        Me.Resta.TabIndex = 1
        Me.Resta.TabStop = True
        Me.Resta.Text = "Resta"
        Me.Resta.UseVisualStyleBackColor = True
        '
        'Division
        '
        Me.Division.AutoSize = True
        Me.Division.Location = New System.Drawing.Point(170, 92)
        Me.Division.Name = "Division"
        Me.Division.Size = New System.Drawing.Size(62, 17)
        Me.Division.TabIndex = 2
        Me.Division.TabStop = True
        Me.Division.Text = "División"
        Me.Division.UseVisualStyleBackColor = True
        '
        'Multiplicacion
        '
        Me.Multiplicacion.AutoSize = True
        Me.Multiplicacion.Location = New System.Drawing.Point(263, 92)
        Me.Multiplicacion.Name = "Multiplicacion"
        Me.Multiplicacion.Size = New System.Drawing.Size(89, 17)
        Me.Multiplicacion.TabIndex = 3
        Me.Multiplicacion.TabStop = True
        Me.Multiplicacion.Text = "Multiplicación"
        Me.Multiplicacion.UseVisualStyleBackColor = True
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(68, 22)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(40, 13)
        Me.Label1.TabIndex = 4
        Me.Label1.Text = "Valor 1"
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(276, 22)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(40, 13)
        Me.Label2.TabIndex = 5
        Me.Label2.Text = "Valor 2"
        '
        'B
        '
        Me.B.Location = New System.Drawing.Point(242, 47)
        Me.B.Name = "B"
        Me.B.Size = New System.Drawing.Size(100, 20)
        Me.B.TabIndex = 6
        '
        'A
        '
        Me.A.Location = New System.Drawing.Point(40, 47)
        Me.A.Name = "A"
        Me.A.Size = New System.Drawing.Size(100, 20)
        Me.A.TabIndex = 7
        '
        'C
        '
        Me.C.Location = New System.Drawing.Point(146, 130)
        Me.C.Name = "C"
        Me.C.Size = New System.Drawing.Size(100, 20)
        Me.C.TabIndex = 8
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Location = New System.Drawing.Point(109, 133)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(31, 13)
        Me.Label3.TabIndex = 9
        Me.Label3.Text = "Total"
        '
        'Button1
        '
        Me.Button1.Location = New System.Drawing.Point(157, 167)
        Me.Button1.Name = "Button1"
        Me.Button1.Size = New System.Drawing.Size(75, 23)
        Me.Button1.TabIndex = 10
        Me.Button1.Text = "Resolver"
        Me.Button1.UseVisualStyleBackColor = True
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(396, 242)
        Me.Controls.Add(Me.Button1)
        Me.Controls.Add(Me.Label3)
        Me.Controls.Add(Me.C)
        Me.Controls.Add(Me.A)
        Me.Controls.Add(Me.B)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.Multiplicacion)
        Me.Controls.Add(Me.Division)
        Me.Controls.Add(Me.Resta)
        Me.Controls.Add(Me.Suma)
        Me.Name = "Form1"
        Me.Text = "Form1"
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub

    Friend WithEvents Suma As RadioButton
    Friend WithEvents Resta As RadioButton
    Friend WithEvents Division As RadioButton
    Friend WithEvents Multiplicacion As RadioButton
    Friend WithEvents Label1 As Label
    Friend WithEvents Label2 As Label
    Friend WithEvents B As TextBox
    Friend WithEvents A As TextBox
    Friend WithEvents C As TextBox
    Friend WithEvents Label3 As Label
    Friend WithEvents Button1 As Button
End Class
