package com.food_service.presentation;

import com.food_service.logic.Categories;
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

@Path("/categories")
public class Categorias {

    @POST
    @Consumes(MediaType.APPLICATION_JSON)
    @Produces({MediaType.APPLICATION_JSON})    
    public List<Categories> add(Categories p) {  
        try {
            Model.instance().categoriasAdd(p);
            return Model.instance().categoriasgetAll();
        } catch (Exception ex) {
            throw new NotAcceptableException(); 
        }
    }
    
    
    @GET 
    @Consumes(MediaType.APPLICATION_JSON)
    public List<Categories> get() {
        try {
            return Model.instance().categoriasgetAll();
        } catch (Exception ex) {
            throw new NotAcceptableException(); 
        }
    }
    
    
    // get by id
    @GET
    @Path("{id}")
    @Produces({MediaType.APPLICATION_JSON})
    public Categories get(@PathParam("id") int id) {
        try {
            return Model.instance().categoriasget(id);
        } catch (Exception ex) {
            throw new NotFoundException(); 
        }
    }
    
    @DELETE
    @Path("{id}")
    @Produces({MediaType.APPLICATION_JSON})
    public List<Categories> delete(@PathParam("id") int id) {
        try {
            Model.instance().clientedelete(id);
            return Model.instance().categoriasgetAll();
        } catch (Exception ex) {
            throw new NotFoundException(); 
        }
    }
    
    @PUT
    @Consumes(MediaType.APPLICATION_JSON)
    @Produces({MediaType.APPLICATION_JSON})    
    public List<Categories> update(Categories p) {  
        try {
            Model.instance().categoriasUpdate(p);
            return Model.instance().categoriasgetAll();       
        } catch (Exception ex) {
            throw new NotFoundException(); 
        }
    }
}
