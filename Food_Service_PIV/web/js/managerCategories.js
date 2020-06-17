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
                '<button type="button" class="btn btn-primary btn-lg btn-block bg-light text-dark">Agregar</button>' +
            '</div>'+
        '</div>'+
    '</div>'+
    '<div class="card bg-light">'+
        '<div class="card-body text-center">'+
            '<div class="table-responsive " overflow: auto">'+
                '<table class="table table-striped table-hover" style="font-size: 22px;">'+
                    '<thead><tr>'+
                    '<th scope="col">Id</th><th scope="col">Nombre</th><th scope="col"></th>'+
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