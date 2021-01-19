/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dodgeball.presentation;
import dodgeball.Ball;
import dodgeball.Circle;
import dodgeball.Racket;
import java.util.ArrayList;
import java.util.Observable;
import java.util.Random;

/**
 * @author Luis David Villalobos González
 */
public class Model extends Observable  {
    private final ArrayList<Ball> balls;
    private Circle circle;
    private Racket racket;
    private int delay;
    private boolean execute;
    private int points;
    public static final int ARR=1;
    public static final int ABA=2;
    public static final int IZQ=3;
    public static final int DER=4;

    public Model() {
        circle = new Circle(395,366,277);
        racket = new Racket(355,505,0,0,137,50,15);
        balls = new ArrayList<>();
        delay = 80;
        points = 0;
        execute = true;
        this.numberOfBalls(1);
    }
    
    public ArrayList<Ball> getBalls() {
        return balls;
    }

    public Circle getCircle() {
        return circle;
    }

    public void setCircle(Circle circle) {
        this.circle = circle;
    }

    public Racket getRacket() {
        return racket;
    }

    public void setRacket(Racket racket) {
        this.racket = racket;
    }

    public int getDelay() {
        return delay;
    }

    public void setDelay(int delay) {
        this.delay = delay;
    }

    public boolean getExecute() {
        return execute;
    }

    public void setExecute(boolean execute) {
        this.execute = execute;
    }

    public int getPoints() {
        return points;
    }

    public void setPoints(int points) {
        this.points = points;
    }
    
    public void start(){
        try{ Thread.sleep(800); }
        catch(InterruptedException es){}
        Runnable code = new Runnable(){
            public void run(){
                while(execute){
                    step();
                    setChanged();
                    notifyObservers();
                    try{
                        Thread.sleep(delay);
                    }
                    catch(InterruptedException es){
                        
                    }
                }
            }
        };
        Thread thread = new Thread(code);
        thread.start();   
    }
    
    public void move(int flecha){
        switch(flecha){
            case ARR: racket.setDy(-racket.speed); break;
            case ABA: racket.setDy(racket.speed); break;
            case IZQ: racket.setDx(-racket.speed); break;
            case DER: racket.setDx(racket.speed); break;
        }
    }
    
    public void stopVer(){
        racket.setDy(0);
    }
    
    public void stopHor(){
        racket.setDx(0);
    }
    
    public void step(){
       for(int i = 0; i< balls.size(); i++){
           balls.get(i).move(this);
       }
       racket.move(this);
       this.setChanged();
       this.notifyObservers();
    }
   
   @Override
   public void addObserver(java.util.Observer o){
       super.addObserver(o);
       setChanged();
       notifyObservers();
   }
    
   public void numberOfBalls(int nBalls){
        balls.clear();
        for (int i = 0; i < nBalls; i++) {
            Random n = new Random();
            boolean sx = n.nextBoolean();
            boolean sy = n.nextBoolean();
            int x = 15; 
            int y = 15;
            if(sx){
                x -= 2*x;
            }
            if(sy){
                y -= 2*y;
            }
            balls.add(new Ball(circle.getX(),circle.getY(),x,y,28));
        }
    }
}