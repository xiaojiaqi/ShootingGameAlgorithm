#include "Mover.h"
#include "Hit.h"
#include "..\LibGame\Input.h"
#include <assert.h>




//==============================================================
// 確保，Group的取得
CMover* CMover::New() {
	CMover* mover=Group->New();
	if (mover) mover->Init(this, NULL);
	return mover;
}

CMover* CMover::New(CMover* model) {
	if (!model) return NULL;
	CMover* mover=model->Group->New();
	if (mover) mover->Init(model, this);
	return mover;
}

CMoverGroup* CMover::GetGroup(GROUP_ID id) {
	return Group->GetManager()->GetGroup(id);
}




//==============================================================
// 建構式
CMover::CMover(CMoverGroup* group) {
	Group=group;
	Parent=NULL;

	X=Y=Z=XRand=YRand=RX=RY=0;
	VX=VY=Speed=SpeedRnd=0;
	AX=AY=Accel=0;
	Angle=AngleRnd=0;
	Obj3D=NULL;
	Color=0;

	ZeroMemory((void*)&Valid, sizeof(VALID));
	
	Damage.Str=1;
	Damage.Vit=1;
	Damage.SpawnModel=NULL;
	Damage.NextModel=NULL;
	Damage.Invincible=true;
	Damage.Transparent=false;
	Damage.TargetOnly=false;
	Damage.Hit=CHit(0, 0, 0, 0);

	Inherit=0xffffffff;
	
	HistIndex=-1;
	NumSpawns=0;
	Prec=NULL;

	Alpha.X=1.0f;
	Alpha.V=0;
	Alpha.Add=false;

	ItemEffect.Accel=0;

	// 武器
	LockOnLaser.Locked=false;
}

CMover::~CMover() {}

CMover::CMover(CMover* mover) {
	*this=*mover;
}




//==============================================================
// 初始化(共通)
void CMover::Init(CMover* model, CMover* parent) {
	assert(Group==model->Group);

	CMover* target;
	int i;

	bool used=Used;
	*this=*model;
	Used=used;

	Parent=parent;
	Dead=false;

	Speed=model->Speed+model->SpeedRnd*Rand05();	
	Angle=model->Angle+model->AngleRnd*Rand05();

	LockOnLaser=model->LockOnLaser;
	if (Valid.LockOnLaser) {
		for (i=0; i<LockOnLaser.MaxAvail; i++) {
			LockOnLaser.LaserMover[i]=NULL;
			LockOnLaser.TargetMover[i]=NULL;
		}
	}

	// 放大縮小
	if (Valid.Scale) {
		Scale=model->Scale;
	} else {
		Scale.X=Scale.Y=1;
		Scale.VX=Scale.VY=0;
	}
	
	// 下一個的狀態
	Next=model->Next;

	// 位置
	Pos=model->Pos;
	if (Valid.Pos) {
		X+=model->Pos.X+XRand*Rand05();
		Y+=model->Pos.Y+YRand*Rand05();
	}
	if (parent) {
		X+=parent->X;
		Y+=parent->Y;
	}

	// 瞄準狙擊
	if (model->Valid.Aiming) {
		if (!Valid.Target || Target.Type==TG_RANDOM_MYSHIP) {
			target=GetRandomMyShip();
			if (target) {
				if (model->Valid.DDA) {
					InitAimingDDA(target->X, target->Y, Speed);
				} else
				if (model->Valid.FPN) {
					InitAimingFPN(target->X, target->Y, Speed);
				} else {
					InitAiming(target->X, target->Y, Speed, Angle);
				}
			} else {
				Group->Delete(this);
				return;
			}
		} else 
		if (Target.Type==TG_LOCKED_ENEMY) {
			target=GetLockedEnemy(model->Target.ID);
			if (target) {
				InitAiming(target->X, target->Y, Speed, Angle);
			} else {
				if (Target.AlterModel) {
					Init(Target.AlterModel, parent);
				} else {
					Group->Delete(this);
				}
				return;
			}
		} else
		if (Target.Type==TG_MOVER) {
			target=Target.Mover;
			if (target) {
				InitAiming(target->X, target->Y, Speed, Angle);
			} else {
				if (Target.AlterModel) {
					Init(Target.AlterModel, parent);
				} else {
					Group->Delete(this);
				}
				return;
			}
		} else 
		if (Target.Type==TG_RANDOM_ENEMY) {
		target=GetGroup(ENEMY_GROUP)->GetRandomUsedMover();
			if (target) {
				InitAiming(target->X, target->Y, Speed, Angle);
			} else {
				if (Target.AlterModel) {
					Init(Target.AlterModel, parent);
				} else {
					Group->Delete(this);
				}
				return;
			}
		}
	}

	// 方向
	if (model->Valid.Directed) {
		if (parent && (Inherit&IH_YAW)) Angle+=parent->Yaw.Pos;
		if (Valid.DDA) {
			InitDirectedDDA(Angle, Speed);
		} else
		if (Valid.INTG) {
			InitDirected16_3(Angle);
		} else {
			InitDirected(Speed, Angle);
		}
	}

	// 旋轉
	if (model->Valid.Looping) {
		Looping=model->Looping;
		if (!parent) {
			Group->Delete(this);
			return;
		}
		parent->RefCount++;
		Looping.Target=parent;
		float rad=D3DX_PI*2*Angle;
		X=Looping.Target->X+Looping.Radius*cos(rad);
		Y=Looping.Target->Y+Looping.Radius*sin(rad);	
	}

	// Roll
	Roll=model->Roll;
	if (!Valid.Roll) Roll.Pos=0;

	// Yaw
	Yaw=model->Yaw;
	if (!Valid.Yaw) Yaw.Pos=0;

	// 產生(雷射)
	Laser=model->Laser;
	if (Valid.Laser) InitLaser(model, parent);

	// 歷程
	HistIndex=model->HistIndex;
	if (HistIndex>=0) {
		for (i=0; i<MAX_HISTS; i++) {
			HIST* hist=&Hists[i];
			hist->X=X;
			hist->Y=Y;
			hist->Yaw=Yaw.Pos;
			hist->Roll=Roll.Pos;
			hist->Valid=false;
		}
	}

	// 結尾
	Prec=model->Prec;
	PrecDelay=model->PrecDelay;
	RefCount=0;

	// 生成
	NumSpawns=model->NumSpawns;
	for (i=0; i<NumSpawns; i++) Spawns[i]=model->Spawns[i];

	// 自機
	if (model->Valid.MyShip) {
		MyShip=model->MyShip;
		X=model->MyShip.X;
		Y=model->MyShip.Y;
	}

	// 武器
	Weapon=model->Weapon;
	if (Valid.Weapon) {
		Weapon.Cmd.HistIndex=0;
		for (i=0; i<NUM_CMD_HIST; i++) Weapon.Cmd.Hist[i]=CMD_NONE;
	}


	// 誘導
	if (model->Valid.Homing) {
		Homing=model->Homing;
		if (Valid.Target) {
			switch (Target.Type) {
				case TG_RANDOM_MYSHIP: target=GetRandomMyShip(); break;
				case TG_MOVER: target=Target.Mover; break;
			}
		} else {
			target=GetRandomMyShip();
		}
		Homing.Target=target;
		if (target) {
			if (Valid.Directed) {
				InitDirected(Speed, Angle);
			} else {
				InitAiming(target->X, target->Y, Speed, Angle);
			}
			target->RefCount++;
		} else {
			Group->Delete(this);
			return;
		}
	}

	// Warp
	Warp=model->Warp;
	if (Valid.Warp) {
		Warp.Input=0;
		Warp.Released=true;
		Warp.Time=0;
	}

	// 按鍵的速度調節
	SCButton=model->SCButton;
	if (Valid.SCButton) Speed=SCButton.MinSpeed;

	// 依項目的速度調節
	SCItem=model->SCItem;
	if (Valid.SCItem) Speed=SCItem.MinSpeed;	

	// 防護罩
	Barrier=model->Barrier;
	if (Valid.Barrier) {
		Barrier.Mover=New(Barrier.Model);
		Barrier.Mover->X=X;
		Barrier.Mover->Y=Y;
	}

	// 軌道
	if (Valid.Orbit && Orbit.Count>0) {
		VX=Orbit.Data[0].VX*Orbit.XMul;
		VY=Orbit.Data[0].VY*Orbit.YMul;
	}

	// 跟隨的友機
	if (Valid.FollowParent) {
		Parent->RefCount++;
		X=Parent->X+RX;
		Y=Parent->Y+RY;
	}
}


