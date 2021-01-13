Public Class Menu_Principal
    Private Sub Button3_Click(sender As Object, e As EventArgs) Handles Regresar.Click
        Me.Hide()
        Title.Show()
    End Sub

    Private Sub Button_Nuevo_Libro_Click(sender As Object, e As EventArgs) Handles Button_Nuevo_Libro.Click
        Me.Hide()
        Add_Book.Show()
    End Sub

    Private Sub Button_Nuevo_Autor_Click(sender As Object, e As EventArgs) Handles Button_Nuevo_Autor.Click
        Me.Hide()
        Add_Autor.Show()
    End Sub

    Private Sub Button_Nuevo_Genero_Click(sender As Object, e As EventArgs) Handles Button_Nuevo_Genero.Click
        Me.Hide()
        Add_Gender.Show()
    End Sub

    Private Sub Button_Nuevo_Pais_Click(sender As Object, e As EventArgs) Handles Button_Nuevo_Pais.Click
        Me.Hide()
        Add_Countries.Show()
    End Sub

    Private Sub Button_Nueva_Editorial_Click(sender As Object, e As EventArgs) Handles Button_Nueva_Editorial.Click
        Me.Hide()
        Add_Editorial.Show()
    End Sub

    Private Sub Menu_Principal_FormClosing(sender As Object, e As EventArgs) Handles MyBase.Closed
        Title.Close()
    End Sub

    Private Sub Menu_Principal_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        'TODO: esta línea de código carga datos en la tabla 'MyLibraryDataSet1.Libro' Puede moverla o quitarla según sea necesario.
        Me.LibroTableAdapter1.Fill(Me.MyLibraryDataSet1.Libro)
        'TODO: esta línea de código carga datos en la tabla 'MyLibraryDataSet.Autor' Puede moverla o quitarla según sea necesario.
        Me.AutorTableAdapter.Fill(Me.MyLibraryDataSet.Autor)
        'TODO: esta línea de código carga datos en la tabla 'MyLibraryDataSet.Libro' Puede moverla o quitarla según sea necesario.
        Me.LibroTableAdapter.Fill(Me.MyLibraryDataSet.Libro)

    End Sub
End Class