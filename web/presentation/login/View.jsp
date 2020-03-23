<%@page import="java.util.HashMap"%>
<%@page import="bank.presentation.login.Model"%>
<%@page import="java.util.Map"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>

<% Map<String, String> errors =(Map<String,String>) request.getAttribute("errors"); %>
<% Model model = (Model) request.getAttribute("model"); %>
<% Map<String, String[]> credencials = (errors!=null)?request.getParameterMap():getCredencials(model); %>
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
            <form name="form" action="/Banco_PIV/presentation/login/login" method="post">
            <div class="login">
                <header>Iniciar Sesion</header>
                <img src="/Banco_PIV/images/icon-account.png" alt="no-image">
                <input class ="<%=verifyErrors("user-name",errors)%>" type="text" name="user-name" placeholder=" Usuario" 
                       value="<%=credencials.get("user-name")[0]%>" title="<%=getTittle("user-name",errors)%>"><br>
                <img src="/Banco_PIV/images/icon-password.png" alt="no-image"> 
                <input class="<%=verifyErrors("password",errors)%>" type="password" name="password" placeholder=" Contraseña" 
                       value="<%=credencials.get("password")[0]%>" title="<%=getTittle("password",errors)%>">
                <footer><input class="buttom" type="submit" value="Iniciar"></footer>
            </div>
            </form>
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
        credencials.put("user-name", new String[]{model.getUser().getIdUsuario()});
        credencials.put("password", new String[]{model.getUser().getPassword()});
        return credencials;
    }
%>
