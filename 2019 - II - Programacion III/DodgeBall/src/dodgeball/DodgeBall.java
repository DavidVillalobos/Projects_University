/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dodgeball;

import dodgeball.presentation.Controller;
import dodgeball.presentation.Model;
import dodgeball.presentation.View;

/**
 *@author Luis David Villalobos González
 */
public class DodgeBall {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Model model = new Model();
        View view = new View();
        Controller controller = new Controller(model, view);
        view.setVisible(true);
        model.start();
    }
    
}
