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
        <title>Transferencias Remotas</title> 
    </head>
    <body>
        <%@ include file="/presentation/Header.jsp" %>
        <%
            Map<String, String> errors = (Map<String, String>) request.getAttribute("errors");
            Model model = (Model) request.getAttribute("model");
            List<Cuenta> origin_accounts = model.getOrigin_accounts();
            List<Cuenta> destination_accounts = model.getDestination_accounts();
            Cuenta select_origin = model.getOrigin_account();
            Cuenta select_destiny = model.getDestination_account();
            Map<String, String[]> credencials = (errors != null) ? request.getParameterMap() : getCredencials(model);
        %>
        
        <div class="content">
            <form name="form" action="/Banco_PIV/presentation/client/transfers/processTransfer" method="post">
                <table class="open_account">
                    <tr class="header">
                        <td colspan="2">Tranferencia remota</td>
                    </tr>
                    <tr>
                        <td>Cuenta Origen</td>
                        <td><select class ="<%=verifyErrors("cuentaOrigen", errors)%>" name="cuentaOrigen" >
                        <% if(select_origin == null){%>
                            <option value="" disabled selected><%= "Seleccione una de sus cuentas "%></option>
                        <%}else{%>
                            <option value="" disabled selected><%=select_origin.getIdCuenta()%></option>
                        <%}%>
                        <%for (Cuenta c : origin_accounts) {%>  
                            <option><%= c.getIdCuenta()%></option>
                        <%}%>
                        </select>
                    </tr>
                    <tr>
                        <td>Monto</td>
                        <td>
                            <input class ="<%=verifyErrors("monto", errors)%>" type="text" name="monto" placeholder="Monto" 
                            value="<%=credencials.get("monto")[0]%>" title="<%=getTittle("monto", errors)%>">
                        </td>
                    </tr>
                    <tr>
                        <td>Cuenta Destino</td>
                        <td><select class ="<%=verifyErrors("cuentaDestino", errors)%>" name="cuentaDestino">
                            <% if(select_destiny == null){%>
                                <option value="" disabled selected><%= "Seleccione una de sus cuentas vinculadas"%></option>
                            <%}else{%>
                                <option value="" disabled selected><%=select_destiny.getIdCuenta()%></option>
                            <%}%>
                            <%for (Cuenta c : destination_accounts) {%>
                                <option><%= c.getIdCuenta()%></option>
                            <%}%>
                        </select></td>
                    </tr>
                    <tr>
                        <td>Motivo</td>
                        <td>
                            <input class ="<%=verifyErrors("motivo", errors)%>" type="text" name="motivo" placeholder="Motivo" 
                            value="<%=credencials.get("motivo")[0]%>" title="<%=getTittle("motivo", errors)%>">
                        </td>
                    </tr>
                    <tr><td>
                        <footer>
                             <a href="/Banco_PIV/presentation/Index.jsp">
                                <input class="buttom" type="" value="Cancelar" name="cancel">
                            </a>
                        </footer>
                    </td><td>
                        <footer>
                            <input class="buttom" type="submit" value="Procesar">
                        </footer>
                    </td></tr>
                </table>
            </form>
            <% if(select_origin != null && select_destiny != null){ %>
                <form name="form" action="/Banco_PIV/presentation/client/transfers/transfer" method="post">
                    <table class="confirm_transfer">
                        <tr class="header"><td colspan="6">Confirmar Tranferencia</td></tr>
                        <tr class="header"><td>Rol</td><td>N° Cuenta</td><td>Propietario</td><td>Moneda</td><td>Saldo</td><td>Movimiento</td></tr>
                        <tr>
                            <td>Origen</td>
                            <td><%= select_origin.getIdCuenta() %></td> 
                            <td><%= select_origin.getCliente().getNombre() %></td> 
                            <td><%= select_origin.getMoneda() %></td> 
                            <td><%= select_origin.getSaldo()%></td> 
                            <td> - <%= model.getMonto() %></td> 
                        </tr>
                        <tr><td><input type="hidden" name="cuentaOrigen" value="<%=select_origin.getIdCuenta() %>"></td></tr>
                        <tr><td><input type="hidden" name="cuentaDestino" value="<%=select_destiny.getIdCuenta() %>"></td></tr>
                        <tr><td><input type="hidden" name="monto" value="<%= model.getMonto() %>"></td></tr>
                        <tr><td><input type="hidden" name="motivo" value="<%= model.getMotivo() %>"></td></tr>
                        <tr>
                            <td>Destino</td>
                            <td><%= select_destiny.getIdCuenta() %></td> 
                            <td><%= select_destiny.getCliente().getNombre() %></td>
                            <td></td>
                            <td></td> 
                            <td> + <%= model.getMonto() %></td> 
                        </tr>
                        <tr id="Header">
                            <td colspan="5">Motivo: <%=model.getMotivo()%> </td>
                            <td>
                            <input class="buttom" type="submit" value="Confirmar">
                            </td>
                        </tr>
                    </table>
                </form>
            <%}%>
        </div>
        <%@ include file="/presentation/Footer.jsp" %>
    </body>
</html>

<%!
    private String verifyErrors(String name, Map<String, String> errors) {
        if (errors != null && errors.get(name) != null) {
            return "invalid";
        }
        return "";
    }

    private String getTittle(String name, Map<String, String> errors) {
        if (errors != null && errors.get(name) != null) {
            return errors.get(name);
        }
        return "";
    }

    private Map<String, String[]> getCredencials(Model model) {
        Map<String, String[]> credencials = new HashMap<String, String[]>();
        credencials.put("monto", new String[]{String.valueOf(model.getMonto())});
        credencials.put("motivo", new String[]{String.valueOf(model.getMotivo())});
        return credencials;
    }

%>