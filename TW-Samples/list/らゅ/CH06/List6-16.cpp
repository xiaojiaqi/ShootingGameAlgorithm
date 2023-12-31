#include <math.h>

void MoveJoints(
	int num_joint,         // 関節の?
	float x[], float y[],  // 関節の座標
	float rad[],           // 関節の回転角ﾃg
	float vrad,            // 関節ｸm回転する速さ
	float lrad,            // 回転角ﾃgの限界値
	float dist,            // 関節間の?離
	float tx, float ty     // 目標の座標
) {
	int i;
	float c, s;
	
	// 前半の??：
	// 先端から根元にﾅﾘかって関節の角ﾃgを?める。
	c=(float)cos(vrad);
	s=(float)sin(vrad);
	for (i=1; i<num_joint; i++) {
		float dxt, dyt;       // 関節から目標へのベクト?
		float dxn, dyn;       // 関節から先端へのベクト?
		float dxr=0, dyr=0;   // �ｸ回りのベクト?
		float dxl=0, dyl=0;   // 左回りのベクト?
		float dpn, dpr, dpl;  // �ｯ積（回らない，�ｸ回り，左回り）
		
		// 関節から目標へのベクト?の計算
		dxt=tx-x[i];
		dyt=ty-y[i];

		// 関節から先端へのベクト?と�ｯ積の計算
		// （回らない場?のベクト?）
		dxn=x[0]-x[i];
		dyn=y[0]-y[i];
		dpn=dxt*dxn+dyt*dyn;
		
		// �ｸ回りのベクト?の計算：
		// 回転角ﾃgの限界を超ｷVたとｪｽには回さない
		if (rad[i]+vrad<=lrad) {
			dxr=c*dxn-s*dyn;
			dyr=s*dxn+c*dyn;
			dpr=dxt*dxr+dyt*dyr;
		} else dpr=dpn;
		
		// 左回りのベクト?の計算：
		// 回転角ﾃgの限界を超ｷVたとｪｽには回さない
		if (rad[i]-vrad>=-lrad) {
			dxl= c*dxn+s*dyn;
			dyl=-s*dxn+c*dyn;
			dpl=dxt*dxl+dyt*dyl;
		} else dpl=dpn;
		
		// 回転方ﾅﾘの選択：
		// �ｯ積を比較して，回転を3通りの?から選ぶ。
		// 先端を回転させて，�閧ｵい先端の位置を?める。
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
	
	// 後半の??：
	// 根元から先端にﾅﾘかって関節の位置を?める。
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
