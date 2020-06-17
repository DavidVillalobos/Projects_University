
function loadDishes() {
    $.ajax({
        type: "GET",
        url: "/Food_Service_PIV/web/api/dishes",
        contentType: "application/json"
    }).then(
            (dishes) => {
        showDishes(dishes);
    },
            (error) => {
        errorMessage(error.status, $("#dishes"));
    }
    );
}

function showDishes(dishes){
    var list = $("#panel");
    list.html("");
    list.html('<div class="container-fluid rounded text-white" style="background-color: rgb(5, 5, 54);">' +
        '<div class="row py-1  align-items-center justify-content-center">'+
            '<div class="col-6 text-center " style="font-size: 60px;"> Menu </div>'+
            '<div class="col-2 center-block">'+
                '<button type="button" class="btn btn-primary btn-lg btn-block bg-success rounded-3 border-success" data-toggle="modal" data-target="#addDialog" onclick="aggregateDish()">Agregar</button>' +
            '</div>'+
        '</div>'+
    '</div>'+
    '<div class="card bg-light">'+
        '<div class="card-body text-center">'+
            '<div class="table-responsive " overflow: auto">'+
                '<table class="table table-striped table-hover" style="font-size: 22px;">'+
                    '<thead><tr><th scope="col">Categoria</th>'+
                    '<th scope="col">Nombre</th><th scope="col">Precio</th>'+
                    '<th colspan="2" scope="col"></th> '+
                    '<tbody id="listado">'+
                    '</tbody>'+
                '</table>'+
            '</div>'+         
        '</div>'+
    '</div>');
    var anchor = $('#listado');
    dishes.forEach((c) => {
        rowDish(anchor, c);
    });
}

function rowDish(anchor, c) {
    var tr =$("<tr />");
    tr.html('<td>' + c.categories.name + '</td>' +
            '<td>' + c.name + '</td>' +
            '<td>' + c.price + '</td>' +
            '<td><button type="button" class="btn btn-primary btn-lg btn-block" style="width: 150px;" data-toggle="modal" data-target="#editDialog" onclick="searchDish('+ c.id +')">Ver / Editar</button>' +
            '</td>' +
            '<td>' +
            '<button type="button" class="btn btn-primary btn-lg btn-block bg-danger border-danger" style="width: 150px;" onclick="deleteDish('+ c.id +')">Eliminar</button>' +
            '</td>' +  
            '</tr>');
    anchor.append(tr);
}

function searchDish(id){
    $.ajax({
        type: "GET",
        url: "/Food_Service_PIV/web/api/dishes/" + id,
        contentType: "application/json"
    }).then(
        (dish) => { editDish(dish);
        },(error) => {
            errorMessage(error.status, $("#dishes"));
        }
    );
}

function editDish(dish){
    var anchor = $('#listado');
    var html = '<div class="form-row">'+
            '<div class="modal" id="editDialog">'+
                '<div class="modal-dialog">'+
                '<div class="modal-content">'+
                    '<form>'+
                        '<div class="modal-body text-center">'+
                                '<div></div>'+
                                '<span class="display-4">' + dish.categories.name + '<br>' + dish.name + '</span>'+
                            '<br><br>'+
                            '<div class = "input-group" style = "margin-bottom: 25px">'+
                                '<div class = "input-group-prepend "><span class = "input-group-text"><i>Nombre</i></span></div>'+
                                    '<input class = "form-control" placeholder = "Nombre" type = "text" id = "name" name="name" value="'+dish.name+'" required>'+
                                '<div class = "invalid-feedback">Favor ingrese el nombre del platillo</div>'+
                            '</div>'+
                            '<div class = "input-group" style = "margin-bottom: 25px">'+
                                '<div class = "input-group-prepend "><span class = "input-group-text"><i>Precio</i></span></div>'+
                                    '<input class = "form-control" placeholder = "Precio" type = "text" id = "price" name="price" value="'+dish.price+'" required>'+
                                '<div class = "invalid-feedback">Favor ingrese el precio del platillo</div>'+
                            '</div>'+
                            '<div class = "input-group" style = "margin-bottom: 25px">'+
                                '<div class = "input-group-prepend "><span class = "input-group-text"><i>Descripción</i></span></div>'+
                                    '<textarea class = "form-control" placeholder = "Descripción" type = "text" id = "decription" name="decription" required>'+dish.decription+'</textarea>'+
                                '<div class = "invalid-feedback">Favor ingrese el precio del platillo</div>'+
                            '</div>'+

                        '</div>'+
                        '<div class="modal-footer d-flex justify-content-center">'+
                            '<div>'+
                             ' <button type="button" class="btn btn-secondary" style="margin-right: 30px;" data-dismiss="modal" onclick="loadDishes()">Cancelar</button>'+
                                '<button type="button" class="btn btn-primary" data-dismiss="modal" onclick="updateDish('+dish.id+')">Actualizar</button>'+
                            '</div>'+
                        '</div>'+
                        '<div id="loginErrorDiv" style="width:80%; margin: auto;"></div> '+    
                    '</form>'+
                '</div>'+
            '</div>'+
        '</div>'+
    '</div> '
    anchor.append(html);
}

