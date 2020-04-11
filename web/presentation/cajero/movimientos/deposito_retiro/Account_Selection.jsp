<%@page import="bank.logic.Cliente"%>
<%@page import="bank.presentation.cashier.movements.deposit_withdrawal.Model"%>
<%@page import="java.util.List"%>
<%@page import="java.util.HashMap"%>
<%@page import="java.util.Map"%>
<%@page import="bank.logic.Cuenta"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>

<% Model model = (Model) request.getAttribute("model");
   Map<String, String> errors =(Map<String,String>) request.getAttribute("errors");
   Map<String, String[]> credencials = (errors!=null)?request.getParameterMap():getCredencials(model);
   List< Cuenta> cuentas = model.getAccounts();
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
            <form name="form"  action="/Banco_PIV/presentation/cashier/movements/d_wd/search" method="post">         
                <table class="search-cashier">
                    <td id="Header" colspan="3">Buscador de Cuentas y Clientes</td>
                    <tr>
                        <td>Cedula</td>
                        <td><input class ="<%=verifyErrors("id",errors)%>" type="text" name="id" placeholder=" Cedula" 
                                   value="<%=credencials.get("id")[0]%>" title="<%=getTittle("id",errors)%>">
                        </td>
                    </tr>
                    <tr>
                        <td>N° Cuenta</td>
                        <td><input class ="<%=verifyErrors("idAccount",errors)%>" type="text" name="idAccount" placeholder=" Numero de Cuenta" 
                                   value="<%=credencials.get("idAccount")[0]%>"title="<%=getTittle("idAccount",errors)%>"></td>
                    </tr>
                    <tr>
                        <td colspan="3"><footer><input class="buttom" type="submit" value="Buscar"></footer></td>
                    </tr>
                </table>
            </form>
            <table class="search-cashier-accounts">
                <tr class="cabecera"><td>Nº Cuenta</td><td>Propietario</td></tr>
                <%for(Cuenta c : cuentas){%>
                    <tr> 
                        <td>
                            <form action="/Banco_PIV/presentation/cashier/movements/d_wd/movementShow">
                                <input type="hidden" name="idCuentafld" value="<%=c.getIdCuenta()%>"> 
                                <button class="link-button"> <%= c.getIdCuenta() %> </button>
                            </form>
                        </td>  
                        <td><%= c.getCliente().getNombre() %></td>
                    </tr>
                <%}%>
            </table>
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
        credencials.put("idAccount", new String[]{
            (model.getAccount_num() == null)?"":model.getAccount_num()
        });
        credencials.put("id", new String[]{
            (model.getId_cliente() == null)?"":model.getId_cliente()
        });
        return credencials;
    }
%>