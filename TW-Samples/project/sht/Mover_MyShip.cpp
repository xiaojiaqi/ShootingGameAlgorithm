#include "Mover.h"
#include "Hit.h"
#include "..\LibGame\Input.h"
#include <assert.h>


//==============================================================
// �]�w

// �۾�
CMover* CMover::SetMyShip(int id, float x, float y, float speed) {
	Valid.MyShip=true;
	MyShip.ID=id;
	MyShip.X=x;
	MyShip.Y=y;
	Speed=speed;
	return this;
}

// �ܧ�
CMover* CMover::SetTransform(CMover* model, CMover* effect, int button_id) {
	Valid.Transform=true;
	Transform.Model=model;
	Transform.Effect=effect;
	Transform.ButtonID=button_id;
	Transform.PrevButton=false;
	return this;
}

// �I�����^��
CMover* CMover::SetBgRotate(float angle) {
	Valid.BgRotate=true;
	BgRotate.Angle=angle;
	return this;
}

// ���ʳt�ת��ո`
CMover* CMover::SetControlScrollY(
	float ytop, float ybottom, float svytop, float svybottom
) {
	Valid.ControlScrollY=true;
	ControlScrollY.YTop=ytop;
	ControlScrollY.YBottom=ybottom;
	ControlScrollY.SVYTop=svytop;
	ControlScrollY.SVYBottom=svybottom;
	return this;
}

// ���O
CMover* CMover::SetGravity(float vx, float vy) {
	Valid.Gravity=true;
	Gravity.VX=vx;
	Gravity.VY=vy;
	return this;
}

// �����۾����ľ� 
CMover* CMover::SetCaptor(CMover* attack) {
	Valid.Captor=true;
	Captor.Attack=attack;
	Captor.State=CPT_NORMAL;
	return this;
}
CMover* CMover::SetCaptee() {
	Valid.Captee=true;
	Captee.Doubled=false;
	return this;
}

// �ۥѲ��ʪ��˷Ǿ�(���s)
CMover* CMover::SetMovableSightB(
	int button_id, float x, float y, float speed,
	CMover* sight, CMover* attack
) {
	Valid.MovableSightB=true;
	MovableSightB.ButtonID=button_id;
	MovableSightB.X=x;
	MovableSightB.Y=Y;
	MovableSightB.Speed=speed;
	MovableSightB.SightModel=sight;
	MovableSightB.AttackModel=attack;
	MovableSightB.State=MSS_NORMAL;
	return this;
}

// �ۥѲ��ʪ��˷Ǿ�(�n��)
CMover* CMover::SetMovableSightS(
	float x, float y, float speed, CMover* sight
) {
	Valid.MovableSightS=true;
	MovableSightS.X=x;
	MovableSightS.Y=y;
	MovableSightS.Speed=speed;
	MovableSightS.SightModel=sight;
	MovableSightS.SightMover=NULL;
	return this;
}

// ��t�B�[�t
CMover* CMover::SetSlow(int button_id, int speed) {
	Valid.Slow=true;
	Slow.ButtonID=button_id;
	Slow.Speed=speed;
	return this;
}
CMover* CMover::SetQuick(int button_id, int speed) {
	Valid.Quick=true;
	Quick.ButtonID=button_id;
	Quick.Speed=speed;
	return this;
}

// Graze
CMover* CMover::SetGraze(CMover* effect) {
	Valid.Graze=true;
	Graze.Grazing=false;
	Graze.Effect=effect;
	return this;
}

// �I��
CMover* CMover::SetCollision(int min_energy, CMover* crash) {
	Valid.Collision=true;
	Collision.MinEnergy=min_energy;
	Collision.Energy=0;
	Collision.Crash=crash;
	return this;
}

// �Ϯg
CMover* CMover::SetReflect(int button_id, CMover* field, CMover* shot) {
	Valid.Reflect=true;
	Reflect.ButtonID=button_id;
	Reflect.FieldModel=field;
	Reflect.FieldMover=NULL;
	Reflect.ShotModel=shot;
	return this;
}

// �����C��
CMover* CMover::SetChangeColor(
	int button_id, int num_color, 
	CObject3D** obj3d, CMover** shot, CMover** effect, CHit* hit
) {
	Valid.ChangeColor=true;
	ChangeColor.ButtonID=button_id;
	ChangeColor.NumColor=num_color;
	ChangeColor.Obj3D=obj3d;
	ChangeColor.Shot=shot;
	ChangeColor.Effect=effect;
	ChangeColor.Hit=hit;
	ChangeColor.PrevButton=false;
	Color=1;
	return this;
}

