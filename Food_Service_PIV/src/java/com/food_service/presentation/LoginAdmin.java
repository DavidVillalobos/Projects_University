package com.food_service.presentation;

import com.food_service.logic.Administrators;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;
import javax.ws.rs.Consumes;
import javax.ws.rs.DELETE;
import javax.ws.rs.NotFoundException;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.Context;
import javax.ws.rs.core.MediaType;
import com.food_service.logic.Model;

@Path("/loginAdmin")
public class LoginAdmin {
    
    @Context
    HttpServletRequest request;
    
    @POST
    @Consumes(MediaType.APPLICATION_JSON)
    @Produces(MediaType.APPLICATION_JSON)    
    public Administrators login(Administrators admin) {
         Administrators logged=null;
        try {
            logged = Model.instance().administradorgetByUserName(admin.getUserName());
            if(!logged.getPassword().equals(admin.getPassword())) throw new Exception("Clave incorrecta");
            request.getSession(true).setAttribute("admin", logged);
            return logged;
        } catch (Exception ex) {
            throw new NotFoundException();
        }  
    }
    
    @DELETE 
    public void logout() {
        HttpSession session = request.getSession(true);
        session.removeAttribute("admin");           
        session.invalidate();
    }
   
}
