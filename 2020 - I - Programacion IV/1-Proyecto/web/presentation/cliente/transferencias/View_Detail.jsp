<%@page import="java.text.SimpleDateFormat"%>
<%@page import="java.util.Date"%>
<%@page import="java.util.List"%>
<%@page import="bank.presentation.client.transfers.Model"%>
<%@page import="bank.logic.Cliente"%>
<%@page import="bank.logic.Cuenta"%>
<%@page import="java.util.HashMap"%>
<%@page import="java.util.Map"%>
<!DOCTYPE html>
<html>
    <head>
        <%@ include file="/presentation/Head.jsp" %>
        <title>Detalle de transferencia</title> 
    </head>
    <body>
        <%@ include file="/presentation/Header.jsp" %>
        <%
            Map<String, String> errors = (Map<String, String>) request.getAttribute("errors");
            Model model = (Model) request.getAttribute("model");
            Cuenta select_origin = model.getOrigin_account();
            Cuenta select_destiny = model.getDestination_account();
            SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
            String toDay = sdf.format(new Date());
        %>
        <div class="content">
            <% if(select_origin != null && select_destiny != null){ %>
                <form name="form" action="/Banco_PIV/presentation/Index.jsp" method="post">
                    <table class="detail_transfer">
                        <tr class="header"><td colspan="7">Detalle de la Tranferencia Realizada</td></tr>
                        <tr class="header"><td>Tipo</td><td>N° Cuenta</td><td>Propietario</td><td>Fecha</td><td>Saldo Anterior</td><td>Monto</td><td>Saldo Actual</td></tr>
                        <tr>
                            <td>Origen</td>
                            <td><%= select_origin.getIdCuenta() %></td> 
                            <td><%= select_origin.getCliente().getNombre() %></td>
                            <td><%= toDay %></td>
                            <td><%= select_origin.getSaldo() + model.getMonto()%></td> 
                            <td> - <%= model.getMonto()%></td>
                            <td><%= select_origin.getSaldo() %></td>
                        </tr>
                        <tr>
                            <td>Destino</td>
                            <td><%= select_destiny.getIdCuenta() %></td> 
                            <td><%= select_destiny.getCliente().getNombre() %></td>
                            <td><%= toDay %></td>
                            <td></td>
                            <td> + <%= model.getMonto() %></td> 
                            <td></td>
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