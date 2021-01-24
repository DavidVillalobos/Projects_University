
function loadOrders() {
    $.ajax({
        type: "GET",
        url: "/Food_Service_PIV/web/api/orders",
        contentType: "application/json"
    }).then(
            (orders) => {
        showOrders(orders);
    },
            (error) => {
        errorMessage(error.status, $("#orders"));
    }
    );
}

function showOrders(orders){
    var list = $("#panel");
    list.html("");
    list.html('<div class="container-fluid rounded text-white" style="background-color: rgb(5, 5, 54);">' +
        '<div class="row py-1  align-items-center justify-content-center">'+
            '<div class="col-6 text-center " style="font-size: 60px;"> Ordenes </div>'+
        '</div>'+
    '</div>'+
    '<div class="card bg-light">'+
        '<div class="card-body text-center">'+
            '<div class="table-responsive " overflow: auto">'+
                '<table class="table table-striped table-hover" style="font-size: 22px;">'+
                    '<thead><tr><th scope="col">Id</th>'+
                    '<th scope="col">Cliente</th><th scope="col">Tipo</th>'+
                    '<th scope="col">Hora de Orden</th><th scope="col">Fecha de Orden</th>'+
                    '<th scope="col">Estado</th><th scope="col">Total</th><th scope="col" colspan="2" style="width: 240px">'+
                    '<div class="form-inline">'+
                        '<div class="input-group flex-fill">'+
                            '<input id="filterByText" type="text" class="form-control" placeholder="Buscar por cliente">'+
                            '<span class="input-group-prepend">'+
                            '<button class="btn btn-primary" onclick="searchOrderByFilter()">'+
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
    orders.forEach((c) => {
        rowOrder(anchor, c);
    });
}

function rowOrder(anchor, c) {
    var tr = $("<tr />");
    tr.html('<td>' + c.id + '</td>' +
            '<td>' + c.clients.name + '</td>' +
            '<td>' + c.type + '</td>' +
            '<td>' + new Date(c.orderDate).toLocaleTimeString() + '</td>' +
            '<td>' + new Date(c.orderDate).toLocaleDateString() + '</td>' +
            '<td style="width: 160px;"><button type="button" style="width: 130px;" class=" btn btn-' + statusOrder(c.orderStatus.name) + '">' + c.orderStatus.name + '</button>' +
            '</td>' +
            '<td>' + c.total + '</td>' +
            '<td style="width: 160px;"><button type="button" class="btn btn-secondary" data-toggle="modal" data-target="#editDialog" onclick="searchOrder('+ c.id +')">Visualizar</button>' +
            '<td style="width: 160px;"><button type="button" class="btn btn-secondary" onclick="deleteOrder('+ c.id +')">Eliminar</button>' +
            '</td>' +
            '</tr>');
    anchor.append(tr);
}

function statusOrder(status){
    switch(status){
        case 'Cancelada': return 'danger'; break;
        case 'Completada': return 'success'; break;
        case 'En preparacion': return 'secondary'; break;
        case 'Entregada': return 'primary'; break;
        case 'Pendiente': return 'warning'; break;
        case 'Recibida': return 'primary'; break;
    }
    return "";
}

function searchOrder(id){
    $.ajax({
        type: "GET",
        url: "/Food_Service_PIV/web/api/orders/" + id,
        contentType: "application/json"
    }).then(
        (administrator) => { editOrder(administrator);
        },(error) => {
            errorMessage(error.status, $("#orders"));
        }
    );
}

function editOrder(administrator){
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
                             ' <button type="button" class="btn btn-secondary" style="margin-right: 30px;" data-dismiss="modal" onclick="loadOrders()">Cancelar</button>'+
                                '<button type="button" class="btn btn-primary" data-dismiss="modal" onclick="updateOrder('+administrator.id+')">Actualizar</button>'+
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
        url: "/Food_Service_PIV/web/api/statusorders",
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
            errorMessage(error.status, $("#statusorders"));
        }
    );
}
  
function searchOrderByFilter(){
    $.ajax({
        type: "GET",
        url: "/Food_Service_PIV/web/api/orders",
        contentType: "application/json"
    }).then(
            (orders) => {
        showOrders( orders.filter(order => filtrarOrden(order)));
    },
            (error) => {
        errorMessage(error.status, $("#ordenes"));
    }
    );
}

function filtrarOrden(order){
    text = String($("#filterByText").val()).toUpperCase();
    n1 = String(order.clients.name).toUpperCase();
    n2 = String(order.id);
    n3 = String(order.orderStatus.name).toUpperCase();
    return n1.includes(text) || n2.includes(text) || n3.includes(text);
}

function updateOrder(administratorId){
  $.ajax({
        type: "GET",
        url: "/Food_Service_PIV/web/api/statusorders",
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
              .then( (orders)=>{$('#editDialog').modal('hide'); showOrders(orders); },
                     (error)=>{errorMessage(error.status,$("#addErrorDiv"));});   
                },
        (error) => {
            errorMessage(error.status, $("#statusorders"));
        }
    );   
}

function addOrder(){ 
    $.ajax({
        type: "GET",
        url: "/Food_Service_PIV/web/api/statusorders",
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
            .then( (orders)=>{$('#addDialog').modal('hide'); showOrders(orders); },
                (error)=>{errorMessage(error.status,$("#addErrorDiv"));});       
        },
        (error) => {
            errorMessage(error.status, $("#statusorders"));
        }
    );                   
}
