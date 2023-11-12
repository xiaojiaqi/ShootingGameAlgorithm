#pragma warning(disable:4786)
#include "Game.h"
#include "Image.h"
#include <map>
using namespace std;

#define IDC_EXIT 0
#define IDC_TOGGLEFULLSCREEN 1
#define IDC_HELPURL 2


//==============================================================
// 取出檔案名稱並傳回
static string ExtractFilePath(string s) {
	int pos=s.rfind("\\");
	if (pos==string::npos) return "";
	return s.substr(0, pos+1);
}


//==============================================================
// HWND與CGame事例關聯的對應
typedef map<HWND, CGame*, less<HWND> > THWndCGameMap;
static THWndCGameMap HWndCGameMap;


//==============================================================
// 空的訊息處理常式
// 圖形初始化之前執行這個
static LRESULT WINAPI DummyWndProc(
	HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam
) {
	return DefWindowProc( hwnd, msg, wparam, lparam );
}


//==============================================================
// 訊息處理常式
static LRESULT WINAPI WndProc(
	HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam
) {
	THWndCGameMap::iterator iter=HWndCGameMap.find(hwnd);
	if (iter==HWndCGameMap.end())
		return DefWindowProc( hwnd, msg, wparam, lparam );
	CGame* game=iter->second;
	return game->WndProc(msg, wparam, lparam);
}

LRESULT WINAPI CGame::WndProc(
	UINT msg, WPARAM wparam, LPARAM lparam
) {
	switch(msg) {

		// 描繪
		case WM_PAINT:
			Draw();
			break;

		// 各種指令
		case WM_COMMAND:
			switch (LOWORD(wparam)) {

				// 結束
				case IDC_EXIT:
					DestroyWindow(HWnd);
					return 0;

				// Alt+Return鍵畫面模式的切換
				case IDC_TOGGLEFULLSCREEN:
					Graphics->SetFullMode(!Graphics->IsFullMode());
					return 0;

				// 求助說明
				case IDC_HELPURL:
					ShellExecute(HWnd, NULL, HelpURL.c_str(),
    					NULL, NULL, SW_SHOWNORMAL);					
					return 0;
			}
			break;

		// 系統指令
		case WM_SYSCOMMAND:
			switch (wparam) {

				// 最大化時畫面模式的切換
				case SC_MAXIMIZE:
					Graphics->SetFullMode(!Graphics->IsFullMode());
					return 0;					

				// 防止螢幕保護程式和電源off
				case SC_SCREENSAVE:
				case SC_MONITORPOWER:
					return 0;
			}
			break;

		// 結束
		case WM_DESTROY:
			PostQuitMessage( 0 );
			return 0;
	}
	return DefWindowProc(HWnd, msg, wparam, lparam);
}


//==============================================================
// ＜CGame＞建構式
CGame::CGame(const char* app_name, bool zbuffer) {

	// 應用程式名稱、執行檔案傳遞、求助說明的URL
	strcpy(AppName, app_name);
	ExePath=ExtractFilePath(__argv[0]);
	HelpURL="";

	// 讀入icon
	HINSTANCE hinst=GetModuleHandle(NULL);
	HICON icon=(HICON)LoadImage(
		hinst, (ExePath+"game.ico").c_str(), 
		IMAGE_ICON, 0, 0, LR_LOADFROMFILE);

	// 登錄視窗類別
	// Dummy訊息處理常式在這裡登錄
	WNDCLASSEX wc={
		sizeof(WNDCLASSEX), CS_CLASSDC, DummyWndProc, 0L, 0L,
		hinst, icon, LoadCursor(NULL, IDC_ARROW), NULL, NULL,
		app_name, NULL
	};
	RegisterClassEx(&wc);

	// 輔助按鍵Accelerator key的設定
	// [ESC] :　結束
	// [Alt]+[Enter] : 畫面模式切換
	// [F1] : 求助說明
	ACCEL accel[]={
		{FVIRTKEY, VK_ESCAPE, IDC_EXIT},
		{FALT|FVIRTKEY, VK_RETURN, IDC_TOGGLEFULLSCREEN},
		{FVIRTKEY, VK_F1, IDC_HELPURL}
	};
	HAccel=CreateAcceleratorTable(
		accel, sizeof(accel)/sizeof(ACCEL));

	// 建立視窗
	HWnd=CreateWindow(
		app_name, app_name,
		WS_CAPTION|WS_VISIBLE|WS_SYSMENU|WS_MINIMIZEBOX|WS_MAXIMIZEBOX,
		0, 0, 0, 0, GetDesktopWindow(), NULL, wc.hInstance, NULL);
	HWndCGameMap.insert(
		THWndCGameMap::value_type(HWnd, this));

	// 建立圖像
	Graphics=new CGraphics(HWnd, true);
	if (!Graphics) {
		MessageBox(HWnd, 
			"本程式需要用到DirectX 9.0或最高的版本。\n"
			"請確認您的電腦中已安裝了DirectX最新版\n"
			"和DirectX最新驅動程式。\n"
			"請在啟動時變更螢幕的解析度。\n\n"
			"視窗畫面大小為：800x600，全螢幕時為1024x768：\n"
			"-w 800 -h 600 -fw 1024 -fh 768",
			app_name,
			MB_OK);
		exit(1);
	}

	// 影像的初始化
	CImage::Init(Graphics->GetDevice());

	// 輸入的初始化
	Input=new CInput(HWnd);
}


//==============================================================
// ＜CGame＞解構式
CGame::~CGame() {
	delete Input;
	CImage::Uninit();
	delete Graphics;
}


//==============================================================
// ＜CGame＞遊戲的執行
void CGame::Run() {

	// 虛擬的訊息處理常式
	// 正式訊息處理常式的調換
	SetWindowLong(HWnd, GWL_WNDPROC, (long)::WndProc);

	// 訊息處理常式
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message!=WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
			if (!TranslateAccelerator(HWnd, HAccel, &msg)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		} else {
			if (HWnd==GetForegroundWindow()) {
				Move();
				Draw();
			}
		}
	}

	// 結束處理
	UnregisterClass(AppName, GetModuleHandle(NULL));
}

