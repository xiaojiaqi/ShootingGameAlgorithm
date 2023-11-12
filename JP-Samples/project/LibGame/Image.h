#ifndef IMAGEH
#define IMAGEH


#include <d3d9.h>
#include <string>
using namespace std;


//==============================================================
// マクロ
inline int ARGB(int a, int r, int g, int b) {
	return ((a&255)<<24 | (r&255)<<16 |
		(g&255)<<8 | (b&255));
}
inline DWORD ARGB_A(DWORD rgb) { return (rgb)>>24&255; }
inline DWORD ARGB_R(DWORD rgb) { return (rgb)>>16&255; }
inline DWORD ARGB_G(DWORD rgb) { return (rgb)>>8&255; }
inline DWORD ARGB_B(DWORD rgb) { return rgb&255; }


//==============================================================
// 頂点形式

// 独自の頂点形式
struct CUSTOMVERTEX
{
	// 変換済み頂点
	FLOAT X, Y, Z, RHW;

	// ディフューズ色
	D3DCOLOR Color;

	// テクスチャ座標
	FLOAT TU, TV;
};

// 独自の頂点形式を表すFVF
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)


//==============================================================
// 画像
class CImage {
protected:

	// Direct3Dデバイス，頂点バッファ
	static LPDIRECT3DDEVICE9 Device;
	static LPDIRECT3DVERTEXBUFFER9 VertexBuffer;

	// テクスチャ
	LPDIRECT3DTEXTURE9* Textures;

	// 画像の幅，高さ，テクスチャ枚数（X方向，Y方向）
	int Width, Height, XCount, YCount;

public:

	// 初期化，デバイス状態の設定，終了
	static void Init(LPDIRECT3DDEVICE9 device);
	static void SetDeviceState();
	static void Uninit();

	// コンストラクタ，デストラクタ
	CImage(int width, int height);
	~CImage();

	int GetWidth() { return Width; }
	int GetHeight() { return Height; }

	// 画像ファイルのロード
	void LoadFromFile(string file_name);

	// 描画（画面左上に画像全体）：
	// colorは透明色（カラーキー）
	void Draw(D3DCOLOR color=0xffffffff) {
		Draw(0, 0, 0, 0, Width, Height, color);
	}

	// 描画（指定位置に画像全体）
	void Draw(int dx, int dy, D3DCOLOR color=0xffffffff) {
		Draw(dx, dy, 0, 0, Width, Height, color);
	}

	// 描画（指定位置に画像内の指定部分）
	void Draw(int dx, int dy, int sx, int sy, int w, int h, 
		D3DCOLOR color=0xffffffff);

	void Clear(D3DCOLOR color=D3DCOLOR_ARGB(0, 0, 0, 0));
};


//==============================================================
// テキストの整列
typedef enum {
	ALIGN_CENTER, 
	ALIGN_LEFT, ALIGN_RIGHT,
	ALIGN_TOP, ALIGN_BOTTOM	
} ALIGN_TYPE;


//==============================================================
// テキスト
class CText : public CImage {
protected:

	// テキスト描画用サーフェイス
	LPDIRECT3DSURFACE9 TextSurface;

public:

	// コンストラクタ，デストラクタ
	CText(int width, int height);
	~CText();

	// テキストの描画
	void DrawText(
		string text, int x, int y, 
		D3DCOLOR color, HFONT font,
		ALIGN_TYPE halign=ALIGN_LEFT, 
		ALIGN_TYPE valign=ALIGN_TOP,
		SIZE* psize=NULL
	);

};


#endif

