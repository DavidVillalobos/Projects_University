
function loadCategories() {
    $.ajax({
        type: "GET",
        url: "/Food_Service_PIV/web/api/categories",
        contentType: "application/json"
    }).then(
            (categories) => {
        showCategories(categories);
    },
            (error) => {
        errorMessage(error.status, $("#categories"));
    }
    );
}

function showCategories(categories){
    var list = $("#panel");
    list.html("");
    list.html('<div class="container-fluid rounded text-white" style="background-color: rgb(5, 5, 54);">' +
        '<div class="row py-1  align-items-center justify-content-center">'+
            '<div class="col-6 text-center " style="font-size: 60px;"> Categorias </div>'+
            '<div class="col-2 center-block">'+
                '<button type="button" class="btn btn-primary rounded-3" data-toggle="modal" data-target="#addDialog" onclick="aggregateCategories()">Agregar Categoria</button>' +
            '</div>'+
        '</div>'+
    '</div>'+
    '<div class="card bg-light">'+
        '<div class="card-body text-center">'+
            '<div class="table-responsive " overflow: auto">'+
                '<table class="table table-striped table-hover" style="font-size: 22px;">'+
                    '<thead><tr><th scope="col">Id</th>'+
                    '<th scope="col">Nombre</th>'+
                    '<th scope="col" colspan="2">'+
                    '<div class="form-inline">'+
                        '<div class="input-group flex-fill">'+
                            '<input id="filterByText" type="text" class="form-control" placeholder="Buscar por nombre o id">'+
                            '<span class="input-group-prepend">'+
                            '<button class="btn btn-primary" onclick="searchCategoriesByName()">'+
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
    categories.forEach((c) => {
        rowCategorie(anchor, c);
    });
}

function rowCategorie(anchor, c) {
    var tr =$("<tr />");
    tr.html('<td>' + c.id + '</td>' +
            '<td>' + c.name + '</td>' +
            '<td style="width: 160px;"><button type="button" class="btn btn-primary" data-toggle="modal" data-target="#editDialog" onclick="searchCategorie('+ c.id +')">Ver / Editar</button>' +
            '</td>' +
            '<td style="width: 160px;">' +
            '<button type="button" class="btn btn-danger" onclick="deleteCategorie('+ c.id +')">Eliminar</button>' +
            '</td>' +  
            '</tr>');
    anchor.append(tr);
}

function searchCategorie(id){
    $.ajax({
        type: "GET",
        url: "/Food_Service_PIV/web/api/categories/" + id,
        contentType: "application/json"
    }).then(
        (categorie) => { editCategorie(categorie);
        },(error) => {
            errorMessage(error.status, $("#categories"));
        }
    );
}

function editCategorie(categorie){
    var anchor = $('#listado');
    var html = '<div class="form-row">'+
            '<div class="modal" id="editDialog">'+
                '<div class="modal-dialog">'+
                '<div class="modal-content">'+
                    '<form>'+
                        '<div class="modal-body text-center">'+
                                '<div></div>'+
                                '<span class="display-4">Editar Categoria<br>' + categorie.name + '</span>'+
                            '<br><br>'+
                            '<div class = "input-group" style = "margin-bottom: 25px">'+
                                '<div class = "input-group-prepend "><span class = "input-group-text"><i>Nombre</i></span></div>'+
                                    '<input class = "form-control" placeholder = "Nombre" type = "text" id = "name" name="name" value="'+categorie.name+'" required>'+
                                '<div class = "invalid-feedback">Favor ingrese el nombre de la categoria</div>'+
                            '</div>'+
                        '</div>'+
                        '<div class="modal-footer d-flex justify-content-center">'+
                            '<div>'+
                             ' <button type="button" class="btn btn-secondary" style="margin-right: 30px;" data-dismiss="modal" onclick="loadCategories()">Cancelar</button>'+
                                '<button type="button" class="btn btn-primary" data-dismiss="modal" onclick="updateCategorie('+categorie.id+')">Actualizar</button>'+
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

function aggregateCategories(){
    var anchor = $('#listado');
    var html = '<div class="form-row">'+
            '<div class="modal" id="addDialog">'+
                '<div class="modal-dialog">'+
                '<div class="modal-content">'+
                    '<form>'+
                        '<div class="modal-body text-center">'+
                                '<div></div>'+
                                '<span class="display-4">Agregar una<br>Categoria</span>'+
                            '<br><br>'+
                            '<div class = "input-group" style = "margin-bottom: 25px">'+
                                '<div class = "input-group-prepend "><span class = "input-group-text"><i>Nombre</i></span></div>'+
                                    '<input class = "form-control" placeholder = "Ingrese el nombre de la categoria" type = "text" id = "name" name="name" value="" required>'+
                                '<div class = "invalid-feedback">Favor ingrese el nombre de la categoria</div>'+
                            '</div>'+
                        '</div>'+
                        '<div class="modal-footer d-flex justify-content-center">'+
                            '<div>'+
                             ' <button type="button" class="btn btn-secondary" style="margin-right: 30px;" data-dismiss="modal">Cancelar</button>'+
                                '<button type="button" class="btn btn-primary" data-dismiss="modal" onclick="addCategorie()">Agregar</button>'+
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

function searchCategoriesByName(){
    $.ajax({
        type: "GET",
        url: "/Food_Service_PIV/web/api/categories",
        contentType: "application/json"
    }).then(
            (categories) => {
        showCategories( categories.filter(categorie => filtrarCategoria(categorie)));
    },
            (error) => {
        errorMessage(error.status, $("#categories"));
    }
    );
}

function filtrarCategoria(categorie){
    text = String($("#filterByText").val()).toUpperCase();
    n1 = String(categorie.name).toUpperCase();
    n2 = String(categorie.id);
    return n1.includes(text) || n2.includes(text);
}

function deleteCategorie(id){
    $.ajax({
        type: "DELETE",
        url: "/Food_Service_PIV/web/api/categories/" + id,
        contentType: "application/json"
    }).then(
            (categories) => {
        showCategories(categories);
    },
            (error) => {
        errorMessage(error.status, $("#categories"));
    }
    );
}

function updateCategorie(categorieId){ 
  categorie = {id: categorieId, 
    name: $("#name").val()};
  $.ajax({type: "PUT", url:"/Food_Service_PIV/web/api/categories",
              data: JSON.stringify(categorie),contentType: "application/json"})
    .then( (categories)=>{$('#editDialog').modal('hide'); showCategories(categories); },
           (error)=>{errorMessage(error.status,$("#addErrorDiv"));});                          
}

function addCategorie(){ 
    categorie = {name: $("#name").val()};
    $.ajax({type: "POST", url:"/Food_Service_PIV/web/api/categories",
        data: JSON.stringify(categorie),contentType: "application/json"})
    .then( (categories)=>{$('#addDialog').modal('hide'); showCategories(categories); },
        (error)=>{errorMessage(error.status,$("#addErrorDiv"));});                          
}
