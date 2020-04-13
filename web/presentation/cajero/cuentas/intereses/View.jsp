<%@page import="bank.logic.Moneda"%>
<%@page import="bank.presentation.cashier.accounts.interests.Model"%>
<%@page import="java.util.List"%>
<%@page import="bank.logic.Cuenta"%>
<%@page import="java.util.HashMap"%>
<%@page import="java.util.Map"%>
<!DOCTYPE html>
<html>
    <head>
        <%@ include file="/presentation/Head.jsp" %>
        <title>Transferencias en Cajas</title> 
    </head>
    <body>
        <%@ include file="/presentation/Header.jsp" %>
        <%
            Map<String, String> errors = (Map<String, String>) request.getAttribute("errors");
            Model model = (Model) request.getAttribute("model");
        %>
        
        <div class="content">
            <form name="form" action="/Banco_PIV/presentation/cashier/accounts/interests/accredit" method="post">
                <table class="table-accredit" border="1">
                    <tr><td id="Header" colspan="3">Monedas</td></tr>
                    <tr id="Header">
                        <td>Codigo</td><td>Nombre</td><td>Porcentaje de Interes</td>
                    </tr>
                    <%for (Moneda c : model.getMonedas()){%>
                        <tr>
                            <td><%=c.getIdMoneda()%></td>
                            <td><%=c.getNombreMoneda() %></td>
                            <td><%=c.getInteres() %>%</td>
                        </tr>
                    <%}%>
                    <tr><td colspan="3"><footer>
                    <input class="buttom" type="submit" value="Acreditar">
                    </footer></td></tr>
                </table>
            <form>
        </div>
        <%@ include file="/presentation/Footer.jsp" %>
    </body>
</html>