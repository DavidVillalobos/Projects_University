<%--
<%@page import="bank.logic.Usuario"%>
<% Usuario user = (Usuario) session.getAttribute("user"); %>
<header>
    <img src="/Banco_PIV/images/banco.png" alt="no-image">
    <a>Banco Nacional</a>
    <div class="menu">
        <ul> 
            <li>
                <a href="/Banco_PIV/presentation/Index.jsp">Home</a>
            </li>
            <% if(user==null){ %>
                <li><a href="/Banco_PIV/presentation/login/show">Login</a></li>         
            <% } %>
            <% if(user!=null){ %>
                <li><a href="/Banco_PIV/presentation/client/data/show">User: <%=user.getIdUsuario()%></a></li>
                <% if(!user.getTipo()){ %>
                 <li><a href="/Banco_PIV/presentation/cashier/manageaccounts/show">Manage Accounts</a></li>
                <%}%>
                <%if(user.getTipo()){ %>
                <li><a href="/Banco_PIV/presentation/client/accounts/show">Accounts</a></li>
                <li><a href="/Banco_PIV/presentation/client/accountsLinked/show">Cuentas Vinculadas</a></li>
                <%} %>
                <li><a href="/Banco_PIV/presentation/logout/show">Logout</a></li>
            <% } %>
            <li>
                <a href="/Banco_PIV/presentation/Index.jsp">About</a>
            </li>
        </ul>
    </div>
</header>
--%>

<%@page import="bank.logic.Usuario"%>
<% Usuario user = (Usuario) session.getAttribute("user"); %>
<header>
    <img src="/Banco_PIV/images/banco.png" alt="no-image">
    <a>Banco Nacional</a>
    <div class="menu">
        <ul> 
            <li>
                <a href="/Banco_PIV/presentation/Index.jsp">Principal</a>
            </li>
            <% if(user==null){ %>
                <li><a href="/Banco_PIV/presentation/login/show">Iniciar Sesion</a></li>         
            <% } %>
            <% if(user!=null){ %>
                <li><a href="/Banco_PIV/presentation/client/data/show">Usuario: <%=user.getIdUsuario()%></a></li>
                <% if(user.getTipo()){ %>
                    <li><a href="/Banco_PIV/presentation/cashier/accounts/open/show">Abrir Cuenta</a></li>
                    <li><a href="/Banco_PIV/presentation/cashier/accounts/search/show">Administrar Cuentas</a></li>
                <%}%>
                <%if(!user.getTipo()){ %>
                    <li><a href="/Banco_PIV/presentation/client/accounts/show">Mis Cuentas</a></li>
                    <li><a href="/Banco_PIV/presentation/client/accountsLinked/show">Cuentas Vinculadas</a></li>
                <%} %>
                <li><a href="/Banco_PIV/presentation/logout/show">Cerrar Sesion</a></li>
            <% } %>
            <li>
                <a href="/Banco_PIV/presentation/Index.jsp">Acerca de</a>
            </li>
        </ul>
    </div>
</header>
