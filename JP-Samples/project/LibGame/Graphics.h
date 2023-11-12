#ifndef GRAPHICSH
#define GRAPHICSH

#include <d3d9.h>


//==============================================================
// �O���t�B�b�N�X�`��@�\���Ǘ�����N���X
class CGraphics {
protected:

	// Direct3D�C���^�[�t�F�C�X�C�f�o�C�X�C���_�o�b�t�@
	LPDIRECT3D9 D3D;
	LPDIRECT3DDEVICE9 Device;

	// �E�B���h�E�n���h��
	HWND HWnd;
	
	// ���ƍ����i�E�B���h�E���[�h�C�S��ʃ��[�h�j
	int WinModeWidth, WinModeHeight;
	int FullModeWidth, FullModeHeight;
	
	// �E�B���h�E�g�̕��ƍ����C�E�B���h�E�X�^�C��
	int FrameWidth, FrameHeight;
	DWORD WindowStyle;

	// �t���X�N���[�����[�h�CZ�o�b�t�@�̎g�p
	bool FullMode, ZBuffer;

	// �f�o�C�X�̕���
	bool RestoreDevice();
	bool Restored;

public:

	// �R���X�g���N�^�C�f�X�g���N�^
	CGraphics(HWND hwnd, bool zbuffer);
	~CGraphics();

	// �V�[���`��̊J�n�C�I��
	bool BeginScene() { return SUCCEEDED(Device->BeginScene()); }
	void EndScene() { Device->EndScene(); }

	// ��ʏ����C��ʃt���b�v
	void Clear(D3DCOLOR color=D3DCOLOR_XRGB(0,0,0));
	void Present();

	// �f�o�C�X�̕���
	bool CheckRestored() {
		bool ret=Restored;
		Restored=false;
		return ret;
	}

	// ��ʂ̕��ƍ���
	int GetWidth() { return FullMode?FullModeWidth:WinModeWidth; }
	int GetHeight() { return FullMode?FullModeHeight:WinModeHeight; }

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 GetDevice() { return Device; }

	// �t���X�N���[�����[�h�i�ݒ�C���ݒl�C�g�O���j
	void SetFullMode(bool full_mode);
	bool IsFullMode() { return FullMode; }

	// ���C�g�̐ݒ�
	void SetLight(
		int id, D3DLIGHTTYPE type, 
		float x, float y, float z,
		float range=1000
	);
};


#endif



