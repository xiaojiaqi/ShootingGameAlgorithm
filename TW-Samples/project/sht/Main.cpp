#include "Main.h"


// 說明
static char common_inst[]=
	"●自機的移動與關卡選擇●\n"
	"●請用鍵盤的方向鍵與搖桿(數位/類比)●\n"
	"\n"
	"●開始遊戲關卡●\n"
	"[Z]鍵／按鈕1\n"
	"\n"
	"●全螢幕切換●\n"
	"[Alt]+[Enter]鍵\n"
	"\n"
	"●結束●\n"
	"[ESC]鍵"
	;

#ifdef CMAGA6
static char book_pr[]=
	"「射擊遊戲演算法與程式原理」\n"
	"2005年2月上市！！\n"
	"\n"
	"●書籍介紹●\n"
	"[F1]鍵"
	;
#else
static char book_pr[]=
	"「射擊遊戲演算法與程式原理」\n"
	"（松浦健一郎著  中文版由博碩文化出版發行）\n"
	"\n"
	"●書籍介紹（Web）●\n"
	"[F1]鍵"
	;
#endif


// 顏色
static const D3DCOLOR 
	name_color=D3DCOLOR_ARGB(255, 200, 200, 255),
	name_shade=D3DCOLOR_ARGB(128, 0, 128, 255),
	inst_color=D3DCOLOR_ARGB(255, 255, 255, 255),
	common_inst_color=D3DCOLOR_ARGB(255, 255, 200, 160),
	book_pr_color=D3DCOLOR_ARGB(255, 200, 255, 160);


//==============================================================
// ＜CShtGame＞舞台關卡的構築
void CShtGame::MakeStages() {
	CMover *crash[100];
	CMoverGroup* sg=MoverGroupManager->GetGroup(STAGE_GROUP);
	CMoverGroup* mg=MoverGroupManager->GetGroup(MYSHIP_GROUP);
	CMoverGroup* wg=MoverGroupManager->GetGroup(WEAPON_GROUP);

	//==========================================================
	// 爆炸
	crash[3]=(new CMover(sg))
		->SetObj3D(Obj3D[CRASH_MYSHIP])
		->SetScale(0.2f, 0.2f, 0.2f, 0.2f)
		->SetAlpha(2, -0.04f)
		->SetNext(NULL, 50);
	crash[0]=(new CMover(sg))
		->AddSpawn(crash[3], 0, 0, 1);

	crash[4]=(new CMover(sg))
		->SetObj3D(Obj3D[CRASH_ENEMY])
		->SetScale(0.5f, 0.5f, 0.1f, 0.1f)
		->SetAlpha(2, -0.04f)
		->SetNext(NULL, 50);
	crash[1]=(new CMover(sg))
		->AddSpawn(crash[4], 0, 0, 1);

	//==========================================================
	// 我機
	MyShipTopView=(new CMover(mg))
		->SetObj3D(Obj3D[MYSHIP])
		->SetMyShip(0, 37.5f, 90, 0.5f)
		->SetAutoRoll(0.1f, 0.01f)
		->SetDamage(1, 1, crash[0], NULL, false, false);
	MyShipSideView=(new CMover(mg))
		->SetObj3D(Obj3D[MYSHIP])
		->SetMyShip(0, 10, 37.5f, 0.5f)
		->SetAutoRoll(0.1f, 0.01f, false)
		->SetDamage(1, 1, crash[0], NULL, false, false);

	//==========================================================
	// 星星
	// 使用Obj3D時，設成
	// ->SetStar(Obj3D[STAR0], -2, -2, 77, 102, 0, vy, -100, 100)
	// 
	CMoverGroup* bgb=MoverGroupManager->GetGroup(BG_GROUP);
	float v;
	int i;
	for (i=0, v=0.2f; i<NUM_STARS; i++, v*=2) {
		StarTV[i]=(new CBgMover(bgb))
			->SetStar(0, v, 1, 100, 0xffc0c0c0, 0xffffffff);
	}
	for (i=0, v=-0.2f; i<NUM_STARS; i++, v*=2) {
		StarSV[i]=(new CBgMover(bgb))
			->SetStar(v, 0, 1, 100, 0xffc0c0c0, 0xffffffff);
	}

	//==========================================================
	// 製成關卡
	MakeStages_Bullet();
	MakeStages_MyShip();
	MakeStages_Weapon();
	MakeStages_Special();
	MakeStages_Enemy();
	MakeStages_Scroll();
}


