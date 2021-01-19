/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dodgeball.presentation;
 /**
 * @author Luis David Villalobos González
 */
import dodgeball.Ball;
import dodgeball.Circle;
import dodgeball.Racket;
import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.event.KeyEvent;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.util.Observable;
import java.util.Observer;
import javax.imageio.ImageIO;
import javax.sound.sampled.AudioFormat;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.sound.sampled.DataLine;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
public class View extends JFrame implements Observer {
    private Model model;
    private Controller controller;
    private Image ballImage, circleImage, rectangleImage;
    private Clip lose, win, startGame;
    private static final String BALL_PATH ="/media/star.png"; 
    private static final String BACKGROUND_PATH ="/media/space.png";
    private static final String RECTANGLE_PATH ="/media/space_ship.png";
    private static final String LOSE_PATH = "/media/lose.wav";
    private static final String WIN_PATH = "/media/win.wav";
    private static final String STARTGAME_PATH = "/media/startGame.wav";
    private javax.swing.JMenuBar jMenuBar1;
    private javax.swing.JMenu mFile;
    private javax.swing.JMenu mEdit;
    private javax.swing.JMenu mAbout;
    private javax.swing.JMenuItem mIsettings;
    private javax.swing.JMenuItem mIexit;
    private javax.swing.JMenuItem mIdodgeBall;
    private javax.swing.JLabel score;
    private javax.swing.JLabel background;
    BufferedImage buffer;
    
    public View() {
        this.setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        this.setSize(854, 660);
        setMinimumSize(new java.awt.Dimension(854, 660));
        setMaximumSize(new java.awt.Dimension(854, 660));
        this.setContentPane(new JPanel(){});
        getContentPane().setLayout(null);
        this.setTitle("DodgeBall 1.0");
        try{
            buffer = new BufferedImage(this.getWidth(), this.getHeight(), BufferedImage.TYPE_INT_RGB);
            ballImage = ImageIO.read(getClass().getResourceAsStream(BALL_PATH));
            circleImage = ImageIO.read(getClass().getResourceAsStream(BACKGROUND_PATH));
            rectangleImage = ImageIO.read(getClass().getResourceAsStream(RECTANGLE_PATH));
            lose = this.loadSound(LOSE_PATH);
            win = this.loadSound(WIN_PATH);
            startGame = this.loadSound(STARTGAME_PATH);
            score = new javax.swing.JLabel();
            score.setFont(new java.awt.Font("Century Gothic", 1, 22));
            score.setForeground(new java.awt.Color(255, 102, 0));
            score.setBorder(javax.swing.BorderFactory.createMatteBorder(2, 2, 2, 2, new java.awt.Color(255, 102, 0)));
            getContentPane().add(score);
            score.setBounds(670, 12, 140, 35);
            background = new javax.swing.JLabel();
            background.setIcon(new javax.swing.ImageIcon(circleImage));
            getContentPane().add(background);
            background.setBounds(0, 0, 854, 598);
            
            jMenuBar1 = new javax.swing.JMenuBar();
            setJMenuBar(jMenuBar1);
            mFile = new javax.swing.JMenu();
            mFile.setText("File");
            mAbout = new javax.swing.JMenu();
            mAbout.setText("About");
            mEdit = new javax.swing.JMenu();
            mEdit.setText("Edit");
            mIsettings = new javax.swing.JMenuItem();
            mIsettings.setText("Settings");
            mIexit = new javax.swing.JMenuItem();
            mIexit.setText("Exit");
            mIdodgeBall = new javax.swing.JMenuItem();
            mIdodgeBall.setText("DodgeBall");
            mFile.add(mIexit);
            mEdit.add(mIsettings);
            mAbout.add(mIdodgeBall);
            jMenuBar1.add(mFile);
            jMenuBar1.add(mEdit);
            jMenuBar1.add(mAbout);
            
        }catch(IOException ex){}
        
        this.addKeyListener(new java.awt.event.KeyAdapter(){
            public void keyPressed(java.awt.event.KeyEvent evt){
                fromKeyPressed(evt);
            }
            public void keyReleased(java.awt.event.KeyEvent evt){
                fromKeyReleased(evt);
            }
        });
        
        mIexit.addActionListener(new java.awt.event.ActionListener() {
                public void actionPerformed(java.awt.event.ActionEvent evt) {
                    mIexitActionPerformed(evt);
                }
        }); 
        
        mIsettings.addActionListener(new java.awt.event.ActionListener() {
                public void actionPerformed(java.awt.event.ActionEvent evt) {
                    mIsettingsActionPerformed(evt);
                }
        }); 
        
        mIdodgeBall.addActionListener(new java.awt.event.ActionListener() {
                public void actionPerformed(java.awt.event.ActionEvent evt) {
                    mIdodgeBallActionPerformed(evt);
                }
        });  
        pack();
    }
    
