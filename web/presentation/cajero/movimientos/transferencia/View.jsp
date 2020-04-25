<%@page import="java.util.List"%>
<%@page import="bank.presentation.cashier.movements.transfer.Model "%>
<%@page import="bank.logic.Cliente"%>
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
            List<Cuenta> origin_accounts = model.getOrigin_accounts();
            List<Cuenta> destination_accounts = model.getDestination_accounts();
            Cuenta select_origin = model.getOrigin_account();
            Cuenta select_destiny = model.getDestination_account();
            Map<String, String[]> credencials = getCredencials(model);
        %>
        
        <div class="content">
            <form name="form_1" action="/Banco_PIV/presentation/cashier/movements/transfer/searchOrigin" method="post">
            <table class="search_account_origin">
                <tr><td colspan="2">Cuenta Origen</td></tr>
                <tr>
                    <td>Nº Cuenta</td>
                    <td>
                        <input class ="<%=verifyErrors("n_account_1", errors)%>" type="text" name="n_account_1" placeholder="Número de Cuenta" 
                        value="<%=credencials.get("n_account_1")[0]%>" title="<%=getTittle("n_account_1", errors)%>">
                    </td>
                </tr>
                <tr>
                    <td>Id Cliente</td>
                    <td>
                        <input class ="<%=verifyErrors("id_1", errors)%>" type="text" name="id_1" placeholder="Cédula Cliente" 
                        value="<%=credencials.get("id_1")[0]%>" title="<%=getTittle("id_1", errors)%>">
                    </td>
                </tr>
                <tr><td><input type="hidden" name="n_account_2" value="<%= credencials.get("n_account_2")[0] %>"></td></tr>
                <tr><td><input type="hidden" name="id_2" value="<%=credencials.get("id_2")[0] %>"></td></tr>
                <tr><td><input type="hidden" name="monto" value="<%= credencials.get("monto")[0] %>"></td></tr>
                <tr><td><input type="hidden" name="motivo" value="<%= credencials.get("motivo")[0] %>"></td></tr>
                <tr><td><input type="hidden" name="cuentaOrigen" value="<%=credencials.get("cuentaOrigen")[0] %>"></td></tr>
                <tr><td><input type="hidden" name="cuentaDestino" value="<%=credencials.get("cuentaDestino")[0] %>"></td></tr>
                <tr>
                    <td colspan="2">
                        <input class="buttom" type="submit" name="back-buttom" value="Buscar">
                    </td>
                </tr>
            </table>
            </form>
            <form name="form_2" action="/Banco_PIV/presentation/cashier/movements/transfer/searchDestiny" method="post">
            <table class="search_account_destiny">
                <tr><td colspan="2">Cuenta Destino</td></tr>
                <tr>
                    <td>Nº Cuenta</td>
                    <td>
                        <input class ="<%=verifyErrors("n_account_2", errors)%>" type="text" name="n_account_2" placeholder="Número de Cuenta" 
                        value="<%=credencials.get("n_account_2")[0]%>" title="<%=getTittle("n_account_2", errors)%>">
                    </td>
                </tr>
                <tr>
                    <td>Id Cliente</td>
                    <td>
                        <input class ="<%=verifyErrors("id_2", errors)%>" type="text" name="id_2" placeholder="Cédula Cliente" 
                        value="<%=credencials.get("id_2")[0]%>" title="<%=getTittle("id_2", errors)%>">
                    </td>
                </tr>
                <tr><td><input type="hidden" name="n_account_1" value="<%= model.getN_account_1() %>"></td></tr>
                <tr><td><input type="hidden" name="id_1" value="<%=model.getId_1() %>"></td></tr>
                <tr><td><input type="hidden" name="monto" value="<%= model.getMonto() %>"></td></tr>
                <tr><td><input type="hidden" name="motivo" value="<%= model.getMotivo() %>"></td></tr>
                <tr><td><input type="hidden" name="cuentaOrigen" value="<%=credencials.get("cuentaOrigen")[0] %>"></td></tr>
                <tr><td><input type="hidden" name="cuentaDestino" value="<%=credencials.get("cuentaDestino")[0] %>"></td></tr>
                <tr>
                    <td colspan="2">
                            <input class="buttom" type="submit" name="back-buttom" value="Buscar">
                    </td>
                </tr>  
            </table>
            </form>
            <form name="form" action="/Banco_PIV/presentation/cashier/movements/transfer/processTransfer" method="post">
                <table class="transfer_in_cash_register">
                    <tr class="header">
                        <td colspan="2">Tranferencia en Cajas</td>
                    </tr>
                    <tr>
                        <td>Cuenta Origen</td>
                        <td><select class ="<%=verifyErrors("cuentaOrigen", errors)%>" name="cuentaOrigen" >
                            <option value="" disabled selected>Seleccione una Cuenta Origen</option>
                            <%for (Cuenta c : origin_accounts) {
                                if(c.getIdCuenta().equals(Integer.parseInt(credencials.get("cuentaOrigen")[0]))){%>
                                        <option selected="true" value="<%= c.getIdCuenta() %>"><%= c.getIdCuenta() %> / <%= c.getCliente().getNombre() %></option>
                                 <% } else{ %>
                                    <option value="<%= c.getIdCuenta() %>"><%= c.getIdCuenta() %> / <%= c.getCliente().getNombre() %></option> 
                                <% }}%>
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
                            <option value="" disabled selected>Seleccione una Cuenta Destino</option>
                            <%for (Cuenta c : destination_accounts) {
                                if(c.getIdCuenta().equals(Integer.parseInt(credencials.get("cuentaDestino")[0]))){%>
                                    <option selected="true" value="<%= c.getIdCuenta() %>"><%= c.getIdCuenta() %> / <%= c.getCliente().getNombre() %></option>
                             <% } else{ %>
                                    <option value="<%= c.getIdCuenta() %>"><%= c.getIdCuenta() %> / <%= c.getCliente().getNombre() %></option> 
                            <% }}%>
                        </select></td>
                    </tr>
                    <tr>
                        <td>Motivo</td>
                        <td>
                            <input class ="<%=verifyErrors("motivo", errors)%>" type="text" name="motivo" placeholder="Motivo" 
                            value="<%=credencials.get("motivo")[0]%>" title="<%=getTittle("motivo", errors)%>">
                        </td>
                    </tr>
                    <tr><td><input type="hidden" name="n_account_1" value="<%= model.getN_account_1() %>"></td></tr>
                    <tr><td><input type="hidden" name="id_1" value="<%=model.getId_1() %>"></td></tr>
                    <tr><td><input type="hidden" name="n_account_2" value="<%= model.getN_account_2() %>"></td></tr>
                    <tr><td><input type="hidden" name="id_2" value="<%=model.getId_2() %>"></td></tr>
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
        credencials.put("monto", new String[]{String.valueOf(model.getMonto())});
        credencials.put("motivo", new String[]{String.valueOf(model.getMotivo())});
        credencials.put("id_1", new String[]{model.getId_1()});
        credencials.put("id_2", new String[]{model.getId_2()});
        credencials.put("n_account_1", new String[]{model.getN_account_1()});
        credencials.put("n_account_2", new String[]{model.getN_account_2()});
        credencials.put("cuentaOrigen", new String[]{
            (model.getOrigin_account() == null)?"0":String.valueOf(model.getOrigin_account().getIdCuenta())
        });
        credencials.put("cuentaDestino", new String[]{
            (model.getDestination_account() == null)?"0":String.valueOf(model.getDestination_account().getIdCuenta())
        });
        return credencials;
    }

%>

<% 
/* <form name="formulario" method="post" action="http://pagina.com/send.php">
  <!-- Campo de texto combinado con lista de opciones -->
  <input type="text" list="items">
  <!-- Lista de opciones -->
  <datalist id="items">
    <option value="1">Opción 1</option>
    <option value="2">Opción 2</option>
    <option value="3">Opción 3</option>
  </datalist>
</form>
 ===================================================================   
 <select name="transporte" size="2">

<option>Coche</option>

<option>Avión</option>

<option>Tren</option>

</select> 
======================================================================
    
<input type="radio" name="transporte" value="1">Coche

<br>

<input type="radio" name="transporte" value="2">Avión

<br>

<input type="radio" name="transporte" value="3">Tren*/
%>

