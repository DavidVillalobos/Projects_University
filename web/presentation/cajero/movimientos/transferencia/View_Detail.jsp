<%@page import="java.text.SimpleDateFormat"%>
<%@page import="java.util.Date"%>
<%@page import="java.util.List"%>
<%@page import="bank.presentation.cashier.movements.transfer.Model"%>
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
            Model model = (Model) request.getAttribute("model");
            Cuenta select_origin = model.getOrigin_account();
            Cuenta select_destiny = model.getDestination_account();
            SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
            String toDay = sdf.format(new Date());
        %>
        <div class="content">
            <% if(select_origin != null && select_destiny != null){ %>
                <form name="form" action="/Banco_PIV/presentation/cashier/movements/transfer/show" method="post">
                    <table class="datail-transfer">
                        <tr id="Header"><td colspan="7">Detalle de la Tranferencia Realizada</td></tr>
                        <tr id="Header"><td>Tipo</td><td>N° Cuenta</td><td>Propietario</td><td>Fecha</td><td>Saldo Anterior</td><td>Monto</td><td>Saldo Actual</td></tr>
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
                            <td> + <%= (model.getMonto() * model.getOrigin_account().getMoneda().getValorColones()) 
                                    /  model.getDestination_account().getMoneda().getValorColones() %></td> 
                            <td></td>
                        </tr>
                        <tr>
                            <td><br>Motivo: </td>
                            <td colspan="7" style="text-align: left"> <i><br><%= model.getMotivo() %></i> </td>
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
