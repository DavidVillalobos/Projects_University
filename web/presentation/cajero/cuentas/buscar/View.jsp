<%@page import="bank.logic.Moneda"%>
<%@page import="bank.logic.Cliente"%>
<%@page import="bank.presentation.cashier.accounts.search.Model"%>
<%@page import="java.util.List"%>
<%@page import="java.util.HashMap"%>
<%@page import="java.util.Map"%>
<%@page import="bank.logic.Cuenta"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>

<% Map<String, String> errors =(Map<String,String>) request.getAttribute("errors");
   Model model = (Model) request.getAttribute("model"); 
   List< Cuenta> cuentas = model.getAccounts();%>
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
            <form name="form"  action="/presentation/cashier/accounts/search/search" method="post">         
                <table id="search">
                    <td id="searchHeader" colspan="3">Buscador de Cuentas y Clientes</td>
                    <tr>
                        <td>Cedula</td>
                        <td><input class ="<%=verifyErrors("id",errors)%>" type="text" name="id" placeholder=" Cedula" 
                        title="<%=getTittle("id",errors)%>">
                        </td>
                    </tr>
                    <tr>
                        <td>N° Cuenta</td>
                        <td><input class ="<%=verifyErrors("idAccount",errors)%>" type="text" name="idAccount" placeholder=" Numero de Cuenta" 
                        title="<%=getTittle("idAccount",errors)%>"></td>
                    </tr>
                    <tr>
                        <td colspan="3"><footer><input class="buttom" type="submit" value="Buscar"></footer></td>
                    </tr>
                </table>
            </form>
            <table id="accounts">
                <tr class="cabecera"><td>Cedula Propietario</td><td>Nº Cuenta</td><td>Moneda</td><td>Saldo</td><td>Límite</td></tr>
                <%for(Cuenta c : cuentas){%>
                    <tr> 
                        <td><%= c.getCliente().getCedula() %></td>
                        <td>
                            <form action="/Banco_Nacional_PIV/presentation/client/account/show">
                                <input type="hidden" name="idCuentafld" value="<%=c.getIdCuenta()%>"> 
                                <button class="link-button"> <%= c.getIdCuenta() %> </button>
                            </form>
                        </td>  
                        <td><%= c.getMoneda() %></td>
                        <td><%= c.getSaldo()%></td>
                        <td><%= c.getLimite()%></td>
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
%>
