<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <%@ include file="presentation/Head.jsp" %>
        <title>Food Service</title> 
    </head>
    <%@ include file="presentation/Header.jsp" %>   
    <body> 
        <!-- LOGIN ADMINISTRATORS -->            
        <div class="row">
            <div class="modal fade" id="loginDialog" tabindex="-1" role="dialog">
                <div class="modal-dialog" style="width: 400px">
                    <div class="modal-content">
                        <form id="loginForm">
                            <div class="modal-body text-center">
                                <div id="div-login-msg">
                                    <div id="icon-login-msg" ></div>
                                    <span class="h1">Panel de Administradores</span>
                                </div>
                                <br>
                                <div class="input-group" style="margin-bottom: 25px">
                                    <div class="input-group-prepend "><span class="input-group-text"><i class="fa fa-user"></i></span></div>
                                    <input class="form-control" placeholder="Usuario" type="text" id="usuario" name="usuario" value="" required>
                                    <div class="invalid-feedback">Favor ingrese el usuario</div>
                                </div>
                                <div class="input-group" style="margin-bottom: 25px">
                                    <div class="input-group-prepend"><span class="input-group-text"><i class="fa fa-lock"></i></span></div>
                                    <input class="form-control" placeholder="Contraseña" type="password" id="contrasena" name="contrasena" value="" required>
                                    <div class="invalid-feedback">Favor ingrese la contraseña</div>
                                </div>                     
                            </div>
                            <div class="modal-footer d-flex justify-content-center">
                                <div>
                                    <button type="button" id="loginButton" class="btn btn-primary btn-lg btn-block">Ingresar</button>
                                </div>
                            </div>
                            <div id="loginErrorDiv" style="width:80%; margin: auto;"></div>     
                        </form>
                    </div>
                </div>
            </div>
        </div> 
        <div class="container-fluid bg-light p-3">
            <div class="text-center">
                <div class="display-1 text-black">Food Service</div>
            </div>
        </div>
        <div class="container-fluid text-center bg-dark">
            <div class="row text-white alto justify-content-center">
                <div class="col-4 pt-5">
                    <button class="navbar-toggler" type="button"> 
                        <a class="display-4 text-white" href="/Food_Service_PIV/web/presentation/client/order.html">Storefront</a>
                    </button>
                    <span class="navbar-toggler-icon"> <img id="icono" src="images/icon.png"></span>
                </div>  
                <div class="col-4 pt-5">
                    <span class="navbar-toggler-icon"> <img id="icono2" src="images/icon2.png"></span>
                    <button class="navbar-toggler button-Admin-Panel" type="button">
                        <div id="login_div">
                            <a class="display-4 text-white pt-2" data-toggle="modal" data-target="#loginDialog">Administrator Panel</a>
                        </div> 
                    </button>
                </div>
                <div id="categories"></div>
            </div>
        </div>
    </body>
    <%@ include file="presentation/Footer.jsp" %> 
    <script>
        function loaded() {
            $("#loginButton").click(login);
        }
        $(loaded);

        function login() {
            if (!loginValidar())
                return;
            admin = {
                userName: $("#usuario").val(),
                password: $("#contrasena").val()
            };
            $.ajax({type: "POST",
                url: "api/loginAdmin",
                data: JSON.stringify(admin),
                contentType: "application/json"
            }).then((admin) => {
                loginSuccess(admin);
            },
            (error) => {
                errorMessage(error.status, $("#loginErrorDiv"));
            });
        }

        function loginValidar() {
            $("#loginForm").addClass("was-validated");
            return $("#loginForm").get(0).checkValidity();
        }

        function loginSuccess(admin) {
            $('#loginDialog').modal('hide');
            $("#login_div").toggle("hide");
            $("#logout_div").toggle("hide");
        }

        function errorMessage(status, place) {
            error = status;
            switch (status){
                case 401:
                    error = "Administrador no registrado";
                    break;
                case 403:
                case 405:
                    error = "Administrador no autorizado";
                    break;
                case 404:
                    error = "Registro no encontrado";
                    break;
            }
            ;
            place.html('<div class="alert alert-danger fade show">' +
                    '<button type="button" class="close" data-dismiss="alert">' +
                    '&times;</button><h4 class="alert-heading">Error!</h4>' + error + '</div>');
            return;
        }
    </script>
</html>