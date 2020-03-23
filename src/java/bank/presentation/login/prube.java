/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package bank.presentation.login;

import bank.data.Dao_Cuenta;
import bank.data.Dao_Moneda;
import bank.data.Dao_Movimiento;
import bank.data.Dao_Usuario;
import bank.logic.Cuenta;
import bank.logic.Moneda;
import bank.logic.Movimiento;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Kevin Flores
 */
public class prube {
    public static void main(String []args){
        Cuenta c=null;
        List<Movimiento> lis = null;
        try {
            c = Dao_Cuenta.instance().get(1002);
            lis = Dao_Movimiento.instance().getRecentMovements(c);
            int y = 0;
            y++;
            y--;
            
        } catch (Exception ex) {
            Logger.getLogger(prube.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
