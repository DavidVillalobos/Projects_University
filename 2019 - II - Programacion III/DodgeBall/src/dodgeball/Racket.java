/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dodgeball;

import dodgeball.presentation.Model;

/**
 *@author Luis David Villalobos González
 */
public class Racket extends Actor {
    private int width;
    private int height;
    public int speed;
    
    public Racket(int x, int y, int dx, int dy, int width, int height, int speed){
        super(x, y, dx, dy);
        this.width = width;//Ancho
        this.height = height;//Alto
        this.speed = speed;
    }

    public int getWidth() {
        return width;
    }

    public void setWidth(int width) {
        this.width = width;
    }

    public int getHeight() {
        return height;
    }

    public void setHeight(int height) {
        this.height = height;
    }
    
    @Override
    public void move(Model m){
        if(m.getCircle().inside(m.getRacket())){
           setX(getX() + getDx());
           setY(getY() + getDy());
        }else{
           setX(getX() - getDx());
           setY(getY() - getDy());
        }
    }
}
