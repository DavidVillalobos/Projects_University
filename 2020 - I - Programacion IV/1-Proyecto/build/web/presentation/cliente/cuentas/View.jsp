<%@page import="bank.logic.Cuenta"%>
<%@page import="bank.presentation.client.accounts.Model"%>
<%@page import="java.util.List"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%
    Model model = (Model) request.getAttribute("model");
    List<Cuenta> cuentas = model.getAccounts();
%>
<!DOCTYPE html>
<html>
<head>
 <%@ include file="/presentation/Head.jsp" %>
 <title>Mis Cuentas</title> 
</head>
<body>
    <%@ include file="/presentation/Header.jsp" %>
    <div class="content">
        <table class="table_accounts">
            <thead class="header">
                <tr><td colspan="4">Lista de Cuentas Bancarias</td></tr>
                <tr><td>Nº Cuenta</td><td>Moneda</td><td>Saldo</td><td>Límite</td></tr>
            </thead>
            <tbody>
            <%for(Cuenta c : cuentas){%>  
                <tr> 
                    <td><form action="/Banco_PIV/presentation/client/account/show">
                            <input type="hidden" name="idCuentafld" value="<%= c.getIdCuenta() %>"> 
                            <button class="link_button"> <%= c.getIdCuenta() %> </button> 
                        </form> 
                    </td>  
                    <td><%= c.getMoneda() %></td>
                    <td><%= c.getSaldo()%></td>
                    <td><%= c.getLimite()%></td>
                </tr>
            <%}%>
            </tbody>
        </table>
    </div>
    <%@ include file="/presentation/Footer.jsp" %>
</body>
</html>