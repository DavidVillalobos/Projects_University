
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
                '<button type="button" class="btn btn-primary rounded-3" onclick="agregateDish()">Agregar platillo</button>' +
            '</div>'+
        '</div>'+
    '</div>'+
    '<div class="card bg-light">'+
        '<div class="card-body text-center">'+
            '<div class="table-responsive " overflow: auto">'+
                '<table class="table table-striped table-hover" style="font-size: 22px;">'+
                    '<thead><tr><th scope="col">Categoria</th>'+
                    '<th scope="col">Nombre</th><th scope="col">Precio</th>'+
                    '<th colspan="2" scope="col">'+
                    '<div class="form-inline">'+
                        '<div class="input-group flex-fill">'+
                            '<input id="filterByText" type="text" class="form-control" placeholder="Buscar por nombre o categoria">'+
                            '<span class="input-group-prepend">'+
                            '<button class="btn btn-primary" onclick="searchDishByFilter()">'+
                            '<i class="fa fa-search"></i>'+
                            '</button>'+
                            '</span>'+
                        '</div>'+
                    '</div>'+
                    '</th> '+
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

function agregateDish(){
    _additionalList = [];
    _optionList = [];
    _dish = {};
    var list = $("#panel");
    list.html("");
    list.html('<div class="display-3" style="margin-left: 60px;">'+
        '<div class="form-row">'+
            '<div class="modal" id="addDialog">'+
                '<div class="modal-dialog">'+
                    '<div class="modal-content">'+
                        '<div>'+
                            '<div class="modal-body text-center" style="width: 510px;  height: 370px;">'+
                                '<span class="display-4" style="font-size: 60px;">Nuevo Platillo</span>'+
                                '<br><br>'+
                                '<div class = "input-group" style = "margin-bottom: 10px; margin-top: -70px;">'+
                                    '<div class = "input-group-prepend "><span class = "input-group-text" style="width: 105px;"><i>Nombre</i></span></div>'+
                                    '<input class = "form-control" placeholder = "Nombre" type = "text" id = "nameDish" name="nameDish" value="" required>'+
                                    '<div class = "invalid-feedback">Favor ingrese el nombre del platillo</div>'+
                                '</div>'+
                                '<div class = "input-group" style = "margin-bottom: 10px">'+
                                    '<div class = "input-group-prepend "><span class = "input-group-text" style="width: 105px;"><i>Precio</i></span></div>'+
                                    '<input class = "form-control" placeholder = "Precio" type = "number" id = "priceDish" name="priceDish" value="" required>'+
                                    '<div class = "invalid-feedback">Favor ingrese el precio del platillo</div>'+
                                '</div>'+
                                '<div class = "input-group" style = "margin-bottom: 10px">'+
                                    '<div class = "input-group-prepend "><span class = "input-group-text"><i>Descripción</i></span></div>'+
                                    '<textarea class = "form-control" placeholder = "Descripción" type = "text" id = "decriptionDish" name="decriptionDish" required></textarea>'+
                                    '<div class = "invalid-feedback">Favor ingrese el precio del platillo</div>'+
                                '</div>'+
                                '<div class = "input-group-prepend display-4" style="font-size:17px; margin: 10px;">'+
                                    '<div class="btn-group dropright">'+
                                        '<a class="btn btn-secondary dropdown-toggle" style="color:white" role="button" '+
                                        'id="dropdownMenuButton" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false"> Elige una Categoria</a>'+
                                        '<div class="dropdown-menu" aria-labelledby="dropdownMenuButton" id="categoriesList">'+
                                        '</div>'+
                                    '</div>'+
                                    '<div class="btn-group dropright" style="margin-left: 50px;">'+
                                        '<a class="btn btn-secondary dropdown-toggle" style="color:white" role="button" '+
                                        'id="dropdownMenuButton" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false"> Adicionales</a>'+
                                        '<div class="dropdown-menu" aria-labelledby="dropdownMenuButton" id="additionalList">'+
                                        '</div>'+
                                    '</div>'+
                                '</div>'+
                                '<button class="btn btn-primary" style="width:150px; margin-left: -295px; margin-top: -60px;" onclick="agregarAdicional()">Agregar Adicional</button>'+
                            '</div>'+
                            '<button type="button" class="btn btn-secondary" style="margin-left: 30px;" onclick="cancelAddDish()">Cancelar</button>'+
                            '<button type="button" class="btn btn-primary"   style="margin-left: 30px;" onclick="addDish()">Agregar</button>'+
                            '<div id="loginErrorDiv" style="width:80%; margin: auto;"></div>     '+
                        '</div>'+
                    '</div>'+
                '</div>'+
            '</div>'+
        '</div> '+
    '</div>'+
    '<!-- Agregar Adicional-->'+
    '<div style="margin-top: -550px; margin-left: 650px;">'+
        '<div class="form-row">'+
            '<div id="addAdditionalDialog" class="modal" role="dialog">'+
                '<div class="modal-dialog" role="document">'+
                    '<div class="modal-content" style="width: 350px;">'+
                        '<div class="modal-body"> '+
                            '<div class="display-4" style="font-size:30px;"><b>Agregar Adicional<b></div>'+
                            '<div style="margin-top: 30px; margin-left: 1px;">'+
                                '<div class = "input-group" id="name">'+
                                    '<input class = "form-control" placeholder = "Nombre" type = "text" id = "nameAdditional" name = "nameAdditional" value = "" required>'+
                                    '<div class = "invalid-feedback">Favor ingrese el nombre del adicional</div>'+
                                '</div>'+
                                '<div class = "input-group-prepend display-4" style="font-size:16px;">'+
                                    'Opcion: '+
                                    '<div class="radio-inline" style="margin-left: 15px;"><input type="radio" name="optradio" value="false" style="margin-right: 15px;" checked>Unica</div>'+
                                    '<div class="radio-inline" style="margin-left: 15px;"><input type="radio" name="optradio" value="true" style="margin-right: 15px;">Multiple</div>'+
                                    '<div class = "invalid-feedback">Favor ingrese una opcion</div>'+
                                '</div>'+
                                '<div class = "input-group-prepend display-4" style="font-size:16px;">'+
                                    '<div class = "input-group-prepend">Obligatorio: </div>'+
                                    '<div class="checkbox-inline" ><input id="mandatoryAditional" type="checkbox" style="margin-left:22px;"></div>'+
                                '</div>'+
                                '<div class = "input-group-prepend display-4" style="font-size:17px;">'+
                                    '<div class="btn-group dropright">'+
                                        '<button type="button" class="btn btn-primary dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false" style="width:130px;">'+
                                            'Opciones'+
                                        '</button>'+
                                        '<div class="dropdown-menu text-center" id="optionList">'+
                                        '</div>'+
                                        '<button class="btn btn-primary" style="width:130px; margin-left: 20px;" onclick="agregarOpcion()">Agregar Opcion</button>'+
                                   '</div>'+
                                '</div>'+
                                '<button class="btn btn-danger" style="width:80px; margin-right: 20px;" data-dismiss="modal" onclick="cancelAddAdditional()">Cancelar</button>'+
                                '<button class="btn btn-primary" style="width:150px;" onclick="addAdicional()">Agregar</button>'+
                            '</div>'+
                        '</div>'+
                    '</div>'+
                '</div>'+
           '</div>'+
        '</div>'+
        '<!-- Agregar Opcion del adicional-->'+
        '<div class="form-row">'+
            '<div id="panelOptionDialog">'+
                '<div class="modal" id="addOptionDialog" role="dialog" aria-hidden="true">'+
                    '<div class="modal-dialog" role="document">'+
                        '<div class="modal-content" style="width: 300px; height: 230px; margin-top: -45px;">'+
                            '<div class="modal-body">'+
                                '<div class="display-4" style="font-size:22px;">Agregar Opcion</div>'+
                                '<div style="margin-top: 20px;">'+
                                    '<div class = "input-group" style = "margin-bottom: 10px;" id="name">'+
                                        '<input class = "form-control" placeholder = "Nombre" type = "text" id = "nameOption" name = "nameOption" value = "" required>'+
                                        '<div class = "invalid-feedback">Favor ingrese el nombre del adicional</div>'+
                                    '</div>'+
                                    '<div class = "input-group" id="name">'+
                                        '<input class = "form-control" placeholder = "Precio" type = "number" id = "priceOption" name = "priceOption" value = "" required>'+
                                        '<div class = "invalid-feedback">Favor ingrese el precio de la opcion</div>'+
                                    '</div>'+
                                    '<button type="button" class="btn btn-secondary" onclick="cancelAddOption()" style="width:80px; margin-left: 40px; margin-top: 20px;">Cancelar</button>'+
                                    '<button type="button" class="btn btn-primary" onclick="addOpcion()" style="width:80px; margin-left: 30px; margin-top: 20px;">Agregar</button>'+
                                 '</div>'+
                            '</div>'+ 
                        '</div>'+
                    '</div>'+
               '</div>'+
            '</div>'+
        '</div>'+
    '</div>');
    $("#addDialog").removeAttr("class");
    loadCategoriesForDish();
}

