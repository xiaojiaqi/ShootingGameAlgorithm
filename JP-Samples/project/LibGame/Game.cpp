#pragma warning(disable:4786)
#include "Game.h"
#include "Image.h"
#include <map>
using namespace std;

#define IDC_EXIT 0
#define IDC_TOGGLEFULLSCREEN 1
#define IDC_HELPURL 2


//==============================================================
// �t�@�C��������p�X�����o���ĕԂ�
static string ExtractFilePath(string s) {
	int pos=s.rfind("\\");
	if (pos==string::npos) return "";
	return s.substr(0, pos+1);
}


//==============================================================
// HWND��CGame�C���X�^���X���֘A�Â���}�b�v
typedef map<HWND, CGame*, less<HWND> > THWndCGameMap;
static THWndCGameMap HWndCGameMap;


//==============================================================
// ��̃��b�Z�[�W�n���h���F
// �O���t�B�b�N�X�Ȃǂ̏������O�ɂ͂�������s����B
static LRESULT WINAPI DummyWndProc(
	HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam
) {
	return DefWindowProc( hwnd, msg, wparam, lparam );
}


//==============================================================
// ���b�Z�[�W�n���h��
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

		// �`��
		case WM_PAINT:
			Draw();
			break;

		// �e��̃R�}���h
		case WM_COMMAND:
			switch (LOWORD(wparam)) {

				// �I��
				case IDC_EXIT:
					DestroyWindow(HWnd);
					return 0;

				// Alt+Return�ŉ�ʃ��[�h�؂�ւ�
				case IDC_TOGGLEFULLSCREEN:
					Graphics->SetFullMode(!Graphics->IsFullMode());
					return 0;

				// �w���v
				case IDC_HELPURL:
					ShellExecute(HWnd, NULL, HelpURL.c_str(),
    					NULL, NULL, SW_SHOWNORMAL);					
					return 0;
			}
			break;

		// �V�X�e���R�}���h
		case WM_SYSCOMMAND:
			switch (wparam) {

				// �ő剻���ɂ͉�ʃ��[�h�؂�ւ�
				case SC_MAXIMIZE:
					Graphics->SetFullMode(!Graphics->IsFullMode());
					return 0;					

				// �X�N���[���Z�[�o�ƃ��j�^�d��Off�̖h�~
				case SC_SCREENSAVE:
				case SC_MONITORPOWER:
					return 0;
			}
			break;

		// �I��
		case WM_DESTROY:
			PostQuitMessage( 0 );
			return 0;
	}
	return DefWindowProc(HWnd, msg, wparam, lparam);
}


//==============================================================
// ��CGame���R���X�g���N�^
CGame::CGame(const char* app_name, bool zbuffer) {

	// �A�v���P�[�V�������C���s�t�@�C���̃p�X�A�w���v�̂t�q�k
	strcpy(AppName, app_name);
	ExePath=ExtractFilePath(__argv[0]);
	HelpURL="";

	// �A�C�R���̓ǂݍ���
	HINSTANCE hinst=GetModuleHandle(NULL);
	HICON icon=(HICON)LoadImage(
		hinst, (ExePath+"game.ico").c_str(), 
		IMAGE_ICON, 0, 0, LR_LOADFROMFILE);

	// �E�B���h�E�N���X�̓o�^�F
	// �����ł̓_�~�[�̃��b�Z�[�W�n���h����o�^����
	WNDCLASSEX wc={
		sizeof(WNDCLASSEX), CS_CLASSDC, DummyWndProc, 0L, 0L,
		hinst, icon, LoadCursor(NULL, IDC_ARROW), NULL, NULL,
		app_name, NULL
	};
	RegisterClassEx(&wc);

	// �A�N�Z�����[�^�L�[�̐ݒ�F
	// [ESC] : �I��
	// [Alt]+[Enter] : ��ʃ��[�h�؂�ւ�
	// [F1] : �w���v
	ACCEL accel[]={
		{FVIRTKEY, VK_ESCAPE, IDC_EXIT},
		{FALT|FVIRTKEY, VK_RETURN, IDC_TOGGLEFULLSCREEN},
		{FVIRTKEY, VK_F1, IDC_HELPURL}
	};
	HAccel=CreateAcceleratorTable(
		accel, sizeof(accel)/sizeof(ACCEL));

	// �E�B���h�E�̍쐬
	HWnd=CreateWindow(
		app_name, app_name,
		WS_CAPTION|WS_VISIBLE|WS_SYSMENU|WS_MINIMIZEBOX|WS_MAXIMIZEBOX,
		0, 0, 0, 0, GetDesktopWindow(), NULL, wc.hInstance, NULL);
	HWndCGameMap.insert(
		THWndCGameMap::value_type(HWnd, this));

	// �O���t�B�b�N�X�̍쐬
	Graphics=new CGraphics(HWnd, true);
	if (!Graphics) {
		MessageBox(HWnd, 
			"���̃v���O�����ɂ�DirectX 9.0�ȏオ�K�v�ł��B\n"
			"DirectX�̍ŐV�ŁA����эŐV�̃h���C�o��\n"
			"�C���X�g�[������Ă��邩�ǂ������m�F���������B\n"
			"�܂��A�N�����̃I�v�V�����ŉ𑜓x��ύX���Ă݂Ă��������B\n\n"
			"�E�B���h�E��800x600�A�t���X�N���[��1024x768�̏ꍇ�F\n"
			"-w 800 -h 600 -fw 1024 -fh 768",
			app_name,
			MB_OK);
		exit(1);
	}

	// �C���[�W�̏�����
	CImage::Init(Graphics->GetDevice());

	// ���͂̏�����
	Input=new CInput(HWnd);
}


//==============================================================
// ��CGame���f�X�g���N�^
CGame::~CGame() {
	delete Input;
	CImage::Uninit();
	delete Graphics;
}


//==============================================================
// ��CGame���Q�[���̎��s
void CGame::Run() {

	// �_�~�[�̃��b�Z�[�W�n���h�����C
	// �����ȃ��b�Z�[�W�n���h���ɒu��������
	SetWindowLong(HWnd, GWL_WNDPROC, (long)::WndProc);

	// ���b�Z�[�W���[�v
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

	// �I������
	UnregisterClass(AppName, GetModuleHandle(NULL));
}

