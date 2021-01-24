<%@page import="bank.presentation.client.data.Model"%>
<%@page import="bank.logic.Cliente"%>
<%@page import="java.util.HashMap"%>
<%@page import="java.util.Map"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>

<!DOCTYPE html>
<html>
<head>
 <%@ include file="/presentation/Head.jsp" %>
 <title>Informacion Personal</title> 
</head>
<body>
    <%@ include file="/presentation/Header.jsp" %>
    
    <% 
        Map<String, String> errors =(Map<String,String>) request.getAttribute("errors");
        Model model = (Model) request.getAttribute("model");
        Cliente cliente = model.getClient();
        Map<String, String[]> credencials = (errors!=null)?request.getParameterMap():getCredencials(model); 
    %>

    <div class="content">
        <form class="table_data" name="form" action="/Banco_PIV/presentation/client/data/update" method="post">
            <table>
                <tr><td class="header" colspan="2">Informacion Personal</td></tr>
                <tr><td>Cedula</td><td><%= cliente.getCedula() %></td></tr>
                <tr><td>Nombre</td>
                    <td><input class ="<%=verifyErrors("name",errors)%>" type="text" name="name" placeholder="Nombre" 
                    value="<%=credencials.get("name")[0]%>" title="<%=getTittle("name",errors)%>"></td>
                </tr><tr>
                    <td>Telefono</td>
                    <td> <input class ="<%=verifyErrors("telephone",errors)%>" type="text" name="telephone" placeholder="Telefono" 
                    value="<%=credencials.get("telephone")[0]%>" title="<%=getTittle("telephone",errors)%>"></td>
                <tr><td>Usuario</td><td><%= cliente.getUsuario().getIdUsuario() %></td></tr>
                <tr>
                    <td>Contraseña</td>
                    <td><input class ="<%=verifyErrors("password",errors)%>" type="text" name="password" placeholder="Contraseña" 
                    value="<%=credencials.get("password")[0]%>" title="<%=getTittle("password",errors)%>"></td>
                </tr><tr>
                    <td colspan="2"><footer>
                    <input class="buttom" type="submit" value="Actualizar">
                    </footer></td>
                </tr>
            </table>
        </form>
    </div>
    <%@ include file="/presentation/Footer.jsp" %>
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
        credencials.put("name", new String[]{model.getClient().getNombre()});
        credencials.put("telephone", new String[]{Integer.toString(model.getClient().getTelefono())});
        credencials.put("user-name", new String[]{model.getClient().getUsuario().getPassword()});
        credencials.put("password", new String[]{model.getClient().getUsuario().getPassword()});
        return credencials;
    }
%>
