import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class 多關節 extends 觸手 {
	
	static final float Dist=15, VRad=0.002f, LRad=0.2f;
	float[] Rad;

	public static void main(String[] args) {
		(new Thread(new 多關節())).start();
	}
	

	public 多關節() {
		setTitle("多關節");
		Rad=new float[NUM_PART];
		for (int i=0; i<NUM_PART; i++) {
			Rad[i]=VRad;
		}
	}
	
	void updatePos() {
		int i;
		float c, s;
		
		c=(float)Math.cos(VRad);
		s=(float)Math.sin(VRad);
		for (i=1; i<NUM_PART; i++) {
			float dxt, dyt;
			float dxn, dyn;
			float dxr=0, dyr=0;
			float dxl=0, dyl=0;
			float dpn, dpr, dpl;
			

			dxt=TX-X[i];
			dyt=TY-Y[i];

			dxn=X[0]-X[i];
			dyn=Y[0]-Y[i];
			dpn=dxt*dxn+dyt*dyn;
			
			if (Rad[i]+VRad<=LRad) {
				dxr=c*dxn-s*dyn;
				dyr=s*dxn+c*dyn;
				dpr=dxt*dxr+dyt*dyr;
			} else dpr=dpn;
			
			if (Rad[i]-VRad>=-LRad) {
				dxl= c*dxn+s*dyn;
				dyl=-s*dxn+c*dyn;
				dpl=dxt*dxl+dyt*dyl;
			} else dpl=dpn;
			
			if (dpr>dpn && dpr>dpl) {
				Rad[i]+=VRad;
				X[0]=X[i]+dxr;
				Y[0]=Y[i]+dyr;
			}
			if (dpl>dpn && dpl>dpr) {
				Rad[i]-=VRad;
				X[0]=X[i]+dxl;
				Y[0]=Y[i]+dyl;
			}
		}
		
		float px=Dist, py=0, qx, qy;
		for (i=NUM_PART-2; i>=0; i--) {
			c=(float)Math.cos(Rad[i+1]);
			s=(float)Math.sin(Rad[i+1]);
			qx=c*px-s*py;
			qy=s*px+c*py;
			X[i]=X[i+1]+qx;
			Y[i]=Y[i+1]+qy;
			px=qx;
			py=qy;
		}
	}
}