// �o�g�������j��
CMover* CMover::SetRFShot(int mode, CMover* shot, CHit* hit) {
	Valid.RFShot=true;
	RFShot.Mode=mode;
	RFShot.Shot=shot;
	RFShot.Hit=hit;
	return this;
}

// �����ľ����Y
CMover* CMover::SetArm(
	int button_id, CObject3D* head, CObject3D* tail, 
	float speed, int max_length, int max_time, int max_stock
) {
	Valid.Arm=true;
	Arm.ButtonID=button_id;
	Arm.Head=head;
	Arm.Tail=tail;
	Arm.Speed=speed;
	Arm.MaxLength=max_length;
	Arm.MaxTime=max_time;
	Arm.State=AS_READY;
	Arm.NumStock=0;
	Arm.MaxStock=max_stock;
	return this;
}

// �H�;����Y
CMover* CMover::SetThrow(
	int button_id, CHit* hit, float vx, float vy, float vyaw, int max_time
) {
	Valid.Throw=true;
	Throw.ButtonID=button_id;
	Throw.Hit=hit;
	Throw.VX=vx;
	Throw.VY=vy;
	Throw.VYaw=vyaw;
	Throw.MaxTime=max_time;
	Throw.Thrown=false;
	return this;
}

// �g��
CMover* CMover::SetBerserk(
	CMover* effect, int req_energy, int max_time, int warn_time, int weak_time
) {
	Valid.Berserk=true;
	Berserk.EffectModel=effect;
	Berserk.EffectMover=NULL;
	Berserk.Energy=0;
	Berserk.ReqEnergy=req_energy;
	Berserk.MaxTime=max_time;
	Berserk.WarnTime=warn_time;
	Berserk.WeakTime=weak_time;
	Berserk.State=BS_NORMAL;
	return this;
}

// �̪��~���S������
CMover* CMover::SetSAItem(
	CMover* shot, CMover* effect, int max_time, int warn_time
) {
	Valid.SAItem=true;
	SAItem.ShotModel=shot;
	SAItem.EffectModel=effect;
	SAItem.EffectMover=NULL;
	SAItem.MaxTime=max_time;
	SAItem.WarnTime=warn_time;
	return this;
}

// ����
CMover* CMover::SetPunch(CMover* model, int button_id, int max_time) {
	Valid.Punch=true;
	Punch.Model=model;
	Punch.ButtonID=button_id;
	Punch.MaxTime=max_time;
	Punch.Mover=NULL;
	return this;
}

// ���@�n
CMover* CMover::SetBarrier(CMover* model, float warn_vit) {
	Valid.Barrier=true;
	Barrier.Model=model;
	Barrier.Mover=NULL;
	Barrier.WarnVit=warn_vit;
	return this;
}

// ����
CMover* CMover::SetUnderwater(float speed, float air_h, float water_h, CMover* wave) {
	Valid.Underwater=true;
	Underwater.Speed=speed;
	Underwater.AirH=air_h;
	Underwater.WaterH=water_h;
	Underwater.Wave=wave;
	return this;
}

// �B��
CMover* CMover::SetWalk(
	float gvx, float gvy, float jvx, float jvy, int jtime, int button_id
) {
	Valid.Walk=true;
	Walk.GVX=gvx;
	Walk.GVY=gvy;
	Walk.JVX=jvx;
	Walk.JVY=jvy;
	Walk.JumpTime=jtime;
	Walk.ButtonID=button_id;
	Walk.Time=0;
	return this;
}

// �ﶵ
CMover* CMover::SetOption(
	int count, int interval, CObject3D* obj3d
) {
	Valid.Option=true;
	Option.Count=count;
	Option.Interval=interval;
	Option.Obj3D=obj3d;
	HistIndex=0;
	return this;
}

// ��a���Ĭ𪺳B�z(���u��)
CMover* CMover::SetGroundHit(
	GROUND_HIT mode_x, GROUND_HIT mode_y
) {
	Valid.GroundHit=true;
	GroundHit.ModeX=mode_x;
	GroundHit.ModeY=mode_y;
	return this;
}

