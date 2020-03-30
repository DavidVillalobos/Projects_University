<%@page import="java.util.HashMap"%>
<%@page import="java.util.Map"%>
<%@page import="bank.logic.Cuenta"%>
<%@page import="bank.presentation.client.accountsLinked.Model"%>
<%@page import="java.util.List"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%
    Map<String, String> errors =(Map<String,String>) request.getAttribute("errors");
    Model model = (Model) request.getAttribute("model");
    List<Cuenta> cuentas = model.getAccountsLinked();
    Cuenta bylink = model.getAccountToLink();
    Map<String, String[]> credencials = (errors!=null)?request.getParameterMap():getCredencials(model);
%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <%@include file="/presentation/Head.jsp" %>
        <title>Login</title>
    </head>
    <body>
        <%@include file="/presentation/Header.jsp" %>
        <div class="content">
            <table id="accounts">
                <tr class="cabecera"><td>Numero de Cuenta</td><td>Cedula</td><td>Propietario</td><td>Moneda</td>
                <%for(Cuenta c : cuentas){%>  
                    <tr>
                        <td><a href="<%=c.getIdCuenta()%>"><%=c.getIdCuenta()%> </td>  
                        <td><%= c.getCliente().getCedula() %></td>
                        <td><%= c.getCliente().getNombre() %></td>
                        <td><%= c.getMoneda() %></td>
                    </tr>
                <%}%>
            </table>
            <form name="form"  action="/Banco_PIV/presentation/client/accountsLinked/search" method="post">         
                <table id="search">
                    <td id="searchHeader" colspan="3">Nuevo Vinculo</td>
                    <tr>
                        <td>N° Cuenta</td>
                        <td><input class ="<%=verifyErrors("idAccount",errors)%>" type="text" name="idAccount" placeholder=" Numero de Cuenta" 
                        value="<%=credencials.get("idAccount")[0]%>" title="<%=getTittle("idAccount",errors)%>"></td>
                    </tr>
                    <tr>
                        <td colspan="3"><footer><input class="buttom" type="submit" value="Buscar"></footer></td>
                    </tr>
                </table>
            </form>
            <% if(bylink != null){ %>
                <form name="form"  action="/Banco_PIV/presentation/client/accountsLinked/link" method="post">         
                    <table id="link">
                        <td id="linkHeader" colspan="3">Informacion de la Cuenta</td>
                        <tr>
                            <td>N° Cuenta</td><td>Propietario</td>
                        </tr>
                        <tr>
                           <td><%= bylink.getIdCuenta() %></td> 
                           <td><%= bylink.getCliente().getNombre() %></td> 
                       </tr>
                        <tr>
                            <td colspan="3"><footer><input class="buttom" type="submit" value="Vincular"></footer></td>
                        </tr>
                    </table>
                    <input type="hidden" name="idAccount" value="<%=credencials.get("idAccount")[0]%>">
                </form>
            <%}%>
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
        if(model.getAccountToLink() != null){
            credencials.put("idAccount", new String[]{Integer.toString(model.getAccountToLink().getIdCuenta())});
        }else{
            credencials.put("idAccount",new String[]{""});
        }
        return credencials;
    }
%>