//==============================================================
// ＜CShtGame＞追加關卡
void CShtGame::AddStage(
	CMover* stage, char* name, char* inst, VIEW_TYPE view_type
) {
	Stages.push_back(CStage(stage, name, inst, view_type));
}
void CShtGame::AddStage(CMover* stage, char* name, VIEW_TYPE view_type) {
	static char dummy_text[]="";
	AddStage(stage, name, dummy_text, view_type);
}


//==============================================================
// ＜CShtGame＞開始關卡
void CShtGame::StartStage() {
	if (Stages.empty()) return;
	CStage& stage=Stages[SelectedStage];

	CMover* mover;
	MoverGroupManager->DeleteAll();

	// 我機
	CMoverGroup* mg=MoverGroupManager->GetGroup(MYSHIP_GROUP);
	mg->SetInput(Input);

	// 關卡舞台
	CMoverGroup* sg=MoverGroupManager->GetGroup(STAGE_GROUP);
	if (mover=sg->New()) mover->Init(stage.Mover);

	// 星星
	CBgMover **star=(stage.ViewType==VIEW_TOP?StarTV:StarSV);
	for (int i=0; i<NUM_STARS; i++) star[i]->New();

	// 關卡名稱
	Text->Clear();
	DrawShadedText(stage.Name, 0, 0, 
		name_color, name_shade, ALIGN_LEFT, ALIGN_TOP);
}


//==============================================================
// ＜CShtGame＞選擇關卡
#define DEADZONE 3
void CShtGame::SelectStage() {
	if (Stages.empty()) return;

	// 選擇關卡
	int size=Stages.size();
	SelectedStage=(SelectedStage%size+size)%size;
	CStage& stage=Stages[SelectedStage];
	
	CMover* mover;
	MoverGroupManager->DeleteAll();

	// 我機
	CMoverGroup* mg=MoverGroupManager->GetGroup(MYSHIP_GROUP);
	mg->SetInput(NULL);

	// 關卡
	CMoverGroup* sg=MoverGroupManager->GetGroup(STAGE_GROUP);
	if (mover=sg->New()) mover->Init(stage.Mover);
	
	// 星星
	CBgMover **star=(stage.ViewType==VIEW_TOP?StarTV:StarSV);
	for (int i=0; i<NUM_STARS; i++) star[i]->New();

	// view的設定
	VIEW_TYPE vt=stage.ViewType;
	CObject3D::SetViewType(vt);
	MoverGroupManager->SetScreenHit(vt==VIEW_TOP?
		CHit(0, 75, 0, 100) : CHit(0, 100, 0, 75));
	MoverGroupManager->SetDeadzoneHit(vt==VIEW_TOP?
		CHit(0-DEADZONE, 75+DEADZONE, 0-DEADZONE, 100+DEADZONE) : 
		CHit(0-DEADZONE, 100+DEADZONE, 0-DEADZONE, 75+DEADZONE));

	// 描繪出關卡名稱與說明
	Text->Clear();
	int w2=Text->GetWidth()/2, y=0;
	char s[100];
	sprintf(s, "Stage#%d ", SelectedStage+1);
	DrawShadedText(s, w2, y, name_color, name_shade, ALIGN_CENTER, ALIGN_TOP);
	y+=20;
	DrawShadedText(stage.Name, w2, y, name_color, name_shade, ALIGN_CENTER, ALIGN_TOP);
	y+=40;
	y=DrawLines(stage.Inst, y, 20, inst_color);
	y+=20;
	y=DrawLines(common_inst, y, 20, common_inst_color);
	y+=20;
	y=DrawLines(book_pr, y, 20, book_pr_color);
}


//==============================================================
// ＜CShtGame＞建構式
CShtGame::CShtGame()
:	CGame("射擊遊戲演算法與程式原理Ver.1.00", true),
	SelectedStage(0), GameMode(GM_SELECT)
{
	// Help
	HelpURL="http://cgi32.plala.or.jp/higpen/index_shtbook.shtml";

	// 文字與字體
	Text=new CText(512, 512);
	LargeFont=CreateFont(20, 0, 0, 0, FW_NORMAL,
		FALSE, FALSE, FALSE, CHINESEBIG5_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY,
		DEFAULT_PITCH, "新細明體");
	SmallFont=CreateFont(16, 0, 0, 0, FW_NORMAL,
		FALSE, FALSE, FALSE, CHINESEBIG5_CHARSET, 
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY,
		DEFAULT_PITCH, "新細明體");

	// 移動物體
	MoverGroupManager=new CMoverGroupManager(Graphics->GetDevice());

	// 讀取3D模型
	CObject3D::Init(Graphics->GetDevice());
	for (int i=0; i<OBJ3D_COUNT; i++) Obj3D.push_back(new CObject3D());
	MakeModels();

	// 關卡的作成和選擇
	MakeStages();
	SelectStage();
}


