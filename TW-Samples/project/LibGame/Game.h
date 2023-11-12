#ifndef GAMEH
#define GAMEH

#include "Graphics.h"
#include "Image.h"
#include "Input.h"
#include <string>
using namespace std;


// �C�����骺���O
class CGame {
protected:

	// Accelerator Key
	HACCEL HAccel;

	// �����N�X
	HWND HWnd;

	// Graphics
	CGraphics* Graphics;

	// ��J
	CInput* Input;

	// �ǰe������
	string ExePath;

	// ���ε{���W��
	char AppName[128];

	// �D�U������URL
	string HelpURL;

public:

	// �غc���B�Ѻc��
	CGame(const char* app_name, bool zbuffer);
	~CGame();

	// �T���B�z�`��
	LRESULT WINAPI WndProc(UINT msg, WPARAM wparam, LPARAM lparam);

	// �C��������
	void Run();

	// ���ʻP�yø�G
	// �b�l���O���мg
	virtual void Move() {}
	virtual void Draw() {}

};


#endif
