#pragma warning(disable:4786)
#include "Game.h"
#include "Image.h"
#include <map>
using namespace std;

#define IDC_EXIT 0
#define IDC_TOGGLEFULLSCREEN 1
#define IDC_HELPURL 2


//==============================================================
// ファイル名からパスを取り出して返す
static string ExtractFilePath(string s) {
	int pos=s.rfind("\\");
	if (pos==string::npos) return "";
	return s.substr(0, pos+1);
}


//==============================================================
// HWNDとCGameインスタンスを関連づけるマップ
typedef map<HWND, CGame*, less<HWND> > THWndCGameMap;
static THWndCGameMap HWndCGameMap;


//==============================================================
// 空のメッセージハンドラ：
// グラフィックスなどの初期化前にはこれを実行する。
static LRESULT WINAPI DummyWndProc(
	HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam
) {
	return DefWindowProc( hwnd, msg, wparam, lparam );
}


//==============================================================
// メッセージハンドラ
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

		// 描画
		case WM_PAINT:
			Draw();
			break;

		// 各種のコマンド
		case WM_COMMAND:
			switch (LOWORD(wparam)) {

				// 終了
				case IDC_EXIT:
					DestroyWindow(HWnd);
					return 0;

				// Alt+Returnで画面モード切り替え
				case IDC_TOGGLEFULLSCREEN:
					Graphics->SetFullMode(!Graphics->IsFullMode());
					return 0;

				// ヘルプ
				case IDC_HELPURL:
					ShellExecute(HWnd, NULL, HelpURL.c_str(),
    					NULL, NULL, SW_SHOWNORMAL);					
					return 0;
			}
			break;

		// システムコマンド
		case WM_SYSCOMMAND:
			switch (wparam) {

				// 最大化時には画面モード切り替え
				case SC_MAXIMIZE:
					Graphics->SetFullMode(!Graphics->IsFullMode());
					return 0;					

				// スクリーンセーバとモニタ電源Offの防止
				case SC_SCREENSAVE:
				case SC_MONITORPOWER:
					return 0;
			}
			break;

		// 終了
		case WM_DESTROY:
			PostQuitMessage( 0 );
			return 0;
	}
	return DefWindowProc(HWnd, msg, wparam, lparam);
}


//==============================================================
// ＜CGame＞コンストラクタ
CGame::CGame(const char* app_name, bool zbuffer) {

	// アプリケーション名，実行ファイルのパス、ヘルプのＵＲＬ
	strcpy(AppName, app_name);
	ExePath=ExtractFilePath(__argv[0]);
	HelpURL="";

	// アイコンの読み込み
	HINSTANCE hinst=GetModuleHandle(NULL);
	HICON icon=(HICON)LoadImage(
		hinst, (ExePath+"game.ico").c_str(), 
		IMAGE_ICON, 0, 0, LR_LOADFROMFILE);

	// ウィンドウクラスの登録：
	// ここではダミーのメッセージハンドラを登録する
	WNDCLASSEX wc={
		sizeof(WNDCLASSEX), CS_CLASSDC, DummyWndProc, 0L, 0L,
		hinst, icon, LoadCursor(NULL, IDC_ARROW), NULL, NULL,
		app_name, NULL
	};
	RegisterClassEx(&wc);

	// アクセラレータキーの設定：
	// [ESC] : 終了
	// [Alt]+[Enter] : 画面モード切り替え
	// [F1] : ヘルプ
	ACCEL accel[]={
		{FVIRTKEY, VK_ESCAPE, IDC_EXIT},
		{FALT|FVIRTKEY, VK_RETURN, IDC_TOGGLEFULLSCREEN},
		{FVIRTKEY, VK_F1, IDC_HELPURL}
	};
	HAccel=CreateAcceleratorTable(
		accel, sizeof(accel)/sizeof(ACCEL));

	// ウィンドウの作成
	HWnd=CreateWindow(
		app_name, app_name,
		WS_CAPTION|WS_VISIBLE|WS_SYSMENU|WS_MINIMIZEBOX|WS_MAXIMIZEBOX,
		0, 0, 0, 0, GetDesktopWindow(), NULL, wc.hInstance, NULL);
	HWndCGameMap.insert(
		THWndCGameMap::value_type(HWnd, this));

	// グラフィックスの作成
	Graphics=new CGraphics(HWnd, true);
	if (!Graphics) {
		MessageBox(HWnd, 
			"このプログラムにはDirectX 9.0以上が必要です。\n"
			"DirectXの最新版、および最新のドライバが\n"
			"インストールされているかどうかご確認ください。\n"
			"また、起動時のオプションで解像度を変更してみてください。\n\n"
			"ウィンドウ時800x600、フルスクリーン1024x768の場合：\n"
			"-w 800 -h 600 -fw 1024 -fh 768",
			app_name,
			MB_OK);
		exit(1);
	}

	// イメージの初期化
	CImage::Init(Graphics->GetDevice());

	// 入力の初期化
	Input=new CInput(HWnd);
}


//==============================================================
// ＜CGame＞デストラクタ
CGame::~CGame() {
	delete Input;
	CImage::Uninit();
	delete Graphics;
}


//==============================================================
// ＜CGame＞ゲームの実行
void CGame::Run() {

	// ダミーのメッセージハンドラを，
	// 正式なメッセージハンドラに置き換える
	SetWindowLong(HWnd, GWL_WNDPROC, (long)::WndProc);

	// メッセージループ
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

	// 終了処理
	UnregisterClass(AppName, GetModuleHandle(NULL));
}

