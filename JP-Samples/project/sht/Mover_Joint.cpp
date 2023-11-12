#include "Mover.h"
#include "Hit.h"
#include "..\LibGame\Input.h"
#include <assert.h>




//==============================================================
// �R���X�g���N�^

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
// ������

void CJointMover::Init(CMover* model_joint, CMover* parent) {
	CMover::Init(model_joint, parent);

	assert(model_joint->Group==GetGroup(JOINT_GROUP));
	CJointMover* model=(CJointMover*)model_joint;
	Joint=model->Joint;

	// �G��
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

	// ���֐�
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
// �ړ��i��j

void CJointMover::PostMove() {
	CMover::PostMove();

	// �G��
	if (Valid.Tentacle) {
		JOINT& jo=Joint;
		CMover *head=jo.Mover[0], *root=jo.Mover[jo.NumPart-1];

		// ��[�̈ړ��͈͂𐧌�����F
		// ��[�ƍ����Ƃ̋��������E�l�𒴂��Ă�����C
		// �ړ��\�͈͓��ɖ߂��B
		float dx=head->X-root->X, dy=head->Y-root->Y;
		float d=sqrt(dx*dx+dy*dy);
		if (d>jo.MaxDist) {
			head->X=dx*jo.MaxDist/d+root->X;
			head->Y=dy*jo.MaxDist/d+root->Y;
		}

		// ���ԕ����̍��W���v�Z����F
		// �אڕ����̍��W�̕��ς��Ƃ�B
		// �v�Z�͐�[���獪���Ɍ������čs���B
		// �K�v�ɉ����Čv�Z�𕡐���J��Ԃ��B
		for (int l=0; l<jo.NumLoop; l++) {
			for (int i=1, n=jo.NumPart-1; i<n; i++) {
				jo.Mover[i]->X=(jo.Mover[i-1]->X+jo.Mover[i+1]->X)/2;
				jo.Mover[i]->Y=(jo.Mover[i-1]->Y+jo.Mover[i+1]->Y)/2;
			}
		}
	}

	// ���֐�
	if (Valid.Joint) {
		JOINT& jo=Joint;
		int i, n=jo.NumPart, n1=n-1;
		float c, s, vrad=jo.VRad, 
			x0=jo.Mover[0]->X, y0=jo.Mover[0]->Y;
		
		// �O���̏����F
		// ��[���獪���Ɍ������Ċ֐߂̊p�x�����߂�B
		c=(float)cos(vrad);
		s=(float)sin(vrad);
		for (i=1; i<jo.NumPart; i++) {
			float dxt, dyt;       // �֐߂���ڕW�ւ̃x�N�g��
			float dxn, dyn;       // �֐߂����[�ւ̃x�N�g��
			float dxr=0, dyr=0;   // �E���̃x�N�g��
			float dxl=0, dyl=0;   // �����̃x�N�g��
			float dpn, dpr, dpl;  // ���ρi���Ȃ��C�E���C�����j
			
			// �֐߂���ڕW�ւ̃x�N�g���̌v�Z
			dxt=jo.Target->X-jo.Mover[i]->X;
			dyt=jo.Target->Y-jo.Mover[i]->Y;

			// �֐߂����[�ւ̃x�N�g���Ɠ��ς̌v�Z
			// �i���Ȃ��ꍇ�̃x�N�g���j
			dxn=x0-jo.Mover[i]->X;
			dyn=y0-jo.Mover[i]->Y;
			dpn=dxt*dxn+dyt*dyn;
			
			// �E���̃x�N�g���̌v�Z�F
			// ��]�p�x�̌��E�𒴂����Ƃ��ɂ͉񂳂Ȃ�
			if (jo.Rad[i]+vrad<=jo.LRad) {
				dxr=c*dxn-s*dyn;
				dyr=s*dxn+c*dyn;
				dpr=dxt*dxr+dyt*dyr;
			} else dpr=dpn;
			
			// �����̃x�N�g���̌v�Z�F
			// ��]�p�x�̌��E�𒴂����Ƃ��ɂ͉񂳂Ȃ�
			if (jo.Rad[i]-vrad>=-jo.LRad) {
				dxl= c*dxn+s*dyn;
				dyl=-s*dxn+c*dyn;
				dpl=dxt*dxl+dyt*dyl;
			} else dpl=dpn;
			
			// ��]�����̑I���F
			// ���ς��r���āC��]��3�ʂ�̒�����I�ԁB
			// ��[����]�����āC�V������[�̈ʒu�����߂�B
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
		
		// �㔼�̏����F
		// ���������[�Ɍ������Ċ֐߂̈ʒu�����߂�B
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
// �ݒ�

// �G��
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

// ���֐�
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

