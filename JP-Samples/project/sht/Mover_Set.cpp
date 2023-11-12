#include "Mover.h"




//==============================================================
// ìG
CMover* CMover::SetOrbit(ORBIT* data, int count, float xmul, float ymul, bool repeat) {
	Valid.Orbit=true;
	Orbit.Data=data;
	Orbit.Index=0;
	Orbit.Time=0;
	Orbit.Count=count;
	Orbit.XMul=xmul;
	Orbit.YMul=ymul;
	Orbit.Repeat=repeat;
	return this;
}




//==============================================================
// äÓñ{
CMover* CMover::SetXYRand(float xrand, float yrand) {
	XRand=xrand;
	YRand=yrand;
	return this;
}

CMover* CMover::SetFollowParent(float rx, float ry) {
	Valid.FollowParent=true;
	RX=rx;
	RY=ry;
	return this;
}

CMover* CMover::SetColor(int color) {
	Color=color;
	return this;
}

CMover* CMover::SetItemEffect_Accel(float accel) {
	ItemEffect.Accel=accel;
	return this;
}

CMover* CMover::SetItemEffect_Docking(bool docking) {
	ItemEffect.Docking=docking;
	return this;
}

CMover* CMover::SetItemEffect_SA(bool special_attack) {
	ItemEffect.SpecialAttack=special_attack;
	return this;
}

CMover* CMover::SetNotInherit(int ih) {
	Inherit&=~ih;
	return this;
}

CMover* CMover::SetScale(
	float sx, float sy, float svx, float svy
) {
	Valid.Scale=true;
	Scale.X=sx;
	Scale.Y=sy;
	Scale.VX=svx;
	Scale.VY=svy;
	return this;
}

CMover* CMover::SetAlpha(
	float alpha, float v_alpha
) {
	Alpha.X=alpha; Alpha.V=v_alpha;
	return this;
}

CMover* CMover::SetDamage(
	float str, float vit, 
	CMover* spawn_model, CMover* next_model,
	bool invincible, bool transparent,
	bool target_only
) {
	Damage.Str=str;
	Damage.Vit=vit;
	Damage.SpawnModel=spawn_model;
	Damage.NextModel=next_model;
	Damage.Invincible=invincible;
	Damage.Transparent=transparent;
	Damage.TargetOnly=target_only;
	return this;
}

CMover* CMover::SetLock(int id) {
	Valid.Lock=true;
	Lock.ID=id;
	return this;
}

CMover* CMover::SetNext(CMover* model, int timer) {
	Valid.Next=true;
	Next.Model=model;
	Next.Timer=timer;
	return this;
}

CMover* CMover::SetObj3D(CObject3D* obj3d) {
	Obj3D=obj3d;
	if (obj3d) Damage.Hit=obj3d->GetHit(HIT_CORE);
	return this;
}

CMover* CMover::SetAccel(float accel) {
	Accel=accel;
	return this;
}

CMover* CMover::SetAccelXY(float ax, float ay) {
	AX=ax;
	AY=ay;
	return this;
}	

CMover* CMover::SetRand(float speed_rnd, float angle_rnd) {
	SpeedRnd=speed_rnd;
	AngleRnd=angle_rnd;
	return this;
}




//==============================================================
// íe

CMover* CMover::SetTarget(
	TARGET_TYPE target_type, int target_id, CMover* alter_model
) {
	Valid.Target=true;
	Target.Type=target_type;
	Target.ID=target_id;
	Target.AlterModel=alter_model;
	return this;
}

CMover* CMover::SetHoming(float speed, float angle) {
	Valid.Homing=true;
	Speed=speed;
	Homing.Angle=angle;
	Homing.Simple=false;
	return this;
}

CMover* CMover::SetSimpleHoming(float speed) {
	Valid.Homing=true;
	Speed=speed;
	Homing.Simple=true;
	return this;
}

CMover* CMover::SetHoming(float angle) {
	Valid.Homing=true;
	Homing.Angle=angle;
	Homing.Simple=false;
	return this;
}