//==============================================================
// ＜CShtGame＞Death tractor
CShtGame::~CShtGame() {
	for (int i=0; i<(int)Obj3D.size(); i++) delete Obj3D[i];
	CObject3D::Uninit();
	delete MoverGroupManager;
	delete Text;
}


//==============================================================
// 移動
void CShtGame::Move() {
	static bool 
		prev_stick=false, prev_select=false,
		pausing=false, prev_pause=false;

	// 輸入狀態的取得
	Input->UpdateState();		
	const CInputState* is=Input->GetState(0);

	// 遊戲進行
	if (!pausing) {
		MoverGroupManager->Check();
		MoverGroupManager->Move();
		
		// 模式切換
		switch (GameMode) {
			case GM_GAME:
				if (!prev_select && is->Button[0]) {
					GameMode=GM_SELECT;
					SelectStage();
				}
				break;
			case GM_SELECT:
				if (!prev_stick && is->Left) {
					SelectedStage--;
					SelectStage();
				} else
				if (!prev_stick && is->Right) {
					SelectedStage++;
					SelectStage();
				} else
				if (!prev_stick && is->Up) {
					SelectedStage-=10;
					SelectStage();
				} else
				if (!prev_stick && is->Down) {
					SelectedStage+=10;
					SelectStage();
				} else
				if (!prev_select && is->Button[0]) {
					GameMode=GM_GAME;
					StartStage();
				}
				break;
		}
		prev_stick=is->Up||is->Down||is->Left||is->Right;
		prev_select=is->Button[0];
	}

	// 暫停
	if (!prev_pause && is->Button[3]) pausing=!pausing;
	prev_pause=is->Button[3];
}


//==============================================================
// 描繪

// 描繪多行文字
int CShtGame::DrawLines(char* lines, int y, int vy, D3DCOLOR color) {
	char c, *p, *q;
	int w2=Text->GetWidth()/2;
	for (p=lines; *p!='\0'; p++) {
		for (q=p; *p!='\n' && *p!='\0'; p++) ;
		if (q!=p) {
			c=*p;
			*p='\0';
			Text->DrawText(q, w2, y, color, SmallFont, ALIGN_CENTER, ALIGN_CENTER);
			*p=c;
			y+=vy;
		} else {
			y+=vy/2;
		}
		if (*p=='\0') break;
	}
	return y;
}

// 文字陰影部份的描繪
void CShtGame::DrawShadedText(
	char* text, int x, int y, D3DCOLOR color, D3DCOLOR shade_color,
	ALIGN_TYPE ax, ALIGN_TYPE ay
) {
	Text->DrawText(text, x+2, y+2, shade_color, LargeFont, ax, ay);
	Text->DrawText(text, x+3, y+2, shade_color, LargeFont, ax, ay);
	Text->DrawText(text, x+1, y  , color      , LargeFont, ax, ay);
	Text->DrawText(text, x  , y  , color      , LargeFont, ax, ay);
}

// 遊戲畫面的描繪
void CShtGame::Draw() {

	// 清除畫面
	CImage::SetDeviceState();
	Graphics->Clear(D3DCOLOR_XRGB(0, 0, 64));

	// 移動物體的顯示
	CObject3D::SetDeviceState();
	Graphics->Clear();

	if (!Graphics->BeginScene()) return;
	MoverGroupManager->Draw();

	// 文字的顯示
	CImage::SetDeviceState();
	if (Stages.size()>0) {
		CStage& stage=Stages[SelectedStage];
		int w=Graphics->GetWidth(), h=Graphics->GetHeight(),
			tw=Text->GetWidth(), th=Text->GetHeight();

		// 選擇畫面:關卡名稱、說明和共通說明的顯示
		if (GameMode==GM_SELECT) {
			Text->Draw((w-tw)/2, (h-th)/2);
		} else
		
		// 遊戲畫面:關卡名稱的顯示
		{
			Text->Draw(stage.ViewType==VIEW_TOP?(w-h*3/4)/2:0, 0, 
				D3DCOLOR_ARGB(128, 255, 255, 255));
		}
	}

	// flip
	Graphics->EndScene();
	Graphics->Present();
}


//==============================================================
// 主程式-Main Program
INT WINAPI WinMain(HINSTANCE hinst, HINSTANCE, LPSTR, INT) {
	CShtGame* game=new CShtGame();
	game->Run();
	delete game;
	return 0;
}

