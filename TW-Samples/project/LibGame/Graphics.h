#ifndef GRAPHICSH
#define GRAPHICSH

#include <d3d9.h>


//==============================================================
// Graphic描繪與管理的類別
class CGraphics {
protected:

	// Direct3D介面、裝置和頂點緩衝區
	LPDIRECT3D9 D3D;
	LPDIRECT3DDEVICE9 Device;

	// 視窗代碼
	HWND HWnd;
	
	// 寬與高(視窗、全螢幕模式)
	int WinModeWidth, WinModeHeight;
	int FullModeWidth, FullModeHeight;
	
	// 視窗框架的寬與高、視窗的樣式
	int FrameWidth, FrameHeight;
	DWORD WindowStyle;

	// 全螢幕模式、Z緩衝區的使用
	bool FullMode, ZBuffer;

	// 裝置的還原
	bool RestoreDevice();
	bool Restored;

public:

	// 建構式、解構式
	CGraphics(HWND hwnd, bool zbuffer);
	~CGraphics();

	// 場景描繪的開始、結束
	bool BeginScene() { return SUCCEEDED(Device->BeginScene()); }
	void EndScene() { Device->EndScene(); }

	// 畫面清除、畫面的翻轉
	void Clear(D3DCOLOR color=D3DCOLOR_XRGB(0,0,0));
	void Present();

	// 裝置的還原
	bool CheckRestored() {
		bool ret=Restored;
		Restored=false;
		return ret;
	}

	// 畫面的寬與高
	int GetWidth() { return FullMode?FullModeWidth:WinModeWidth; }
	int GetHeight() { return FullMode?FullModeHeight:WinModeHeight; }

	// 取得裝置
	LPDIRECT3DDEVICE9 GetDevice() { return Device; }

	// 全螢幕模式(設定, 現在值, 雙態)
	void SetFullMode(bool full_mode);
	bool IsFullMode() { return FullMode; }

	// 燈光的設定
	void SetLight(
		int id, D3DLIGHTTYPE type, 
		float x, float y, float z,
		float range=1000
	);
};


#endif



