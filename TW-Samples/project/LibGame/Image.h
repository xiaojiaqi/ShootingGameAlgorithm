#ifndef IMAGEH
#define IMAGEH


#include <d3d9.h>
#include <string>
using namespace std;


//==============================================================
// ����
inline int ARGB(int a, int r, int g, int b) {
	return ((a&255)<<24 | (r&255)<<16 |
		(g&255)<<8 | (b&255));
}
inline DWORD ARGB_A(DWORD rgb) { return (rgb)>>24&255; }
inline DWORD ARGB_R(DWORD rgb) { return (rgb)>>16&255; }
inline DWORD ARGB_G(DWORD rgb) { return (rgb)>>8&255; }
inline DWORD ARGB_B(DWORD rgb) { return rgb&255; }


//==============================================================
// ���I�Φ�

// �ۭq�����I�Φ�
struct CUSTOMVERTEX
{
	// �ܴ��������I
	FLOAT X, Y, Z, RHW;

	// �w�]�C��
	D3DCOLOR Color;

	// ����y��
	FLOAT TU, TV;
};

// FVF���ۭq���I�Φ�
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)


//==============================================================
// �v��
class CImage {
protected:

	// Direct3D�˸m�A���I�w�İ�
	static LPDIRECT3DDEVICE9 Device;
	static LPDIRECT3DVERTEXBUFFER9 VertexBuffer;

	// ����
	LPDIRECT3DTEXTURE9* Textures;

	// �v�����e�P���A�����(X, Y)
	int Width, Height, XCount, YCount;

public:

	// ��l�ơA�˸m���A���]�w�A����
	static void Init(LPDIRECT3DDEVICE9 device);
	static void SetDeviceState();
	static void Uninit();

	// �غc���B�Ѻc��
	CImage(int width, int height);
	~CImage();

	int GetWidth() { return Width; }
	int GetHeight() { return Height; }

	// ���J�v����
	void LoadFromFile(string file_name);

	// �yø(����v���e�����W��)
	// color�z����(color key)
	void Draw(D3DCOLOR color=0xffffffff) {
		Draw(0, 0, 0, 0, Width, Height, color);
	}

	// �yø(����v�������w��m)
	void Draw(int dx, int dy, D3DCOLOR color=0xffffffff) {
		Draw(dx, dy, 0, 0, Width, Height, color);
	}

	// �yø(�v�����w���������w��m)
	void Draw(int dx, int dy, int sx, int sy, int w, int h, 
		D3DCOLOR color=0xffffffff);

	void Clear(D3DCOLOR color=D3DCOLOR_ARGB(0, 0, 0, 0));
};


//==============================================================
// ��r�����
typedef enum {
	ALIGN_CENTER, 
	ALIGN_LEFT, ALIGN_RIGHT,
	ALIGN_TOP, ALIGN_BOTTOM	
} ALIGN_TYPE;


//==============================================================
// ��r
class CText : public CImage {
protected:

	// ��r�yø�Ϊ���
	LPDIRECT3DSURFACE9 TextSurface;

public:

	// �غc���B�Ѻc��
	CText(int width, int height);
	~CText();

	// ��r���yø
	void DrawText(
		string text, int x, int y, 
		D3DCOLOR color, HFONT font,
		ALIGN_TYPE halign=ALIGN_LEFT, 
		ALIGN_TYPE valign=ALIGN_TOP,
		SIZE* psize=NULL
	);

};


#endif

