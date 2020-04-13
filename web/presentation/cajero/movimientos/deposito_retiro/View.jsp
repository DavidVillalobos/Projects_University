<%@page import="bank.logic.Moneda"%>
<%@page import="java.util.List"%>
<%@page import="bank.presentation.cashier.movements.deposit_withdrawal.Model"%>
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
            Map<String, String[]> credencials = (errors != null) ? request.getParameterMap() : getCredencials(model);
            List<Moneda> monedas = model.getMonedas();
        %>
        
        <div class="content">
            <form name="form" action="/Banco_PIV/presentation/cashier/movements/d_wd/doMovement" method="post">
                <table class="remote-transfer">
                    <tr id="Header">
                        <td colspan="2">Tranferencia en Caja</td>
                    </tr>
                    <tr>
                        <td>Nº Cuenta</td>
                        <td><input type="hidden" name="cuenta" value="<%= credencials.get("cuenta")[0] %>" ><%= credencials.get("cuenta")[0] %></td>
                    </tr>
                    <tr>
                        <td>Monto</td>
                        <td>
                            <input class ="<%=verifyErrors("monto", errors)%>" type="text" name="monto" placeholder="Monto" 
                            value="<%=credencials.get("monto")[0]%>" title="<%=getTittle("monto", errors)%>">
                        </td>
                    </tr>
                    <tr>
                        <td>Nombre</td>
                        <td>
                            <input class ="<%=verifyErrors("nombre", errors)%>" type="text" name="nombre" placeholder="Nombre del Solicitante" 
                            value="<%=credencials.get("nombre")[0]%>" title="<%=getTittle("nombre", errors)%>">
                        </td>
                    </tr>
                    <tr>
                        <td>Motivo</td>
                        <td>
                            <input class ="<%=verifyErrors("motivo", errors)%>" type="text" name="motivo" placeholder="Motivo" 
                            value="<%=credencials.get("motivo")[0]%>" title="<%=getTittle("motivo", errors)%>">
                        </td>
                    </tr>
                    </tr>
                        <td>Moneda</td>
                        <td>
                            <select class="<%=verifyErrors("moneda", errors)%>" name="moneda">
                            <option value="" disabled selected>Seleccione una Moneda</option>
                            <%for (Moneda c : monedas) {
                                if(credencials.get("moneda") != null){
                                    if(c.getNombreMoneda().equals(credencials.get("moneda")[0])){%>
                                        <option selected="true" ><%= c.getNombreMoneda() %></option>
                                    <% } else{ %>
                                        <option><%= c.getNombreMoneda() %></option> 
                                    <% }} else { %>
                                       <option><%= c.getNombreMoneda() %></option>
                            <% }}%>
                            </select>
                        </td>
                    <tr>
                    <tr>
                        <td>Movimiento</td>
                        <td>
                            <input  type="radio" name="tipoMovimiento" value="1">Retiro
                            <input  type="radio" name="tipoMovimiento" value="2">Deposito<br>
                        </td>
                    </tr>
                    <% if(verifyErrors("tipoMovimiento", errors).equals("invalid")){ %>
                        <tr>
                        <td id="invalid-message" colspan="2">Es necesario elegir un movimiento.</td>
                        
                        </tr>
                    <% } %>
                    <tr><td>
                        <footer>
                            <input class="buttom" type="reset" value="Cancelar">
                        </footer>
                    </td><td>
                        <footer>
                            <input class="buttom" type="submit" value="Procesar">
                        </footer>
                    </td></tr>
                </table>
            </form>
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
        credencials.put("cuenta", new String[]{model.getAccount_num()});
        credencials.put("monto", new String[]{String.valueOf(model.getMonto())});
        credencials.put("motivo", new String[]{model.getMotivo()});
        credencials.put("nombre", new String[]{model.getNombre_solicitante()});
        credencials.put("moneda", new String[]{
            (model.getMoneda() == null)?"":model.getMoneda().getNombreMoneda()
        });
        return credencials;
    }

%>