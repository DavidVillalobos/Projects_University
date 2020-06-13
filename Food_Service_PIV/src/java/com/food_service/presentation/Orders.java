package com.food_service.presentation;

/**
 *
 * @author Kevin Flores
 */
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
import javax.ws.rs.QueryParam;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.DELETE;
import javax.ws.rs.NotAcceptableException;
import javax.ws.rs.POST;

@Path("/orders")
public class Orders {

//    @POST
//    @Consumes(MediaType.APPLICATION_JSON)
//    @Produces({MediaType.APPLICATION_JSON})    
//    public List<Persona> add(Persona p) {  
//        try {
//            Model.instance().personaAdd(p);
//            return Model.instance().personaListAll();
//        } catch (Exception ex) {
//            throw new NotAcceptableException(); 
//        }
//    }
    
    @GET
    @Path("categories")
    @Produces({MediaType.APPLICATION_JSON})
    public List<Categories> get() {
        try {
            return Model.instance().categoriasgetAll();
        } catch (Exception ex) {
            throw new NotAcceptableException(); 
        }
    }

//    @DELETE
//    @Path("{cedula}")
//    @Produces({MediaType.APPLICATION_JSON})
//    public List<Persona> del(@PathParam("cedula") String cedula) {
//        try {
//            Model.instance().personaDelete(cedula);
//            return Model.instance().personaListAll();
//        } catch (Exception ex) {
//            throw new NotFoundException(); 
//        }
//    }
//    
//    @GET
//    @Produces({MediaType.APPLICATION_JSON})
//    public List<Persona> list(@QueryParam("nombre") String nombre) { 
//        return Model.instance().personaSearch(nombre);
//    } 
//    
//    @PUT
//    @Consumes(MediaType.APPLICATION_JSON)
//    @Produces({MediaType.APPLICATION_JSON})    
//    public List<Persona> update(Persona p) {  
//        try {
//            Model.instance().personaUpdate(p);
//            return Model.instance().personaListAll();            
//        } catch (Exception ex) {
//            throw new NotFoundException(); 
//        }
//    }
}
