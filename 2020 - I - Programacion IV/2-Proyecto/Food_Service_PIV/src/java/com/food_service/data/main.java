package com.food_service.data;

import com.food_service.logic.Administrators;
import java.util.logging.Level;
import java.util.logging.Logger;

public class main {  // Testers For Daos
    public static void main(String[] args) {
        try {
            Administrators a;
            a = Dao_Administrators.instance().get(1);
            System.out.print(a.toString());
        } catch (Exception ex) {
            Logger.getLogger(main.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
}
