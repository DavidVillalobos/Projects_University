/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dodgeball.presentation;

/**
 * @author Luis David Villalobos González
 */
public class Controller {
    Model model;
    View view;

    public Controller(Model model, View view) {
        this.model = model;
        this.view = view;
        view.setController(this);
        view.setModel(model);
    }

    public Model getModel() {
        return model;
    }

    public void setModel(Model model) {
        this.model = model;
    }

    public View getView() {
        return view;
    }

    public void setView(View view) {
        this.view = view;
    }
    
    public void move(int flecha){
        model.move(flecha);
    }
    
    public void stopVer(){
        model.stopVer();
    }
    
    public void stopHor(){
        model.stopHor();
    }
    
    public void pause() {
        model.setExecute(false);
    }

    public void settings(int nBalls, int speed) {
        model.numberOfBalls(nBalls);
        model.setDelay(speed);
        model.setPoints(0);
    }

    public void activate() {
        model.setExecute(true);
        model.start();
    }
}
