#ifndef WEAPONH
#define WEAPONH

#include "Object3D.h"

#include <vector>
using namespace std;


// ïêäÌÇÃéÌóﬁ
typedef enum {
	WP_BASIC_SHOT, WP_AUTO_SHOT, 
	WP_POWER_SHOT, WP_SEMI_AUTO_SHOT, WP_POWER_SHOT_RELEASED,
	WP_SHOT_AND_LASER, WP_LOCK_SHOT, WP_COMMAND_SHOT,
	WP_SIGHTED_BOMB, WP_LOCK_ON_LASER, WP_GROUND_MISSILES,
	WP_REFLECT_SHOT, WP_REFLECT_LASER,
	WP_TURN_MARKER
} WEAPON_ID;


class CWeapon;
class CWeaponGroup;


class CWeapon {
friend CWeaponGroup;
private:
	CWeaponGroup* Group;
	bool Used, Dead;
	CWeapon *Prev, *Next;
};


class CWeaponGroup {
public:
	CWeaponGroup:
	CWeapon* New();
	void Delete(CWeapon* wp);
};


#endif