// 生成(雷射)
void CMover::InitLaser(CMover* org_model, CMover* parent) {
	CMover* prec=NULL;
	float alpha=1.0f;
	CMover model=*org_model;
	model.Valid.Laser=false;

	if (model.Group->GetNumFree()<model.Laser.Length-1) {
		Dead=true;
		return;
	}

	Prec=prec;
	PrecDelay=1;
	HistIndex=0;
	Alpha.X=alpha;
	alpha+=model.Laser.VAlpha;
	Alpha.Add=model.Laser.AddAlpha;

	model.PrecDelay=1;
	model.HistIndex=0;
	CMover* mover;
	//prec=this;
	for (int i=1; i<model.Laser.Length; i++, prec=mover) {
		model.Prec=prec;
		model.Alpha.X=alpha;
		alpha+=model.Laser.VAlpha;
		model.Alpha.Add=model.Laser.AddAlpha;
		if (prec) {
			prec->RefCount++;
			model.NumSpawns=0;
			model.Valid.Next=false;
			model.Damage.SpawnModel=NULL;
			model.Damage.NextModel=NULL;
			model.Damage.Invincible=true;
			if (model.Laser.TailObj3D) {
				model.Obj3D=model.Laser.TailObj3D;
				model.Alpha.Add=model.Laser.TailAddAlpha;
				model.Damage.Transparent=model.Laser.TailDamageTransparent;
			}
		}
		mover=parent->New(&model);
	}
}


// 初始化(方向)
void CMover::InitDirected(
	float speed, float angle
) {
	VX=cos(D3DX_PI*2*Angle)*Speed;
	VY=sin(D3DX_PI*2*Angle)*Speed;
}


// 初始化(瞄準狙擊)
void CMover::InitAiming(
	float tx, float ty,  // 目標
	float speed,         // 子彈速度
	float angle          // 轉彎角度
) {
	// 求出到目標為止的距離d
	float vx=tx-X, vy=ty-Y;
	float d=sqrt(vx*vx+vy*vy);

	// 讓子彈速呈固定值speed下求出速度(vx,vy)：
	// 離目標的距離d為0時，向下發射。
	if (d>0) {
		vx*=speed/d; vy*=speed/d;
	} else {
		vx=0; vy=speed;
	}

	// 轉動Angle角度的發射方向
	float rad=D3DX_PI*2*angle;
	float cosr=cos(rad), sinr=sin(rad);
	VX=cosr*vx-sinr*vy;
	VY=sinr*vx+cosr*vy;
}


