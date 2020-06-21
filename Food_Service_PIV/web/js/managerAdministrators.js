
function loadAdministrators() {
    $.ajax({
        type: "GET",
        url: "/Food_Service_PIV/web/api/administradores",
        contentType: "application/json"
    }).then(
            (administrators) => {
        showAdministrators(administrators);
    },
            (error) => {
        errorMessage(error.status, $("#administrators"));
    }
    );
}

function showAdministrators(administrators){
    var list = $("#panel");
    list.html("");
    list.html('<div class="container-fluid rounded text-white" style="background-color: rgb(5, 5, 54);">' +
        '<div class="row py-1  align-items-center justify-content-center">'+
            '<div class="col-6 text-center " style="font-size: 60px;"> Administradores </div>'+
            '<div class="col-2 center-block">'+
                '<button type="button" class="btn btn-primary rounded-3" data-toggle="modal" data-target="#addDialog" onclick="aggregateAdministrators()">Nuevo Administrador</button>' +
            '</div>'+
        '</div>'+
    '</div>'+
    '<div class="card bg-light">'+
        '<div class="card-body text-center">'+
            '<div class="table-responsive " overflow: auto">'+
                '<table class="table table-striped table-hover" style="font-size: 22px;">'+
                    '<thead><tr><th scope="col">Usuario</th>'+
                    '<th scope="col">Nombre</th><th scope="col">Email</th>'+
                    '<th scope="col">Estado</th><th scope="col" style="width: 300px">'+
                    '<div class="form-inline">'+
                        '<div class="input-group flex-fill">'+
                            '<input id="filterByText" type="text" class="form-control" placeholder="Buscar por usuario o nombre ">'+
                            '<span class="input-group-prepend">'+
                            '<button class="btn btn-primary" onclick="searchAdminByFilter()">'+
                            '<i class="fa fa-search"></i>'+
                            '</button>'+
                            '</span>'+
                        '</div>'+
                    '</div>'+
                    '</th> '+
                    '<th scope="col"></th>'+
                    '<tbody id="listado">'+
                    '</tbody>'+
                '</table>'+
            '</div>'+         
        '</div>'+
    '</div>');
    var anchor = $('#listado');
    administrators.forEach((c) => {
        rowAdministrator(anchor, c);
    });
}

function rowAdministrator(anchor, c) {
    var tr = $("<tr />");
    tr.html('<td>' + c.userName + '</td>' +
            '<td>' + c.name + '</td>' +
            '<td>' + c.email + '</td>' +
            '<td style="width: 160px;"><button type="button" style="width: 130px;" class=" btn btn-' + statusAdmin(c.administratorStatus.name) + '">' + c.administratorStatus.name + '</button>' +
            '</td>' +
            '<td style="width: 160px;"><button type="button" class="btn btn-secondary" data-toggle="modal" data-target="#editDialog" onclick="searchAdministrator('+ c.id +')">Ver / Editar</button>' +
            '</td>' +
            '</tr>');
    anchor.append(tr);
}

function statusAdmin(status){
    switch(status){
        case 'Conectado': return 'success'; break;
        case 'Desconectado': return 'danger'; break;
        case 'Vuelvo pronto': return 'warning'; break;
    }
    return "";
}

function searchAdministrator(id){
    $.ajax({
        type: "GET",
        url: "/Food_Service_PIV/web/api/administradores/" + id,
        contentType: "application/json"
    }).then(
        (administrator) => { editAdministrator(administrator);
        },(error) => {
            errorMessage(error.status, $("#administrators"));
        }
    );
}

