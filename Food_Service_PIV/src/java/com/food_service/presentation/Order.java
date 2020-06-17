package com.food_service.presentation;

/**
 *
 * @author Kevin Flores
 */
import com.food_service.logic.Additionals;
import com.food_service.logic.Categories;
import com.food_service.logic.ClientDish;
import com.food_service.logic.Details;
import com.food_service.logic.Dishes;
import com.food_service.logic.Model;
import com.food_service.logic.Orders;
import com.google.gson.Gson;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.http.HttpServletRequest;
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
import javax.ws.rs.core.Context;

@Path("/orders")
public class Order {

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
    @Context
    HttpServletRequest request;
    
    @GET
    @Path("categories")
    @Produces({MediaType.APPLICATION_JSON})
    public List<Categories> getCategories() {
        try {
            return Model.instance().categoriasgetAll();
        } catch (Exception ex) {
            throw new NotFoundException(); 
        }
    }
    
    @GET
    @Produces({MediaType.APPLICATION_JSON})
    public List<Dishes> getDishes(@QueryParam("categorie") String idCategoria){
        try {
            List<Dishes> l = Model.instance().platilloByCategoria(idCategoria);
            return l;
        } catch (SQLException ex) {
            throw new NotFoundException();
        }
    }
    
    @GET
    @Path("hasAdditionals/{idDish}")  
    @Produces({MediaType.APPLICATION_JSON})
    public List<Additionals> hasAdditionals(@PathParam("idDish") String idDish){
        try {
            return Model.instance().adicionalesByDish(idDish);
        } catch (SQLException ex) {
            throw new NotFoundException();
        }
    }
    
    @GET
    @Path("details/{idDish}")  
    @Produces({MediaType.APPLICATION_JSON})
    public List<Additionals> getDetails(@PathParam("idDish") String idDish){
        try {
            List<Additionals> result = Model.instance().adicionalesByDish(idDish);
            for(Additionals a:result){
                a.setDetailsList(Model.instance().detallesByAdditional(a.getId()));
            }
            return result;
        } catch (SQLException ex) {
            throw new NotFoundException();
        }
    }
    
    @POST
    @Consumes(MediaType.APPLICATION_JSON)
    @Produces({MediaType.APPLICATION_JSON})    
    public List<Orders> updateOrder(ClientDish dish) {  
        try {
            Orders globalOrder = (Orders) request.getSession(true).getAttribute("globalOrder");
            if(globalOrder==null){  
                globalOrder = new Orders();    
            }
            if(dish.getClienteAdditionalsList() == null){
                Model.instance().addDishToOrder(globalOrder, dish, false);
            }else{
                Model.instance().addDishToOrder(globalOrder, dish, true);
            }
            List<Orders> list = new ArrayList<>();
            globalOrder.setTotal(Model.instance().calculateTotalOrder(globalOrder));
            request.getSession(true).setAttribute("globalOrder", globalOrder);
            list.add(globalOrder);
            return list;            
        } catch (Exception ex) {
            throw new NotAcceptableException(); 
        }
    }

    @DELETE
    @Path("delete/{index}")
    @Produces({MediaType.APPLICATION_JSON})
    public List<Orders> del(@PathParam("index") String index) {
        try {
            Orders globalOrder = (Orders) request.getSession(true).getAttribute("globalOrder");
            if(globalOrder==null){  
                globalOrder = new Orders();    
            }
            Model.instance().deleteFromOrder(index, globalOrder);
            List<Orders> list = new ArrayList<>();
            globalOrder.setTotal(Model.instance().calculateTotalOrder(globalOrder));
            request.getSession(true).setAttribute("globalOrder", globalOrder);
            list.add(globalOrder);
            return list;         
        } catch (Exception ex) {
            throw new NotFoundException(); 
        }
    }
//    
//    @GET
//    @Produces({MediaType.APPLICATION_JSON})
//    public List<Persona> list(@QueryParam("nombre") String nombre) { 
//        return Model.instance().personaSearch(nombre);
//    } 
//    
}