// 初始化(瞄準狙擊-DDA)
void CMover::InitAimingDDA(
	float ftx, float fty,  // 目標
	float fspeed           // 子彈速度
) {
	// 在顯示時，座標為10倍
	int x=(int)(X*10), y=(int)(Y*10), 
		tx=(int)(ftx*10), ty=(int)(fty*10),
		speed=(int)(fspeed*10);

	// 座標與速度的初始化
	Dda.X=x; Dda.Y=y;
	Dda.Speed=max(speed, 1);

	// 求出子彈移動方向(vx,vy)：值為1或 -1
	int vx=Dda.VX=tx>x?1:-1;
	int vy=Dda.VY=ty>y?1:-1;

	// 求出相對目標的X方向與Y方向誤差的絕對值
	int dx=Dda.DX=tx>=x?tx-x:x-tx;
	int dy=Dda.DY=ty>=y?ty-y:y-ty;

	// 誤差diff：
	// dx>=dy時dx/2，dx<dy時則dy/2
	Dda.Diff=dx>=dy?dx/2:dy/2;

	// 在這裡的顯示上，設定速度為浮點小數
	VX=(float)vx*dx/100;
	VY=(float)vy*dy/100;
}


// 初始化(瞄準狙擊-FPN)
void CMover::InitAimingFPN(
	float ftx, float fty,  // 目標
	float fspeed           // 子彈速度
) {
	int x=(int)(X*256), y=(int)(Y*256),
		tx=(int)(ftx*256), ty=(int)(fty*256),
		speed=(int)(fspeed*256);

	// 座標的初始化
	Fpn.X=x; Fpn.Y=y;

	// 求出相對目標的X方向與Y方向誤差的絕對值(dx,dy)
	int dx=tx>=x?tx-x:x-tx;
	int dy=ty>=y?ty-y:y-ty;

	// 以X方向與Y方向差分中較長者作為距離d
	int d=dx>=dy?dx:dy;

	// 求速度(IVX,IVY)
	int vx=Fpn.VX=(tx-x)*speed/d;
	int vy=Fpn.VY=(ty-y)*speed/d;	

	// 在這裡的顯示上，設定速度為浮點小數
	VX=(float)vx/256;
	VY=(float)vy/256;
}


// 初始化(方向-DDA)
void CMover::InitDirectedDDA(
	float angle, float speed
) {
	// 製成表格(啟動時只作一次)
	static bool init=false;
	static int target[360][2];
	if (!init) {
		for (int i=0; i<360; i++) {
			target[i][0]=(int)(cos(D3DX_PI/180*i)*1000);
			target[i][1]=(int)(sin(D3DX_PI/180*i)*1000);
		}
	}

	// 從表單讀出目標的座標
	int dir=((int)(angle*360)%360+360)%360;
	int tx=target[dir][0];
	int ty=target[dir][1];

	// 初始化瞄準狙擊-DDA
	InitAimingDDA((float)tx, (float)ty, speed);
}


// 初始化(方向-16向,速度為3)
void CMover::InitDirected16_3(
	float angle
) {
	// 在顯示時，座標為10倍
	Intg.X=(int)X*10;
	Intg.Y=(int)Y*10;

	// 速度3的速度表單
	static const int v3[][2]={
		{ 3, 0}, { 3, 1}, { 2, 2}, { 1, 3},
		{ 0, 3}, {-1, 3}, {-2, 2}, {-3, 1},
		{-3, 0}, {-3,-1}, {-2,-2}, {-1,-3},
		{ 0,-3}, { 1,-3}, { 2,-2}, { 3,-1}
	};

	//把角度Angle（0.0∼1.0）變換成16個方向（0∼15）
	int dir=((int)(angle*16)%16+16)%16;

	// 由表單求出移動物體的速度(IVX,IVY)
	Intg.VX=v3[dir][0];
	Intg.VY=v3[dir][1];

	// 在這裡的顯示上，設定速度為浮點小數
	VX=(float)Intg.VX/10;
	VY=(float)Intg.VY/10;
}


// 移動(DDA)
void CMover::MoveDDA() {
	int i;

	// 處理X方向的移動長度
	if (Dda.DX>=Dda.DY) {
		for (i=0; i<Dda.Speed; i++) {

			// 在X方向每次的移動距離
			Dda.X+=Dda.VX;
			
			// 在Y方向累積誤差到條件後才移動
			Dda.Diff+=Dda.DY;
			if (Dda.Diff>=Dda.DX) {
				Dda.Diff-=Dda.DX;
				Dda.Y+=Dda.VY;
			}
		}
	} 

	// 處理Y方向的移動長度
	else {
		for (i=0; i<Dda.Speed; i++) {

			// 在Y方向每次的移動距離
			Dda.Y+=Dda.VY;

			// 在X方向累積誤差到條件後才移動
			Dda.Diff+=Dda.DX;
			if (Dda.Diff>=Dda.DY) {
				Dda.Diff-=Dda.DY;
				Dda.X+=Dda.VX;
			}
		}
	}

	// 在這裡的顯示上，設定速度為浮點小數
	X=(float)Dda.X/10;
	Y=(float)Dda.Y/10;
}




