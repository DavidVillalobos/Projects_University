Public Class Add_Editorial
    Private Sub Regresar_Click(sender As Object, e As EventArgs) Handles Regresar.Click
        Me.Hide()
        Menu_Principal.Show()
    End Sub

    Private Sub Add_Countries_FormClosing(sender As Object, e As EventArgs) Handles MyBase.Closed
        Me.Hide()
        Menu_Principal.Show()
    End Sub
End Class