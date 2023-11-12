#ifndef CObject3DH
#define CObject3DH


#include <d3dx9.h>
#include <string>
#include "Hit.h"
using namespace std;


//==============================================================
// 判定擊中的種類
typedef enum {
	HIT_ALL, HIT_CORE, NUM_HIT
} HIT_TYPE;


//==============================================================
// View的種類
typedef enum {
	VIEW_TOP, VIEW_SIDE
} VIEW_TYPE;


//==============================================================
// 3D物件的的顯示類別
class CObject3D {
private:

	// Mesh
	ID3DXMesh* Mesh;

	// 材料數、材料
	DWORD NumMaterials;
	D3DMATERIAL9* Materials;

	// 林質
	LPDIRECT3DTEXTURE9* Textures;

	// 擊中判定
	CHit Hit[NUM_HIT];

	// 顯示模型
	static VIEW_TYPE ViewType;

	// 裝置
	static LPDIRECT3DDEVICE9 Device;

	// 裝置狀態的設定
	static void SetDeviceState_Common();
	static void SetDeviceState_TopView();
	static void SetDeviceState_SideView();
	static float RotationRad;

	// 打光的初始化
	static void InitLight(
		D3DLIGHT9& light, D3DLIGHTTYPE type, 
		FLOAT x, FLOAT y, FLOAT z);

	// 取得BackBuffer的大小
	static SIZE GetBackBufferSize();

	// 是不是TopView
	bool TopViewOnly;

public:

	// 建構式、解構式
	CObject3D();
	~CObject3D();

	// 讀取檔案
	CObject3D* LoadFromFile(string file);

	// 描繪
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

	// 擊中判定
	CObject3D* SetHit(HIT_TYPE type, const CHit& hit);
	CHit GetHit(HIT_TYPE type);

	void SetTopViewOnly(bool tv_only) { TopViewOnly=tv_only; }

	// 初始化、結束
	static void Init(LPDIRECT3DDEVICE9 device);
	static void Uninit();

	// 顯示模式、裝置狀態的設定
	static void SetViewType(VIEW_TYPE view_type) { ViewType=view_type; }
	static void SetDeviceState();
	static void SetRotation(float angle);
};




#endif