//==============================================================
// 移動前的處理
void CMover::Check() {
	int i;

	if (Prec) {
		PrecHist=Prec->Hists[(Prec->HistIndex-PrecDelay+MAX_HISTS)%MAX_HISTS];
	}

	// 地面(飛彈)
	CMoverGroup* gg=GetGroup(GROUND_GROUP);
	if (Valid.GroundHit && Obj3D) {
		GroundHit.HitX=GroundHit.HitY=false;
		float vx=VX, vy=VY;
		if (GroundHit.ModeX==GR_ALONG) {
			CHit hit=Obj3D->GetHit(HIT_CORE);
			hit.SetPos(X+vx, Y+vy);
			if (gg->FirstHit(&hit)) { GroundHit.HitX=true; vx=0; }
		} else
		if (GroundHit.ModeX==GR_REFLECT) {
			CHit hit=Obj3D->GetHit(HIT_CORE);
			hit.SetPos(X+vx, Y+vy);
			if (gg->FirstHit(&hit)) { GroundHit.HitX=true; vx=-vx; }
		}
		if (GroundHit.ModeY==GR_ALONG) {
			CHit hit=Obj3D->GetHit(HIT_CORE);
			hit.SetPos(X+vx, Y+vy);
			if (gg->FirstHit(&hit)) { GroundHit.HitY=true; vy=0; }
		} else
		if (GroundHit.ModeY==GR_REFLECT) {
			CHit hit=Obj3D->GetHit(HIT_CORE);
			hit.SetPos(X+vx, Y+vy);
			if (gg->FirstHit(&hit)) { GroundHit.HitY=true; vy=-vy; }
		}
		if (GroundHit.ModeX==GR_HIT || GroundHit.ModeY==GR_HIT) {
			CHit hit=Obj3D->GetHit(HIT_CORE);
			hit.SetPos(X+vx, Y+vy);
			CMover* mover;
			if (mover=gg->FirstHit(&hit)) {
				Damage.Vit-=mover->Damage.Str;
			}
		}
	}

	// 瞄準
	if (Valid.SightedBomb) {
		CHit sight_hit=SightedBomb.Ready->GetHit(HIT_CORE);
		sight_hit.L+=X+SightedBomb.SX;
		sight_hit.R+=X+SightedBomb.SX;
		sight_hit.B+=Y+SightedBomb.SY;
		sight_hit.T+=Y+SightedBomb.SY;
		CMoverGroup* eg=Group->GetManager()->GetGroup(ENEMY_GROUP);
		CMoverGroup* geg=Group->GetManager()->GetGroup(GROUND_ENEMY_GROUP);
		if (eg->FirstHit(&sight_hit) || geg->FirstHit(&sight_hit)) {
			SightedBomb.Locking=true;
		} else {
			SightedBomb.Locking=false;
		}
	}

	// 鎖定雷射
	if (Valid.LockOnLaser) {
		LOCKON_LASER& lol=LockOnLaser;

		// 鎖定
		CHit sight_hit=LockOnLaser.Ready->GetHit(HIT_CORE);
		sight_hit.SetPos(X+lol.SX, Y+lol.SY);
		CMoverGroup* eg=Group->GetManager()->GetGroup(ENEMY_GROUP);
		CMover* mover;
		if (lol.NumAvail>0 && (mover=eg->FirstHit(&sight_hit))) {
			do {
				if (!mover->LockOnLaser.Locked) {
					lol.NumAvail--;
					for (i=0; i<lol.MaxAvail && lol.TargetMover[i]; i++) ;
					lol.TargetMover[i]=mover;
					mover->RefCount++;
					mover->LockOnLaser.Locked=true;
				}
			} while (lol.NumAvail>0 && (mover=eg->NextHit(&sight_hit)));
		}

		// 不鎖定
		int avail=0;
		for (i=0; i<lol.MaxAvail; i++) {
			CMover* mover;
			mover=lol.TargetMover[i];
			if (mover && mover->Dead) {
				lol.TargetMover[i]=NULL;
				mover->RefCount--;
				mover->LockOnLaser.Locked=false;
			}
			mover=lol.LaserMover[i];
			if (mover && mover->Dead) {
				lol.LaserMover[i]=NULL;
				mover->RefCount--;
			}
			if (!lol.TargetMover[i] && !lol.LaserMover[i]) avail++;
		}
		lol.NumAvail=avail;
	}

	// 背景
	if (Valid.Bg && Group==GetGroup(GROUND_GROUP)) {
		float sx=Bg.SX, sy=Bg.SY, sw=Bg.SW, sh=Bg.SH, cw=Bg.CW, ch=Bg.CH;
		int mw=Bg.MW, mh=Bg.MH, x0, y0, x1, y1;
		x0=(int)(sx/cw-1);
		y0=(int)(sy/ch-1);
		x1=(int)((sx+sw-1)/cw+1);
		y1=(int)((sy+sh-1)/ch+1);
		CMoverGroup* mg=GetGroup(MYSHIP_GROUP);
		CMover* myship;
		if (myship=mg->FirstUsed()) {
			do {
				CHit hit=myship->Obj3D->GetHit(HIT_CORE);
				hit.SetPos(myship->X, myship->Y);
				for (int i=y0; i<=y1; i++) {
					for (int j=x0; j<=x1; j++) {
						CObject3D* obj3d=Bg.Chip[Bg.Map[(i%mh+mh)%mh*mw+(j%mw+mw)%mw]];
						if (obj3d && obj3d->GetHit(HIT_CORE).IsHit(j*cw-sx, i*ch-sy, hit)) {
							myship->Damage.Vit-=Damage.Str;
						}
					}
				}
			} while (myship=mg->NextUsed());
		}
	}
}




