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
        <table class="form" border="1">
            <tr id="Header">
                <td colspan="4">Lista de Cuentas Bancarias</td>
            </tr>
            <tr id="Header">
                <td>Nº Cuenta</td><td>Moneda</td><td>Saldo</td><td>Límite</td>
            </tr>
            <%for(Cuenta c : cuentas){%>  
                <tr> 
                    <td><form action="/Banco_PIV/presentation/client/account/show">
                            <input type="hidden" name="idCuentafld" value="<%= c.getIdCuenta() %>"> 
                            <button class="link-button"> <%= c.getIdCuenta() %> </button> 
                        </form> 
                    </td>  
                    <td><%= c.getMoneda() %></td>
                    <td><%= c.getSaldo()%></td>
                    <td><%= c.getLimite()%></td>
                </tr>
            <%}%>
        </table>
    </div>
    <%@ include file="/presentation/Footer.jsp" %>
</body>
</html>