import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class 觸手 extends JFrame implements Runnable {

	static final int WIDTH=800, HEIGHT=600, R=10;
	static final int NUM_PART=30;
	float[] X, Y;
	float TX, TY;

	public static void main(String[] args) {
		(new Thread(new 觸手())).start();
	}
	
	public 觸手() {
		setTitle("觸手");
		setSize(WIDTH, HEIGHT);

		X=new float[NUM_PART];
		Y=new float[NUM_PART];
		for (int i=0; i<NUM_PART; i++) {
			X[i]=WIDTH/2-i*WIDTH/2/NUM_PART;
			Y[i]=HEIGHT/2;
		}

		Container cp=getContentPane();
		cp.setLayout(new BorderLayout());
		cp.add(new JComponent() {
			public void paint(Graphics gra) {
				setBackground(Color.white);
				gra.clearRect(0, 0, 觸手.WIDTH, 觸手.HEIGHT);
				gra.setColor(Color.black);
				for (int i=0; i<NUM_PART; i++) {
					gra.fillOval(
						(int)X[i]-R, (int)Y[i]-R, 
						R*2, R*2);
				}
			}
		}, BorderLayout.CENTER);

		addMouseMotionListener(new MouseMotionAdapter() {
			public void mouseMoved(MouseEvent e) {
				TX=e.getX();
				TY=e.getY();
			}
		});

		addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				System.exit(0);
			}
		});

		setVisible(true);
	}
	

	public void run() {
		while (true) {
			updatePos();
			repaint();
			try { Thread.sleep(20); } 
				catch (InterruptedException ie) { break; }
		}
	}

	void updatePos() {
		final float LIMIT=600, MIN_LIMIT=200;
		final int WARP=5;
		final float V=4;
		X[0]+=(TX>X[0]+V?V:(TX<X[0]-V?-V:0));
		Y[0]+=(TY>Y[0]+V?V:(TY<Y[0]-V?-V:0));
		
		float dx=X[0]-X[NUM_PART-1], dy=Y[0]-Y[NUM_PART-1];
		float d=(float)Math.sqrt(dx*dx+dy*dy);
		if (d>LIMIT) {
			X[0]=dx*LIMIT/d+X[NUM_PART-1];
			Y[0]=dy*LIMIT/d+Y[NUM_PART-1];
		}
		if (d<MIN_LIMIT) {
			X[0]=dx*MIN_LIMIT/d+X[NUM_PART-1];
			Y[0]=dy*MIN_LIMIT/d+Y[NUM_PART-1];
		}
		
		for (int w=0; w<WARP; w++) {
		for (int i=1; i<NUM_PART-1; i++) {
			X[i]=(X[i-1]+X[i+1])/2;
			Y[i]=(Y[i-1]+Y[i+1])/2;
		}
		}
	}
}