function aggregateDish(){
    var anchor = $('#listado');
    var html = '<div class="form-row">'+
            '<div class="modal" id="addDialog">'+
                '<div class="modal-dialog">'+
                '<div class="modal-content">'+
                    '<form>'+
                        '<div class="modal-body text-center">'+
                                '<div></div>'+
                                '<span class="display-4">Agregar un<br>Platillo</span>'+
                            '<br><br>'+
                            '<div class = "input-group" style = "margin-bottom: 25px">'+
                                '<div class = "input-group-prepend "><span class = "input-group-text"><i>Nombre</i></span></div>'+
                                    '<input class = "form-control" placeholder = "Nombre" type = "text" id = "name" name="name" value="" required>'+
                                '<div class = "invalid-feedback">Favor ingrese el nombre del platillo</div>'+
                            '</div>'+
                            '<div class = "input-group" style = "margin-bottom: 25px">'+
                                '<div class = "input-group-prepend "><span class = "input-group-text"><i>Precio</i></span></div>'+
                                    '<input class = "form-control" placeholder = "Precio" type = "text" id = "price" name="price" value="" required>'+
                                '<div class = "invalid-feedback">Favor ingrese el precio del platillo</div>'+
                            '</div>'+
                            '<div class = "input-group" style = "margin-bottom: 25px">'+
                                '<div class = "input-group-prepend "><span class = "input-group-text"><i>Descripción</i></span></div>'+
                                    '<textarea class = "form-control" placeholder = "Descripción" type = "text" id = "decription" name="decription" required></textarea>'+
                                '<div class = "invalid-feedback">Favor ingrese el precio del platillo</div>'+
                            '</div>'+

                        '</div>'+
                        '<div class="modal-footer d-flex justify-content-center">'+
                            '<div>'+
                             ' <button type="button" class="btn btn-secondary" style="margin-right: 30px;" data-dismiss="modal">Cancelar</button>'+
                                '<button type="button" class="btn btn-primary" data-dismiss="modal" onclick="addDish()">Agregar</button>'+
                            '</div>'+
                        '</div>'+
                        '<div id="loginErrorDiv" style="width:80%; margin: auto;"></div> '+    
                    '</form>'+
                '</div>'+
            '</div>'+
        '</div>'+
    '</div> '
    anchor.append(html);
}

function deleteDish(id){
    $.ajax({
        type: "DELETE",
        url: "/Food_Service_PIV/web/api/dishes/" + id,
        contentType: "application/json"
    }).then(
            (dishes) => {
        showDishes(dishes);
    },
            (error) => {
        errorMessage(error.status, $("#dishes"));
    }
    );
}

function updateDish(dishId){ 
  dish = {id: dishId, 
    name: $("#name").val(),      
    price: $("#price").val(),
    decription: $("#decription").val()};
  $.ajax({type: "PUT", url:"/Food_Service_PIV/web/api/dishes",
              data: JSON.stringify(dish),contentType: "application/json"})
    .then( (dishes)=>{$('#editDialog').modal('hide'); showDishes(dishes); },
           (error)=>{errorMessage(error.status,$("#addErrorDiv"));});                          
}

function addDish(){ 
    dish = {"name": $("#name").val(),      
    "price": $("#price").val(),
    "decription": $("#decription").val(),
    "categories": { id : "1" }
    };
    $.ajax({type: "POST", url:"/Food_Service_PIV/web/api/dishes",
        data: JSON.stringify(dish),contentType: "application/json"})
    .then( (dishes)=>{$('#addDialog').modal('hide'); showDishes(dishes); },
        (error)=>{errorMessage(error.status,$("#addErrorDiv"));});                          
}
