function loaded() {
    $("#loginButton").click(login);
}
$(loaded);

function showPassword(){
        var cambio = document.getElementById("contrasena");
        if(cambio.type == "password"){
            cambio.type = "text";
            $('.icon').removeClass('fa fa-eye-slash').addClass('fa fa-eye');
        }else{
            cambio.type = "password";
            $('.icon').removeClass('fa fa-eye').addClass('fa fa-eye-slash');
        }
} 

function login() {
    if (!loginValidar())
        return;
    admin = {
        userName: $("#usuario").val(),
        password: $("#contrasena").val()
    };
    $.ajax({type: "POST",
        url: "/Food_Service_PIV/web/api/loginAdmin",
        data: JSON.stringify(admin),
        contentType: "application/json"
    }).then((admin) => {
        loginSuccess();
    },
    (error) => {
        errorMessage(error.status, $("#loginErrorDiv"));
    });
}

function loginValidar() {
    $("#loginForm").addClass("was-validated");
    return $("#loginForm").get(0).checkValidity();
}



function loginSuccess(){
    location.href="/Food_Service_PIV/web/presentation/admin/manager.html";
}

function logout(){
    $.ajax({type: "DELETE", 
        url:"/Food_Service_PIV/web/api/loginAdmin"               
    })
    .then( ()=>{logoutSuccess();},
        (error)=>{ errorMessage(error.status,$("#loginErrorDiv"));});                
}

function logoutSuccess() {
    location.href="/Food_Service_PIV/web/Index.html";
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
            error = "Usuario o Contraseña Incorrecta";
            break;
    };
    place.html('<div class="alert alert-danger fade show">' +
            '<button type="button" class="close" data-dismiss="alert">' +
            '&times;</button><h4 class="alert-heading">Error!</h4>' + error + '</div>');
    return;
}

function startOrder(){
    location.href="/Food_Service_PIV/web/presentation/client/order.html"
}