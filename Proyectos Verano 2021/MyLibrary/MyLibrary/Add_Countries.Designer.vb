<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Add_Countries
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
        Me.Regresar = New System.Windows.Forms.Button()
        Me.SuspendLayout()
        '
        'Regresar
        '
        Me.Regresar.BackColor = System.Drawing.Color.Moccasin
        Me.Regresar.FlatAppearance.BorderColor = System.Drawing.Color.White
        Me.Regresar.FlatAppearance.BorderSize = 0
        Me.Regresar.FlatStyle = System.Windows.Forms.FlatStyle.Flat
        Me.Regresar.Font = New System.Drawing.Font("Segoe UI", 11.0!)
        Me.Regresar.ForeColor = System.Drawing.SystemColors.ActiveCaptionText
        Me.Regresar.Location = New System.Drawing.Point(317, 229)
        Me.Regresar.Name = "Regresar"
        Me.Regresar.Size = New System.Drawing.Size(168, 52)
        Me.Regresar.TabIndex = 7
        Me.Regresar.Text = "Regresar"
        Me.Regresar.UseVisualStyleBackColor = False
        '
        'Add_Countries
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(13.0!, 29.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.BackColor = System.Drawing.Color.CornflowerBlue
        Me.ClientSize = New System.Drawing.Size(802, 511)
        Me.Controls.Add(Me.Regresar)
        Me.Font = New System.Drawing.Font("Cascadia Code SemiBold", 11.0!, System.Drawing.FontStyle.Bold)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.Margin = New System.Windows.Forms.Padding(4, 4, 4, 4)
        Me.Name = "Add_Countries"
        Me.Text = "Add_Countries"
        Me.ResumeLayout(False)

    End Sub

    Friend WithEvents Regresar As Button
End Class
