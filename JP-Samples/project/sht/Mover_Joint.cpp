#include "Mover.h"
#include "Hit.h"
#include "..\LibGame\Input.h"
#include <assert.h>




//==============================================================
// コンストラクタ

CJointMover::CJointMover(CMoverGroup* group)
:	CMover(group)
{}


CJointMoverGroup::CJointMoverGroup(
	CMoverGroupManager* manager, LPDIRECT3DDEVICE9 device, 
	int num_all_movers
)
:	CMoverGroup(manager, device, num_all_movers)
{
	int i;
	for (i=0; i<NumAllMovers; i++) delete AllMovers[i];
	for (i=0; i<NumAllMovers; i++) AllMovers[i]=new CJointMover(this);
	DeleteAll();
}


CJointMoverGroup::~CJointMoverGroup() {
}




//==============================================================
// 初期化

void CJointMover::Init(CMover* model_joint, CMover* parent) {
	CMover::Init(model_joint, parent);

	assert(model_joint->Group==GetGroup(JOINT_GROUP));
	CJointMover* model=(CJointMover*)model_joint;
	Joint=model->Joint;

	// 触手
	if (Valid.Tentacle) {
		JOINT& jo=Joint;
		int n=jo.NumPart-1;
		CMover* head=jo.Mover[0]=New(jo.HeadModel);
		CMover* root=jo.Mover[n]=New(jo.RootModel);
		float hx=head->X, hy=head->Y, rx=root->X, ry=root->Y;
		for (int i=1; i<n; i++) {
			CMover* body=jo.Mover[i]=New(jo.BodyModel);
			body->X=(hx*(n-i)+rx*i)/n;
			body->Y=(hy*(n-i)+ry*i)/n;
		}
	}

	// 多関節
	if (Valid.Joint) {
		JOINT& jo=Joint;
		int i, n=jo.NumPart;
		CMover* head=jo.Mover[0]=New(jo.HeadModel);
		CMover* root=jo.Mover[n-1]=New(jo.RootModel);
		for (i=1; i<n-1; i++) jo.Mover[i]=New(jo.BodyModel);
		for (i=0; i<n; i++) jo.Rad[i]=0;
		float px, py;
		px=jo.Dist*cos(jo.CRad);
		py=jo.Dist*sin(jo.CRad);
		for (i=n-2; i>=0; i--) {
			jo.Mover[i]->X=jo.Mover[i+1]->X+px;
			jo.Mover[i]->Y=jo.Mover[i+1]->Y+py;
		}
		jo.Target=GetGroup(MYSHIP_GROUP)->GetRandomUsedMover();
	}
}




//==============================================================
// 移動（後）

