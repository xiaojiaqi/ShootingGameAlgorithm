#ifndef CObject3DH
#define CObject3DH


#include <d3dx9.h>
#include <string>
#include "Hit.h"
using namespace std;


//==============================================================
// �P�w����������
typedef enum {
	HIT_ALL, HIT_CORE, NUM_HIT
} HIT_TYPE;


//==============================================================
// View������
typedef enum {
	VIEW_TOP, VIEW_SIDE
} VIEW_TYPE;


//==============================================================
// 3D���󪺪�������O
class CObject3D {
private:

	// Mesh
	ID3DXMesh* Mesh;

	// ���ƼơB����
	DWORD NumMaterials;
	D3DMATERIAL9* Materials;

	// �L��
	LPDIRECT3DTEXTURE9* Textures;

	// �����P�w
	CHit Hit[NUM_HIT];

	// ��ܼҫ�
	static VIEW_TYPE ViewType;

	// �˸m
	static LPDIRECT3DDEVICE9 Device;

	// �˸m���A���]�w
	static void SetDeviceState_Common();
	static void SetDeviceState_TopView();
	static void SetDeviceState_SideView();
	static float RotationRad;

	// ��������l��
	static void InitLight(
		D3DLIGHT9& light, D3DLIGHTTYPE type, 
		FLOAT x, FLOAT y, FLOAT z);

	// ���oBackBuffer���j�p
	static SIZE GetBackBufferSize();

	// �O���OTopView
	bool TopViewOnly;

public:

	// �غc���B�Ѻc��
	CObject3D();
	~CObject3D();

	// Ū���ɮ�
	CObject3D* LoadFromFile(string file);

	// �yø
	void Draw(float alpha, bool alpha_addition);
	void Draw(float x, float y, float z);
	void DrawTopView(float x, float y, 
		float sx, float sy, 
		float yaw, float pitch, float roll,
		float alpha, bool alpha_addition);
	void DrawTopView(float x, float y, float z,
		float sx, float sy, 
		float yaw, float pitch, float roll,
		float alpha, bool alpha_addition);
	void Draw(
		D3DXMATRIX& mat,		
		float x, float y, float z, 
		float sx, float sy, float sz,
		float rx, float ry, float rz,
		float alpha, bool alpha_addition);

	// �����P�w
	CObject3D* SetHit(HIT_TYPE type, const CHit& hit);
	CHit GetHit(HIT_TYPE type);

	void SetTopViewOnly(bool tv_only) { TopViewOnly=tv_only; }

	// ��l�ơB����
	static void Init(LPDIRECT3DDEVICE9 device);
	static void Uninit();

	// ��ܼҦ��B�˸m���A���]�w
	static void SetViewType(VIEW_TYPE view_type) { ViewType=view_type; }
	static void SetDeviceState();
	static void SetRotation(float angle);
};




#endif