CMover* CMover::SetAiming(
	float speed, float angle
) {
	Valid.Aiming=true;
	Speed=speed;
	Angle=angle;
	return this;
}

CMover* CMover::SetAimingDDA(float speed, float angle) {
	Valid.DDA=true;
	return SetAiming(speed, angle);
}

CMover* CMover::SetAimingFPN(float speed, float angle) {
	Valid.FPN=true;
	return SetAiming(speed, angle);
}

CMover* CMover::SetDirected(float speed, float angle) {
	Valid.Directed=true;
	Speed=speed;
	Angle=angle;
	return this;
}

CMover* CMover::SetDirectedDDA(float speed, float angle) {
	Valid.DDA=true;
	return SetDirected(speed, angle);
}

CMover* CMover::SetDirected16_3(float speed, float angle) {
	Valid.INTG=true;
	return SetDirected(speed, angle);
}

CMover* CMover::SetLooping(float angle, float va, float aa, float radius, float vr, float ar) {
	Valid.Looping=true;
	Angle=angle;
	Looping.VAngle=va;
	Looping.AAngle=aa;
	Looping.Radius=radius;
	Looping.VRadius=vr;
	Looping.ARadius=ar;
	return this;
}

CMover* CMover::AddSpawn(CMover* model, int timer, int cycle, int count, float rx, float ry) {
	SPAWN* spawn=&Spawns[NumSpawns++];
	spawn->Model=model;
	spawn->Timer=timer;
	spawn->Cycle=cycle;
	spawn->Count=count;
	spawn->NWayCount=0;
	spawn->CircleCount=0;
	spawn->RX=rx;
	spawn->RY=ry;
	return this;
}

CMover* CMover::SetLaser(
	int length, float valpha, bool add_alpha, 
	CObject3D* tail_obj3d, bool tail_add_alpha, 
	bool tail_damage_transparent
) {
	Valid.Laser=true;
	Laser.Length=length;
	Laser.VAlpha=valpha;
	Laser.AddAlpha=add_alpha;
	Laser.TailObj3D=tail_obj3d;
	Laser.TailAddAlpha=tail_add_alpha;
	Laser.TailDamageTransparent=tail_damage_transparent;
	return this;
}

CMover* CMover::SetLaser(
	int count, float valpha, bool add_alpha
) {
	return SetLaser(count, valpha, add_alpha, NULL, true, true);
}

CMover* CMover::AddSpawnNWay(CMover* model, int timer, int cycle, int count, int nway_count, float nway_angle) {
	SPAWN* spawn=&Spawns[NumSpawns++];
	spawn->Model=model;
	spawn->Timer=timer;
	spawn->Cycle=cycle;
	spawn->Count=count;
	spawn->NWayCount=nway_count;
	spawn->NWayAngle=nway_angle;
	spawn->CircleCount=0;
	return this;
}

CMover* CMover::AddSpawnCircle(CMover* model, int timer, int cycle, int count, int circle_count, bool circle_odd) {
	SPAWN* spawn=&Spawns[NumSpawns++];
	spawn->Model=model;
	spawn->Timer=timer;
	spawn->Cycle=cycle;
	spawn->Count=count;
	spawn->NWayCount=0;
	spawn->CircleCount=circle_count;
	spawn->CircleOdd=circle_odd;
	return this;
}




//==============================================================
// ïêäÌ

CMover* CMover::SetWeapon_Common(WEAPON_ID id) {
	Valid.Weapon=true;
	Weapon.ID=id;
	Weapon.PrevButton=false;
	Weapon.Power=0;
	Weapon.Gauge=0;
	Weapon.PowerEffect=NULL;
	Weapon.MaxEffect=NULL;
	return this;
}

CMover* CMover::SetWeapon_Shot(WEAPON_ID id, CMover* shot) {
	SetWeapon_Common(id);
	Weapon.Shot=shot;
	return this;
}

