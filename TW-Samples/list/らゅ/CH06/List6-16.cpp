#include <math.h>

void MoveJoints(
	int num_joint,         // ŠÖß‚Ì?
	float x[], float y[],  // ŠÖß‚ÌÀ•W
	float rad[],           // ŠÖß‚Ì‰ñ“]ŠpÃg
	float vrad,            // ŠÖß¸m‰ñ“]‚·‚é‘¬‚³
	float lrad,            // ‰ñ“]ŠpÃg‚ÌŒÀŠE’l
	float dist,            // ŠÖßŠÔ‚Ì?—£
	float tx, float ty     // –Ú•W‚ÌÀ•W
) {
	int i;
	float c, s;
	
	// ‘O”¼‚Ì??F
	// æ’[‚©‚çªŒ³‚ÉÅØ‚©‚Á‚ÄŠÖß‚ÌŠpÃg‚ð?‚ß‚éB
	c=(float)cos(vrad);
	s=(float)sin(vrad);
	for (i=1; i<num_joint; i++) {
		float dxt, dyt;       // ŠÖß‚©‚ç–Ú•W‚Ö‚ÌƒxƒNƒg?
		float dxn, dyn;       // ŠÖß‚©‚çæ’[‚Ö‚ÌƒxƒNƒg?
		float dxr=0, dyr=0;   // …¸‰ñ‚è‚ÌƒxƒNƒg?
		float dxl=0, dyl=0;   // ¶‰ñ‚è‚ÌƒxƒNƒg?
		float dpn, dpr, dpl;  // …¯Ïi‰ñ‚ç‚È‚¢C…¸‰ñ‚èC¶‰ñ‚èj
		
		// ŠÖß‚©‚ç–Ú•W‚Ö‚ÌƒxƒNƒg?‚ÌŒvŽZ
		dxt=tx-x[i];
		dyt=ty-y[i];

		// ŠÖß‚©‚çæ’[‚Ö‚ÌƒxƒNƒg?‚Æ…¯Ï‚ÌŒvŽZ
		// i‰ñ‚ç‚È‚¢ê?‚ÌƒxƒNƒg?j
		dxn=x[0]-x[i];
		dyn=y[0]-y[i];
		dpn=dxt*dxn+dyt*dyn;
		
		// …¸‰ñ‚è‚ÌƒxƒNƒg?‚ÌŒvŽZF
		// ‰ñ“]ŠpÃg‚ÌŒÀŠE‚ð’´·V‚½‚Æª½‚É‚Í‰ñ‚³‚È‚¢
		if (rad[i]+vrad<=lrad) {
			dxr=c*dxn-s*dyn;
			dyr=s*dxn+c*dyn;
			dpr=dxt*dxr+dyt*dyr;
		} else dpr=dpn;
		
		// ¶‰ñ‚è‚ÌƒxƒNƒg?‚ÌŒvŽZF
		// ‰ñ“]ŠpÃg‚ÌŒÀŠE‚ð’´·V‚½‚Æª½‚É‚Í‰ñ‚³‚È‚¢
		if (rad[i]-vrad>=-lrad) {
			dxl= c*dxn+s*dyn;
			dyl=-s*dxn+c*dyn;
			dpl=dxt*dxl+dyt*dyl;
		} else dpl=dpn;
		
		// ‰ñ“]•ûÅØ‚Ì‘I‘ðF
		// …¯Ï‚ð”äŠr‚µ‚ÄC‰ñ“]‚ð3’Ê‚è‚Ì?‚©‚ç‘I‚ÔB
		// æ’[‚ð‰ñ“]‚³‚¹‚ÄCöè‚µ‚¢æ’[‚ÌˆÊ’u‚ð?‚ß‚éB
		if (dpr>dpn && dpr>dpl) {
			rad[i]+=vrad;
			x[0]=x[i]+dxr;
			y[0]=y[i]+dyr;
		}
		if (dpl>dpn && dpl>dpr) {
			rad[i]-=vrad;
			x[0]=x[i]+dxl;
			y[0]=y[i]+dyl;
		}
	}
	
	// Œã”¼‚Ì??F
	// ªŒ³‚©‚çæ’[‚ÉÅØ‚©‚Á‚ÄŠÖß‚ÌˆÊ’u‚ð?‚ß‚éB
	float px=dist, py=0, qx, qy;
	for (i=num_joint-2; i>=0; i--) {
		c=(float)cos(rad[i+1]);
		s=(float)sin(rad[i+1]);
		qx=c*px-s*py;
		qy=s*px+c*py;
		x[i]=x[i+1]+qx;
		y[i]=y[i+1]+qy;
		px=qx;
		py=qy;
	}
}
