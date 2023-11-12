#ifndef GAMEH
#define GAMEH

#include "Graphics.h"
#include "Image.h"
#include "Input.h"
#include <string>
using namespace std;


// ゲーム本体のクラス
class CGame {
protected:

	// アクセラレータキー
	HACCEL HAccel;

	// ウィンドウハンドル
	HWND HWnd;

	// グラフィックス
	CGraphics* Graphics;

	// 入力
	CInput* Input;

	// 実行ファイルのパス
	string ExePath;

	// アプリケーション名
	char AppName[128];

	// ヘルプのURL
	string HelpURL;

public:

	// コンストラクタ，デストラクタ
	CGame(const char* app_name, bool zbuffer);
	~CGame();

	// メッセージハンドラ
	LRESULT WINAPI WndProc(UINT msg, WPARAM wparam, LPARAM lparam);

	// ゲームの実行
	void Run();

	// 移動と描画：
	// サブクラスでオーバーライドする
	virtual void Move() {}
	virtual void Draw() {}

};


#endif