function loadCategoriesForDish() {
    $.ajax({
        type: "GET",
        url: "/Food_Service_PIV/web/api/categories",
        contentType: "application/json"
    }).then(
            (categories) => {
        var list = $("#categoriesList");
        categories.forEach( categorie => list.append('<a class="dropdown-item">' + categorie.name + '</a>'));   // '<a class="class=dropdown-item">aja</a>'+
        $('#dropdownMenuButton + [aria-labelledby="dropdownMenuButton"] a').on('click', function () {
                $("#dropdownMenuButton").html(this.textContent);
        });
    },
        (error) => {
    errorMessage(error.status, $("#categories"));
    }
    );
}

function rowDish(anchor, c) {
    var tr =$("<tr />");
    tr.html('<td>' + c.categories.name + '</td>' +
            '<td>' + c.name + '</td>' +
            '<td>' + c.price + '</td>' +
            '<td style="width: 160px;"><button type="button" class="btn btn-primary" data-toggle="modal" data-target="#editDialog" onclick="searchDish('+ c.id +')">Ver / Editar</button>' +
            '</td>' +
            '<td style="width: 160px;">' +
            '<button type="button" class="btn btn-danger" onclick="deleteDish('+ c.id +')">Eliminar</button>' +
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
                                '<span class="display-4">Editar Platillo<br>' + dish.name + '</span>'+
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
    '</div> ';
    anchor.append(html);
}

function searchDishByFilter(){
    $.ajax({
        type: "GET",
        url: "/Food_Service_PIV/web/api/dishes",
        contentType: "application/json"
    }).then(
            (dishes) => {
        showDishes( dishes.filter(dish => filtrar(dish)));
    },
            (error) => {
        errorMessage(error.status, $("#dishes"));
    }
    );
}

function filtrar(dish){
    text = String($("#filterByText").val()).toUpperCase();
    n1 = String(dish.name).toUpperCase();
    n2 = String(dish.categories.name).toUpperCase();
    if(n1.includes(text) || n2.includes(text)){
        return true;
    }
    return false;
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

// - - - - - - - - - - - - - - -  AÑADIR UN PLATILLO - - - - - - - - - - - - - -

_additionalList = [];
_optionList = [];
_dish = {};


function agregarAdicional(){
    $("#addAdditionalDialog").removeClass("modal");
}

function agregarOpcion(){
    $("#addOptionDialog").removeClass("modal");
}

function addOpcion(){
        var nameOption = $("#nameOption").val();
        var priceOption = $("#priceOption").val();
        var option = { 
            name: nameOption,
            price: priceOption
        }
        _optionList.push(option);
        var list = $("#optionList");
        var html = $("<a class='dropdown-item'/>");
        html.html(option.name +' &nbsp;&nbsp;&nbsp;&nbsp;₡'+ option.price + '</a>');	
        list.append(html);
        $("#priceOption").val("");
        $("#nameOption").val("");
         $("#addOptionDialog").addClass("modal");
}

function addAdicional(){
    var nameAdditional = $("#nameAdditional").val();
    var typeAdditional = $('input:radio[name=optradio]:checked').val() == "true";
    var mandatoryAdditional = $('#mandatoryAditional').is(":checked");
    var additional = { 
           name: nameAdditional, 
           type: typeAdditional,
           mandatory: mandatoryAdditional,
           detailsList: _optionList
    };
    _optionList = [];
    _additionalList.push(additional);
    var list = $("#additionalList");
    var html = $("<a class='dropdown-item'/>");
    html.html(additional.name + '</a>');	
    list.append(html);
    $("#nameAdditional").val("");
    $("#addAdditionalDialog").addClass("modal");
}

function addDish(){
     $.ajax({
        type: "GET",
        url: "/Food_Service_PIV/web/api/categories",
        contentType: "application/json"
    }).then(
        (categories) => {
            var categorieDish = undefined;
            categories.forEach((categorie) => {
                if(categorie.name === $("#dropdownMenuButton").html()){
                    categorieDish = categorie; 
                }
            });
            if(categorieDish != undefined){
                var nameDish = $("#nameDish").val();
                var priceDish = $("#priceDish").val();
                var decriptionDish = $("#decriptionDish").val();
                $("#nameDish").val("");
                $("#priceDish").val("");
                $("#decriptionDish").val("");
                dish = {
                    name: nameDish,      
                    price: priceDish,
                    decription: decriptionDish,
                    categories: categorieDish,
                    additionalsList: _additionalList
                };
                $.ajax({type: "POST", url:"/Food_Service_PIV/web/api/dishes",
                    data: JSON.stringify(dish),contentType: "application/json"})
                .then( (dishes)=>{$('#addDialog').modal('hide'); showDishes(dishes); },
                    (error)=>{errorMessage(error.status,$("#addErrorDiv"));});  
                }
        },
        (error) => {
            errorMessage(error.status, $("#categories"));
        }
    );   
}

function cancelAddOption(){
    $("#priceOption").val("");
    $("#nameOption").val("");
    $("#addOptionDialog").addClass("modal");
}

function cancelAddAdditional(){
    $("#nameAdditional").val("");
    $("#addAdditionalDialog").addClass("modal");
}

function cancelAddDish(){
    $("#nameDish").val("");
    $("#priceDish").val("");
    $("#decriptionDish").val("");
    $("#addDialog").addClass("modal");
}