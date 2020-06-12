<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
    <%@ include file="Head.jsp" %>
    <title>Food Service</title> 
</head>
<%@ include file="Header.jsp" %>   
<body class="bg-dark">
    <div class="container-fluid">
        <div class="text-center">
            <div class="display-1 text-white">Food Service</div>
        </div>
    </div>
     <nav class="navbar navbar-expand navbar-dark container-fluid bg-success">
      <div class="collapse navbar-collapse">
        <ul class="navbar-nav ml-auto">
          <li class="nav-item active">
            <a class="nav-link h3 pt-2" href="#">Sign in</a>
          </li>
          <li class="nav-item">
            <a class="nav-link h3 pt-2" href="#">Sing up</a>
          </li>
        </ul>
      </div>
    </nav>
    <div class="container-fluid text-center">
     <div class="row text-white alto justify-content-center">
         <div class="col-4 pt-5">
             <button class="navbar-toggler" type="button">
               <a class="h1 text-white">Storefront</a>
              </button>
             <span class="navbar-toggler-icon"> <img id="icono" src="../images/icon.png"></span>
         </div>  
         <div class="col-4 pt-5">
             <span class="navbar-toggler-icon"> <img id="icono2" src="../images/icon2.png"></span>
              <button class="navbar-toggler" type="button">
                  <a class="h1 text-white">Administrator Panel</a>
                </button>
         </div>
     </div>
    </div> 
</body>
   <%@ include file="Footer.jsp" %> 
</html>