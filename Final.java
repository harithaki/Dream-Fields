//package tutu;

import javax.imageio.ImageIO;
import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import java.awt.Color;
import java.awt.EventQueue;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.io.*;
import java.net.*;

@SuppressWarnings("serial")
public class Final extends JFrame implements Runnable{
	
	static String path1 = "http://localhost:8081/out.jpg?q=30&id=0.7831696697076174&r=1466712365455";
	static JFrame f ;
	static String path;
	static URL url;
	static BufferedImage image;
	static JLabel label, l1;
	static JPanel pa, p1, p2;
	static ImageIcon icon;
	static int packetsize = 10 ;
	static byte [] data = new byte [packetsize];
	static char u = 'u';
	static char d = 'd';
    static char l = 'l';
    static char r = 'r';
    static char o = 'o';
    static char p = 'p';
	private static JButton up, up2;
	private static JButton down, down2;
	private static JButton left, right;
	private static JButton open, open2, open3;
	private static JButton close;
	private static JLabel dig;
	private static JLabel seed, seed2;
	private static JLabel water;
	static boolean isUpPressed, isDownPressed, isLeftPressed, isRightPressed, isUPressed, isDPressed, isSPressed, isAPressed, isWPressed, isQPressed;
	static PrintWriter out = null;
	
	public static void main(String[] args) throws IOException {
		new Final();

		String serverHostname = new String ("192.168.8.102");

        if (args.length > 0)
           serverHostname = args[0];
        
        System.out.println ("Attemping to connect to host " + serverHostname + " on port 7");

        Socket echoSocket = null;
        
        BufferedReader in = null;

        try {
            echoSocket = new Socket(serverHostname, 7);
            out = new PrintWriter(echoSocket.getOutputStream(), true);
            in = new BufferedReader(new InputStreamReader(
                                        echoSocket.getInputStream()));
        } catch (UnknownHostException e) {
            System.err.println("Don't know about host: " + serverHostname);
            System.exit(1);
        } catch (IOException e) {
            System.err.println("Couldn't get I/O for "
                               + "the connection to: " + serverHostname);
            System.exit(1);
        }

		BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
		
		@SuppressWarnings("unused")
		String userInput;
	
		while ((userInput = stdIn.readLine()) != null) {
	
		}
	
		out.close();
		in.close();
		stdIn.close();
		echoSocket.close();
		
	}
	
	public Final(){
			new Thread(this).start();
            EventQueue.invokeLater(new Runnable() {
            @Override
            public void run() {
                try {
                    UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
                } catch (Exception e) {
                }
                try {
                	pack();                    
                    setResizable(true);
                    setSize(1000,530);
                    
                    path = path1;
                    url = new URL(path);
                    image = ImageIO.read(url);                    
                    
                    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                    setTitle("Dream Fields");
                    
                    pa = new JPanel();
					
					pa.setLayout(new BoxLayout(pa, BoxLayout.X_AXIS));
					pa.setBackground(Color.darkGray);

					p1 = new JPanel();

                    label = new JLabel(new ImageIcon(image));                                    
			    	label.setOpaque(true);
                	label.setBounds(0,0,630,480);
                	p1.add(label);
                    
					p2 = new JPanel();
					p2.setLayout(null);
                    up = new JButton("Up");
                    up.setBounds(40, 10, 70, 25);
		        	p2.add(up);
		        	up.setMnemonic(KeyEvent.VK_UP);
		        	up.addKeyListener(new event());
		        	
		        	down = new JButton("Down");
		        	down.setBounds(40, 60, 70, 25);
		        	p2.add(down);
		        	down.setMnemonic(KeyEvent.VK_DOWN);
		        	down.addKeyListener(new event());
		        	
		        	left = new JButton("Left");
		        	left.setBounds(0, 35, 70, 25);
		        	p2.add(left);
		        	left.setMnemonic(KeyEvent.VK_LEFT);
		        	left.addKeyListener(new event());
		        	
		        	right = new JButton("Right");
		        	right.setBounds(80, 35, 70, 25);
		        	p2.add(right);
		        	right.setMnemonic(KeyEvent.VK_RIGHT);
		        	right.addKeyListener(new event());
		        	
		        	dig = new JLabel("Digging");
		        	dig.setBounds(0, 100, 50, 25);
		        	dig.setForeground (Color.BLUE);
		        	p2.add(dig);
		        	
		        	up2 = new JButton("Up");
		        	up2.setBounds(0, 130, 70, 25);
		        	p2.add(up2);
		        	down.setMnemonic(KeyEvent.VK_U);
		        	up2.addKeyListener(new event());
		        	
		        	down2 = new JButton("Down");
		        	down2.setBounds(80, 130, 70, 25);
		        	p2.add(down2);
		        	down.setMnemonic(KeyEvent.VK_D);
		        	down2.addKeyListener(new event());
		        	
		        	seed = new JLabel("Seeding");
		        	seed.setBounds(0, 170, 50, 25);
		        	seed.setForeground (Color.BLUE);
		        	p2.add(seed);
		        	
		        	open = new JButton("Drop");
		        	open.setBounds(0, 200, 70, 25);
		        	p2.add(open);
		        	down.setMnemonic(KeyEvent.VK_S);
		        	open.addKeyListener(new event());
		        	
		        	seed2 = new JLabel("Automatic Plant");
		        	seed2.setBounds(0, 240, 100, 25);
		        	seed2.setForeground (Color.BLUE);
		        	p2.add(seed2);
		        	
		        	open2 = new JButton("Plant");
		        	open2.setBounds(0, 270, 70, 25);
		        	p2.add(open2);
		        	down.setMnemonic(KeyEvent.VK_A);
		        	open2.addKeyListener(new event());
		        	
		        	water = new JLabel("Watering");
		        	water.setBounds(0, 310, 70, 25);
		        	water.setForeground (Color.BLUE);
		        	p2.add(water);
		        	
		        	open3 = new JButton("Water");
		        	open3.setBounds(0, 340, 70, 25);
		        	p2.add(open3);
		        	down.setMnemonic(KeyEvent.VK_W);
		        	open3.addKeyListener(new event());
		        	
		        	close = new JButton("Close");
		        	close.setBounds(80, 340, 70, 25);
		        	p2.add(close);
		        	down.setMnemonic(KeyEvent.VK_Q);
		        	close.addKeyListener(new event());
		        	
					add(pa);
					pa.add(p1);
					pa.add(p2);
                    setFocusable(true);
					
                    Timer timer = new Timer(41, actionListener);
                    timer.start();                    
                    
                } catch (Exception exp) {
                    exp.printStackTrace();
                }
            }
        });

	}
      
