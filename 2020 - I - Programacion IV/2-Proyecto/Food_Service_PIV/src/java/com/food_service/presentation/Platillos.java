package com.food_service.presentation;

import com.food_service.logic.Additionals;
import com.food_service.logic.Details;
import com.food_service.logic.Dishes;
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

@Path("/dishes")
public class Platillos {

    @POST
    @Consumes(MediaType.APPLICATION_JSON)
    @Produces({MediaType.APPLICATION_JSON})    
    public List<Dishes> add(Dishes p) {  
        try {
            Model.instance().platillosAdd(p);
            Dishes dish = Model.instance().getDishByName(p.getName());
            for(Additionals a : p.getAdditionalsList()){
                a.setDishes(dish);
                Model.instance().adicionalesAdd(a);
                Additionals d = Model.instance().getAdditionalByName(a.getName());
                for (Details e: a.getDetailsList()) {
                    e.setAdditionals(d);
                    Model.instance().detallesAdd(e);
                }
            }
            
            return Model.instance().platillosgetAll();
        } catch (Exception ex) {
            throw new NotAcceptableException(); 
        }
    }
    
    // get by id
    @GET
    @Path("{id}")
    @Produces({MediaType.APPLICATION_JSON})
    public Dishes get(@PathParam("id") int id) {
        try {
            return Model.instance().platillosget(id);
        } catch (Exception ex) {
            throw new NotFoundException(); 
        }
    }
    
    @GET 
    @Consumes(MediaType.APPLICATION_JSON)
    public List<Dishes> get() {
        try {
            return Model.instance().platillosgetAll();
        } catch (Exception ex) {
            throw new NotAcceptableException(); 
        }
    }
    
    @DELETE
    @Path("{id}")
    @Produces({MediaType.APPLICATION_JSON})
    public List<Dishes> delete(@PathParam("id") int id) {
        try {
            Model.instance().platillosdelete(id);
            return Model.instance().platillosgetAll();
        } catch (Exception ex) {
            throw new NotFoundException(); 
        }
    }
    
    @PUT
    @Consumes(MediaType.APPLICATION_JSON)
    @Produces({MediaType.APPLICATION_JSON})    
    public List<Dishes> update(Dishes p) {  
        try {
            Model.instance().platillosUpdate(p);
            return Model.instance().platillosgetAll();       
        } catch (Exception ex) {
            throw new NotFoundException(); 
        }
    }
}
