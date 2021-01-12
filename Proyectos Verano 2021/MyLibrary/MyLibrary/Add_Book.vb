Public Class Add_Book
    Private Sub Button3_Click(sender As Object, e As EventArgs) Handles Regresar.Click
        Me.Hide()
        Menu_Principal.Show()
    End Sub

    Private Sub Add_Book_FormClosing(sender As Object, e As EventArgs) Handles MyBase.Closed
        Me.Hide()
        Menu_Principal.Show()
    End Sub
End Class