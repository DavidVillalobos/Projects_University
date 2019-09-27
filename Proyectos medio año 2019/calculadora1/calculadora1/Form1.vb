Public Class Form1



    Private Sub Resta_CheckedChanged(sender As Object, e As EventArgs) Handles Resta.CheckedChanged
        A.Text = 0
        B.Text = 0
        C.Text = 0
    End Sub

    Private Sub Division_CheckedChanged(sender As Object, e As EventArgs) Handles Division.CheckedChanged
        A.Text = 0
        B.Text = 0
        C.Text = 0
    End Sub

    Private Sub Multiplicacion_CheckedChanged(sender As Object, e As EventArgs) Handles Multiplicacion.CheckedChanged
        A.Text = 0
        B.Text = 0
        C.Text = 0
    End Sub

    Private Sub Suma_CheckedChanged(sender As Object, e As EventArgs) Handles Suma.CheckedChanged
        A.Text = 0
        B.Text = 0
        C.Text = 0
    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Dim V1, V2 As Integer
        V1 = A.Text
        V2 = B.Text
        If Suma.Checked = True Then
            C.Text = V1 + V2
        ElseIf Resta.Checked = True Then
            C.Text = V1 - V2
        ElseIf Multiplicacion.Checked = True Then
            C.Text = V1 * V2
        ElseIf Division.Checked = True Then
            C.Text = V1 / V2
        End If
    End Sub
End Class
