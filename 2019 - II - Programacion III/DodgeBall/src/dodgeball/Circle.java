/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dodgeball;

/**
 * @author Luis David Villalobos González
 */
public class Circle {
    private int x;
    private int y;
    private int radio;
    private int diameter;
    
    public Circle(int x, int y, int radio) {
        this.x = x;
        this.y = y;
        this.radio = radio;
        this.diameter = radio * 2;
    }

    public int getX() {
        return x;
    }

    public void setX(int x) {
        this.x = x;
    }

    public int getY() {
        return y;
    }

    public void setY(int y) {
        this.y = y;
    }

    public int getRadio() {
        return radio;
    }

    public void setRadio(int radio) {
        this.radio = radio;
    }

    public int getDiameter() {
        return diameter;
    }

    public void setDiameter(int diameter) {
        this.diameter = diameter;
    }

    public double Distancia(int x_2, int y_2){
        return Math.sqrt( Math.pow((x_2 - x), 2) + Math.pow((y_2 - y), 2));
    }
    
    public boolean in(Ball b){
        double dist = Distancia( ( b.getX() + b.getDx() ) , ( b.getY() + b.getDy() ) );
        /*if(-5 < b.getDx() &&  b.getDx() < 5){// verificacion rebote horizontal
            if(b.getDy() < 0){
                return dist - b.getRadio()+32  <= radio;
            }
            return dist + b.getRadio()+2  <= radio;
        }*/
        if(b.getDx() < 0 && b.getDy() < 0){//Esquina superior izquierda
            //System.out.println("1");
            return dist + b.getDiameter()-20  <= radio;// perfect bouncing
        }
        if(b.getDx() < 0 && 0 < b.getDy() ){ //Esquina inferior Izquierda
            //System.out.println("2");
            return dist+18 <= radio;
        }
        if( 0 < b.getDx() && b.getDy() < 0){//Esquina inferior derecha
            //System.out.println("3");// perfect bouncing
            return dist + b.getRadio() <= radio;
        }//Esquina inferior Izquierda
        //System.out.println("4");// gooood
        return  dist + 10 <= radio;
    }
    
    public boolean inside(Racket r){
        int rx, ry;
        //esquina inferior derecha
        rx = r.getX() + r.getWidth()+ r.getDx();
        ry = r.getY() + r.getHeight() + r.getDy();
        boolean c1 = Distancia(rx,ry) < radio;
        //esquina inferior izquierda
        rx = r.getX()+ r.getDx();
        ry = r.getY() + r.getHeight() + r.getDy();
        boolean c2 = Distancia(rx,ry) < radio;
        //esquina superior derecha
        rx = r.getX() + r.getWidth()+ r.getDx();
        ry = r.getY() + r.getDy();
        boolean c3 = Distancia(rx,ry) < radio;
        //esquina superior izquierda
        rx = r.getX() + r.getDx();
        ry = r.getY() + r.getDy();
        boolean c4 = Distancia(rx,ry) < radio;
        return c1 && c2 && c3 && c4;
    }
}


