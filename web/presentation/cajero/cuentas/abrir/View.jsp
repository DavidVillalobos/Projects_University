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
            <form name="form" action="/Banco_PIV/presentation/cashier/accounts/open/create" method="post">
                <table class="remote-transfer">
                    <tr id="Header">
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
                        <td>Moneda</td>
                        <td>
                            <select class="<%=verifyErrors("moneda", errors)%>" name="moneda">
                            <option value="" disabled selected>Seleccione una Moneda</option>
                            <%for (Moneda c : monedas) {%>  
                            <option><%= c.getIdMoneda() %></option>
                            <%}%>
                            </select>
                        </td>
                    <tr><td>
                        <footer>
                            <input class="buttom" type="reset" value="Cancelar" name="cancel">
                        </footer>
                    </td><td>
                        <footer>
                            <input class="buttom" type="submit" value="Procesar">
                        </footer>
                    </td></tr>
                </table>
                <% if(model.getRegistrated() == false){ %>
                <table class="new-client">
                    <tr id="Header">
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
                    <tr id="Header">
                        <td colspan="2"> <br> </td>
                    </tr>  
                </table> <% } %>
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
            (model.getAccount().getMoneda() == null)?"":model.getAccount().getMoneda().getIdMoneda()
        });
        return credencials;
    }
%>
