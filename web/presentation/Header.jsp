<%@page import="bank.logic.Usuario"%>
<% Usuario user = (Usuario) session.getAttribute("user"); %>
<header>
    <img src="/Banco_PIV/images/banco.png" alt="no-image">
    <a>Banco Estatal</a>
    <div class="menu">
        <ul class="nav"> 
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
                    <li><a href="">Movimientos</a>
                    <ul>
			<li><a href="/Banco_PIV/presentation/cashier/movements/d_wd/show">Deposito o Retiro</a></li>
			<li><a href="/Banco_PIV/presentation/cashier/movements/transfer/show">Tranferencia</a></li>
                    </ul>
                    </li>
                    <li>
                        <a href="/Banco_PIV/presentation/cashier/accounts/interests/show">Acreditar Intereses</a>
                    </li>
                <%}%>
                <%if(!user.getTipo()){ %>
                    <li><a href="/Banco_PIV/presentation/client/accounts/show">Mis Cuentas</a></li>
                    <li><a href="/Banco_PIV/presentation/client/accountsLinked/show">Cuentas Vinculadas</a></li>
                    <li><a href="/Banco_PIV/presentation/client/transfers/show">Transferencias</a></li>
                <%} %>
                <li><a href="/Banco_PIV/presentation/logout/show">Cerrar Sesion</a></li>
            <% } %>
        </ul>
    </div>
</header>
