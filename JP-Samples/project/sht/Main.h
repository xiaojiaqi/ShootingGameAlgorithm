#ifndef MAINH
#define MAINH

#include "..\LibGame\Game.h"
#include "Object3D.h"
#include "Mover.h"

//#define CMAGA6


//==============================================================
// 自機，敵，弾のグラフィックス
enum {
	MYSHIP, MYSHIP2, OPTION, BARRIER, BERSERK, PUNCH,
	DOCKING_MYSHIP, DOCKING_ENEMY, DOCKING_ITEM,
	WALK_MYSHIP,
	BOSS0, BOSS1, BOSS2, BOSS_CANNON,
	CHIP0, CHIP1, CHIP2, CHIP3, CHIP4, CHIP5,
	STAR0, STAR1, STAR2,
	ITEM_YELLOW, ITEM_BLUE,
	POWER_EFFECT, MAX_EFFECT,
	ENEMY, ENEMY_REV, ENEMY_CANNON, ENEMY_BLUE, RUIN,
	GROUND_YELLOW, GROUND_CYAN,
	WATER, WAVE, 
	CRASH_MYSHIP, CRASH_ENEMY, CRASH_MISSILE,
	BULLET_SMALL_BLUE, BULLET_SMALL_PURPLE,
	BULLET_SMALL_ORANGE, BULLET_SMALL_GREEN,
	BULLET_MEDIUM_BLUE, BULLET_MEDIUM_PURPLE,
	NEEDLE_SMALL_BLUE, NEEDLE_SMALL_PURPLE,
	LASER_THIN_BLUE, LASER_THIN_PURPLE,
	LASER_THICK_BLUE, LASER_SIGN,
	MISSILE_SMALL, MISSILE_TAIL_SMALL,
	SHOT_SMALL, SHOT_MEDIUM, SHOT_LARGE,
	SHOT_SMALL_ORANGE, SHOT_SMALL_GREEN,
	SIGHT_BOMB_READY, SIGHT_BOMB_LOCK,
	SIGHT_BOMB_TARGET, SIGHT_BOMB_BUSY,
	SIGHT_BOMB_BOMB,
	OBJ3D_COUNT
};


//==============================================================
// ステージ
class CStage {
public:
	CMover* Mover;
	char *Name, *Inst;
	VIEW_TYPE ViewType;
	CStage(CMover* mover, char* name, char* inst, VIEW_TYPE view_type=VIEW_TOP)
	:	Mover(mover), Name(name), Inst(inst), ViewType(view_type)
	{
		Name=new char[strlen(name)+1];
		strcpy(Name, name);
		Inst=new char[strlen(inst)+1];
		strcpy(Inst, inst);
	}
};


//==============================================================
// ゲームの状態
typedef enum {
	GM_GAME, GM_SELECT
} GAME_MODE;

#define NUM_STARS 3


//==============================================================
// シューティングゲームのクラス
class CShtGame : public CGame {
private:

	CText *Text;
	HFONT LargeFont, SmallFont;
	vector<CObject3D*> Obj3D;
	CMoverGroupManager *MoverGroupManager;
	CMover *MyShipTopView, *MyShipSideView;
	CBgMover *StarTV[NUM_STARS], *StarSV[NUM_STARS];

	// ステージ
	vector<CStage> Stages;
	int SelectedStage;

	// ゲームの状態
	GAME_MODE GameMode;

	// ステージの追加，開始，選択
	void AddStage(
		CMover* stage, char* name, char* inst, VIEW_TYPE view_type=VIEW_TOP);
	void AddStage(CMover* stage, char* name, VIEW_TYPE view_type=VIEW_TOP);
	void StartStage();
	void SelectStage();

	// 3Dモデルとステージの初期化
	void MakeModels();
	void MakeStages();
	void MakeStages_Bullet();
	void MakeStages_Weapon();
	void MakeStages_MyShip();
	void MakeStages_Special();
	void MakeStages_Enemy();
	void MakeStages_Scroll();

	// テキストの描画
	void DrawShadedText(
		char* text, int x, int y, D3DCOLOR color, D3DCOLOR shade_color,
		ALIGN_TYPE ax, ALIGN_TYPE ay
	);
	int DrawLines(char* lines, int y, int vy, D3DCOLOR color);

public:

	CShtGame();
	~CShtGame();
	void Draw();
	void Move();

};


#endif




