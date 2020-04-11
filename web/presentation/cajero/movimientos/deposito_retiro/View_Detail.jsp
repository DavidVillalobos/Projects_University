<%@page import="java.text.SimpleDateFormat"%>
<%@page import="java.util.Date"%>
<%@page import="java.util.List"%>
<%@page import="bank.presentation.cashier.movements.deposit_withdrawal.Model"%>
<%@page import="bank.logic.Cliente"%>
<%@page import="bank.logic.Cuenta"%>
<%@page import="java.util.HashMap"%>
<%@page import="java.util.Map"%>
<!DOCTYPE html>

<%
    Map<String, String> errors = (Map<String, String>) request.getAttribute("errors");
    Model model = (Model) request.getAttribute("model");
    Cuenta select_origin = model.getSelected();
    SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
    String toDay = sdf.format(new Date());
%>
<html>
    <head>
        <%@ include file="/presentation/Head.jsp" %>
        <title>Detalle de <%= model.getTipoMovimiento()==1?"Retiro":"Deposito" %></title> 
    </head>
    <body>
        <%@ include file="/presentation/Header.jsp" %>

        <div class="content">
            <% if(select_origin != null){ %>
                <form name="form" action="/Banco_PIV/presentation/cashier/movements/d_wd/show" method="post">
                    <table class="datail-transfer">
                        <tr id="Header"><td colspan="7">Detalle del <%= model.getTipoMovimiento()==1?"Retiro":"Deposito" %> Realizado</td></tr>
                        <tr id="Header"><td>N° Cuenta</td><td>Propietario</td><td>Fecha</td><td>Monto</td><td>Saldo Actual</td></tr>
                        <tr>
                            <td><%= select_origin.getIdCuenta() %></td> 
                            <td><%= select_origin.getCliente().getNombre() %></td>
                            <td><%= toDay %></td>
                            <td><%= model.getTipoMovimiento()==1?"-":"+"%> <%= model.getMonto()%></td>
                            <td><%= select_origin.getSaldo() %></td>
                        </tr>
                        <tr><td colspan="7"><footer>
                        <input class="buttom" type="submit" value="OK" name="process">
                    </footer></td></tr>  
                    </table>
                </form>
            <%}%>
        </div>
        <%@ include file="/presentation/Footer.jsp" %>
    </body>
</html>