//==============================================================
// 移動(共通)
void CMover::Move() {
	if (!Dead) {

		// 生成
		for (int i=0; i<NumSpawns; i++) {
			SPAWN* spawn=&Spawns[i];
			assert(spawn->Timer>=0);
			if (spawn->Count!=0) {
				if (spawn->Timer==0) {
					if (spawn->Count>0) spawn->Count--;
					spawn->Timer=spawn->Cycle;
					if (spawn->NWayCount>0) SpawnNWay(spawn); else
					if (spawn->CircleCount>0) SpawnCircle(spawn); else
					{
						CMover* mover=New(spawn->Model);
						if (mover) {
							mover->RX=spawn->RX;
							mover->RY=spawn->RY;
						}
					}
				} else {
					spawn->Timer--;
				}
			}
		}

		// Graze
		if (Valid.Graze) {
			CMoverGroup* bg=GetGroup(BULLET_GROUP);
			CMover *bullet, *effect;
			CHit hit=Obj3D->GetHit(HIT_CORE);
			hit.SetPos(X, Y);
			Graze.Grazing=false;
			if (bullet=bg->FirstHit(&hit)) {
				do {
					effect=New(Graze.Effect);
					effect->X=bullet->X;
					effect->Y=bullet->Y;
					Graze.Grazing=true;
				} while (bullet=bg->NextHit(&hit));
			}
		}

		// 與地面的干擾
		float vx=VX, vy=VY;
		if (GroundHit.HitX) {
			if (GroundHit.ModeX==GR_ALONG) vx=0; else
			if (GroundHit.ModeX==GR_REFLECT) VX=vx=-vx;
		}
		if (GroundHit.HitY) {
			if (GroundHit.ModeY==GR_ALONG) vy=0; else
			if (GroundHit.ModeY==GR_REFLECT) VY=vy=-vy;
		}

		// 移動
		if (Prec) {
			X=PrecHist.X;
			Y=PrecHist.Y;
			Yaw.Pos=PrecHist.Yaw;
			Roll.Pos=PrecHist.Roll;
		} else
		if (Valid.MyShip) {
			MoveMyShip();
		} else
		if (Valid.Homing) {
			if (Homing.Simple) MoveSimpleHoming(); else MoveHoming();
		} else
		if (Valid.Looping) {
			MoveLooping(); 
		} else
		if (Valid.Aiming || Valid.Directed) {
			if (Valid.DDA) MoveDDA(); else
			if (Valid.FPN) {
				Fpn.X+=Fpn.VX;
				Fpn.Y+=Fpn.VY;
				X=(float)Fpn.X/256;
				Y=(float)Fpn.Y/256;
			} else
			if (Valid.INTG) {
				Intg.X+=Intg.VX;
				Intg.Y+=Intg.VY;
				X=(float)Intg.X/10;
				Y=(float)Intg.Y/10;
			} else {
				X+=vx; Y+=vy;
			}
		} else

		// 捲動
		if (Valid.Bg) {
			if (Valid.BgRotate) {
				float rad=D3DX_PI*2*BgRotate.Angle;
				float c=cos(rad), s=sin(rad);
				Bg.SX+= c*Bg.SVX+s*Bg.SVY;
				Bg.SY+=-s*Bg.SVX+c*Bg.SVY;
			} else {
				Bg.SX+=Bg.SVX;
				Bg.SY+=Bg.SVY;
			}
		} else

		if (Valid.Orbit) {
			VX=Orbit.Data[Orbit.Index].VX*Orbit.XMul;
			VY=Orbit.Data[Orbit.Index].VY*Orbit.YMul;
			X+=VX;
			Y+=VY;
			Orbit.Time++;
			if (Orbit.Time>=Orbit.Data[Orbit.Index].Time) {
				Orbit.Time=0;
				Orbit.Index++;
				if (Orbit.Index>=Orbit.Count) {
					if (Orbit.Repeat) Orbit.Index=0; else Orbit.Index=Orbit.Count-1;
				}
			}
		}

		// Yaw
		if (Valid.Yaw && !Prec) {
			if (Yaw.Auto) {
				Yaw.Pos=atan2(vy, vx)/D3DX_PI/2+0.25f;
			} else {
				Yaw.Pos+=Yaw.Speed;
			}
		}

		// Roll
		if (Valid.Roll) {
			if (Roll.Auto) {
				if (Roll.OnVX) {
					if (Roll.Plus) {
						if (vx<0 && -Roll.Max<=Roll.Pos) Roll.Pos-=Roll.Speed; else
						if (vx>0 && Roll.Pos<=Roll.Max) Roll.Pos+=Roll.Speed;
					} else {
						if (vx>0 && -Roll.Max<=Roll.Pos) Roll.Pos-=Roll.Speed; else
						if (vx<0 && Roll.Pos<=Roll.Max) Roll.Pos+=Roll.Speed;
					}
				} else {
					if (Roll.Plus) {
						if (vy<0 && -Roll.Max<=Roll.Pos) Roll.Pos-=Roll.Speed; else
						if (VY>0 && Roll.Pos<=Roll.Max) Roll.Pos+=Roll.Speed;
					} else {
						if (vy>0 && -Roll.Max<=Roll.Pos) Roll.Pos-=Roll.Speed; else
						if (vy<0 && Roll.Pos<=Roll.Max) Roll.Pos+=Roll.Speed;
					}
				}
			} else {
				Roll.Pos+=Roll.Speed;
			}
		}

		// 加速
		if (Accel!=0 && Speed!=0) {
			VX/=Speed; VY/=Speed;
			Speed+=Accel;
			VX*=Speed; VY*=Speed;
		}
		VX+=AX; VY+=AY;

		// 放大縮小
		if (Valid.Scale) {
			float sx=Scale.X+=Scale.VX;
			float sy=Scale.Y+=Scale.VY;
			if (Obj3D) {
				CHit hit=Obj3D->GetHit(HIT_CORE);
				Damage.Hit=CHit(hit.L*sx, hit.R*sx, hit.T*sy, hit.B*sy);
			}
		}

		// Alpha值
		Alpha.X+=Alpha.V;

		// 歷程
		if (HistIndex>=0) {
			HIST* hpre=&Hists[(HistIndex-1+MAX_HISTS)%MAX_HISTS];
			if (!Valid.Option || hpre->X!=X || hpre->Y!=Y) {
				HIST* hist=&Hists[HistIndex];
				hist->X=X;
				hist->Y=Y;
				hist->Yaw=Yaw.Pos;
				hist->Roll=Roll.Pos;
				hist->Valid=!Prec || (Prec && PrecHist.Valid);
				HistIndex=(HistIndex+1)%MAX_HISTS;
			}
		}

		// 下一個的狀態
		if (Valid.Next) {
			if (Next.Timer==0) {
				if (Next.Model) {
					GoNext(Next.Model);
				} else {
					Dead=true;
				}
			} else {
				Next.Timer--;
			}
		}

		// 捕捉自機的敵機
		if (Valid.Captor) {
			if (Captor.State==CPT_NORMAL) {
				CMoverGroup* mg=GetGroup(MYSHIP_GROUP);
				CMover* m=mg->GetRandomUsedMover();
				if (!m->Captee.Doubled) New(Captor.Attack);
			}
		}

		// 破壞
		if (Damage.Vit<=0) {
			if (Damage.SpawnModel) {
				New(Damage.SpawnModel);
			}
			if (Damage.NextModel) {
				GoNext(Damage.NextModel);
			} else {
				Dead=true;
			}
			if (Valid.Collision) {
				CMoverGroup* g=GetGroup(STAGE_GROUP);
				g->IncCollisionEnergy();
				if (g->GetCollisionEnergy()>Collision.MinEnergy) {
					New(Collision.Crash);
				}
			}

			// 被敵機捕獲的自機
			if (Valid.Captee) {
				CMoverGroup* eg=GetGroup(ENEMY_GROUP);
				CMover* e=eg->GetRandomUsedMover();
				if (e) {
					e->Captor.State=CPT_CAPTURED;
					e->Captor.MyShip=Obj3D;
				}
			}

			// 捕捉自機的敵機
			if (Valid.Captor && Captor.State==CPT_CAPTURED) {
				CMoverGroup* mg=GetGroup(MYSHIP_GROUP);
				CMover* m=mg->GetRandomUsedMover();
				if (m) m->Captee.Doubled=true;
			}
		}

		// 消失的判定
		if (Obj3D) {
			CHit hit=Obj3D->GetHit(HIT_ALL);
			CHit deadzone_hit=Group->GetDeadzoneHit();
			if (!hit.IsHit(X, Y, deadzone_hit)) Dead=true;
		}
		if (Prec && Prec->Dead) {
			Dead=true;
		}
	}

	// 完全消失判斷(無參照時)
	if (Dead && RefCount==0) {
		if (Prec) Prec->RefCount--;
		if (Valid.Homing) Homing.Target->RefCount--;
		if (Valid.Looping) Looping.Target->RefCount--;
		Group->Delete(this);
	}
}




