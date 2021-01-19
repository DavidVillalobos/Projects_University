/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dodgeball;
import dodgeball.presentation.Model;
import java.util.Random;

/**
 *@author Luis David Villalobos González
 */
public class Ball extends Actor {
    private int radio;
    private int diameter;
    private boolean win;
    private boolean lose;
    public Ball(int x, int y, int dx, int dy, int radio) {
        super(x, y, dx, dy);
        this.radio = radio;
        this.diameter = radio*2;
        win = false;
        lose = false;
    }

    public boolean getLose() {
        return lose;
    }

    public void setLose(boolean lose) {
        this.lose = lose;
    }
    
    public double getDiameter() {
        return diameter;
    }

    public void setDiameter(int diameter) {
        this.diameter = diameter;
    }

    public int getRadio() {
        return radio;
    }

    public void setRadio(int radio) {
        this.radio = radio;
    }

    public boolean getWin() {
        return win;
    }

    public void setWin(boolean win) {
        this.win = win;
    }
    
    public double Distancia(int x_2, int y_2){
        return Math.sqrt( Math.pow((x_2 - getX()), 2) + Math.pow((y_2 - getY()), 2));
    }
    
    @Override
    public void move(Model m){
        Circle c = m.getCircle();
        if(!c.in(this)){// si no esta dentro del circulo
            double A;
            double angulo = 0;
            if(getDx() > 0 && getDy() > 0){//Esquina inferior derecha
                A = getY() - c.getY() + radio;
                angulo = 270 + Math.toDegrees(Math.acos(A/c.getRadio()));// no questione :v
                if( 284 <= angulo && angulo <= 301){
                    win = true;
                }else if( 331 <= angulo && angulo < 351){
                    lose = true;
                }
            }
            else{
                if(getDx() < 0 && getDy() < 0){//Esquina superior izquierda
                    A = c.getY() - getY() - radio;
                    angulo = 70 + Math.toDegrees(Math.acos(A/c.getRadio()));// no questione :v
                    if( 115 <= angulo && angulo <= 126){
                        win = true;
                    }else if( 144 <= angulo && angulo <= 160){
                        lose = true;
                    }
                }
                else{
                    if(getDx() < 0 && 0 < getDy() ){//Esquina inferior Izquierda
                        A = c.getX() - getX() + radio;
                        angulo = 180 + Math.toDegrees(Math.acos(A/c.getRadio()));// no questione :v
                        if( 194 <= angulo && angulo <= 214){
                            win = true;
                        }else if( 241 <= angulo && angulo <= 262){
                            lose = true;
                        }
                    }
                    else{
                        A = getX() + radio - c.getX(); 
                        angulo = Math.toDegrees(Math.acos(A/c.getRadio()));// no questione :v
                        if( 19 <= angulo && angulo <= 41){
                           win = true;
                        }else if( 61 <= angulo && angulo <= 78){
                            lose = true;
                        }
                    }
                }
            }
            bounce();
        }
        else{
            Racket r = m.getRacket();
            int px = getX();
            if ( px < r.getX() ) px = r.getX();
            if ( px > r.getX() + r.getWidth() ) px = r.getX() + r.getWidth();
            int py = getY();
            if ( py < r.getY() ) py = r.getY();
            if ( py > r.getY() + r.getHeight() ) py = r.getY() + r.getHeight();
            if (Math.sqrt( (getX() - px)*(getX() - px) + (getY() - py)*(getY() - py) ) <= radio - 5 ) {
                setDx(getDx()*-1);
                bounce();
            }
        }
        setX(getX()+getDx());
        setY(getY()+getDy());
    }
    
    private void bounce(){// Aca va el metodo de rebote con angulos
        setDy(getDy()*-1);
        setDx(getDx()*-1);
        /*Random r = new Random();
        int angleX = r.nextInt(14);
        int angleY = r.nextInt(14);
        if(angleX < 12){
            if(angleX < 5){
                angleX += 9;
            }else{
                angleX += 5;
            }
        }
        if(angleY < 12){
            if(angleX < 5){
                angleX += 9;
            }else{
                angleX += 5;
            }
        }
        if(getDx() < 0){
            setDx(angleX*-1);
        }else{
            setDx(angleX);
        }
        if(getDy() < 0){
            setDy(angleY);
        }else{
            setDy(angleY*-1);
        }*/
    }
}