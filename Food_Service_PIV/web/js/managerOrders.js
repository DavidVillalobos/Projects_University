
function loadOrders() {
    $.ajax({
        type: "GET",
        url: "/Food_Service_PIV/web/api/clientes",
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
            '<div class="col-6 text-center " style="font-size: 60px;"> Clientes </div>'+
        '</div>'+
    '</div>'+
    '<div class="card bg-light">'+
        '<div class="card-body text-center">'+
            '<div class="table-responsive " overflow: auto">'+
                '<table class="table table-striped table-hover" style="font-size: 22px;">'+
                    '<thead><tr><th scope="col">Nombre</th>'+
                    '<th scope="col">Apellido</th><th scope="col">Telefono</th>'+
                    '<th scope="col">Email</th><th scope="col" style="width: 300px">'+
                    '<div class="form-inline">'+
                        '<div class="input-group flex-fill">'+
                            '<input id="filterByText" type="text" class="form-control" placeholder="Buscar por nombre o apellido">'+
                            '<span class="input-group-prepend">'+
                            '<button class="btn btn-primary" onclick="searchClientByFilter()">'+
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
        rowClient(anchor, c);
    });
}

function rowClient(anchor, c) {
    var tr =$("<tr />");
    tr.html('<td>' + c.name + '</td>' +
            '<td>' + c.lastName + '</td>' +
            '<td>' + c.telephone + '</td>' +
            '<td>' + c.email + '</td>' +
            '<td style="width: 160px;">' +
            '<button type="button" class="btn btn-danger" onclick="deleteClient('+ c.id +')">Eliminar</button>' +
            '</td>' +  
            '</tr>');
    anchor.append(tr);
}

function searchClientByFilter(){
    $.ajax({
        type: "GET",
        url: "/Food_Service_PIV/web/api/clientes",
        contentType: "application/json"
    }).then(
            (orders) => {
        showOrders( orders.filter(client => filtrarCliente(client)));
    },
            (error) => {
        errorMessage(error.status, $("#orders"));
    }
    );
}

function filtrarCliente(client){
    text = String($("#filterByText").val()).toUpperCase();
    n1 = String(client.name).toUpperCase();
    n2 = String(client.lastName).toUpperCase();
    return (n1.includes(text) || n2.includes(text));
}

function deleteClient(id){
    $.ajax({
        type: "DELETE",
        url: "/Food_Service_PIV/web/api/clientes/" + id,
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