//==============================================================
// 移動後的處理
void CMover::PostMove() {
	if (Valid.FollowParent) {
		X=Parent->X+RX;
		Y=Parent->Y+RY;
		if (Parent->Damage.Vit<=0) {
			Damage.Vit=0;
			Parent->RefCount--;
		}
	}
}



// 下一個的狀態
void CMover::GoNext(CMover* model) {
	Accel=model->Accel;
	AX=model->AX; AY=model->AY;
	Alpha.V=model->Alpha.V;
	if (model->Valid.Yaw) Yaw.Speed=model->Yaw.Speed;
	if (model->Valid.Roll) Roll.Speed=model->Roll.Speed;
	Next=model->Next;
	if (model->Valid.Homing) Homing.Angle=model->Homing.Angle;
	Damage.Transparent=model->Damage.Transparent;
}


// 移動(簡易誘導)
void CMover::MoveSimpleHoming() {

	// 求出到目標為止的距離d
	float tx=Homing.Target->X, ty=Homing.Target->Y;
	float vx=tx-X, vy=ty-Y;
	float d=sqrt(vx*vx+vy*vy);

	// 讓子彈速呈固定值speed下求出速度(vx,vy)：
	// 離目標的距離d為0時，向下移動。
	if (d) {
		vx*=Speed/d;
		vy*=Speed/d;
	} else {
		vx=0;
		vy=Speed;
	}

	// 移動子彈
	X+=vx;
	Y+=vy;
	VX=VX;
	VY=VY;
}


