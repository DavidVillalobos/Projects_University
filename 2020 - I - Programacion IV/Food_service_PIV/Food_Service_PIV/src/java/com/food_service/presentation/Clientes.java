package com.food_service.presentation;

import com.food_service.logic.Clients;
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

@Path("/clientes")
public class Clientes {

    @POST
    @Consumes(MediaType.APPLICATION_JSON)
    @Produces({MediaType.APPLICATION_JSON})    
    public List<Clients> add(Clients p) {  
        try {
            Model.instance().clienteAdd(p);
            return Model.instance().clientegetAll();
        } catch (Exception ex) {
            throw new NotAcceptableException(); 
        }
    }
    
    @GET 
    @Consumes(MediaType.APPLICATION_JSON)
    public List<Clients> get() {
        try {
            return Model.instance().clientegetAll();
        } catch (Exception ex) {
            throw new NotAcceptableException(); 
        }
    }
    
    // get by id
    @GET
    @Path("{id}")
    @Produces({MediaType.APPLICATION_JSON})
    public Clients get(@PathParam("id") int id) {
        try {
            return Model.instance().clienteget(id);
        } catch (Exception ex) {
            throw new NotFoundException(); 
        }
    }
    
    // get by email
    @GET
    @Produces({MediaType.APPLICATION_JSON})
    public Clients get(@PathParam("email") String email) {
         try {
            return Model.instance().clientegetByEmail(email);
        } catch (Exception ex) {
            throw new NotFoundException(); 
        }
    } 
    
    @DELETE
    @Path("{id}")
    @Produces({MediaType.APPLICATION_JSON})
    public List<Clients> delete(@PathParam("id") int id) {
        try {
            Model.instance().clientedelete(id);
            return Model.instance().clientegetAll();
        } catch (Exception ex) {
            throw new NotFoundException(); 
        }
    }
    
    @PUT
    @Consumes(MediaType.APPLICATION_JSON)
    @Produces({MediaType.APPLICATION_JSON})    
    public List<Clients> update(Clients p) {  
        try {
            Model.instance().clienteUpdate(p);
            return Model.instance().clientegetAll();       
        } catch (Exception ex) {
            throw new NotFoundException(); 
        }
    }
}
