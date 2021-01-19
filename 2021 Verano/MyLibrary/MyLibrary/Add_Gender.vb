Public Class Add_Gender
    Private Sub Button3_Click(sender As Object, e As EventArgs) Handles Regresar.Click
        Me.Hide()
        Menu_Principal.Show()
    End Sub

    Private Sub Add_Gender_FormClosing(sender As Object, e As EventArgs) Handles MyBase.Closed
        Me.Hide()
        Menu_Principal.Show()
    End Sub
End Class