#ifndef GAMEH
#define GAMEH

#include "Graphics.h"
#include "Image.h"
#include "Input.h"
#include <string>
using namespace std;


// �Q�[���{�̂̃N���X
class CGame {
protected:

	// �A�N�Z�����[�^�L�[
	HACCEL HAccel;

	// �E�B���h�E�n���h��
	HWND HWnd;

	// �O���t�B�b�N�X
	CGraphics* Graphics;

	// ����
	CInput* Input;

	// ���s�t�@�C���̃p�X
	string ExePath;

	// �A�v���P�[�V������
	char AppName[128];

	// �w���v��URL
	string HelpURL;

public:

	// �R���X�g���N�^�C�f�X�g���N�^
	CGame(const char* app_name, bool zbuffer);
	~CGame();

	// ���b�Z�[�W�n���h��
	LRESULT WINAPI WndProc(UINT msg, WPARAM wparam, LPARAM lparam);

	// �Q�[���̎��s
	void Run();

	// �ړ��ƕ`��F
	// �T�u�N���X�ŃI�[�o�[���C�h����
	virtual void Move() {}
	virtual void Draw() {}

};


#endif