// Warp
CMover* CMover::SetWarp(
	int time_limit, float distance, CMover* effect
) {
	Valid.Warp=true;
	Warp.Distance=distance;
	Warp.TimeLimit=time_limit;
	Warp.Effect=effect;
	return this;
}

// �H���s�ո`�t��
CMover* CMover::SetSCButton(
	float accel, float min_speed, float max_speed, 
	int button_id
) {
	Valid.SCButton=true;
	SCButton.Accel=accel;
	SCButton.MinSpeed=min_speed;
	SCButton.MaxSpeed=max_speed;
	SCButton.PrevButton=false;
	SCButton.ButtonID=button_id;
	return this;
}

// �̪��~����ո`�t��
CMover* CMover::SetSCItem(
	float min_speed, float max_speed
) {
	Valid.SCItem=true;
	SCItem.MinSpeed=min_speed;
	SCItem.MaxSpeed=max_speed;
	return this;
}

// �X��
CMover* CMover::SetDocking(
	CObject3D* obj3d, CMover* shot
) {
	Valid.Docking=true;
	Docking.Docked=false;
	Docking.Obj3D=obj3d;
	Docking.Shot=shot;
	return this;
}




//==============================================================
// ����
void CMover::MoveMyShip() {
	CHit all_hit=Obj3D->GetHit(HIT_ALL);

	CInput* input=Group->GetInput();
	if (!input) return;
	const CInputState* is=input->GetState(MyShip.ID);
	float x=X, y=Y;
	CHit screen_hit=Group->GetScreenHit();
	int i;

	// �ܧ�
	if (Valid.Transform) {
		bool button=is->Button[Transform.ButtonID];
		if (!Transform.PrevButton && button) {
			Dead=true;
			New(Transform.Effect);
			CMover* mover=New(Transform.Model);
			if (mover) {
				mover->X=X;
				mover->Y=Y;
				mover->Transform.PrevButton=true;
			}
		}
		Transform.PrevButton=button;
	}

	// �H���s�ո`�t��
	if (Valid.SCButton) {

		// �C�����}�@��:
		// �i��t�ת��ո`
		if (!SCButton.PrevButton && is->Button[SCButton.ButtonID]) {
			if (Speed>=SCButton.MaxSpeed) Speed=SCButton.MinSpeed;
			else Speed+=SCButton.Accel;
		}

		SCButton.PrevButton=is->Button[SCButton.ButtonID];
	}

	// ���~����
	CMoverGroup* ig=Group->GetManager()->GetGroup(ITEM_GROUP);
	CMover* item;
	CHit core_hit=Obj3D->GetHit(HIT_CORE);
	core_hit.SetPos(X, Y);
	if (item=ig->FirstHit(&core_hit)) {
		do {
			item->Dead=true;
			
			// �t�׽ո`
			if (Valid.SCItem) {
				Speed+=item->ItemEffect.Accel;
				if (Speed>SCItem.MaxSpeed) Speed=SCItem.MaxSpeed;
				if (Speed<SCItem.MinSpeed) Speed=SCItem.MinSpeed;
			}

			// �X��
			if (Valid.Docking && !Docking.Docked) {
				Docking.Docked=true; 
				//ItemEffect.Docking;
				Damage.Hit=Docking.Docked?
					Docking.Obj3D->GetHit(HIT_CORE):
					Obj3D->GetHit(HIT_CORE);
			}

			// �S�������G
			// �p�G�b�@�몬�A�U�ߨ�Y�Ǫ��~�A
			// �|�ಾ��S�����A�A�ó]�w�Ѿl�ɶ��C
			if (Valid.SAItem) {
				if (!SAItem.EffectMover) {
					SAItem.Time=SAItem.MaxTime;
					SAItem.EffectMover=New(SAItem.EffectModel);
				}
			}

			// �g�ɪ��A�G
			// �p�G��q�R���n�s��A
			// �i�ഫ��g�ɪ��A�C
			if (Valid.Berserk && Berserk.State==BS_NORMAL) {
				Berserk.Energy++;
				if (Berserk.Energy>=Berserk.ReqEnergy) {
					Berserk.State=BS_BERSERK;
					Berserk.EffectMover=New(Berserk.EffectModel);
					Berserk.Time=Berserk.MaxTime;
					Berserk.Energy=0;
				}
			}

		} while (item=ig->NextHit(&core_hit));
	}

	// �I���^��
	if (Valid.BgRotate) {
		float vangle=BgRotate.Angle*is->AnalogX;
		CMoverGroup* sg=GetGroup(STAGE_GROUP);
		CMover* bg;
		if (bg=sg->FirstUsed()) {
			do {
				if (bg->Valid.BgRotate) bg->BgRotate.Angle-=vangle;
			} while (bg=sg->NextUsed());
		}
	} else

	// Warp�ಾ
	if (Valid.Warp) {
		int input=
			(is->Up?CMD_UP:0)|
			(is->Down?CMD_DOWN:0)|
			(is->Left?CMD_LEFT:0)|
			(is->Right?CMD_RIGHT:0);
		if (input) {

			// �nWarp�ಾ�ɡG
			// �����F�L��J���A�A�B�b����ɶ����A
			// ��J�F�e�@���ҿ�J���ۦP��V�ɡC
			if (Warp.Released && Warp.Time>0 && 
				Warp.Input==input
			) {
				// ?�[�v��?�o����
				if (Warp.Effect) New(Warp.Effect);

				// ?�[�v�ړ�����
				float new_y=Y+Warp.Distance*is->AnalogY;
				if (all_hit.IsInside(x, new_y, screen_hit)) Y=new_y;
				float new_x=X+Warp.Distance*is->AnalogX;
				if (all_hit.IsInside(new_x, y, screen_hit)) X=new_x;				
			}
			
			// ��Warp�ಾ�ɡG
			// �S�������F�L��J���A�A�άO�W�L����ɶ��A
			// �ο�J�M�e�@���ҿ�J���P��V�ɡC
			else {
				
				// �s�@��V�O���A�]�w����ɶ�
				Warp.Input=input;
				Warp.Time=Warp.TimeLimit;
				
				// ���q����
				float new_y=Y+Speed*is->AnalogY;
				if (all_hit.IsInside(x, new_y, screen_hit)) Y=new_y;
				float new_x=X+Speed*is->AnalogX;
				if (all_hit.IsInside(new_x, y, screen_hit)) X=new_x;
			}

			Warp.Released=false;
		}
		
		// �n��L��J���A��
		else Warp.Released=true;
		
		// �ɶ��Y�u
		if (Warp.Time>0) Warp.Time--;
	} else

	// �B��
	if (Valid.Walk) {
		
		// �W�@
		if (Walk.Time>0) {
			Walk.Time--;
			X+=Walk.JVX; Y+=Walk.JVY;
		} else

		// ���U
		{
			CMoverGroup* gg=GetGroup(GROUND_GROUP);
			CHit hit=Obj3D->GetHit(HIT_ALL);
			float new_x=X+Walk.GVX, new_y=Y+Walk.GVY;
			hit.SetPos(new_x, new_y);
			if (!gg->FirstHit(&hit)) {
				X=new_x; Y=new_y;
			} else {
			
				// �}�l���D
				if (is->Button[Walk.ButtonID]) Walk.Time=Walk.JumpTime;
			}
		}

		// ���k����
		float new_x=X+Speed*is->AnalogX;
		if (all_hit.IsInside(new_x, y, screen_hit)) X=new_x;

	} else

	// ���Y�ɪ��ʧ@
	if (Valid.Throw && Throw.Thrown) {
		if (Throw.Time<=0) {
			Throw.Thrown=false;
		} else {
			Throw.Time--;
			if (!all_hit.IsInside(X, Y+Throw.VY, screen_hit)) Throw.VY=-Throw.VY;
			if (!all_hit.IsInside(X+Throw.VX, Y, screen_hit)) Throw.VX=-Throw.VX;
			X+=Throw.VX;
			Y+=Throw.VY;
			Yaw.Pos+=Throw.VYaw;
		}
	} else

	// �@�벾��(����/�Ʀ�ݥ�)
	{
		float speed;

		// �������B�z
		if (Valid.Underwater) {
			speed=(Y<Underwater.WaterH?Speed:Underwater.Speed);
			if (Underwater.AirH<=Y && Y<Underwater.WaterH) {
				New(Underwater.Wave);
			}
		} else {
			speed=Speed;
		}

		// �@��B�z
		if (!Valid.MovableSightB || MovableSightB.State!=MSS_SIGHT) {
			float vy=speed*is->AnalogY, vx=speed*is->AnalogX;
			
			// ���O
			if (Valid.Gravity) {
				vx+=Gravity.VX;
				vy+=Gravity.VY;
			}

			// ����
			float new_y=Y+vy, new_x=X+vx;
			if (all_hit.IsInside(x, new_y, screen_hit)) Y=new_y;
			if (all_hit.IsInside(new_x, y, screen_hit)) X=new_x;

			// ���N����
			if (Valid.FreeScrollY) {
				CMoverGroup* sg=GetGroup(STAGE_GROUP);
				CMover* bg;
				if (bg=sg->FirstUsed()) {
					do {
						if (bg->Valid.Bg) bg->Bg.SY+=vy;
					} while (bg=sg->NextUsed());
				}
				sg=GetGroup(GROUND_GROUP);
				if (bg=sg->FirstUsed()) {
					do {
						if (bg->Valid.Bg) bg->Bg.SY+=vy;
					} while (bg=sg->NextUsed());
				}
			}
		}
	}

	// �u��Roll
	if (Valid.Roll && Roll.Auto && !Valid.Walk && !Valid.BgRotate &&
		(!Valid.MovableSightB || MovableSightB.State!=MSS_SIGHT)
	) {
		if (Roll.OnVX) {
			if (is->Left!=is->Right) {
				if (is->Left && -Roll.Max<Roll.Pos) Roll.Pos-=Roll.Speed; else
				if (is->Right && Roll.Pos<Roll.Max) Roll.Pos+=Roll.Speed;
			} else {
				if (Roll.Pos<0) Roll.Pos+=Roll.Speed; else
				if (0<Roll.Pos) Roll.Pos-=Roll.Speed;
			}
		} else {
			if (is->Up!=is->Down) {
				if (is->Down && -Roll.Max<Roll.Pos) Roll.Pos-=Roll.Speed; else
				if (is->Up && Roll.Pos<Roll.Max) Roll.Pos+=Roll.Speed;
			} else {
				if (Roll.Pos<0) Roll.Pos+=Roll.Speed; else
				if (0<Roll.Pos) Roll.Pos-=Roll.Speed;
			}
		}
	}

	// �o�g
	bool button=is->Button[1];
	if (Valid.Weapon) {
		WEAPON& wp=Weapon;
		switch (Weapon.ID) {
			case WP_BASIC_SHOT:
				BasicShot(button, wp.PrevButton);
				break;
			case WP_AUTO_SHOT:
				AutoShot(button);
				break;
			case WP_POWER_SHOT:
				PowerShot(button, wp.MinPower, wp.MaxPower, wp.Power);
				break;
			case WP_SEMI_AUTO_SHOT:
				SemiAutoShot(button, wp.MinPower, wp.MaxPower, wp.MaxGauge, wp.Power, wp.Gauge);
				break;
			case WP_POWER_SHOT_RELEASED:
				PowerShotReleased(button, wp.MinPower, wp.MaxPower, wp.Power);
				break;
			case WP_SHOT_AND_LASER:
				ShotAndLaser(button, wp.MinPower, wp.MaxGauge, wp.Power, wp.Gauge);
				break;
			case WP_LOCK_SHOT:
				LockShot(button, wp.MinPower, wp.MaxGauge, wp.Power, wp.Gauge);
				break;
			case WP_COMMAND_SHOT:
				CommandShot(is);
				break;
		}
	}

	// �˷��F��
	if (Valid.SightedBomb) {
		SIGHTED_BOMB& sb=SightedBomb;
		
		// ���O�b�F�������ɡG
		// �p�G���F�F���s�A
		// �h�]�w���u����l�y�ЩM���u�I���y�СC
		if (!sb.Bombing) {
			if (button) {			
				sb.Bombing=true;
				sb.TX=X+sb.SX; sb.TY=Y+sb.SY;
				CMover* mover=sb.Mover=New(sb.Model);
				if (mover) {
					mover->RefCount++;
				}
			}
		}
		
		// �b�F�������ɡG
		// ���F�������ɥi�g�X�U�Ӭ��u�C
		else {
			if (sb.Mover->Dead) {
				sb.Mover->RefCount--;
				sb.Bombing=false;
			}
		}
	}

	// ��w�p�g
	if (Valid.LockOnLaser) {
		LOCKON_LASER& lol=LockOnLaser;
		if (button) {
			for (i=0; i<lol.MaxAvail; i++) {
				if (!lol.LaserMover[i] && lol.TargetMover[i]) {
					CMover* model=lol.LaserModel;
					model->Valid.Target=true;
					model->Target.Type=TG_MOVER;
					model->Target.Mover=lol.TargetMover[i];
					CMover* mover=lol.LaserMover[i]=New(model);
					if (mover) mover->RefCount++;
				}
			}
		}
	}

	// �^��аO
	if (Valid.TurnMarker) {
		TURN_MARKER& tm=TurnMarker;

		// �^��}�l�G
		// ��X�^��аO���y�СC
		if (!tm.Turning && is->Button[tm.ButtonID]) {
			tm.Turning=true;
			tm.MX=X-tm.Dist*cos(D3DX_PI*2*(Yaw.Pos-tm.Yaw));
			tm.MY=Y-tm.Dist*sin(D3DX_PI*2*(Yaw.Pos-tm.Yaw));
		}

		// �^�൲��
		if (!is->Button[tm.ButtonID]) tm.Turning=false;

		// �p��^�त�^�઺����
		if (tm.Turning) Yaw.Pos=-atan2(X-tm.MX, Y-tm.MY)/D3DX_PI/2;
	}

	// ���@�n
	if (Valid.Barrier) {
		CMover* b=Barrier.Mover;
		b->X=X;
		b->Y=Y;
		if (b->Damage.Vit<Barrier.WarnVit) 
			b->Alpha.X=b->Damage.Vit/Barrier.WarnVit;
	}

	// ����
	if (Valid.Punch) {
		
		// �񨭮ɥX������
		if (!Punch.Mover && is->Button[Punch.ButtonID]) {
			Punch.Mover=New(Punch.Model);
			Punch.Time=Punch.MaxTime;
		}
		
		// �񨭧���������P�����G
		// �p�G����ɶ��L�F�A�M�^�񨭧����C
		if (Punch.Mover) {
			Punch.Mover->X=X;
			Punch.Mover->Y=Y;
			if (Punch.Time==0) {
				Punch.Mover->Dead=true;
				Punch.Mover=NULL;
			} else {
				Punch.Time--;
			}
		}
	}

	// ���u
	if (Valid.Arm) {
		switch (Arm.State) {
			
			// �ݾ��G
			// ���U���s�ɦ��X���u�C
			case AS_READY:
				if (is->Button[Arm.ButtonID]) {
					Arm.State=AS_EXTENDING;
					Arm.Length=0;
					Arm.Captured=false;
				}
				break;
			
			// ���X�L�{���G
			// �p�G���X�F���u�A
			// �P�_�O�_����̪����A�C
			case AS_EXTENDING:
				if (Arm.Length<Arm.MaxLength) {
					Arm.Length++;
				} else {
					Arm.State=AS_EXTENDED;
					Arm.Time=Arm.MaxTime;
				}
				break;
			
			// ������G
			// �g�L�@�q�ɶ��h�Y�^�C
			case AS_EXTENDED:
				if (Arm.Time<=0) {
					Arm.State=AS_SHRINKING;
				} else {
					Arm.Time--;
				}
				break;
			
			// �Y�^�L�{���G
			// ������0�ɦ^��ݾ����A�C
			case AS_SHRINKING:
				if (Arm.Length>0) {
					Arm.Length--;
				} else {
					Arm.State=AS_READY;
				}
				break;
		}

		// �P�w���u�����ľ�
		if ((Arm.State==AS_EXTENDING || Arm.State==AS_EXTENDED) && !Arm.Captured) {
			CMoverGroup* eg=GetGroup(ENEMY_GROUP);
			CMover* mover;
			CHit hit=Arm.Head->GetHit(HIT_CORE);
			hit.SetPos(X, Y-Arm.Speed*Arm.Length);
			if (mover=eg->FirstHit(&hit)) {
				do {
					if (Arm.NumStock<Arm.MaxStock) {
						mover->Dead=true;
						Arm.Captured=true;
						Arm.State=AS_SHRINKING;
						Arm.Stock[Arm.NumStock]=mover->Obj3D;
						Arm.NumStock++;
					}
				} while (mover=eg->NextHit(&hit));
			}
		}
	}

	// �S�������G
	// ���S�������ɶ��L�h��^�_�@�몬�A�C
	if (Valid.SAItem && SAItem.EffectMover) {
		if (SAItem.Time==0) {
			SAItem.EffectMover->Dead=true;
			SAItem.EffectMover=NULL;
		} else {
			SAItem.Time--;
			SAItem.EffectMover->X=X;
			SAItem.EffectMover->Y=Y;
			if (SAItem.Time<SAItem.WarnTime)
				SAItem.EffectMover->Alpha.X=(float)SAItem.Time/SAItem.WarnTime;
		}
	}

	// �g��
	if (Valid.Berserk) {

		// �g�ɪ��A�G
		// ���Ѿl�ɶ����F�ಾ��z�����A�C
		if (Berserk.EffectMover) {
			if (Berserk.Time==0) {
				Berserk.EffectMover->Dead=true;
				Berserk.EffectMover=NULL;
				Berserk.State=BS_WEAK;
				Berserk.Time=Berserk.WeakTime;
			} else {
				Berserk.Time--;
				Berserk.EffectMover->X=X;
				Berserk.EffectMover->Y=Y;
				if (Berserk.Time<Berserk.WarnTime)
					Berserk.EffectMover->Alpha.X=(float)Berserk.Time/Berserk.WarnTime;
			}
		} else

		// �z�����A�G
		// ���Ѿl�ɶ����F�ಾ��@�몺���A�C
		if (Berserk.State==BS_WEAK) {			
			if (Berserk.Time==0) {
				Berserk.State=BS_NORMAL;
			} else {
				Berserk.Time--;
			}
		}
	}

	// ���Y�;�
	if (Valid.Throw) {
		if (is->Button[Throw.ButtonID]) {
			CMoverGroup* mg=GetGroup(MYSHIP_GROUP);
			CMover* mover;
			CHit hit=*Throw.Hit;
			hit.SetPos(X, Y);
			if (mover=mg->FirstHit(&hit)) {
				do {
					if (mover!=this && mover->Valid.Throw && !mover->Throw.Thrown) {
						mover->Throw.Thrown=true;
						mover->Throw.Time=mover->Throw.MaxTime;
					}
				} while (mover=mg->NextHit(&hit));
			}
		}
	}

	// �Q�Τ;��j�Ƨ���
	if (Valid.RFShot && RFShot.Mode==2) {
		CMoverGroup* wg=GetGroup(WEAPON_GROUP);
		CMover* mover;
		CHit hit=*RFShot.Hit;
		hit.SetPos(X, Y);
		if (mover=wg->FirstHit(&hit)) {
			do {
				if (mover->Parent!=this) {
					mover->Dead=true;
					New(RFShot.Shot);
				}
			} while (mover=wg->NextHit(&hit));
		}
	}

	// �����C��
	if (Valid.ChangeColor) {
		
		// ����
		if (!ChangeColor.PrevButton && is->Button[ChangeColor.ButtonID]) {
			Color++;
			if (Color>ChangeColor.NumColor) Color=1;
			New(ChangeColor.Effect[Color-1]);
		}
		ChangeColor.PrevButton=is->Button[ChangeColor.ButtonID];


		// �l���l�u
		CMoverGroup* bg=GetGroup(BULLET_GROUP);
		CMover* mover;
		CHit hit=*ChangeColor.Hit;
		hit.SetPos(X, Y);
		if (mover=bg->FirstHit(&hit)) {
			do {
				if (mover->Color==Color) {
					mover->Damage.Vit=0;
				}
			} while (mover=bg->NextHit(&hit));
		}
	}

	// �Ϯg
	if (Valid.Reflect) {		
		if (Reflect.FieldMover) {

			// �l�u���^
			Reflect.FieldMover->X=X;
			Reflect.FieldMover->Y=Y;
			CMoverGroup* bg=GetGroup(BULLET_GROUP);
			CMover* mover;
			CHit hit=Reflect.FieldModel->Obj3D->GetHit(HIT_CORE);
			hit.SetPos(X, Y);
			if (mover=bg->FirstHit(&hit)) {
				do {
					mover->Damage.Vit=0;
					New(Reflect.ShotModel);
				} while (mover=bg->NextHit(&hit));
			}

			// �R�h���
			if (!is->Button[Reflect.ButtonID]) {
				Reflect.FieldMover->Dead=true;
				Reflect.FieldMover=NULL;
				Damage.Invincible=false;
			}

		} else {

			// ��X���
			if (is->Button[Reflect.ButtonID]) {
				Reflect.FieldMover=New(Reflect.FieldModel);
				Damage.Invincible=true;
			}

		}
	}

	// ��t�B�[�t
	int group_speed=0;
	if (Valid.Slow && is->Button[Slow.ButtonID]) {
		group_speed=Slow.Speed;
	}
	if (Valid.Quick && is->Button[Quick.ButtonID]) {
		group_speed=Quick.Speed;
	}
	GetGroup(ENEMY_GROUP)->SetSpeed(group_speed);
	GetGroup(BULLET_GROUP)->SetSpeed(group_speed);

	// �ۥѲ��ʺ˷Ǿ��]�n��^
	if (Valid.MovableSightS) {
		MOVABLE_SIGHT_S& ms=MovableSightS;
		CMover* sight;
		if (!ms.SightMover) {
			sight=ms.SightMover=New(ms.SightModel);
			sight->X=X+ms.X;
			sight->Y=Y+ms.Y;
		} else {
			sight=ms.SightMover;
			float new_y=sight->Y+ms.Speed*is->AnalogY2;
			if (all_hit.IsInside(sight->X, new_y, screen_hit)) sight->Y=new_y;
			float new_x=sight->X+ms.Speed*is->AnalogX2;
			if (all_hit.IsInside(new_x, sight->Y, screen_hit)) sight->X=new_x;
		}
	}

	// �ۥѲ��ʺ˷Ǿ��]���s�^
	if (Valid.MovableSightB) {
		MOVABLE_SIGHT_B& ms=MovableSightB;
		bool button=is->Button[ms.ButtonID];
		float new_x, new_y;
		CMover *sight, *attack;
		switch (ms.State) {

			// ���`���A�G
			// �Y�����U�˷Ƕs�A�h��X�˷Ǿ��A�öi�J�˷Ǫ��A�C
			case MSS_NORMAL:
				if (button) {
					ms.State=MSS_SIGHT;
					sight=ms.Mover=New(ms.SightModel);
					sight->X=X+ms.X;
					sight->Y=Y+ms.Y;
				}
				break;
			
			// �˷Ǫ��A�G
			// ���ʺ˷��I�A�Y���s�Q��}�h�i�J�������A�C
			case MSS_SIGHT:
				sight=ms.Mover;				
				new_y=sight->Y+ms.Speed*is->AnalogY;
				if (all_hit.IsInside(sight->X, new_y, screen_hit)) sight->Y=new_y;
				new_x=sight->X+ms.Speed*is->AnalogX;
				if (all_hit.IsInside(new_x, sight->Y, screen_hit)) sight->X=new_x;
				if (!button) {
					ms.State=MSS_ATTACK;
					sight->Damage.Vit=0;
					attack=ms.Mover=New(ms.AttackModel);
					attack->RefCount++;
					attack->X=sight->X;
					attack->Y=sight->Y;
				}
				break;
			
			// �������A�G
			// �L�F�@�q�ɶ���h�^�쥿�`���A�C
			case MSS_ATTACK:
				attack=ms.Mover;
				if (attack->Dead) {
					ms.State=MSS_NORMAL;
					attack->RefCount--;
				}
				break;
		}
	}

	// ���w��V���b
	if (Valid.LimitedScrollX) {
		CMoverGroup* sg=GetGroup(STAGE_GROUP);
		CMover* bg;
		if (bg=sg->FirstUsed()) {
			do {
				if (bg->Valid.Bg) {
					bg->Bg.SX=X*(bg->Bg.MW*bg->Bg.CW-bg->Bg.SW)/bg->Bg.SW;
				}
			} while (bg=sg->NextUsed());
		}
	}

	// ���b�t�ת��ո`
	if (Valid.ControlScrollY) {
		CONTROL_SCROLL_Y& cs=ControlScrollY;
		CMoverGroup* sg=GetGroup(STAGE_GROUP);
		CMover* bg;
		float yt=cs.YTop, yb=cs.YBottom, st=cs.SVYTop, sb=cs.SVYBottom;
		float svy=st+(Y-yt)*(sb-st)/(yb-yt);
		if (bg=sg->FirstUsed()) {
			do {
				if (bg->Valid.Bg) bg->Bg.SVY=svy;
			} while (bg=sg->NextUsed());
		}
	}
}


