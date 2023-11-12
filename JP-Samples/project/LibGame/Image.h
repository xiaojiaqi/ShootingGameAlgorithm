#ifndef IMAGEH
#define IMAGEH


#include <d3d9.h>
#include <string>
using namespace std;


//==============================================================
// �}�N��
inline int ARGB(int a, int r, int g, int b) {
	return ((a&255)<<24 | (r&255)<<16 |
		(g&255)<<8 | (b&255));
}
inline DWORD ARGB_A(DWORD rgb) { return (rgb)>>24&255; }
inline DWORD ARGB_R(DWORD rgb) { return (rgb)>>16&255; }
inline DWORD ARGB_G(DWORD rgb) { return (rgb)>>8&255; }
inline DWORD ARGB_B(DWORD rgb) { return rgb&255; }


//==============================================================
// ���_�`��

// �Ǝ��̒��_�`��
struct CUSTOMVERTEX
{
	// �ϊ��ςݒ��_
	FLOAT X, Y, Z, RHW;

	// �f�B�t���[�Y�F
	D3DCOLOR Color;

	// �e�N�X�`�����W
	FLOAT TU, TV;
};

// �Ǝ��̒��_�`����\��FVF
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)


//==============================================================
// �摜
class CImage {
protected:

	// Direct3D�f�o�C�X�C���_�o�b�t�@
	static LPDIRECT3DDEVICE9 Device;
	static LPDIRECT3DVERTEXBUFFER9 VertexBuffer;

	// �e�N�X�`��
	LPDIRECT3DTEXTURE9* Textures;

	// �摜�̕��C�����C�e�N�X�`�������iX�����CY�����j
	int Width, Height, XCount, YCount;

public:

	// �������C�f�o�C�X��Ԃ̐ݒ�C�I��
	static void Init(LPDIRECT3DDEVICE9 device);
	static void SetDeviceState();
	static void Uninit();

	// �R���X�g���N�^�C�f�X�g���N�^
	CImage(int width, int height);
	~CImage();

	int GetWidth() { return Width; }
	int GetHeight() { return Height; }

	// �摜�t�@�C���̃��[�h
	void LoadFromFile(string file_name);

	// �`��i��ʍ���ɉ摜�S�́j�F
	// color�͓����F�i�J���[�L�[�j
	void Draw(D3DCOLOR color=0xffffffff) {
		Draw(0, 0, 0, 0, Width, Height, color);
	}

	// �`��i�w��ʒu�ɉ摜�S�́j
	void Draw(int dx, int dy, D3DCOLOR color=0xffffffff) {
		Draw(dx, dy, 0, 0, Width, Height, color);
	}

	// �`��i�w��ʒu�ɉ摜���̎w�蕔���j
	void Draw(int dx, int dy, int sx, int sy, int w, int h, 
		D3DCOLOR color=0xffffffff);

	void Clear(D3DCOLOR color=D3DCOLOR_ARGB(0, 0, 0, 0));
};


//==============================================================
// �e�L�X�g�̐���
typedef enum {
	ALIGN_CENTER, 
	ALIGN_LEFT, ALIGN_RIGHT,
	ALIGN_TOP, ALIGN_BOTTOM	
} ALIGN_TYPE;


//==============================================================
// �e�L�X�g
class CText : public CImage {
protected:

	// �e�L�X�g�`��p�T�[�t�F�C�X
	LPDIRECT3DSURFACE9 TextSurface;

public:

	// �R���X�g���N�^�C�f�X�g���N�^
	CText(int width, int height);
	~CText();

	// �e�L�X�g�̕`��
	void DrawText(
		string text, int x, int y, 
		D3DCOLOR color, HFONT font,
		ALIGN_TYPE halign=ALIGN_LEFT, 
		ALIGN_TYPE valign=ALIGN_TOP,
		SIZE* psize=NULL
	);

};


#endif