CMover* CMover::SetWeapon_PowerShot(
	WEAPON_ID id, 
	CMover* shot, CMover* power_shot, CMover* max_shot, 
	CObject3D* power_effect, CObject3D* max_effect,
	int min_power, int max_power, int max_gauge
) {
	SetWeapon_Common(id);	
	Weapon.MinPower=min_power;
	Weapon.MaxPower=max_power;
	Weapon.MaxGauge=max_gauge;
	Weapon.Shot=shot;
	Weapon.BigShot=power_shot;
	Weapon.MaxShot=max_shot;
	Weapon.PowerEffect=power_effect;
	Weapon.MaxEffect=max_effect;
	return this;
}

CMover* CMover::SetWeapon_Laser(
	WEAPON_ID id, 
	CMover* shot, CMover* laser, 
	int min_power, int max_gauge
) {
	SetWeapon_Common(id);	
	Weapon.Shot=shot;
	Weapon.Laser=laser;
	Weapon.MinPower=min_power;
	Weapon.MaxGauge=max_gauge;
	return this;
}

CMover* CMover::SetWeapon_Command(
	WEAPON_ID id, COMMAND_LIST* list
) {
	SetWeapon_Common(id);
	Weapon.Cmd.List=list;
	return this;
}

CMover* CMover::SetSightedBomb(
	float sx, float sy,
	CObject3D* ready, CObject3D* lock, 
	CObject3D* target, CObject3D* busy,
	CMover* model
) {
	Valid.SightedBomb=true;
	SightedBomb.SX=sx;
	SightedBomb.SY=sy;
	SightedBomb.Ready=ready;
	SightedBomb.Lock=lock;
	SightedBomb.Target=target;
	SightedBomb.Busy=busy;
	SightedBomb.Model=model;
	SightedBomb.Locking=false;
	SightedBomb.Bombing=false;
	return this;
}

CMover* CMover::SetLockonLaser(
	int max_avail, float sx, float sy,
	CObject3D* ready, CObject3D* lock, 
	CObject3D* target, CObject3D* busy,
	CMover* laser_model
) {
	Valid.LockOnLaser=true;
	LockOnLaser.MaxAvail=max_avail;
	LockOnLaser.NumAvail=max_avail;
	LockOnLaser.SX=sx;
	LockOnLaser.SY=sy;
	LockOnLaser.Ready=ready;
	LockOnLaser.Lock=lock;
	LockOnLaser.Target=target;
	LockOnLaser.Busy=busy;
	LockOnLaser.LaserModel=laser_model;
	return this;
}

CMover* CMover::SetTurnMarker(
	int button_id, float dist, float yaw, CObject3D* obj3d
) {
	TURN_MARKER& tm=TurnMarker;
	Valid.TurnMarker=true;
	tm.Turning=false;
	tm.ButtonID=button_id;
	tm.Yaw=yaw;
	tm.Dist=dist;
	tm.Obj3D=obj3d;
	return this;
}




//==============================================================
// à íuÅCâÒì]

CMover* CMover::SetRoll(float speed) {
	Valid.Roll=true;
	Roll.Pos=0;
	Roll.Speed=speed;
	Roll.Auto=false;
	return this;
}

CMover* CMover::SetAutoRoll(float max, float speed, bool on_vx, bool plus) {
	Valid.Roll=true;
	Roll.Pos=0;
	Roll.Max=max;
	Roll.Speed=speed;
	Roll.Auto=true;
	Roll.OnVX=on_vx;
	Roll.Plus=plus;
	return this;
}

CMover* CMover::SetYaw(float speed) {
	Valid.Yaw=true;
	Yaw.Pos=0;
	Yaw.Speed=speed;
	Yaw.Auto=false;
	return this;
}

CMover* CMover::SetAutoYaw() {
	Valid.Yaw=true;
	Yaw.Pos=0;
	Yaw.Speed=0;
	Yaw.Auto=true;
	return this;
}

CMover* CMover::SetPos(float x, float y) {
	Valid.Pos=true;
	Pos.X=x;
	Pos.Y=y;
	return this;
}


