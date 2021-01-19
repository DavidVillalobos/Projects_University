package com.food_service.presentation;

import com.food_service.logic.Administrators;
import com.food_service.logic.Model;
import java.util.List;
import javax.ws.rs.Consumes;
import javax.ws.rs.GET;
import javax.ws.rs.PUT;
import javax.ws.rs.NotFoundException;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.DELETE;
import javax.ws.rs.NotAcceptableException;
import javax.ws.rs.POST;

@Path("/administradores")
public class Administradores {

    @POST
    @Consumes(MediaType.APPLICATION_JSON)
    @Produces({MediaType.APPLICATION_JSON})    
    public List<Administrators> add(Administrators p) {  
        try {
            Model.instance().administradorAdd(p);
            return Model.instance().administradorgetAll();
        } catch (Exception ex) {
            throw new NotAcceptableException(); 
        }
    }
    
    @GET 
    @Consumes(MediaType.APPLICATION_JSON)
    public List<Administrators> get() {
        try {
            return Model.instance().administradorgetAll();
        } catch (Exception ex) {
            throw new NotAcceptableException(); 
        }
    }
    
    // get by id
    @GET
    @Path("{id}")
    @Produces({MediaType.APPLICATION_JSON})
    public Administrators get(@PathParam("id") int id) {
        try {
            return Model.instance().administradorget(id);
        } catch (Exception ex) {
            throw new NotFoundException(); 
        }
    }
    
    // get by user name
    @GET
    @Produces({MediaType.APPLICATION_JSON})
    public Administrators get(@PathParam("userName") String userName) {
         try {
            return Model.instance().administradorgetByUserName(userName);
        } catch (Exception ex) {
            throw new NotFoundException(); 
        }
    } 
    
    @DELETE
    @Path("{id}")
    @Produces({MediaType.APPLICATION_JSON})
    public List<Administrators> delete(@PathParam("id") int id) {
        try {
            Model.instance().administradordelete(id);
            return Model.instance().administradorgetAll();
        } catch (Exception ex) {
            throw new NotFoundException(); 
        }
    }
    
    @PUT
    @Consumes(MediaType.APPLICATION_JSON)
    @Produces({MediaType.APPLICATION_JSON})    
    public List<Administrators> update(Administrators p) {  
        try {
            Model.instance().administradorUpdate(p);
            return Model.instance().administradorgetAll();       
        } catch (Exception ex) {
            throw new NotFoundException(); 
        }
    }
}
