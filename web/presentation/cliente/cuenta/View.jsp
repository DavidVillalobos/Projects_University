<%@page import="bank.logic.Movimiento"%>
<%@page import="java.util.List"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@page import="bank.presentation.client.account.Model" %>
<%@page import="bank.logic.Cuenta"%>

<% 
    Model model = (Model) request.getAttribute("model");
    Cuenta account = model.getAccount();
    List<Movimiento> list = model.getMovements();
%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <%@include file="/presentation/Head.jsp"%>
        <title>Account</title>
    </head>
    <body>
        <%@include file="/presentation/Header.jsp"%>
        <div class="content">
            <table class="table_cuenta">
                <tr><td>Nº Cuenta</td><td><%= account.getIdCuenta() %></td></tr>
                <tr><td>Saldo</td><td><%= account.getSaldo() %></td></tr>
                <tr><td>Limite</td><td><%= account.getLimite() %></td></tr>
                <tr><td>Moneda</td><td><%= account.getMoneda() %></td></tr> 
                <tr>
                    <td colspan="2">
                        <a href="/Banco_PIV/presentation/client/accounts/show">
                            <input class="buttom" type="submit" name="back-buttom" value="Atrás">
                        </a>
                        
                    </td>
                </tr>
            </table>
            <table class="table_movimientos">
                <th colspan="4">HISTORIAL DE MOVIMIENTOS RECIENTES</th>
                <tr class="cabecera">
                    <td style="width: 20%">Monto</td>
                    <td style="width: 15%">Fecha</td>
                    <td style="width: 15%">tipo</td>
                    <td style="width: 50%">Motivo</td>
                </tr>
                <% for(Movimiento m:list){%>
                <tr class="td_m">
                    <td><%=m.getMonto()%></td>
                    <td><%=m.getFechaString()%></td>
                    <td><%=m.getTipo().getNombre()%></td>
                    <td><%=m.getMotivo()%></td>
                </tr>
                <%}%>   
            </table> 
        </div>
        <%@include file="/presentation/Footer.jsp" %>
    </body>
</html>