void CJointMover::PostMove() {
	CMover::PostMove();

	// 触手
	if (Valid.Tentacle) {
		JOINT& jo=Joint;
		CMover *head=jo.Mover[0], *root=jo.Mover[jo.NumPart-1];

		// 先端の移動範囲を制限する：
		// 先端と根元との距離が限界値を超えていたら，
		// 移動可能範囲内に戻す。
		float dx=head->X-root->X, dy=head->Y-root->Y;
		float d=sqrt(dx*dx+dy*dy);
		if (d>jo.MaxDist) {
			head->X=dx*jo.MaxDist/d+root->X;
			head->Y=dy*jo.MaxDist/d+root->Y;
		}

		// 中間部分の座標を計算する：
		// 隣接部分の座標の平均をとる。
		// 計算は先端から根元に向かって行う。
		// 必要に応じて計算を複数回繰り返す。
		for (int l=0; l<jo.NumLoop; l++) {
			for (int i=1, n=jo.NumPart-1; i<n; i++) {
				jo.Mover[i]->X=(jo.Mover[i-1]->X+jo.Mover[i+1]->X)/2;
				jo.Mover[i]->Y=(jo.Mover[i-1]->Y+jo.Mover[i+1]->Y)/2;
			}
		}
	}

	// 多関節
	if (Valid.Joint) {
		JOINT& jo=Joint;
		int i, n=jo.NumPart, n1=n-1;
		float c, s, vrad=jo.VRad, 
			x0=jo.Mover[0]->X, y0=jo.Mover[0]->Y;
		
		// 前半の処理：
		// 先端から根元に向かって関節の角度を決める。
		c=(float)cos(vrad);
		s=(float)sin(vrad);
		for (i=1; i<jo.NumPart; i++) {
			float dxt, dyt;       // 関節から目標へのベクトル
			float dxn, dyn;       // 関節から先端へのベクトル
			float dxr=0, dyr=0;   // 右回りのベクトル
			float dxl=0, dyl=0;   // 左回りのベクトル
			float dpn, dpr, dpl;  // 内積（回らない，右回り，左回り）
			
			// 関節から目標へのベクトルの計算
			dxt=jo.Target->X-jo.Mover[i]->X;
			dyt=jo.Target->Y-jo.Mover[i]->Y;

			// 関節から先端へのベクトルと内積の計算
			// （回らない場合のベクトル）
			dxn=x0-jo.Mover[i]->X;
			dyn=y0-jo.Mover[i]->Y;
			dpn=dxt*dxn+dyt*dyn;
			
			// 右回りのベクトルの計算：
			// 回転角度の限界を超えたときには回さない
			if (jo.Rad[i]+vrad<=jo.LRad) {
				dxr=c*dxn-s*dyn;
				dyr=s*dxn+c*dyn;
				dpr=dxt*dxr+dyt*dyr;
			} else dpr=dpn;
			
			// 左回りのベクトルの計算：
			// 回転角度の限界を超えたときには回さない
			if (jo.Rad[i]-vrad>=-jo.LRad) {
				dxl= c*dxn+s*dyn;
				dyl=-s*dxn+c*dyn;
				dpl=dxt*dxl+dyt*dyl;
			} else dpl=dpn;
			
			// 回転方向の選択：
			// 内積を比較して，回転を3通りの中から選ぶ。
			// 先端を回転させて，新しい先端の位置を求める。
			if (dpr>dpn && dpr>dpl) {
				jo.Rad[i]+=vrad;
				x0=jo.Mover[i]->X+dxr;
				y0=jo.Mover[i]->Y+dyr;
			}
			if (dpl>dpn && dpl>dpr) {
				jo.Rad[i]-=vrad;
				x0=jo.Mover[i]->X+dxl;
				y0=jo.Mover[i]->Y+dyl;
			}
		}
		
		// 後半の処理：
		// 根元から先端に向かって関節の位置を求める。
		float px, py, qx, qy;
		px=jo.Dist*cos(jo.CRad);
		py=jo.Dist*sin(jo.CRad);
		for (i=n-2; i>=0; i--) {
			c=(float)cos(jo.Rad[i+1]);
			s=(float)sin(jo.Rad[i+1]);
			qx=c*px-s*py;
			qy=s*px+c*py;
			jo.Mover[i]->X=jo.Mover[i+1]->X+qx;
			jo.Mover[i]->Y=jo.Mover[i+1]->Y+qy;
			px=qx;
			py=qy;
		}
	}
}




//==============================================================
// 設定

// 触手
CJointMover* CJointMover::SetTentacle(
	CMover* head, CMover* body, CMover* root, 
	int num_part, int num_loop, float max_dist
) {
	Valid.Tentacle=true;
	Joint.HeadModel=head;
	Joint.BodyModel=body;
	Joint.RootModel=root;
	Joint.NumPart=num_part;
	Joint.NumLoop=num_loop;
	Joint.MaxDist=max_dist;
	return this;
}

// 多関節
CJointMover* CJointMover::SetJoint(
	CMover* head, CMover* body, CMover* root, 
	int num_part, float center_angle, float vangle, float limit_angle, float dist
) {
	Valid.Joint=true;
	Joint.HeadModel=head;
	Joint.BodyModel=body;
	Joint.RootModel=root;
	Joint.NumPart=num_part;
	Joint.CRad=D3DX_PI*2*center_angle;
	Joint.VRad=D3DX_PI*2*vangle;
	Joint.LRad=D3DX_PI*2*limit_angle;
	Joint.Dist=dist;
	return this;
}

