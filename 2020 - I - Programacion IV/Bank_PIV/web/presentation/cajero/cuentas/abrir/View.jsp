<%@page import="bank.logic.Moneda"%>
<%@page import="java.util.List"%>
<%@page import="java.util.HashMap"%>
<%@page import="bank.presentation.cashier.accounts.open.Model"%>
<%@page import="java.util.Map"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>

<% Map<String, String> errors =(Map<String,String>) request.getAttribute("errors"); %>
<% Model model = (Model) request.getAttribute("model"); %>
<% Map<String, String[]> credencials = (errors!=null)?request.getParameterMap():getCredencials(model); %>
<% List<Moneda> monedas = model.getMonedas(); %>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <%@include file="/presentation/Head.jsp" %>
        <title>Abrir Cuenta</title>
    </head>
    <body>
        <%@include file="/presentation/Header.jsp" %>
        <div class="content">
            <% if(request.getAttribute("added") == null){ %>
            <form name="form" action="/Banco_PIV/presentation/cashier/accounts/open/create" method="post">
                <table class="open_account">
                    <tr class="header">
                        <td colspan="2">Abrir Cuenta</td>
                    </tr>
                    <tr>
                        <td>Cliente</td>
                        <td>
                           <input class ="<%=verifyErrors("cedula", errors)%>" type="text" name="cedula" placeholder="Cedula" 
                            value="<%=credencials.get("cedula")[0]%>" title="<%=getTittle("cedula", errors)%>"> 
                        </td>
                    </tr>
                    <tr>
                        <td>Limite Diario</td>
                        <td>
                            <input class ="<%=verifyErrors("limite", errors)%>" type="text" name="limite" 
                            value="<%=credencials.get("limite")[0]%>" title="<%=getTittle("limite", errors)%>">
                        </td>
                    </tr>
                    <tr>
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
                    </tr>
                    <tr><td>
                        <footer>
                            <a href="/Banco_PIV/presentation/Index.jsp">
                                <input class="buttom" type="" value="Cancelar" name="cancel">
                            </a>
                        </footer>
                    </td><td>
                        <footer>
                            <input class="buttom" type="submit" value="Procesar" name="process">
                        </footer> 
                    </td></tr>
                </table>
                <% if(model.getRegistrated() == false){ %>
                <table class="new_client">
                    <tr class="header">
                        <td colspan="2">Nuevo Cliente</td>
                    </tr>
                    <tr>
                        <td>Cliente</td>
                        <td>
                            <%=credencials.get("cedula")[0]%>
                        </td>
                    </tr>
                    <tr>
                        <td>Nombre</td>
                        <td>
                            <input class ="<%=verifyErrors("nombre", errors)%>" type="text" name="nombre" placeholder="Nombre"
                            value="<%=credencials.get("nombre")[0]%>" title="<%=getTittle("nombre", errors)%>">
                        </td>
                    </tr>
                    <tr>
                        <td>Teléfono</td>
                        <td>
                            <input class ="<%=verifyErrors("telefono", errors)%>" type="text" name="telefono" 
                            value="<%=credencials.get("telefono")[0]%>" title="<%=getTittle("telefono", errors)%>">
                        </td>
                    </tr>
                    <tr class="header">
                        <td colspan="2"> <br> </td>
                    </tr>  
                </table> <% } %>
            </form><% } %>
            <% if(request.getAttribute("added")!= null){ %>
            <form name="form_2" action="/Banco_PIV/presentation/cashier/accounts/open/show" method="post">
                <center>
                <table class="remote_transfer">
                    <tr class="header">
                        <td colspan="2">Detalle de Cuenta</td>
                    </tr>
                    <tr><td>Cliente</td><td><%=credencials.get("cedula")[0]%></td></tr>
                    <% if(request.getAttribute("newClient")!=null){ %>
                    <tr><td>Contraseña</td><td><%=credencials.get("contrasena")[0]%></td></tr>
                    <% } %>
                    <tr><td>Nombre</td><td><%=credencials.get("nombre")[0]%></td></tr>
                    <tr><td>Teléfono</td><td><%=credencials.get("telefono")[0]%></td></tr>
                    <tr><td>Numero de Cuenta</td><td><%=credencials.get("num_cuenta")[0]%></td></tr>
                    <tr><td>Limite Diario</td><td><%=credencials.get("limite")[0]%></td></tr>
                    <tr><td>Moneda</td><td><%=credencials.get("moneda")[0]%></td></tr>
                    <tr><td colspan="2"><footer>
                        <input class="buttom" type="submit" value="OK" name="process">
                    </footer></td></tr>  
                </table>
                </center>
            </form> <% } %>
        </div>
        <%@include file="/presentation/Footer.jsp" %>
    </body>
</html>
<%!
    private String verifyErrors(String name, Map<String,String> errors){
        if(errors!=null && errors.get(name)!=null){ return "invalid"; }
        return "";
    }

    private String getTittle(String name, Map<String,String> errors){
        if(errors!=null && errors.get(name)!=null){ return errors.get(name); }
        return "";
    }
    
    private Map<String,String[]> getCredencials(Model model){
        Map<String,String[]> credencials = new HashMap<String,String[]>();
        credencials.put("limite", new String[]{String.valueOf(model.getAccount().getLimite())});
        credencials.put("cedula", new String[]{model.getClient().getCedula()});
        credencials.put("nombre", new String[]{model.getClient().getNombre()});
        credencials.put("telefono", new String[]{String.valueOf(model.getClient().getTelefono())});
        credencials.put("moneda", new String[]{
            (model.getAccount().getMoneda() == null)?"":model.getAccount().getMoneda().getNombreMoneda()
        });
        credencials.put("num_cuenta", new String[]{String.valueOf(model.getAccount().getIdCuenta())});
        credencials.put("contrasena", new String[]{
            (model.getClient().getUsuario() == null)?"":model.getClient().getUsuario().getPassword()});
        return credencials;
    }
%>