// 移動(旋轉彈)
void CMover::MoveLooping() {
	float rad=D3DX_PI*2*Angle, c=cos(rad), s=sin(rad);
	float r=Looping.Radius;
	X=Looping.Target->X+r*c;
	Y=Looping.Target->Y+r*s;
	float v=Looping.VAngle*Looping.Radius;
	VX=-v*s; VY=v*c;
	Angle+=Looping.VAngle;
	Looping.VAngle+=Looping.AAngle;
	Looping.Radius+=Looping.VRadius;
	Looping.VRadius+=Looping.ARadius;
}

// 生成(n-way彈)
void CMover::SpawnNWay(SPAWN* spawn) {
	int count=spawn->NWayCount;
	float space_angle=spawn->NWayAngle;
	float angle=count%2 ? -count/2*space_angle : (-count/2+0.5f)*space_angle;
	CMover model=*spawn->Model;
	float m_angle=model.Angle;
	for (int i=0; i<count; i++, angle+=space_angle) {
		model.Angle=m_angle+angle;
		New(&model);
	}
}

// 生成(圓形彈)
void CMover::SpawnCircle(SPAWN* spawn) {
	int count=spawn->CircleCount;
	bool odd=spawn->CircleOdd;
	float space_angle=1.0f/count;
	float angle=odd ? 0 : space_angle/2;
	CMover model=*spawn->Model;
	float m_angle=model.Angle;
	for (int i=0; i<count; i++, angle+=space_angle) {
		model.Angle=m_angle+angle;
		New(&model);
	}
}

// 誘導
void CMover::MoveHoming() {
	if (Homing.Target->Dead) {
		X+=VX; Y+=VY;
		return;
	}
	float x=X, y=Y;
	float tx=Homing.Target->X, ty=Homing.Target->Y;
	float speed=Speed, angle=Homing.Angle;

	// 速度向量(原來速度, 自機方向, 右曲轉彎上限, 逆時針旋轉上限)
	float vx0=VX, vy0=VY, vx1, vy1, vx2, vy2, vx3, vy3;

	// 求取自機方向的速度向量(vx1,vy1)
	vx1=tx-x; vy1=ty-y;
	float d=sqrt(vx1*vx1+vy1*vy1);
	if (d) {
		vx1*=speed/d;
		vy1*=speed/d;
	} else {
		vx1=0;
		vy1=0;
	}

	// 求取向右曲轉彎之角度上限的速度向量(vx2,vy2)
	float rad=D3DX_PI*2*angle;
	float c=cos(rad), s=sin(rad);
	vx2=c*vx0-s*vy0;
	vy2=s*vx0+c*vy0;

	// 決定要向自機方向或是要向轉彎角度上限彎曲
	if (vx0*vx1+vy0*vy1>=vx0*vx2+vy0*vy2) {
		
		// 自機方向在可轉彎的範圍內時
		// 向自機方向彎曲
		VX=vx1; VY=vy1;

	} else {

		// 自機方向為可轉彎的範圍外時：
		// 求取左曲轉彎角度上限的速度向量(vx3,vy3)
		vx3= c*vx0+s*vy0;
		vy3=-s*vx0+c*vy0;

		// 求取子彈對自機的相對位置向量(px,py)
		float px=tx-x, py=ty-y;
		
		// 決定右曲或左曲
		if (px*vx2+py*vy2>=px*vx3+py*vy3) {
			VX=vx2; VY=vy2;
		} else {
			VX=vx3; VY=vy3;
		}
	}

	// 移動子彈
	X+=VX;
	Y+=VY;
}




