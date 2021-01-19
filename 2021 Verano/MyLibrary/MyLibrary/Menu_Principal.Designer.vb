<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Menu_Principal
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
        Me.components = New System.ComponentModel.Container()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.Button_Nuevo_Libro = New System.Windows.Forms.Button()
        Me.Button_Nuevo_Autor = New System.Windows.Forms.Button()
        Me.Button_Nuevo_Genero = New System.Windows.Forms.Button()
        Me.Regresar = New System.Windows.Forms.Button()
        Me.Button_Nuevo_Pais = New System.Windows.Forms.Button()
        Me.Button_Nueva_Editorial = New System.Windows.Forms.Button()
        Me.MyLibraryDataSet = New MyLibrary.MyLibraryDataSet()
        Me.MyLibraryDataSetBindingSource = New System.Windows.Forms.BindingSource(Me.components)
        Me.LibroBindingSource = New System.Windows.Forms.BindingSource(Me.components)
        Me.LibroTableAdapter = New MyLibrary.MyLibraryDataSetTableAdapters.LibroTableAdapter()
        Me.AutorBindingSource = New System.Windows.Forms.BindingSource(Me.components)
        Me.AutorTableAdapter = New MyLibrary.MyLibraryDataSetTableAdapters.AutorTableAdapter()
        Me.MyLibraryDataSetBindingSource1 = New System.Windows.Forms.BindingSource(Me.components)
        Me.MyLibraryDataSet1 = New MyLibrary.MyLibraryDataSet1()
        Me.LibroBindingSource1 = New System.Windows.Forms.BindingSource(Me.components)
        Me.LibroTableAdapter1 = New MyLibrary.MyLibraryDataSet1TableAdapters.LibroTableAdapter()
        CType(Me.MyLibraryDataSet, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.MyLibraryDataSetBindingSource, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.LibroBindingSource, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.AutorBindingSource, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.MyLibraryDataSetBindingSource1, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.MyLibraryDataSet1, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.LibroBindingSource1, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(12, 9)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(286, 29)
        Me.Label1.TabIndex = 0
        Me.Label1.Text = "Listado de mis libros"
        '
        'Button_Nuevo_Libro
        '
        Me.Button_Nuevo_Libro.BackColor = System.Drawing.Color.Moccasin
        Me.Button_Nuevo_Libro.FlatAppearance.BorderColor = System.Drawing.Color.White
        Me.Button_Nuevo_Libro.FlatAppearance.BorderSize = 0
        Me.Button_Nuevo_Libro.FlatStyle = System.Windows.Forms.FlatStyle.Flat
        Me.Button_Nuevo_Libro.Font = New System.Drawing.Font("Segoe UI", 11.0!)
        Me.Button_Nuevo_Libro.ForeColor = System.Drawing.SystemColors.ActiveCaptionText
        Me.Button_Nuevo_Libro.Location = New System.Drawing.Point(12, 60)
        Me.Button_Nuevo_Libro.Name = "Button_Nuevo_Libro"
        Me.Button_Nuevo_Libro.Size = New System.Drawing.Size(168, 55)
        Me.Button_Nuevo_Libro.TabIndex = 2
        Me.Button_Nuevo_Libro.Text = "Nuevo Libro"
        Me.Button_Nuevo_Libro.UseVisualStyleBackColor = False
        '
        'Button_Nuevo_Autor
        '
        Me.Button_Nuevo_Autor.BackColor = System.Drawing.Color.Moccasin
        Me.Button_Nuevo_Autor.FlatAppearance.BorderColor = System.Drawing.Color.White
        Me.Button_Nuevo_Autor.FlatAppearance.BorderSize = 0
        Me.Button_Nuevo_Autor.FlatStyle = System.Windows.Forms.FlatStyle.Flat
        Me.Button_Nuevo_Autor.Font = New System.Drawing.Font("Segoe UI", 11.0!)
        Me.Button_Nuevo_Autor.ForeColor = System.Drawing.SystemColors.ActiveCaptionText
        Me.Button_Nuevo_Autor.Location = New System.Drawing.Point(12, 140)
        Me.Button_Nuevo_Autor.Name = "Button_Nuevo_Autor"
        Me.Button_Nuevo_Autor.Size = New System.Drawing.Size(168, 53)
        Me.Button_Nuevo_Autor.TabIndex = 3
        Me.Button_Nuevo_Autor.Text = "Nuevo Autor"
        Me.Button_Nuevo_Autor.UseVisualStyleBackColor = False
        '
        'Button_Nuevo_Genero
        '
        Me.Button_Nuevo_Genero.BackColor = System.Drawing.Color.Moccasin
        Me.Button_Nuevo_Genero.FlatAppearance.BorderColor = System.Drawing.Color.White
        Me.Button_Nuevo_Genero.FlatAppearance.BorderSize = 0
        Me.Button_Nuevo_Genero.FlatStyle = System.Windows.Forms.FlatStyle.Flat
        Me.Button_Nuevo_Genero.Font = New System.Drawing.Font("Segoe UI", 11.0!)
        Me.Button_Nuevo_Genero.ForeColor = System.Drawing.SystemColors.ActiveCaptionText
        Me.Button_Nuevo_Genero.Location = New System.Drawing.Point(12, 213)
        Me.Button_Nuevo_Genero.Name = "Button_Nuevo_Genero"
        Me.Button_Nuevo_Genero.Size = New System.Drawing.Size(168, 52)
        Me.Button_Nuevo_Genero.TabIndex = 4
        Me.Button_Nuevo_Genero.Text = "Nuevo Genero"
        Me.Button_Nuevo_Genero.UseVisualStyleBackColor = False
        '
        'Regresar
        '
        Me.Regresar.BackColor = System.Drawing.Color.Moccasin
        Me.Regresar.FlatAppearance.BorderColor = System.Drawing.Color.White
        Me.Regresar.FlatAppearance.BorderSize = 0
        Me.Regresar.FlatStyle = System.Windows.Forms.FlatStyle.Flat
        Me.Regresar.Font = New System.Drawing.Font("Segoe UI", 11.0!)
        Me.Regresar.ForeColor = System.Drawing.SystemColors.ActiveCaptionText
        Me.Regresar.Location = New System.Drawing.Point(12, 436)
        Me.Regresar.Name = "Regresar"
        Me.Regresar.Size = New System.Drawing.Size(168, 52)
        Me.Regresar.TabIndex = 5
        Me.Regresar.Text = "Regresar"
        Me.Regresar.UseVisualStyleBackColor = False
        '
        'Button_Nuevo_Pais
        '
        Me.Button_Nuevo_Pais.BackColor = System.Drawing.Color.Moccasin
        Me.Button_Nuevo_Pais.FlatAppearance.BorderColor = System.Drawing.Color.White
        Me.Button_Nuevo_Pais.FlatAppearance.BorderSize = 0
        Me.Button_Nuevo_Pais.FlatStyle = System.Windows.Forms.FlatStyle.Flat
        Me.Button_Nuevo_Pais.Font = New System.Drawing.Font("Segoe UI", 11.0!)
        Me.Button_Nuevo_Pais.ForeColor = System.Drawing.SystemColors.ActiveCaptionText
        Me.Button_Nuevo_Pais.Location = New System.Drawing.Point(12, 288)
        Me.Button_Nuevo_Pais.Name = "Button_Nuevo_Pais"
        Me.Button_Nuevo_Pais.Size = New System.Drawing.Size(168, 52)
        Me.Button_Nuevo_Pais.TabIndex = 6
        Me.Button_Nuevo_Pais.Text = "Nuevo Pais"
        Me.Button_Nuevo_Pais.UseVisualStyleBackColor = False
        '
        'Button_Nueva_Editorial
        '
        Me.Button_Nueva_Editorial.BackColor = System.Drawing.Color.Moccasin
        Me.Button_Nueva_Editorial.FlatAppearance.BorderColor = System.Drawing.Color.White
        Me.Button_Nueva_Editorial.FlatAppearance.BorderSize = 0
        Me.Button_Nueva_Editorial.FlatStyle = System.Windows.Forms.FlatStyle.Flat
        Me.Button_Nueva_Editorial.Font = New System.Drawing.Font("Segoe UI", 11.0!)
        Me.Button_Nueva_Editorial.ForeColor = System.Drawing.SystemColors.ActiveCaptionText
        Me.Button_Nueva_Editorial.Location = New System.Drawing.Point(12, 365)
        Me.Button_Nueva_Editorial.Name = "Button_Nueva_Editorial"
        Me.Button_Nueva_Editorial.Size = New System.Drawing.Size(168, 52)
        Me.Button_Nueva_Editorial.TabIndex = 7
        Me.Button_Nueva_Editorial.Text = "Nueva Editorial"
        Me.Button_Nueva_Editorial.UseVisualStyleBackColor = False
        '
        'MyLibraryDataSet
        '
        Me.MyLibraryDataSet.DataSetName = "MyLibraryDataSet"
        Me.MyLibraryDataSet.SchemaSerializationMode = System.Data.SchemaSerializationMode.IncludeSchema
        '
        'MyLibraryDataSetBindingSource
        '
        Me.MyLibraryDataSetBindingSource.DataSource = Me.MyLibraryDataSet
        Me.MyLibraryDataSetBindingSource.Position = 0
        '
        'LibroBindingSource
        '
        Me.LibroBindingSource.DataMember = "Libro"
        Me.LibroBindingSource.DataSource = Me.MyLibraryDataSetBindingSource
        '
        'LibroTableAdapter
        '
        Me.LibroTableAdapter.ClearBeforeFill = True
        '
        'AutorBindingSource
        '
        Me.AutorBindingSource.DataMember = "Autor"
        Me.AutorBindingSource.DataSource = Me.MyLibraryDataSetBindingSource
        '
        'AutorTableAdapter
        '
        Me.AutorTableAdapter.ClearBeforeFill = True
        '
        'MyLibraryDataSetBindingSource1
        '
        Me.MyLibraryDataSetBindingSource1.DataSource = Me.MyLibraryDataSet
        Me.MyLibraryDataSetBindingSource1.Position = 0
        '
        'MyLibraryDataSet1
        '
        Me.MyLibraryDataSet1.DataSetName = "MyLibraryDataSet1"
        Me.MyLibraryDataSet1.SchemaSerializationMode = System.Data.SchemaSerializationMode.IncludeSchema
        '
        'LibroBindingSource1
        '
        Me.LibroBindingSource1.DataMember = "Libro"
        Me.LibroBindingSource1.DataSource = Me.MyLibraryDataSet1
        '
        'LibroTableAdapter1
        '
        Me.LibroTableAdapter1.ClearBeforeFill = True
        '
        'Menu_Principal
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(13.0!, 29.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.BackColor = System.Drawing.Color.CornflowerBlue
        Me.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center
        Me.ClientSize = New System.Drawing.Size(802, 511)
        Me.Controls.Add(Me.Button_Nueva_Editorial)
        Me.Controls.Add(Me.Button_Nuevo_Pais)
        Me.Controls.Add(Me.Regresar)
        Me.Controls.Add(Me.Button_Nuevo_Genero)
        Me.Controls.Add(Me.Button_Nuevo_Autor)
        Me.Controls.Add(Me.Button_Nuevo_Libro)
        Me.Controls.Add(Me.Label1)
        Me.Font = New System.Drawing.Font("Cascadia Code SemiBold", 11.0!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.Margin = New System.Windows.Forms.Padding(4)
        Me.Name = "Menu_Principal"
        Me.Text = "MyLibrary"
        CType(Me.MyLibraryDataSet, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.MyLibraryDataSetBindingSource, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.LibroBindingSource, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.AutorBindingSource, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.MyLibraryDataSetBindingSource1, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.MyLibraryDataSet1, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.LibroBindingSource1, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub

    Friend WithEvents Label1 As Label
    Friend WithEvents Button_Nuevo_Libro As Button
    Friend WithEvents Button_Nuevo_Autor As Button
    Friend WithEvents Button_Nuevo_Genero As Button
    Friend WithEvents Regresar As Button
    Friend WithEvents Button_Nuevo_Pais As Button
    Friend WithEvents Button_Nueva_Editorial As Button
    Friend WithEvents MyLibraryDataSetBindingSource As BindingSource
    Friend WithEvents MyLibraryDataSet As MyLibraryDataSet
    Friend WithEvents LibroBindingSource As BindingSource
    Friend WithEvents LibroTableAdapter As MyLibraryDataSetTableAdapters.LibroTableAdapter
    Friend WithEvents AutorBindingSource As BindingSource
    Friend WithEvents AutorTableAdapter As MyLibraryDataSetTableAdapters.AutorTableAdapter
    Friend WithEvents MyLibraryDataSetBindingSource1 As BindingSource
    Friend WithEvents MyLibraryDataSet1 As MyLibraryDataSet1
    Friend WithEvents LibroBindingSource1 As BindingSource
    Friend WithEvents LibroTableAdapter1 As MyLibraryDataSet1TableAdapters.LibroTableAdapter
End Class
