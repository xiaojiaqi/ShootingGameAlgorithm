#ifndef IMAGEH
#define IMAGEH


#include <d3d9.h>
#include <string>
using namespace std;


//==============================================================
// 巨集
inline int ARGB(int a, int r, int g, int b) {
	return ((a&255)<<24 | (r&255)<<16 |
		(g&255)<<8 | (b&255));
}
inline DWORD ARGB_A(DWORD rgb) { return (rgb)>>24&255; }
inline DWORD ARGB_R(DWORD rgb) { return (rgb)>>16&255; }
inline DWORD ARGB_G(DWORD rgb) { return (rgb)>>8&255; }
inline DWORD ARGB_B(DWORD rgb) { return rgb&255; }


//==============================================================
// 頂點形式

// 自訂的頂點形式
struct CUSTOMVERTEX
{
	// 變換完的頂點
	FLOAT X, Y, Z, RHW;

	// 預設顏色
	D3DCOLOR Color;

	// 材質座標
	FLOAT TU, TV;
};

// FVF的自訂頂點形式
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)


//==============================================================
// 影像
class CImage {
protected:

	// Direct3D裝置，頂點緩衝區
	static LPDIRECT3DDEVICE9 Device;
	static LPDIRECT3DVERTEXBUFFER9 VertexBuffer;

	// 材質
	LPDIRECT3DTEXTURE9* Textures;

	// 影像的寬與高，材質數(X, Y)
	int Width, Height, XCount, YCount;

public:

	// 初始化，裝置狀態的設定，結束
	static void Init(LPDIRECT3DDEVICE9 device);
	static void SetDeviceState();
	static void Uninit();

	// 建構式、解構式
	CImage(int width, int height);
	~CImage();

	int GetWidth() { return Width; }
	int GetHeight() { return Height; }

	// 載入影像檔
	void LoadFromFile(string file_name);

	// 描繪(整體影像畫面左上角)
	// color透明色(color key)
	void Draw(D3DCOLOR color=0xffffffff) {
		Draw(0, 0, 0, 0, Width, Height, color);
	}

	// 描繪(整體影像的指定位置)
	void Draw(int dx, int dy, D3DCOLOR color=0xffffffff) {
		Draw(dx, dy, 0, 0, Width, Height, color);
	}

	// 描繪(影像指定部份的指定位置)
	void Draw(int dx, int dy, int sx, int sy, int w, int h, 
		D3DCOLOR color=0xffffffff);

	void Clear(D3DCOLOR color=D3DCOLOR_ARGB(0, 0, 0, 0));
};


//==============================================================
// 文字的對齊
typedef enum {
	ALIGN_CENTER, 
	ALIGN_LEFT, ALIGN_RIGHT,
	ALIGN_TOP, ALIGN_BOTTOM	
} ALIGN_TYPE;


//==============================================================
// 文字
class CText : public CImage {
protected:

	// 文字描繪用的表面
	LPDIRECT3DSURFACE9 TextSurface;

public:

	// 建構式、解構式
	CText(int width, int height);
	~CText();

	// 文字的描繪
	void DrawText(
		string text, int x, int y, 
		D3DCOLOR color, HFONT font,
		ALIGN_TYPE halign=ALIGN_LEFT, 
		ALIGN_TYPE valign=ALIGN_TOP,
		SIZE* psize=NULL
	);

};


#endif

