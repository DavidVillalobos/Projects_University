/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.food_service.presentation;

import com.food_service.logic.Clients;
import com.food_service.logic.Model;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;
import javax.ws.rs.Consumes;
import javax.ws.rs.DELETE;
import javax.ws.rs.GET;
import javax.ws.rs.NotAcceptableException;
import javax.ws.rs.NotFoundException;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.Produces;
import javax.ws.rs.core.Context;
import javax.ws.rs.core.MediaType;

/**
 *
 * @author David Villalobos
 */
@Path("/loginClient")
public class LoginClient {
    
    @Context
    HttpServletRequest request;
    
    @POST
    @Consumes(MediaType.APPLICATION_JSON)
    @Produces(MediaType.APPLICATION_JSON)    
    public Clients login(Clients client) {
         Clients logged=null;
        try {
            logged = Model.instance().clientegetByEmail(client.getEmail());
            if(!logged.getPassword().equals(client.getPassword())) throw new Exception("Clave incorrecta");
            request.getSession(true).setAttribute("client", logged);
            return logged;
        } catch (Exception ex) {
            throw new NotFoundException();
        }  
    }
    
    @GET 
    @Consumes(MediaType.APPLICATION_JSON)
    public Clients get() {
        try {
            Clients admin = (Clients) request.getSession(true).getAttribute("client");
            return admin;
        } catch (Exception ex) {
            throw new NotAcceptableException(); 
        }
    }
    
    @POST
    @Path("register")
    @Consumes(MediaType.APPLICATION_JSON)
    @Produces(MediaType.APPLICATION_JSON) 
    public Clients get_( Clients c) {
        try {
            Clients x = Model.instance().clientegetByEmail(c.getEmail());
            if(x==null){
                Model.instance().clienteAdd(c);
                x = Model.instance().clientegetByEmail(c.getEmail());
                request.getSession(true).setAttribute("client",x);
                return x;
            }
            return null;
        } catch (Exception ex) {
            throw new NotAcceptableException(); 
        }
    }
    
    @POST
    @Path("update")
    @Consumes(MediaType.APPLICATION_JSON)
    @Produces(MediaType.APPLICATION_JSON) 
    public Clients update(Clients c) {
        try {
            Model.instance().clienteUpdate(c);
            
            request.getSession(true).setAttribute("client",c);
            return c;
        } catch (Exception ex) {
            throw new NotAcceptableException(); 
        }
    }
    
    @DELETE 
    public void logout() {
        HttpSession session = request.getSession(true);
        session.removeAttribute("client");           
       // session.invalidate();
    }
    
}
