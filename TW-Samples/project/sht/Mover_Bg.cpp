#include "Mover.h"
#include "Hit.h"
#include "..\LibGame\Input.h"
#include <assert.h>




//==============================================================
// �غc���B�Ѻc��

// �غc��
CBgMover::CBgMover(CMoverGroup* group)
:	CMover(group)
{}


// �غc���]Group�^
CBgMoverGroup::CBgMoverGroup(
	CMoverGroupManager* manager, LPDIRECT3DDEVICE9 device, 
	int num_all_movers
)
:	CMoverGroup(manager, device, num_all_movers), 
	StarVertexBuffer(NULL)
{
	// ���I�w�İϪ��s�@
	if (!StarVertexBuffer) {
		Device->CreateVertexBuffer(
			MAX_STARS*sizeof(STAR_VERTEX), 0, D3DFVF_STAR_VERTEX, 
			D3DPOOL_MANAGED, &StarVertexBuffer, NULL);
	}

	int i;
	for (i=0; i<NumAllMovers; i++) delete AllMovers[i];
	for (i=0; i<NumAllMovers; i++) AllMovers[i]=new CBgMover(this);
	DeleteAll();
}


// �Ѻc���]Group�^
CBgMoverGroup::~CBgMoverGroup() {
	if (StarVertexBuffer) {
		StarVertexBuffer->Release();
		StarVertexBuffer=NULL;
	}
}




//==============================================================
// ��l��

// ��l��
void CBgMover::Init(CMover* model_bg, CMover* parent) {
	CMover::Init(model_bg, parent);

	assert(model_bg->Group==GetGroup(BG_GROUP));
	CBgMover* model=(CBgMover*)model_bg;
	Star=model->Star;

	// �P�P
	if (Valid.Star) {
		if (Star.Obj3D) {
			float 
				cx=(Star.X0+Star.X1)/2, w=Star.X1-Star.X0,
				cy=(Star.Y0+Star.Y1)/2, h=Star.Y1-Star.Y0;
			for (int i=0; i<Star.Num; i++) {
				Star.X[i]=cx+w*Rand05();
				Star.Y[i]=cy+h*Rand05();
			}
		} else {
			int a0=(Star.MinARGB>>24&255),
				a1=(Star.MaxARGB>>24&255)-a0,
				r0=(Star.MinARGB>>16&255),
				r1=(Star.MaxARGB>>16&255)-r0,
				g0=(Star.MinARGB>> 8&255),
				g1=(Star.MaxARGB>> 8&255)-g0,
				b0=(Star.MinARGB    &255),
				b1=(Star.MaxARGB    &255)-b0;
			for (int i=0; i<Star.Num; i++) {
				Star.X[i]=Rand1();
				Star.Y[i]=Rand1();
				Star.Color[i]=D3DCOLOR_ARGB(
					(int)(a0+Rand1()*a1), (int)(r0+Rand1()*r1), 
					(int)(g0+Rand1()*g1), (int)(b0+Rand1()*b1));
			}
		}
	}
}




//==============================================================
// ����

void CBgMover::Move() {
	CMover::Move();

	// �P�P
	if (Valid.Star) {
		if (Star.Obj3D) {
			for (int i=0; i<Star.Num; i++) {
				float& x=Star.X[i];
				float& y=Star.Y[i];
				x+=VX;
				y+=VY;
				if (x<Star.X0) x=Star.X1; else
				if (x>Star.X1) x=Star.X0;
				if (y<Star.Y0) y=Star.Y1; else
				if (y>Star.Y1) y=Star.Y0;
			}
		} else {
			for (int i=0; i<Star.Num; i++) {
				float& x=Star.X[i];
				float& y=Star.Y[i];
				x+=VX;
				y+=VY;
				if (x<0) x=1; else if (x>1) x=0;
				if (y<0) y=1; else if (y>1) y=0;
			}
		}
	}
}




//==============================================================
// �yø

void CBgMover::Draw() {
	CMover::Draw();

	// �P�P
	if (Valid.Star) {
		if (Star.Obj3D) {
			for (int i=0; i<Star.Num; i++) {
				Star.Obj3D->DrawTopView(
					Star.X[i], Star.Y[i], Z, 1, 1, 0, 0, 0, 1, false);
			}
		} else {
			assert(Group==Group->GetManager()->GetGroup(BG_GROUP));
			LPDIRECT3DVERTEXBUFFER9 vb=
				((CBgMoverGroup*)Group)->GetStarVertexBuffer();

			// ��w���I�w�İ�
			STAR_VERTEX* v;
			if (SUCCEEDED(vb->Lock(0, Star.Num*sizeof(STAR_VERTEX), (void**)&v, 0))) {
				LPDIRECT3DDEVICE9 device=Group->GetDevice();
				D3DVIEWPORT9 vp;
				device->GetViewport(&vp);
				float x=(float)vp.X, y=(float)vp.Y, w=(float)vp.Width, h=(float)vp.Height;

				// ���I�y�Ъ��]�w
				for (int i=0; i<Star.Num; i++) {
					v[i].X=Star.X[i]*w+x;
					v[i].Y=Star.Y[i]*h+y;
					v[i].Z=Z;
					v[i].RHW=1;
					v[i].Color=Star.Color[i];
				}
				vb->Unlock();

				// �yø
				// Z�O�̫e���O0�A�̫᭱�O1�C
				// device->SetRenderState(D3DRS_ZENABLE, FALSE);
				// �]�����ϥ�Z�w�İϦb�̭I���W�yø�P�P����k
				device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_DISABLE);
				device->SetStreamSource(0, vb, 0, sizeof(STAR_VERTEX));
				device->SetFVF(D3DFVF_STAR_VERTEX);
				device->DrawPrimitive(D3DPT_POINTLIST, 0, Star.Num);
			}
		}
	}
}




//==============================================================
// �]�w

// �P�P�]�����^
CBgMover* CBgMover::SetStar(
	float vx, float vy, float z, 
	int num, int min_argb, int max_argb
) {
	Valid.Star=true;
	Star.Obj3D=NULL;
	VX=vx/100;
	VY=vy/100;
	Z=z;
	Star.Num=num;
	Star.MinARGB=min_argb;
	Star.MaxARGB=max_argb;
	return this;
}


// �P�P�]����^
CBgMover* CBgMover::SetStar(
	CObject3D* obj3d, float x0, float y0, float x1, float y1, 
	float vx, float vy, float z, int num
) {
	Valid.Star=true;
	Star.Obj3D=obj3d;
	Star.X0=x0;
	Star.Y0=y0;
	Star.X1=x1;
	Star.Y1=y1;
	Z=z;
	VX=vx;
	VY=vy;
	Star.Num=num;
	return this;
}


// �I��
CMover* CMover::SetBg(
	CObject3D** chip, int* map, 
	int map_w, int map_h,
	float sx, float sy, float scrn_w, float scrn_h, 
	float chip_w, float chip_h, float svx, float svy
) {
	Valid.Bg=true;
	Bg.Chip=chip;
	Bg.Map=map;
	Bg.MW=map_w;
	Bg.MH=map_h;
	Bg.SX=sx;
	Bg.SY=sy;
	Bg.SW=scrn_w;
	Bg.SH=scrn_h;
	Bg.CW=chip_w;
	Bg.CH=chip_h;
	Bg.SVX=svx;
	Bg.SVY=svy;
	return this;
}



