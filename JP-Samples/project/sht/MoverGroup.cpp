#include "Mover.h"
#include "Hit.h"
#include "..\LibGame\Input.h"
#include <assert.h>




//==============================================================
// コンストラクタ，デストラクタ

CMoverGroup::CMoverGroup(
	CMoverGroupManager* manager, LPDIRECT3DDEVICE9 device,
	int num_all_movers
) :	Manager(manager), Input(NULL), Device(device),
	NumAllMovers(num_all_movers)
{
	AllMovers=new CMover*[NumAllMovers];
	FreeMovers=new CMover*[NumAllMovers];
	UsedMovers=new CMover*[NumAllMovers];
	for (int i=0; i<NumAllMovers; i++) AllMovers[i]=new CMover(this);
	DeleteAll();
}

CMoverGroup::~CMoverGroup() {
	for (int i=0; i<NumAllMovers; i++) delete AllMovers[i];
	delete[] AllMovers;
	delete[] FreeMovers;
	delete[] UsedMovers;
}




//==============================================================
// 確保，解放

CMover* CMoverGroup::New() {
	if (NumFreeMovers==0) return NULL;
	--NumFreeMovers;
	CMover* mover=FreeMovers[NumFreeMovers];
	mover->Used=true;
	return mover;
}

void CMoverGroup::Delete(CMover* mover) {
	assert(NumFreeMovers<NumAllMovers);
	FreeMovers[NumFreeMovers++]=mover;
	mover->Used=false;
}

void CMoverGroup::DeleteAll() {
	int i;
	for (i=0; i<NumAllMovers; i++) {
		CMover* mover=AllMovers[i];
		FreeMovers[i]=mover;
		mover->Used=false;
	}
	for (i=0; i<MAX_LOCKS; i++) {
		LockedMovers[i]=NULL;
	}
	NumFreeMovers=NumAllMovers;
	NumUsedMovers=0;
	CollisionEnergy=0;
	Speed=SpeedTime=0;
}




//==============================================================
// 移動，描画

void CMoverGroup::Check() {
	int i;

	NumUsedMovers=0;
	for (i=0; i<NumAllMovers; i++) {
		CMover* mover=AllMovers[i];
		if (mover->Used) UsedMovers[NumUsedMovers++]=mover;
	}

	for (i=0; i<MAX_LOCKS; i++) {
		CMover* mover=LockedMovers[i];
		if (mover && mover->Dead) {
			mover->RefCount--;
			LockedMovers[i]=NULL;
		}
	}
	for (i=0; i<NumUsedMovers; i++) {
		UsedMovers[i]->Check();
	}
}

void CMoverGroup::Move() {
	if (Speed>=0 || SpeedTime==0) {
		for (int n=(Speed>0?Speed:0); n>=0; n--) {
			for (int i=0; i<NumUsedMovers; i++) {
				UsedMovers[i]->Move();
			}
		}
	}
	SpeedTime--;
	if (SpeedTime<0) SpeedTime=-Speed;
	CollisionEnergy--;
}

void CMoverGroup::PostMove() {
	for (int i=0; i<NumUsedMovers; i++) UsedMovers[i]->PostMove();
}

void CMoverGroup::Draw() {
	for (int i=0; i<NumUsedMovers; i++) {
		if (!UsedMovers[i]->Dead) UsedMovers[i]->Draw();
	}
}




//==============================================================
// 取得，当たり判定処理

CMover* CMoverGroup::FirstUsed() {
	HitIndex=0;
	return NextUsed();
}

CMover* CMoverGroup::NextUsed() {
	for (; HitIndex<NumUsedMovers; HitIndex++) {
		CMover* mover=UsedMovers[HitIndex];
		if (!mover->Dead) {
			HitIndex++;
			return mover;
		}
	}
	return NULL;
}

CMover* CMoverGroup::FirstHit(CHit* hit) {
	HitIndex=0;
	return NextHit(hit);
}

CMover* CMoverGroup::NextHit(CHit* hit) {
	for (; HitIndex<NumUsedMovers; HitIndex++) {
		CMover* mover=UsedMovers[HitIndex];
		if (!mover->Dead && mover->Obj3D &&
			mover->Obj3D->GetHit(HIT_CORE).IsHit(mover->X, mover->Y, *hit)) {
			HitIndex++;
			return mover;
		}
	}
	return NULL;
}

CMover* CMoverGroup::FirstInside(CHit* hit) {
	HitIndex=0;
	return NextInside(hit);
}

CMover* CMoverGroup::NextInside(CHit* hit) {
	for (; HitIndex<NumUsedMovers; HitIndex++) {
		CMover* mover=UsedMovers[HitIndex];
		if (!mover->Dead && mover->Obj3D &&
			hit->IsInside(0, 0, mover->Obj3D->GetHit(HIT_CORE), mover->X, mover->Y)) {
			HitIndex++;
			return mover;
		}
	}
	return NULL;
}




