#ifndef GRAPHICSH
#define GRAPHICSH

#include <d3d9.h>


//==============================================================
// Graphic�yø�P�޲z�����O
class CGraphics {
protected:

	// Direct3D�����B�˸m�M���I�w�İ�
	LPDIRECT3D9 D3D;
	LPDIRECT3DDEVICE9 Device;

	// �����N�X
	HWND HWnd;
	
	// �e�P��(�����B���ù��Ҧ�)
	int WinModeWidth, WinModeHeight;
	int FullModeWidth, FullModeHeight;
	
	// �����ج[���e�P���B�������˦�
	int FrameWidth, FrameHeight;
	DWORD WindowStyle;

	// ���ù��Ҧ��BZ�w�İϪ��ϥ�
	bool FullMode, ZBuffer;

	// �˸m���٭�
	bool RestoreDevice();
	bool Restored;

public:

	// �غc���B�Ѻc��
	CGraphics(HWND hwnd, bool zbuffer);
	~CGraphics();

	// �����yø���}�l�B����
	bool BeginScene() { return SUCCEEDED(Device->BeginScene()); }
	void EndScene() { Device->EndScene(); }

	// �e���M���B�e����½��
	void Clear(D3DCOLOR color=D3DCOLOR_XRGB(0,0,0));
	void Present();

	// �˸m���٭�
	bool CheckRestored() {
		bool ret=Restored;
		Restored=false;
		return ret;
	}

	// �e�����e�P��
	int GetWidth() { return FullMode?FullModeWidth:WinModeWidth; }
	int GetHeight() { return FullMode?FullModeHeight:WinModeHeight; }

	// ���o�˸m
	LPDIRECT3DDEVICE9 GetDevice() { return Device; }

	// ���ù��Ҧ�(�]�w, �{�b��, ���A)
	void SetFullMode(bool full_mode);
	bool IsFullMode() { return FullMode; }

	// �O�����]�w
	void SetLight(
		int id, D3DLIGHTTYPE type, 
		float x, float y, float z,
		float range=1000
	);
};


#endif



