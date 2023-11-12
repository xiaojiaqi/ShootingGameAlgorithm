#include "Main.h"


//==============================================================
// ƒCShtGame„3Dƒ‚ƒfƒ‹‚Ìì¬
void CShtGame::MakeModels() {
	string dir=ExePath+"models\\";
	
	Obj3D[MYSHIP]->LoadFromFile(dir+"myship.x")
		->SetHit(HIT_ALL,  CHit(-4, 4, -3.5f, 3.5f))
		->SetHit(HIT_CORE, CHit(-0.25f, 0.25f, -0.5f, 1))
		->SetTopViewOnly(false);
	Obj3D[MYSHIP2]->LoadFromFile(dir+"myship2.x")
		->SetHit(HIT_ALL,  CHit(-4, 4, -3.5f, 3.5f))
		->SetHit(HIT_CORE, CHit(-0.25f, 0.25f, -0.5f, 1))
		->SetTopViewOnly(false);

	Obj3D[OPTION]->LoadFromFile(dir+"option.x");
	Obj3D[POWER_EFFECT]->LoadFromFile(dir+"power_effect.x");
	Obj3D[MAX_EFFECT]->LoadFromFile(dir+"max_effect.x");

	Obj3D[BOSS0]->LoadFromFile(dir+"boss0.x")
		->SetHit(HIT_ALL,  CHit(-50, 50, -50, 50))
		->SetHit(HIT_CORE,  CHit(-8, 8, -8, 8));
	Obj3D[BOSS1]->LoadFromFile(dir+"boss1.x")
		->SetHit(HIT_ALL,  CHit(-50, 50, -50, 50));
	Obj3D[BOSS2]->LoadFromFile(dir+"boss2.x")
		->SetHit(HIT_ALL,  CHit(-50, 50, -50, 50));
	Obj3D[BOSS_CANNON]->LoadFromFile(dir+"boss_cannon.x")
		->SetHit(HIT_ALL,  CHit(-10, 10, -5, 5))
		->SetHit(HIT_CORE,  CHit(-6, 6, -3, 3));

	Obj3D[STAR0]->LoadFromFile(dir+"star0.x")
		->SetHit(HIT_ALL,  CHit(-1, 1, -1, 1));
	Obj3D[STAR1]->LoadFromFile(dir+"star0.x")
		->SetHit(HIT_ALL,  CHit(-1, 1, -1, 1));
	Obj3D[STAR2]->LoadFromFile(dir+"star0.x")
		->SetHit(HIT_ALL,  CHit(-1, 1, -1, 1));

	Obj3D[CHIP0]->LoadFromFile(dir+"chip0.x")
		->SetHit(HIT_ALL,  CHit(-5, 5, -5, 5));
	Obj3D[CHIP1]->LoadFromFile(dir+"chip1.x")
		->SetHit(HIT_ALL,  CHit(-5, 5, -5, 5));
	Obj3D[CHIP2]->LoadFromFile(dir+"chip2.x")
		->SetHit(HIT_ALL,  CHit(-5, 5, -5, 5));
	Obj3D[CHIP3]->LoadFromFile(dir+"chip3.x")
		->SetHit(HIT_ALL,  CHit(-5, 5, -5, 5));
	Obj3D[CHIP4]->LoadFromFile(dir+"chip4.x")
		->SetHit(HIT_ALL,  CHit(-5, 5, -5, 5));
	Obj3D[CHIP5]->LoadFromFile(dir+"chip5.x")
		->SetHit(HIT_ALL,  CHit(-5, 5, -5, 5));

	Obj3D[PUNCH]->LoadFromFile(dir+"punch.x")
		->SetHit(HIT_ALL,  CHit(-1, 5, -14, 1))
		->SetHit(HIT_CORE, CHit(-1, 5, -14, -6));
	Obj3D[BARRIER]->LoadFromFile(dir+"barrier.x")
		->SetHit(HIT_ALL,  CHit(-6, 6, -6, 6))
		->SetHit(HIT_CORE, CHit(-6, 6, -6, 6));
	Obj3D[BERSERK]->LoadFromFile(dir+"berserk.x")
		->SetHit(HIT_ALL,  CHit(-6, 6, -6, 6))
		->SetHit(HIT_CORE, CHit(-6, 6, -6, 6));

	Obj3D[DOCKING_MYSHIP]->LoadFromFile(dir+"docking_myship.x")
		->SetHit(HIT_ALL,  CHit(-6.5f, 6.5f, -3.5f, 6.5f))
		->SetHit(HIT_CORE, CHit(-3, 3, -0.5f, 4))
		->SetTopViewOnly(false);
	Obj3D[DOCKING_ENEMY]->LoadFromFile(dir+"docking_enemy.x")
		->SetHit(HIT_ALL,  CHit(-3.5f, 3.5f, -3, 3))
		->SetHit(HIT_CORE, CHit(-1.5f, 1.5f, -1.5f, 1.5f))
		->SetTopViewOnly(false);
	Obj3D[DOCKING_ITEM]->LoadFromFile(dir+"docking_item.x")
		->SetHit(HIT_ALL,  CHit(-6.5f, 6.5f, -3, 3))
		->SetHit(HIT_CORE, CHit(-3, 3, -1, 1))
		->SetTopViewOnly(false);

	Obj3D[WALK_MYSHIP]->LoadFromFile(dir+"walk_myship.x")
		->SetHit(HIT_ALL,  CHit(-4, 4, -3.5f, 3.5f))
		->SetHit(HIT_CORE, CHit(-0.25f, 0.25f, -0.5f, 1))
		->SetTopViewOnly(false);

	Obj3D[ITEM_YELLOW]->LoadFromFile(dir+"item_yellow.x")
		->SetHit(HIT_ALL,  CHit(-4, 4, -4, 4))
		->SetHit(HIT_CORE, CHit(-4, 4, -4, 4));
	Obj3D[ITEM_BLUE]->LoadFromFile(dir+"item_blue.x")
		->SetHit(HIT_ALL,  CHit(-4, 4, -4, 4))
		->SetHit(HIT_CORE, CHit(-4, 4, -4, 4));

	Obj3D[GROUND_YELLOW]->LoadFromFile(dir+"ground_yellow.x")
		->SetHit(HIT_ALL,  CHit(-4, 4, -4, 4))
		->SetHit(HIT_CORE, CHit(-4, 4, -4, 4));
	Obj3D[GROUND_CYAN]->LoadFromFile(dir+"ground_cyan.x")
		->SetHit(HIT_ALL,  CHit(-4, 4, -4, 4))
		->SetHit(HIT_CORE, CHit(-4, 4, -4, 4));
	Obj3D[WATER]->LoadFromFile(dir+"water.x")
		->SetHit(HIT_ALL,  CHit(-4, 4, -4, 4))
		->SetHit(HIT_CORE, CHit(-4, 4, -4, 4));
	Obj3D[WAVE]->LoadFromFile(dir+"wave.x")
		->SetHit(HIT_ALL,  CHit(-4, 4, -4, 4));

	Obj3D[SHOT_SMALL]->LoadFromFile(dir+"shot_small.x")
		->SetHit(HIT_ALL,  CHit(-1, 1, -1.5f, 1.5f))
		->SetHit(HIT_CORE, CHit(-1.5f, 1.5f, -2, 2));
	Obj3D[SHOT_SMALL_ORANGE]->LoadFromFile(dir+"shot_small_orange.x")
		->SetHit(HIT_ALL,  CHit(-1, 1, -1.5f, 1.5f))
		->SetHit(HIT_CORE, CHit(-1.5f, 1.5f, -2, 2));
	Obj3D[SHOT_SMALL_GREEN]->LoadFromFile(dir+"shot_small_green.x")
		->SetHit(HIT_ALL,  CHit(-1, 1, -1.5f, 1.5f))
		->SetHit(HIT_CORE, CHit(-1.5f, 1.5f, -2, 2));
	Obj3D[SHOT_MEDIUM]->LoadFromFile(dir+"shot_medium.x")
		->SetHit(HIT_ALL,  CHit(-1.5, 1.5, -2.25f, 2.25f))
		->SetHit(HIT_CORE, CHit(-2.25f, 2.25f, -3, 3));
	Obj3D[SHOT_LARGE]->LoadFromFile(dir+"shot_large.x")
		->SetHit(HIT_ALL,  CHit(-2, 2, -3.0f, 3.0f))
		->SetHit(HIT_CORE, CHit(-3.0f, 3.0f, -4, 4));

	Obj3D[SIGHT_BOMB_READY]->LoadFromFile(dir+"sight_bomb_ready.x")
		->SetHit(HIT_ALL,  CHit(-4, 4, -4, 4))
		->SetHit(HIT_CORE, CHit(-8, 8, -8, 8));
	Obj3D[SIGHT_BOMB_LOCK]->LoadFromFile(dir+"sight_bomb_lock.x")
		->SetHit(HIT_ALL,  CHit(-1.5f, 1.5f, -1.5f, 1.5f));
	Obj3D[SIGHT_BOMB_TARGET]->LoadFromFile(dir+"sight_bomb_target.x")
		->SetHit(HIT_ALL,  CHit(-1.5f, 1.5f, -1.5f, 1.5f));
	Obj3D[SIGHT_BOMB_BUSY]->LoadFromFile(dir+"sight_bomb_busy.x")
		->SetHit(HIT_ALL,  CHit(-1.5f, 1.5f, -1.5f, 1.5f));
	Obj3D[SIGHT_BOMB_BOMB]->LoadFromFile(dir+"sight_bomb_bomb.x")
		->SetHit(HIT_ALL,  CHit(-1.5f, 1.5f, -1.5f, 1.5f))
		->SetHit(HIT_CORE, CHit(-3, 3, -3, 3));

	Obj3D[CRASH_MYSHIP]->LoadFromFile(dir+"crash_myship.x")
		->SetHit(HIT_ALL,  CHit(-2.5f, 2.5f, -2.5f, 2.5f))
		->SetHit(HIT_CORE, CHit(-1, 1, -1, 1));
	Obj3D[CRASH_ENEMY]->LoadFromFile(dir+"crash_enemy.x")
		->SetHit(HIT_ALL,  CHit(-2.5f, 2.5f, -2.5f, 2.5f))
		->SetHit(HIT_CORE, CHit(-1, 1, -1, 1));
	Obj3D[CRASH_MISSILE]->LoadFromFile(dir+"crash_missile.x")
		->SetHit(HIT_ALL,  CHit(-2.5f, 2.5f, -2.5f, 2.5f))
		->SetHit(HIT_CORE, CHit(-1, 1, -1, 1));
	Obj3D[ENEMY]->LoadFromFile(dir+"enemy.x")
		->SetHit(HIT_ALL,  CHit(-3.5f, 3.5f, -3, 3))
		->SetHit(HIT_CORE, CHit(-1.5f, 1.5f, -1.5f, 1.5f));
	Obj3D[ENEMY_BLUE]->LoadFromFile(dir+"enemy_blue.x")
		->SetHit(HIT_ALL,  CHit(-3.5f, 3.5f, -3, 3))
		->SetHit(HIT_CORE, CHit(-1.5f, 1.5f, -1.5f, 1.5f));
	Obj3D[ENEMY_REV]->LoadFromFile(dir+"enemy_rev.x")
		->SetHit(HIT_ALL,  CHit(-3.5f, 3.5f, -3, 3))
		->SetHit(HIT_CORE, CHit(-1.5f, 1.5f, -1.5f, 1.5f));
	Obj3D[ENEMY_CANNON]->LoadFromFile(dir+"enemy_cannon.x")
		->SetHit(HIT_ALL,  CHit(-3.0f, 3.0f, -3, 3))
		->SetHit(HIT_CORE, CHit(-1.5f, 1.5f, -1.5f, 1.5f))
		->SetTopViewOnly(false);
	Obj3D[RUIN]->LoadFromFile(dir+"ruin.x")
		->SetHit(HIT_ALL,  CHit(-3.0f, 3.0f, -3, 3));
	Obj3D[BULLET_SMALL_BLUE]->LoadFromFile(dir+"bullet_small_blue.x")
		->SetHit(HIT_ALL,  CHit(-1, 1, -1, 1))
		->SetHit(HIT_CORE, CHit(-0.5f, 0.5f, -0.5f, 0.5f));
	Obj3D[BULLET_SMALL_PURPLE]->LoadFromFile(dir+"bullet_small_purple.x")
		->SetHit(HIT_ALL,  CHit(-1, 1, -1, 1))
		->SetHit(HIT_CORE, CHit(-0.5f, 0.5f, -0.5f, 0.5f));		
	Obj3D[BULLET_SMALL_ORANGE]->LoadFromFile(dir+"bullet_small_orange.x")
		->SetHit(HIT_ALL,  CHit(-1, 1, -1, 1))
		->SetHit(HIT_CORE, CHit(-0.5f, 0.5f, -0.5f, 0.5f));
	Obj3D[BULLET_SMALL_GREEN]->LoadFromFile(dir+"bullet_small_green.x")
		->SetHit(HIT_ALL,  CHit(-1, 1, -1, 1))
		->SetHit(HIT_CORE, CHit(-0.5f, 0.5f, -0.5f, 0.5f));		
	Obj3D[BULLET_MEDIUM_BLUE]->LoadFromFile(dir+"bullet_medium_blue.x")
		->SetHit(HIT_ALL,  CHit(-1.5f, 1.5f, -1.5f, 1.5f))
		->SetHit(HIT_CORE, CHit(-0.75f, 0.75f, -0.75f, 0.75f));		
	Obj3D[BULLET_MEDIUM_PURPLE]->LoadFromFile(dir+"bullet_medium_purple.x")
		->SetHit(HIT_ALL,  CHit(-1.5f, 1.5f, -1.5f, 1.5f))
		->SetHit(HIT_CORE, CHit(-0.75f, 0.75f, -0.75f, 0.75f));		
	Obj3D[NEEDLE_SMALL_BLUE]->LoadFromFile(dir+"needle_small_blue.x")
		->SetHit(HIT_ALL,  CHit(-0.3f, 0.3f, -1, 1))
		->SetHit(HIT_CORE, CHit(-0.2f, 0.2f, -0.2f, 0.2f));		
	Obj3D[NEEDLE_SMALL_PURPLE]->LoadFromFile(dir+"needle_small_purple.x")
		->SetHit(HIT_ALL,  CHit(-0.3f, 0.3f, -1, 1))
		->SetHit(HIT_CORE, CHit(-0.2f, 0.2f, -0.2f, 0.2f));		
	Obj3D[LASER_THIN_BLUE]->LoadFromFile(dir+"laser_thin_blue.x")
		->SetHit(HIT_ALL,  CHit(-0.5f, 0.5f, -1, 1))
		->SetHit(HIT_CORE, CHit(-0.3f, 0.3f, -0.3f, 0.3f));		
	Obj3D[LASER_THIN_PURPLE]->LoadFromFile(dir+"laser_thin_purple.x")
		->SetHit(HIT_ALL,  CHit(-0.5f, 0.5f, -1, 1))
		->SetHit(HIT_CORE, CHit(-0.3f, 0.3f, -0.3f, 0.3f));		
	Obj3D[LASER_THICK_BLUE]->LoadFromFile(dir+"laser_thick_blue.x")
		->SetHit(HIT_ALL,  CHit(-10, 10, -10, 10))
		->SetHit(HIT_CORE, CHit(-8, 8, -8, 8));		
	Obj3D[LASER_SIGN]->LoadFromFile(dir+"laser_sign.x")
		->SetHit(HIT_ALL,  CHit(-0.5f, 0.5f, -1, 1))
		->SetHit(HIT_CORE, CHit(0, 0, 0, 0));	
	Obj3D[MISSILE_SMALL]->LoadFromFile(dir+"missile_small.x")
		->SetHit(HIT_ALL,  CHit(-1.1f, 1.1f, -2.5f, 2.5f))
		->SetHit(HIT_CORE, CHit(-0.5f, 0.5f, -0.5f, 0.5f));		
	Obj3D[MISSILE_TAIL_SMALL]->LoadFromFile(dir+"missile_tail_small.x")
		->SetHit(HIT_ALL,  CHit(-0.5f, 0.5f, -1, 1))
		->SetHit(HIT_CORE, CHit(0, 0, 0, 0));
}


