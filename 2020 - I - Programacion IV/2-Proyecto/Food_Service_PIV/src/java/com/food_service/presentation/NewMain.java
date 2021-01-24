/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.food_service.presentation;

import com.food_service.logic.Administrators;
import com.food_service.logic.Model;
import com.food_service.logic.Dishes;
import com.google.gson.Gson;
import java.util.List;

/**
 *
 * @author Home
 */
public class NewMain {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws Exception {
        Model m = Model.instance();
        List<Dishes> ad = m.platilloByCategoria("4");
        String jason = "{userName: \"1\", password: \"1\"}";
        Gson gson = new Gson();
        Administrators admin = gson.fromJson(jason, Administrators.class);
        System.out.println(admin.toString());
    }
    
}
