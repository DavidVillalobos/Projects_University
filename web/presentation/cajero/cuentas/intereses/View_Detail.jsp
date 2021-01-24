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
                <table class="table_view_accredit">
                    <thead class="header">
                    <tr><td colspan="7">Intereses Acreditados Correctamente</td></tr>
                    <tr>
                        <td>Fecha</td>
                        <td>Numero</td>
                        <td>Cuenta</td>
                        <td>Motivo</td>
                        <td>Solicitante</td>
                        <td>Tipo</td>
                        <td>Monto</td>
                    </tr>
                    </thead>
                    <tbody>
                        <% for(Movimiento m: model.getAcreditas() ){%>
                            <tr>
                                <td><%=m.getFechaString()%></td>
                                <td><%=m.getIdMovimiento() %></td>
                                <td><%=m.getCuentaDestino().getIdCuenta() %></td>
                                <td><%=m.getMotivo()%></td>
                                <td><%=m.getSolicitante()%></td>
                                <td><%=m.getTipo().getNombre()%></td>
                                <td><%=m.getMonto()%></td>
                            </tr>
                        <%}%>   
                        <tr>
                        <td colspan="7">
                            <footer>
                            <input class="buttom" type="submit" value="OK">
                            </footer>
                        </td>
                        </tr>
                    </tbody>
                </table>
            </form>
        </div>
        <%@ include file="/presentation/Footer.jsp" %>
    </body>
</html>