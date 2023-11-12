#pragma warning(disable:4786)
#include "Game.h"
#include "Image.h"
#include <map>
using namespace std;

#define IDC_EXIT 0
#define IDC_TOGGLEFULLSCREEN 1
#define IDC_HELPURL 2


//==============================================================
// ���X�ɮצW�٨öǦ^
static string ExtractFilePath(string s) {
	int pos=s.rfind("\\");
	if (pos==string::npos) return "";
	return s.substr(0, pos+1);
}


//==============================================================
// HWND�PCGame�ƨ����p������
typedef map<HWND, CGame*, less<HWND> > THWndCGameMap;
static THWndCGameMap HWndCGameMap;


//==============================================================
// �Ū��T���B�z�`��
// �ϧΪ�l�Ƥ��e����o��
static LRESULT WINAPI DummyWndProc(
	HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam
) {
	return DefWindowProc( hwnd, msg, wparam, lparam );
}


//==============================================================
// �T���B�z�`��
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

		// �yø
		case WM_PAINT:
			Draw();
			break;

		// �U�ث��O
		case WM_COMMAND:
			switch (LOWORD(wparam)) {

				// ����
				case IDC_EXIT:
					DestroyWindow(HWnd);
					return 0;

				// Alt+Return��e���Ҧ�������
				case IDC_TOGGLEFULLSCREEN:
					Graphics->SetFullMode(!Graphics->IsFullMode());
					return 0;

				// �D�U����
				case IDC_HELPURL:
					ShellExecute(HWnd, NULL, HelpURL.c_str(),
    					NULL, NULL, SW_SHOWNORMAL);					
					return 0;
			}
			break;

		// �t�Ϋ��O
		case WM_SYSCOMMAND:
			switch (wparam) {

				// �̤j�Ʈɵe���Ҧ�������
				case SC_MAXIMIZE:
					Graphics->SetFullMode(!Graphics->IsFullMode());
					return 0;					

				// ����ù��O�@�{���M�q��off
				case SC_SCREENSAVE:
				case SC_MONITORPOWER:
					return 0;
			}
			break;

		// ����
		case WM_DESTROY:
			PostQuitMessage( 0 );
			return 0;
	}
	return DefWindowProc(HWnd, msg, wparam, lparam);
}


//==============================================================
// ��CGame�֫غc��
CGame::CGame(const char* app_name, bool zbuffer) {

	// ���ε{���W�١B�����ɮ׶ǻ��B�D�U������URL
	strcpy(AppName, app_name);
	ExePath=ExtractFilePath(__argv[0]);
	HelpURL="";

	// Ū�Jicon
	HINSTANCE hinst=GetModuleHandle(NULL);
	HICON icon=(HICON)LoadImage(
		hinst, (ExePath+"game.ico").c_str(), 
		IMAGE_ICON, 0, 0, LR_LOADFROMFILE);

	// �n���������O
	// Dummy�T���B�z�`���b�o�̵n��
	WNDCLASSEX wc={
		sizeof(WNDCLASSEX), CS_CLASSDC, DummyWndProc, 0L, 0L,
		hinst, icon, LoadCursor(NULL, IDC_ARROW), NULL, NULL,
		app_name, NULL
	};
	RegisterClassEx(&wc);

	// ���U����Accelerator key���]�w
	// [ESC] :�@����
	// [Alt]+[Enter] : �e���Ҧ�����
	// [F1] : �D�U����
	ACCEL accel[]={
		{FVIRTKEY, VK_ESCAPE, IDC_EXIT},
		{FALT|FVIRTKEY, VK_RETURN, IDC_TOGGLEFULLSCREEN},
		{FVIRTKEY, VK_F1, IDC_HELPURL}
	};
	HAccel=CreateAcceleratorTable(
		accel, sizeof(accel)/sizeof(ACCEL));

	// �إߵ���
	HWnd=CreateWindow(
		app_name, app_name,
		WS_CAPTION|WS_VISIBLE|WS_SYSMENU|WS_MINIMIZEBOX|WS_MAXIMIZEBOX,
		0, 0, 0, 0, GetDesktopWindow(), NULL, wc.hInstance, NULL);
	HWndCGameMap.insert(
		THWndCGameMap::value_type(HWnd, this));

	// �إ߹Ϲ�
	Graphics=new CGraphics(HWnd, true);
	if (!Graphics) {
		MessageBox(HWnd, 
			"���{���ݭn�Ψ�DirectX 9.0�γ̰��������C\n"
			"�нT�{�z���q�����w�w�ˤFDirectX�̷s��\n"
			"�MDirectX�̷s�X�ʵ{���C\n"
			"�Цb�Ұʮ��ܧ�ù����ѪR�סC\n\n"
			"�����e���j�p���G800x600�A���ù��ɬ�1024x768�G\n"
			"-w 800 -h 600 -fw 1024 -fh 768",
			app_name,
			MB_OK);
		exit(1);
	}

	// �v������l��
	CImage::Init(Graphics->GetDevice());

	// ��J����l��
	Input=new CInput(HWnd);
}


//==============================================================
// ��CGame�ָѺc��
CGame::~CGame() {
	delete Input;
	CImage::Uninit();
	delete Graphics;
}


//==============================================================
// ��CGame�ֹC��������
void CGame::Run() {

	// �������T���B�z�`��
	// �����T���B�z�`�����մ�
	SetWindowLong(HWnd, GWL_WNDPROC, (long)::WndProc);

	// �T���B�z�`��
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

	// �����B�z
	UnregisterClass(AppName, GetModuleHandle(NULL));
}

