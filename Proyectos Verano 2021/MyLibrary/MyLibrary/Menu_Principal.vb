Public Class Menu_Principal
    Private Sub Button3_Click(sender As Object, e As EventArgs) Handles Regresar.Click
        Me.Hide()
        Title.Show()
    End Sub

    Private Sub Button_Nuevo_Libro_Click(sender As Object, e As EventArgs) Handles Button_Nuevo_Libro.Click
        Me.Hide()
        Add_Book.Show()
    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button_Nuevo_Autor.Click
        Me.Hide()
        Add_Autor.Show()
    End Sub

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button_Nuevo_Genero.Click
        Me.Hide()
        Add_Gender.Show()
    End Sub

    Private Sub Menu_Principal_FormClosing(sender As Object, e As EventArgs) Handles MyBase.Closed
        Title.Close()
    End Sub
End Class