	ActionListener actionListener = new ActionListener() {
	      public void actionPerformed(ActionEvent actionEvent) {
	        
		        try {
					path = path1;
		            url = new URL(path);
		            image = ImageIO.read(url);
		            p1.remove(label);
		            label = new JLabel(new ImageIcon(image));
		            label.setOpaque(true);
		            label.setBounds(0,0,630,480);
		            p1.add(label);		            
		            setVisible(true);	            
		            
				} catch(Exception e){
					e.printStackTrace();										
				}
		      }
	};
	
	static class event implements KeyListener {
		@Override
		public void keyTyped(KeyEvent arg0) {
			// TODO Auto-generated method stub
			
		}
		
		public void keyPressed(KeyEvent ke) {
		    switch(ke.getKeyCode()) {
		        case KeyEvent.VK_UP: isUpPressed = true; up.setBackground(Color.BLUE); break;
		        case KeyEvent.VK_DOWN: isDownPressed = true; down.setBackground(Color.BLUE); break;
		        case KeyEvent.VK_LEFT: isLeftPressed = true; left.setBackground(Color.BLUE); break;
		        case KeyEvent.VK_RIGHT: isRightPressed = true; right.setBackground(Color.BLUE); break;
		        case KeyEvent.VK_U: isUPressed = true; up2.setBackground(Color.BLUE); break;
		        case KeyEvent.VK_D: isDPressed = true; down2.setBackground(Color.BLUE); break;
		        case KeyEvent.VK_S: isSPressed = true; open.setBackground(Color.BLUE); break;
		        case KeyEvent.VK_A: isAPressed = true; open2.setBackground(Color.BLUE); break;
		        case KeyEvent.VK_W: isWPressed = true; open3.setBackground(Color.BLUE); break;
		        case KeyEvent.VK_Q: isQPressed = true; close.setBackground(Color.BLUE); break;
		    }
		}
		 
		public void keyReleased(KeyEvent ke) {
		    switch(ke.getKeyCode()) {
		        case KeyEvent.VK_UP: isUpPressed = false; up.setBackground(Color.WHITE); break;
		        case KeyEvent.VK_DOWN: isDownPressed = false; down.setBackground(Color.WHITE); break;
		        case KeyEvent.VK_LEFT: isLeftPressed = false; left.setBackground(Color.WHITE); break;
		        case KeyEvent.VK_RIGHT: isRightPressed = false; right.setBackground(Color.WHITE); break;
		        case KeyEvent.VK_U: isUPressed = false; up2.setBackground(Color.WHITE); break;
		        case KeyEvent.VK_D: isDPressed = false; down2.setBackground(Color.WHITE); break;
		        case KeyEvent.VK_S: isSPressed = false; open.setBackground(Color.BLUE); break;
		        case KeyEvent.VK_A: isAPressed = false; open2.setBackground(Color.BLUE); break;
		        case KeyEvent.VK_W: isWPressed = false; open3.setBackground(Color.BLUE); break;
		        case KeyEvent.VK_Q: isQPressed = false; close.setBackground(Color.BLUE); break;
		    }
		}
	}
	
    public void run() {
        while(true) {
            try {
            	if(isUpPressed==true)	 {out.println('d'); System.out.println("u\n");Thread.sleep(50);} 
                if(isDownPressed==true)  {out.println('u');  System.out.println("d\n");Thread.sleep(50);} 
                if(isLeftPressed==true)  {out.println('l'); System.out.println("l\n");Thread.sleep(50);} 
                if(isRightPressed==true) {out.println('r'); System.out.println("r\n");Thread.sleep(50);} 
                if(isUPressed==true) {out.println('o'); System.out.println("p\n");Thread.sleep(50);} 
                if(isDPressed==true) {out.println('p'); System.out.println("o\n");Thread.sleep(50);}
                if(isSPressed==true) {out.println('s'); System.out.println("s\n");Thread.sleep(500);}
                if(isAPressed==true) {out.println('a'); System.out.println("a\n");Thread.sleep(50);}
                if(isWPressed==true) {out.println('w'); System.out.println("w\n");Thread.sleep(50);}
                if(isQPressed==true) {out.println('q'); System.out.println("q\n");Thread.sleep(50);}
                Thread.sleep(5);
            }
            catch(Exception exc) {
                exc.printStackTrace();
                break;
            }
        }
    }
}
