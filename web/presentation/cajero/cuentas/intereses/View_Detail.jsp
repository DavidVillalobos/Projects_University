<%@page import="bank.logic.Movimiento"%>
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
            <form name="form" action="/Banco_PIV/presentation/Index.jsp" method="post">
                <table class="table-accredit" border="1">
                    <tr><td id="Header" colspan="6">Intereses Acreditados Correctamente</td></tr>
                    <tr id="Header">
                        <td>Fecha</td>
                        <td>Numero</td>
                        <td>Motivo</td>
                        <td>Solicitante</td>
                        <td>Tipo</td>
                        <td>Monto</td>
                    </tr>
                    <% for(Movimiento m: model.getAcreditas() ){%>
                        <tr>
                            <td><%=m.getFechaString()%></td>
                            <td><%=m.getIdMovimiento() %></td>
                            <td><%=m.getMotivo()%></td>
                            <td><%=m.getSolicitante()%></td>
                            <td><%=m.getTipo().getNombre()%></td>
                            <td><%=m.getMonto()%></td>
                        </tr>
                    <%}%>   
                    <tr>
                    <td colspan="6">
                        <footer>
                        <input class="buttom" type="submit" value="OK">
                        </footer>
                    </td>
                    </tr>
                </table>
            </form>
        </div>
        <%@ include file="/presentation/Footer.jsp" %>
    </body>
</html>