    Clip loadSound(String path){
        try{
            AudioInputStream audioInputStream = AudioSystem.getAudioInputStream(getClass().getResourceAsStream(path));
            AudioFormat soundFormat = audioInputStream.getFormat();
            int soundSize=(int) (soundFormat.getFrameSize() * audioInputStream.getFrameLength());
            byte[] soundData = new byte[soundSize];
            DataLine.Info soundInfo = new DataLine.Info(Clip.class, soundFormat, soundSize);
            audioInputStream.read(soundData, 0, soundSize);
            Clip clip = (Clip) AudioSystem.getLine(soundInfo);
            clip.open(soundFormat, soundData, 0, soundSize);
            return clip;
        }
        catch(Exception e){return null;}
    }
    
    private void fromKeyPressed(java.awt.event.KeyEvent evt){
        switch(evt.getKeyCode()){
            case KeyEvent.VK_UP: controller.move(Model.ARR); break;
            case KeyEvent.VK_DOWN: controller.move(Model.ABA); break; 
            case KeyEvent.VK_LEFT: controller.move(Model.IZQ); break;
            case KeyEvent.VK_RIGHT: controller.move(Model.DER); break;
        }
    }
    
    private void fromKeyReleased(java.awt.event.KeyEvent evt){
        int key = evt.getKeyCode();
        switch(key){
            case KeyEvent.VK_LEFT: case KeyEvent.VK_RIGHT: controller.stopHor(); break;
            case KeyEvent.VK_UP: case KeyEvent.VK_DOWN: controller.stopVer(); break;
        }
    }

    public Model getModel() { return model; }

    public void setModel(Model model) {
        this.model = model;
        model.addObserver(this);
    }

    public Controller getController() { return controller; }

    public void setController(Controller controller) { this.controller = controller; }
    
    @Override
    public void update(Observable o, Object arg){
        this.repaint();
    }
    
    @Override
    public void paint(Graphics g){
        Graphics graph = buffer.getGraphics();
        super.paint(graph);
        this.renderModel(model, graph);
        g.drawImage(buffer,0,0,null);
    }
    
    void renderModel(Model m, Graphics media){
        score.setText(" SCORE: " + model.getPoints());
        renderCircle(m.getCircle(), media);
        renderRacket(m.getRacket(), media);
        for(int i = 0; i < m.getBalls().size(); i++){
            renderBall(m.getBalls().get(i), media);
        }
    }
    
void renderBall(Ball b, Graphics g){
        g.drawImage(ballImage, (int)(b.getX()-b.getRadio()-7), (int)(b.getY() - b.getRadio()-7), this);
        Graphics2D circulo = (Graphics2D) g;
        circulo.setStroke(new BasicStroke(2.f));
        circulo.setPaint(Color.red);
        if(b.getWin()){
            win.setFramePosition(0);
            win.start();
            model.setPoints(model.getPoints()+1);
            b.setWin(false);
        }
        if(b.getLose()){
            lose.setFramePosition(0);
            lose.start();
            model.setPoints(model.getPoints()-1);
            b.setLose(false);
        }
    }

    public void renderCircle(Circle c, Graphics media){
        Graphics2D circulo = (Graphics2D) media;
        circulo.setStroke(new BasicStroke(6.f));
        media.setColor(Color.black);
        media.drawOval(c.getX() - c.getRadio(), c.getY() - c.getRadio(), c.getDiameter(), c.getDiameter());
        media.setColor(Color.green);
        for (int i = 20; i <= 380; i+=90) {
            media.drawArc(c.getX() - c.getRadio(), c.getY() - c.getRadio(), c.getDiameter(), c.getDiameter(), i, 17);
        }
        media.setColor(Color.red);
        for(int i = 65; i <= 355; i+=90){
            media.drawArc(c.getX() - c.getRadio(), c.getY() - c.getRadio(), c.getDiameter(), c.getDiameter(), i, 17);
        }
    }
    
    void renderRacket(Racket raq, Graphics media){
        media.drawImage(rectangleImage, (int) raq.getX(), (int) raq.getY(), this);
    }
    
    private void mIexitActionPerformed(java.awt.event.ActionEvent evt){
        controller.pause();
	System.exit(0);
    }
    
    private void mIsettingsActionPerformed(java.awt.event.ActionEvent evt){
	controller.pause();
        int numB; 
        int spd;
        JTextField balls = new JTextField();
        JTextField speed = new JTextField();
        Object[] message = {
        	"Balls: ", balls,
                "Speed: ", speed
        };
        int option = JOptionPane.showConfirmDialog(null, message, "Settings", JOptionPane.OK_CANCEL_OPTION);
        if(option == JOptionPane.OK_OPTION){
            try{
                if(speed.getText().length() == 0){
                    spd = model.getDelay();
                }
                else{
                    spd = Integer.parseInt(speed.getText());
                }
                if(balls.getText().length() == 0){
                    numB = model.getBalls().size();
                }
                else{
                    numB = Integer.parseInt(balls.getText());
                }
                controller.settings(numB, spd);
            }
            catch(Exception e){}
	}
        startGame.setFramePosition(0);
        startGame.start();
        controller.activate();
    }
    
    private void mIdodgeBallActionPerformed(java.awt.event.ActionEvent evt){
        controller.pause();
	JOptionPane.showMessageDialog(this, "DodgeBall 1.0. Programacion III. Escuela de Informatica. Universidad Nacional","About DodgeBall",JOptionPane.PLAIN_MESSAGE);
        controller.activate();
    }
    
}
