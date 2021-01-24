package com.food_service.presentation;

import com.food_service.logic.AdministratorStatus;
import com.food_service.logic.Model;
import java.util.List;
import javax.ws.rs.Consumes;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.NotAcceptableException;

@Path("/statusadministrators")
public class EstadosAdministrador {
    
    @GET 
    @Consumes(MediaType.APPLICATION_JSON)
    public List<AdministratorStatus> get() {
        try {
            return Model.instance().estadosAdministradorgetAll();
        } catch (Exception ex) {
            throw new NotAcceptableException(); 
        }
    }
}
