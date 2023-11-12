#ifndef GRAPHICSH
#define GRAPHICSH

#include <d3d9.h>


//==============================================================
// グラフィックス描画機能を管理するクラス
class CGraphics {
protected:

	// Direct3Dインターフェイス，デバイス，頂点バッファ
	LPDIRECT3D9 D3D;
	LPDIRECT3DDEVICE9 Device;

	// ウィンドウハンドル
	HWND HWnd;
	
	// 幅と高さ（ウィンドウモード，全画面モード）
	int WinModeWidth, WinModeHeight;
	int FullModeWidth, FullModeHeight;
	
	// ウィンドウ枠の幅と高さ，ウィンドウスタイル
	int FrameWidth, FrameHeight;
	DWORD WindowStyle;

	// フルスクリーンモード，Zバッファの使用
	bool FullMode, ZBuffer;

	// デバイスの復旧
	bool RestoreDevice();
	bool Restored;

public:

	// コンストラクタ，デストラクタ
	CGraphics(HWND hwnd, bool zbuffer);
	~CGraphics();

	// シーン描画の開始，終了
	bool BeginScene() { return SUCCEEDED(Device->BeginScene()); }
	void EndScene() { Device->EndScene(); }

	// 画面消去，画面フリップ
	void Clear(D3DCOLOR color=D3DCOLOR_XRGB(0,0,0));
	void Present();

	// デバイスの復旧
	bool CheckRestored() {
		bool ret=Restored;
		Restored=false;
		return ret;
	}

	// 画面の幅と高さ
	int GetWidth() { return FullMode?FullModeWidth:WinModeWidth; }
	int GetHeight() { return FullMode?FullModeHeight:WinModeHeight; }

	// デバイスの取得
	LPDIRECT3DDEVICE9 GetDevice() { return Device; }

	// フルスクリーンモード（設定，現在値，トグル）
	void SetFullMode(bool full_mode);
	bool IsFullMode() { return FullMode; }

	// ライトの設定
	void SetLight(
		int id, D3DLIGHTTYPE type, 
		float x, float y, float z,
		float range=1000
	);
};


#endif



