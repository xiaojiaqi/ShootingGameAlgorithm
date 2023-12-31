#include "Graphics.h"
#include <d3dx9.h>

#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 600


//==============================================================
// 建構式
CGraphics::CGraphics(HWND hwnd, bool zbuffer)
:	HWnd(hwnd), 
	WinModeWidth(DEFAULT_WIDTH), WinModeHeight(DEFAULT_HEIGHT),
	FullModeWidth(DEFAULT_WIDTH), FullModeHeight(DEFAULT_HEIGHT),
	FullMode(false), ZBuffer(zbuffer), 
	Device(NULL), Restored(false)
{
	// 解譯指令行選項
	for (int i=1; i<__argc; i++) {
		char* s=__argv[i];
		if (strcmp("-w", s)==0 && ++i<__argc) {
			WinModeWidth=FullModeWidth=atoi(__argv[i]);
		} else
		if (strcmp("-h", s)==0 && ++i<__argc) {
			WinModeHeight=FullModeHeight=atoi(__argv[i]);
		} else
		if (strcmp("-ww", s)==0 && ++i<__argc) {
			WinModeWidth=atoi(__argv[i]);
		} else
		if (strcmp("-wh", s)==0 && ++i<__argc) {
			WinModeHeight=atoi(__argv[i]);
		} else
		if (strcmp("-fw", s)==0 && ++i<__argc) {
			FullModeWidth=atoi(__argv[i]);
		} else
		if (strcmp("-fh", s)==0 && ++i<__argc) {
			FullModeHeight=atoi(__argv[i]);
		} else
		if (strcmp("-f", s)==0) {
			FullMode=true;
		}
	}

	// 大小與位置的調整：
	RECT dr, wr, cr;
	GetWindowRect(GetDesktopWindow(), &dr);
	GetWindowRect(HWnd, &wr);
	GetClientRect(HWnd, &cr);
	FrameWidth=(wr.right-wr.left)-(cr.right-cr.left);
	FrameHeight=(wr.bottom-wr.top)-(cr.bottom-cr.left);
	int w=FrameWidth+WinModeWidth, h=FrameHeight+WinModeHeight;
	SetWindowPos(HWnd, HWND_NOTOPMOST, 
		(dr.right-dr.left-w)/2, (dr.bottom-dr.top-h)/2, 
		w, h, SWP_SHOWWINDOW);
	WindowStyle=GetWindowLong(HWnd, GWL_STYLE);

	// 建立Direct3D事例
	if (!(D3D=Direct3DCreate9(D3D_SDK_VERSION))) return;

	// 建立裝置
	if (!RestoreDevice()) return;
}


//==============================================================
// 裝置的初始化
bool CGraphics::RestoreDevice() {

	// 裝置的參數設定
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.hDeviceWindow=HWnd;
	d3dpp.Windowed=!FullMode;
	d3dpp.BackBufferWidth=FullMode?FullModeWidth:WinModeWidth;
	d3dpp.BackBufferHeight=FullMode?FullModeHeight:WinModeHeight;
	d3dpp.SwapEffect=D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat=D3DFMT_A8R8G8B8;
	d3dpp.PresentationInterval=D3DPRESENT_INTERVAL_DEFAULT;

	// 建立Z緩衝區
	if (ZBuffer) {
		d3dpp.EnableAutoDepthStencil=TRUE;
		d3dpp.AutoDepthStencilFormat=D3DFMT_D16;
	}

	// 建立或重設裝置
	if (!Device) {
		if (FAILED(D3D->CreateDevice(
			D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, HWnd,
			D3DCREATE_HARDWARE_VERTEXPROCESSING,
			&d3dpp, &Device))
		) 
		if (FAILED(D3D->CreateDevice(
			D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, HWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &Device))
		)
		if (FAILED(D3D->CreateDevice(
			D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, HWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &Device))
		) return false;
	} else {
		if (FAILED(Device->Reset(&d3dpp))) return false;
	}

	Restored=true;
	return true;
}


//==============================================================
// 建構式
CGraphics::~CGraphics() {
	if (Device) Device->Release();
	if (D3D) D3D->Release();
}


//==============================================================
// 視窗與全螢幕模式的切換
void CGraphics::SetFullMode(bool full_mode) {
	if (FullMode!=full_mode) {
		FullMode=full_mode;
		RestoreDevice();
		if (full_mode) {

			// 全螢幕模式：
			// 移掉標題列與系統功能表
			SetWindowLong(HWnd, GWL_STYLE, WS_VISIBLE);

		} else {

			// 視窗模式：
			// 還原回原來的視窗大小及樣式
			SetWindowLong(HWnd, GWL_STYLE, WindowStyle);
			RECT dr;
			GetWindowRect(GetDesktopWindow(), &dr);
			int w=FrameWidth+WinModeWidth, h=FrameHeight+WinModeHeight;
			SetWindowPos(HWnd, HWND_NOTOPMOST, 
				(dr.right-dr.left-w)/2, (dr.bottom-dr.top-h)/2, 
				w, h, SWP_SHOWWINDOW);

		}
	}
}


//==============================================================
// 清除畫面（Back Buffer）
void CGraphics::Clear(D3DCOLOR color) {
	Device->Clear(0, NULL, 
		D3DCLEAR_TARGET | (ZBuffer?D3DCLEAR_ZBUFFER:0), 
		color, 1, 0 );
}


//==============================================================
// 畫面更新
void CGraphics::Present() {

	// 當裝置消失時重新建立
	switch (Device->TestCooperativeLevel()) {
		case D3DERR_DEVICELOST: 
			return;
		case D3DERR_DEVICENOTRESET:
			if (!RestoreDevice()) return;
			break;
	}

	// 畫面更新
	Device->Present(0, 0, 0, 0);
}


//==============================================================
// 打光的初始化
void CGraphics::SetLight(
	int id, D3DLIGHTTYPE type, 
	float x, float y, float z,
	float range
) {
	// 建立燈光
	D3DLIGHT9 light;
	D3DXVECTOR3 vec_lightdir(x, y, z);
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type=type;
	light.Diffuse.r=1.0f;
	light.Diffuse.g=1.0f;
	light.Diffuse.b=1.0f;
	D3DXVec3Normalize(
		(D3DXVECTOR3*)&light.Direction, &vec_lightdir);
	light.Position.x=x;
	light.Position.y=y;
	light.Position.z=z;
	light.Range=range;

	// 燈光的設定
	Device->SetLight(id, &light);
	Device->LightEnable(id, TRUE);
	Device->SetRenderState(D3DRS_LIGHTING, TRUE);
}


