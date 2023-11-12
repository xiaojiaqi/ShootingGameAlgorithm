#ifndef GAMEH
#define GAMEH

#include "Graphics.h"
#include "Image.h"
#include "Input.h"
#include <string>
using namespace std;


// 遊戲本體的類別
class CGame {
protected:

	// Accelerator Key
	HACCEL HAccel;

	// 視窗代碼
	HWND HWnd;

	// Graphics
	CGraphics* Graphics;

	// 輸入
	CInput* Input;

	// 傳送執行檔
	string ExePath;

	// 應用程式名稱
	char AppName[128];

	// 求助說明的URL
	string HelpURL;

public:

	// 建構式、解構式
	CGame(const char* app_name, bool zbuffer);
	~CGame();

	// 訊息處理常式
	LRESULT WINAPI WndProc(UINT msg, WPARAM wparam, LPARAM lparam);

	// 遊戲的執行
	void Run();

	// 移動與描繪：
	// 在子類別中覆寫
	virtual void Move() {}
	virtual void Draw() {}

};


#endif