//==============================================================
// 描繪
void CMover::Draw() {
	if (Prec && !PrecHist.Valid) return;

	// 背景
	if (Valid.Bg) {
		float sx=Bg.SX, sy=Bg.SY, sw=Bg.SW, sh=Bg.SH, cw=Bg.CW, ch=Bg.CH;
		int mw=Bg.MW, mh=Bg.MH, x0, y0, x1, y1;

		if (Valid.BgRotate) {

			// 取得從畫面內於轉彎進入的背景的最大範圍
			float w2=sw/2, h2=sh/2;
			float r=(float)sqrt(w2*w2+h2*h2);
			x0=(int)((sx-r)/cw-1);
			y0=(int)((sy-r)/ch-1);
			x1=(int)((sx+r)/cw+1);
			y1=(int)((sy+r)/ch+1);

			// 描繪碎片�`�b�v���`��
			CObject3D::SetRotation(BgRotate.Angle);
			for (int i=y0; i<=y1; i++) {
				for (int j=x0; j<=x1; j++) {
					CObject3D* obj3d=Bg.Chip[Bg.Map[(i%mh+mh)%mh*mw+(j%mw+mw)%mw]];
					if (obj3d) obj3d->DrawTopView(j*cw-sx+sw/2, i*ch-sy+sh/2, Z, 1, 1, 0, 0, 0, 1, false);
				}
			}
			CObject3D::SetRotation(0);

		} else {

			// 描繪碎片的範圍(左上, 右下)
			x0=(int)(sx/cw-1);
			y0=(int)(sy/ch-1);
			x1=(int)((sx+sw-1)/cw+1);
			y1=(int)((sy+sh-1)/ch+1);

			// 描繪碎片
			for (int i=y0; i<=y1; i++) {
				for (int j=x0; j<=x1; j++) {
					CObject3D* obj3d=Bg.Chip[Bg.Map[(i%mh+mh)%mh*mw+(j%mw+mw)%mw]];
					if (obj3d) obj3d->DrawTopView(j*cw-sx, i*ch-sy, Z, 1, 1, 0, 0, 0, 1, false);
				}
			}
		}

	} else
	
	// 停靠
	if (Valid.Docking && Docking.Docked) {
		Docking.Obj3D->DrawTopView(
			X, Y, Z, Scale.X, Scale.Y, Yaw.Pos, 0, Roll.Pos, Alpha.X, Alpha.Add);
	} else
	
	// 切換顏色
	if (Valid.ChangeColor) {
		ChangeColor.Obj3D[Color-1]->DrawTopView(
			X, Y, Z, Scale.X, Scale.Y, Yaw.Pos, 0, Roll.Pos, Alpha.X, Alpha.Add);
	} else

	// 一般的描繪
	{
		if ((!Valid.Graze || Graze.Grazing) && Obj3D) {
			Obj3D->DrawTopView(X, Y, Z, Scale.X, Scale.Y, Yaw.Pos, 0, Roll.Pos, Alpha.X, Alpha.Add);
		}
	}

	// 捕捉自機的敵機
	if (Valid.Captor && Captor.State==CPT_CAPTURED) {
		Captor.MyShip->DrawTopView(X, Y-10, Z, 1, 1, 0, 0, 0, 1, false);
	}
	if (Valid.Captee && Captee.Doubled) {
		Obj3D->DrawTopView(X+10, Y, Z, Scale.X, Scale.Y, Yaw.Pos, 0, Roll.Pos, Alpha.X, Alpha.Add);
	}

	// 集氣效果
	if (Valid.Weapon) {
		WEAPON& wp=Weapon;
		if (wp.Power==wp.MaxPower && wp.MaxEffect) {
			wp.MaxEffect->DrawTopView(X, Y, Z, 1, 1, 0, 0, 0, 1, false);
		} else
		if (wp.Power>wp.MinPower && wp.PowerEffect) {
			wp.PowerEffect->DrawTopView(X, Y, Z, 1, 1, 0, 0, 0, 1, false);
		}
	}

	// 炸彈的瞄準與目標
	if (Valid.SightedBomb) {
		SIGHTED_BOMB& sb=SightedBomb;
		CObject3D* sight_obj3d=
			sb.Bombing?sb.Busy:(sb.Locking?sb.Lock:sb.Ready);
		sight_obj3d->DrawTopView(
			X+sb.SX, Y+sb.SY, Z, 1, 1, 0, 0, 0, 1, false);
		if (sb.Bombing) {
			sb.Target->DrawTopView(
				sb.TX, sb.TY, Z, 1, 1, 0, 0, 0, 1, false);
		}
	}

	// 鎖定雷射的瞄準與目標
	if (Valid.LockOnLaser) {
		LOCKON_LASER& lol=LockOnLaser;
		CObject3D* sight_obj3d=
			lol.NumAvail>0?lol.Ready:lol.Busy;
		sight_obj3d->DrawTopView(
			X+lol.SX, Y+lol.SY, 1, 1, 0, 0, 0, 1, false);
		for (int i=0; i<lol.MaxAvail; i++) {
			CMover* mover=lol.TargetMover[i];
			if (mover && !mover->Dead) {
				lol.Target->DrawTopView(
					mover->X, mover->Y, Z, 1, 1, 0, 0, 0, 1, false);
			}
		}
	}

	// 切換標記
	TURN_MARKER& tm=TurnMarker;
	if (Valid.TurnMarker && tm.Turning) {
		tm.Obj3D->DrawTopView(tm.MX, tm.MY, Z, 1, 1, Yaw.Pos, 0, 0, 1, false);
	}

	// 選項
	if (Valid.Option) {
		for (int c=0, i=HistIndex; c<Option.Count; c++) {
			i=(i-Option.Interval+MAX_HISTS)%MAX_HISTS;
			if (Hists[i].Valid) 
				Option.Obj3D->DrawTopView(
					Hists[i].X, Hists[i].Y, Z, 1, 1, 0, 0, 0, 1, false);
		}
	}

	// 手臂
	if (Valid.Arm) {
		float x, y;
		int i;

		// 手臂
		if (Arm.State!=AS_READY) {
			for (i=0, y=Y; i<Arm.Length; i++, y-=Arm.Speed) {
				Arm.Tail->DrawTopView(X, y, Z, 1, 1, 0, 0, 0, 1, false);
			}
			Arm.Head->DrawTopView(X, y, Z, 1, 1, 0, 0, 0, 1, false);
		}

		// 捕捉敵機
		x=X-(float)(Arm.NumStock-1)/2*10, y=Y+10;
		for (i=0; i<Arm.NumStock; i++, x+=10) {
			Arm.Stock[i]->DrawTopView(x, y, Z, 1, 1, 0, 0, 0, 1, false);
		}
	}
}




