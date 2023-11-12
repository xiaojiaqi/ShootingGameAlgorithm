#include "Mover.h"
#include "Hit.h"
#include "..\LibGame\Input.h"
#include <assert.h>




//==============================================================
// コンストラクタ，デストラクタ

CMoverGroupManager::CMoverGroupManager(
	LPDIRECT3DDEVICE9 device
) {
	Groups[MYSHIP_GROUP]=new CMoverGroup(this, device, 20);
	Groups[WEAPON_GROUP]=new CMoverGroup(this, device, 300);
	Groups[ENEMY_GROUP]=new CMoverGroup(this, device, 300);
	Groups[BULLET_GROUP]=new CMoverGroup(this, device, 1000);
	Groups[STAGE_GROUP]=new CMoverGroup(this, device, 300);
	Groups[GROUND_GROUP]=new CMoverGroup(this, device, 300);
	Groups[ITEM_GROUP]=new CMoverGroup(this, device, 300);
	Groups[WATER_GROUP]=new CMoverGroup(this, device, 300);
	Groups[BARRIER_GROUP]=new CMoverGroup(this, device, 20);
	Groups[GROUND_ENEMY_GROUP]=new CMoverGroup(this, device, 300);
	Groups[BG_GROUP]=new CBgMoverGroup(this, device, 20);
	Groups[JOINT_GROUP]=new CJointMoverGroup(this, device, 100);
}

CMoverGroupManager::~CMoverGroupManager() {
	for (int i=0; i<NUM_GROUPS; i++) delete Groups[i];
}




//==============================================================
// 移動，描画

void CMoverGroupManager::Check() {
	for (int i=0; i<NUM_GROUPS; i++) Groups[i]->Check();
	Groups[MYSHIP_GROUP]->CheckDamage(Groups[ENEMY_GROUP], DAMAGE_BOTH);
	Groups[MYSHIP_GROUP]->CheckDamage(Groups[JOINT_GROUP], DAMAGE_TAKE);
	Groups[MYSHIP_GROUP]->CheckDamage(Groups[BULLET_GROUP], DAMAGE_TAKE);
	Groups[MYSHIP_GROUP]->CheckDamage(Groups[GROUND_GROUP], DAMAGE_TAKE);
	Groups[WEAPON_GROUP]->CheckDamage(Groups[ENEMY_GROUP], DAMAGE_BOTH);
	Groups[WEAPON_GROUP]->CheckDamage(Groups[GROUND_ENEMY_GROUP], DAMAGE_BOTH);
	Groups[BARRIER_GROUP]->CheckDamage(Groups[ENEMY_GROUP], DAMAGE_BOTH);
	Groups[BARRIER_GROUP]->CheckDamage(Groups[BULLET_GROUP], DAMAGE_BOTH);
	Groups[BARRIER_GROUP]->CheckDamage(Groups[JOINT_GROUP], DAMAGE_TAKE);
}

void CMoverGroupManager::Move() {
	int i;
	for (i=0; i<NUM_GROUPS; i++) {
		Groups[i]->Move();
	}
	for (i=0; i<NUM_GROUPS; i++) {
		Groups[i]->PostMove();
	}
}

void CMoverGroupManager::Draw() {
	for (int i=0; i<NUM_GROUPS; i++) Groups[i]->Draw();
}




//==============================================================
// 当たり判定処理

void CMoverGroup::CheckDamage(CMoverGroup* group, DAMAGE_MODE mode) {
	CMover *mi, *mj;
	for (int i=0; i<NumAllMovers; i++) {
		mi=AllMovers[i];
		if (mi->Used && !mi->Dead && !mi->Damage.Transparent) {
			for (int j=0; j<group->NumAllMovers; j++) {
				mj=group->AllMovers[j];
				if (mj->Damage.TargetOnly && mj->Target.Mover!=mi) continue;
				if (mi->Damage.TargetOnly && mi->Target.Mover!=mj) continue;
				if (mj->Used && !mj->Dead && !mj->Damage.Transparent &&
					mj->Damage.Hit.IsHit(mj->X, mj->Y, mi->Damage.Hit, mi->X, mi->Y)) {
					assert(mode==DAMAGE_TAKE || mode==DAMAGE_BOTH);
					if (!mi->Damage.Invincible &&
						(mi->Color==0 || mi->Color!=mj->Color)) mi->Damage.Vit-=mj->Damage.Str;
					if (mj->Valid.Lock) {
						mi->Group->LockedMovers[mj->Lock.ID]=mi;
						mi->RefCount++;
					}
					if (mode==DAMAGE_BOTH) {
						if (!mj->Damage.Invincible) mj->Damage.Vit-=mi->Damage.Str;
						if (mi->Valid.Lock) {
							mj->Group->LockedMovers[mi->Lock.ID]=mj;
							mj->RefCount++;
						}
					}
				}
			}
		}
	}
}




//==============================================================
// 取得，共通プロパティ

void CMoverGroupManager::DeleteAll() {
	for (int i=0; i<NUM_GROUPS; i++) Groups[i]->DeleteAll();
}

void CMoverGroupManager::SetScreenHit(const CHit& hit) {
	for (int i=0; i<NUM_GROUPS; i++) Groups[i]->SetScreenHit(hit);
}

void CMoverGroupManager::SetDeadzoneHit(const CHit& hit) {
	for (int i=0; i<NUM_GROUPS; i++) Groups[i]->SetDeadzoneHit(hit);
}

CMover* CMoverGroup::GetRandomUsedMover() {
	if (NumUsedMovers==0) return NULL;
	return UsedMovers[rand()%NumUsedMovers];
}

CMover* CMover::GetRandomMyShip() {
	return Group->GetManager()->GetGroup(MYSHIP_GROUP)->GetRandomUsedMover();
}

CMover* CMover::GetLockedEnemy(int id) {
	return Group->GetManager()->GetGroup(ENEMY_GROUP)->GetLockedMover(id);
}

void CMover::ClearLockedEnemy() {
	Group->GetManager()->GetGroup(ENEMY_GROUP)->ClearLockedMover();
}

void CMoverGroup::ClearLockedMover() {
	for (int i=0; i<MAX_LOCKS; i++) {
		CMover* mover=LockedMovers[i];
		if (mover) mover->RefCount--;
		LockedMovers[i]=NULL;
	}
}




