<%@page import="bank.logic.Cuenta"%>
<%@page import="bank.presentation.client.accountsLinked.Model"%>
<%@page import="java.util.List"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%
    Model model = (Model) request.getAttribute("model");
    List<Cuenta> cuentas = model.getAccountsLinked();
%>
<!DOCTYPE html>
<html>
<head>
 <%@ include file="/presentation/Head.jsp" %>
 <title>Accounts</title> 
</head>
<body>
    <%@ include file="/presentation/Header.jsp" %>
    <div class="content">
        <table class="form">
            <tr class="cabecera">
                <td>Id</td><td>Moneda</td><td>Cedula</td><td>Nombre</td>
            </tr>
            <%for(Cuenta c : cuentas){%>  
                <tr>
                    <td><a href="<%=c.getIdCuenta()%>"><%=c.getIdCuenta()%> </td>  
                    <td><%= c.getMoneda() %></td>
                    <td><%= c.getCliente().getCedula() %></td>
                    <td><%= c.getCliente().getNombre() %></td>
                </tr>
            <%}%>
        </table>
    </div>
    <%@ include file="/presentation/Footer.jsp" %>
</body>
</html>