function editAdministrator(administrator){
    var anchor = $('#listado');
    var html = '<div class="form-row">'+
            '<div class="modal" id="editDialog">'+
                '<div class="modal-dialog">'+
                '<div class="modal-content">'+
                    '<form>'+
                        '<div class="modal-body text-center">'+
                            '<span class="display-4">Editar Administrador</span>'+
                            '<br><br>'+
                            '<div class = "input-group" style = "margin-bottom: 25px">'+
                                '<div class = "input-group-prepend "><span class = "input-group-text"><i>Usuario</i></span></div>'+
                                    '<input class = "form-control" placeholder = "Usuario" type = "text" id = "userName" name="userName" value="'+administrator.userName+'" required>'+
                                '<div class = "invalid-feedback">Favor ingrese el usuario del administrador</div>'+
                            '</div>'+
                            '<div class = "input-group" style = "margin-bottom: 25px">'+
                                '<div class = "input-group-prepend "><span class = "input-group-text"><i>Nombre</i></span></div>'+
                                    '<input class = "form-control" placeholder = "Nombre" type = "text" id = "name" name="name" value="'+administrator.name+'" required>'+
                                '<div class = "invalid-feedback">Favor ingrese el nombre del administrador</div>'+
                            '</div>'+
                            '<div class = "input-group" style = "margin-bottom: 25px">'+
                                '<div class = "input-group-prepend "><span class = "input-group-text"><i>Email</i></span></div>'+
                                    '<input class = "form-control" placeholder = "Email" type = "text" id = "email" name="email" value="'+administrator.email+'" required>'+
                                '<div class = "invalid-feedback">Favor ingrese el email del administrador</div>'+
                            '</div>'+
                            '<div class = "input-group" style = "margin-bottom: 25px">'+
                                '<div class = "input-group-prepend "><span class = "input-group-text"><i>Estado</i></span></div>'+
                                '<div class="dropdown show">'+
                                    '<a class="btn btn-secondary dropdown-toggle bg-'+ statusAdmin(administrator.administratorStatus.name) +'" style="color:black" role="button" '+
                                    'id="dropdownMenuButton" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false"> ' + administrator.administratorStatus.name + ' </a>'+
                                    '<div class="dropdown-menu" aria-labelledby="dropdownMenuButton" id="statusAdmin">'+
                                    '</div>'+
                                '</div>'+
                            '</div>'+
                        '</div>'+
                        '<div class="modal-footer d-flex justify-content-center">'+
                            '<div>'+
                             ' <button type="button" class="btn btn-secondary" style="margin-right: 30px;" data-dismiss="modal" onclick="loadAdministrators()">Cancelar</button>'+
                                '<button type="button" class="btn btn-primary" data-dismiss="modal" onclick="updateAdministrator('+administrator.id+')">Actualizar</button>'+
                            '</div>'+
                        '</div>'+
                        '<div id="loginErrorDiv" style="width:80%; margin: auto;"></div> '+    
                    '</form>'+
                '</div>'+
            '</div>'+
        '</div>'+
    '</div> ';
    anchor.append(html);
    loadStatusAdmin();
}

function loadStatusAdmin(){
    $.ajax({
        type: "GET",
        url: "/Food_Service_PIV/web/api/statusadministrators",
        contentType: "application/json"
    }).then(
        (status) => {
            var list = $("#statusAdmin");
            list.html("");
            status.forEach((state) => {
                list.append('<a class="dropdown-item btn-secondary bg-'+ statusAdmin(state.name) +'">'+state.name+'</a>');
            });
            $('#dropdownMenuButton + [aria-labelledby="dropdownMenuButton"] a').on('click', function () {
                $("#dropdownMenuButton").html(this.textContent);
            });
        },
        (error) => {
            errorMessage(error.status, $("#statusadministrators"));
        }
    );
}

