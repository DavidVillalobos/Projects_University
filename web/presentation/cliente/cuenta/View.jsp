<%@page import="java.util.Date"%>
<%@page import="java.util.HashMap"%>
<%@page import="java.util.Map"%>
<%@page import="bank.logic.Movimiento"%>
<%@page import="java.util.List"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@page import="bank.presentation.client.account.Model" %>
<%@page import="bank.logic.Cuenta"%>

<% 
    Map<String, String> errors =(Map<String,String>) request.getAttribute("errors");
    Model model = (Model) request.getAttribute("model");
    Cuenta account = model.getAccount();
    List<Movimiento> list = model.getMovements();
%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <%@include file="/presentation/Head.jsp"%>
        <title>Detalle de Cuenta: <%= account.getIdCuenta() %></title>
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
            <form name="form"  action="/Banco_PIV/presentation/client/account/searchMove" method="post">         
            <table class="table_cuenta">
                <tr><td colspan="3">Buscar Movimientos</td></tr>
                <tr><td>Desde</td>
                    <td><input type="date" name="fechaInicial" class ="<%=verifyErrors("fechaInicial",errors)%>"
                               min="2020-01-01" max="2020-12-31"></td>
                </tr>
                <tr><td>Hasta</td>
                    <td><input type="date" name="fechaFinal" class ="<%=verifyErrors("fechaFinal",errors)%>"
                               min="2020-01-01" max="2020-12-31"></td>
                </tr>
                <tr><td colspan="3"><input class="buttom" type="submit" value="Buscar"></td></tr>
            </table>
            <input type="hidden" name="idCuentafld" value="<%= account.getIdCuenta() %>">
            </form>
            <table class="table_movimientos" border="1">
                <tr id="Header"><td colspan="6">Historial de movimientos recientes</td></tr>
                <tr id="Header">
                    <td>Fecha</td>
                    <td>Numero</td>
                    <td>Motivo</td>
                    <td>Solicitante</td>
                    <td>Tipo</td>
                    <td>Monto</td>
                </tr>
                <% for(Movimiento m:list){%>
                <tr>
                    <td><%=m.getFechaString()%></td>
                    <td><%=m.getIdMovimiento() %></td>
                    <td><%=m.getMotivo()%></td>
                    <td><%=m.getSolicitante()%></td>
                    <td><%=m.getTipo().getNombre()%></td>
                    <td><%=m.getMonto()%></td>
                </tr>
                <%}%>   
            </table> 
        </div>
        <%@include file="/presentation/Footer.jsp" %>
    </body>
</html>

<%!
    private String verifyErrors(String name, Map<String,String> errors){
        if(errors!=null && errors.get(name)!=null){ 
            return "invalid"; 
        }
        return "";
    }
%>