function aggregateAdministrators(){
    var anchor = $('#listado');
    var html = '<div class="form-row">'+
            '<div class="modal" id="addDialog">'+
                '<div class="modal-dialog">'+
                '<div class="modal-content">'+
                    '<form>'+
                        '<div class="modal-body text-center">'+
                            '<span class="display-4">Agregar Administrador</span>'+
                            '<br><br>'+
                            '<div class = "input-group" style = "margin-bottom: 25px">'+
                                '<div class = "input-group-prepend "><span class = "input-group-text"><i class=" fa fa-user"></i></span></div>'+
                                    '<input class = "form-control" placeholder = "Usuario" type = "text" id = "userName" name="userName" value="" required>'+
                                '<div class = "invalid-feedback">Favor ingrese el usuario del administrador</div>'+
                            '</div>'+
                            '<div class = "input-group" style = "margin-bottom: 25px">'+
                                '<div class = "input-group-prepend "><span class = "input-group-text"><i class=" fa fa-lock"></i></span></div>'+
                                    '<input class = "form-control" placeholder = "Contraseña" type = "text" id = "password" name="password" value="" required>'+
                                '<div class = "invalid-feedback">Favor ingrese la contraseña del administrador</div>'+
                            '</div>'+
                            '<div class = "input-group" style = "margin-bottom: 25px">'+
                                '<div class = "input-group-prepend "><span class = "input-group-text"><i>Nombre</i></span></div>'+
                                    '<input class = "form-control" placeholder = "Nombre" type = "text" id = "name" name="name" value="" required>'+
                                '<div class = "invalid-feedback">Favor ingrese el nombre del administrador</div>'+
                            '</div>'+
                            '<div class = "input-group" style = "margin-bottom: 25px">'+
                                '<div class = "input-group-prepend "><span class = "input-group-text"><i>Email</i></span></div>'+
                                    '<input class = "form-control" placeholder = "Email" type = "text" id = "email" name="email" value="" required>'+
                                '<div class = "invalid-feedback">Favor ingrese el email del administrador</div>'+
                            '</div>'+
                            '<div class = "input-group" style = "margin-bottom: 25px">'+
                                '<div class = "input-group-prepend "><span class = "input-group-text"><i>Estado</i></span></div>'+
                                '<div class="dropdown show">'+
                                    '<a class="btn btn-secondary dropdown-toggle" style="color:black" role="button" '+
                                    'id="dropdownMenuButton" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false"> Elige un estado </a>'+
                                    '<div class="dropdown-menu" aria-labelledby="dropdownMenuButton" id="statusAdmin">'+
                                    '</div>'+
                                '</div>'+
                            '</div>'+
                        '</div>'+
                        '<div class="modal-footer d-flex justify-content-center">'+
                            '<div>'+
                             ' <button type="button" class="btn btn-secondary" style="margin-right: 30px;" data-dismiss="modal" onclick="loadAdministrators()">Cancelar</button>'+
                                '<button type="button" class="btn btn-primary" data-dismiss="modal" onclick="addAdministrator()">Agregar</button>'+
                            '</div>'+
                        '</div>'+
                        '<div id="loginErrorDiv" style="width:80%; margin: auto;"></div> '+    
                    '</form>'+
                '</div>'+
            '</div>'+
        '</div>'+
    '</div> ';
    anchor.append(html);
    loadStatusAdmin();
}
        
function searchAdminByFilter(){
    $.ajax({
        type: "GET",
        url: "/Food_Service_PIV/web/api/administradores",
        contentType: "application/json"
    }).then(
            (administrators) => {
        showAdministrators( administrators.filter(administrator => filtrarAdministrador(administrator)));
    },
            (error) => {
        errorMessage(error.status, $("#administradores"));
    }
    );
}

function filtrarAdministrador(administrator){
    text = String($("#filterByText").val()).toUpperCase();
    n1 = String(administrator.name).toUpperCase();
    n2 = String(administrator.userName).toUpperCase();
    return n1.includes(text) || n2.includes(text);
}

function updateAdministrator(administratorId){
  $.ajax({
        type: "GET",
        url: "/Food_Service_PIV/web/api/statusadministrators",
        contentType: "application/json"
    }).then(
        (status) => {
            var stateAdmin = undefined;
            status.forEach((state) => {
                if(state.name === $("#dropdownMenuButton").html()){
                    stateAdmin = state; 
                }
            });
            administrator = {id: administratorId, 
              userName: $("#userName").val(),
              name: $("#name").val(),
              email: $("#email").val(),
              administratorStatus: stateAdmin
            };
            $.ajax({type: "PUT", url:"/Food_Service_PIV/web/api/administradores",
                        data: JSON.stringify(administrator),contentType: "application/json"})
              .then( (administrators)=>{$('#editDialog').modal('hide'); showAdministrators(administrators); },
                     (error)=>{errorMessage(error.status,$("#addErrorDiv"));});   
                },
        (error) => {
            errorMessage(error.status, $("#statusadministrators"));
        }
    );   
}

function addAdministrator(){ 
    $.ajax({
        type: "GET",
        url: "/Food_Service_PIV/web/api/statusadministrators",
        contentType: "application/json"
    }).then(
        (status) => {
            var stateAdmin = undefined;
            status.forEach((state) => {
                if(state.name === $("#dropdownMenuButton").html()){
                    stateAdmin = state; 
                }
            });
            administrator = {
                userName: $("#userName").val(),
                password: $("#password").val(),
                name: $("#name").val(),
                email: $("#email").val(),
                administratorStatus: stateAdmin
            };
            $.ajax({type: "POST", url:"/Food_Service_PIV/web/api/administradores",
                data: JSON.stringify(administrator),contentType: "application/json"})
            .then( (administrators)=>{$('#addDialog').modal('hide'); showAdministrators(administrators); },
                (error)=>{errorMessage(error.status,$("#addErrorDiv"));});       
        },
        (error) => {
            errorMessage(error.status, $("#statusadministrators"));
        }
    );                   
}
