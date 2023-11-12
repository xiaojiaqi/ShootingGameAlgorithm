#ifndef CObject3DH
#define CObject3DH


#include <d3dx9.h>
#include <string>
#include "Hit.h"
using namespace std;


//==============================================================
// 当たり判定の種類
typedef enum {
	HIT_ALL, HIT_CORE, NUM_HIT
} HIT_TYPE;


//==============================================================
// ビューの種類
typedef enum {
	VIEW_TOP, VIEW_SIDE
} VIEW_TYPE;


//==============================================================
// 3Dオブジェクトの表示を行うクラス
class CObject3D {
private:

	// メッシュ
	ID3DXMesh* Mesh;

	// マテリアルの数，マテリアル
	DWORD NumMaterials;
	D3DMATERIAL9* Materials;

	// テクスチャ
	LPDIRECT3DTEXTURE9* Textures;

	// 当たり判定
	CHit Hit[NUM_HIT];

	// 表示モード
	static VIEW_TYPE ViewType;

	// デバイス
	static LPDIRECT3DDEVICE9 Device;

	// デバイス状態の設定
	static void SetDeviceState_Common();
	static void SetDeviceState_TopView();
	static void SetDeviceState_SideView();
	static float RotationRad;

	// ライトの初期化
	static void InitLight(
		D3DLIGHT9& light, D3DLIGHTTYPE type, 
		FLOAT x, FLOAT y, FLOAT z);

	// バックバッファのサイズを得る
	static SIZE GetBackBufferSize();

	// トップビューのみかどうか
	bool TopViewOnly;

public:

	// コンストラクタ，デストラクタ
	CObject3D();
	~CObject3D();

	// ファイルの読み込み
	CObject3D* LoadFromFile(string file);

	// 描画
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

	// 当たり判定
	CObject3D* SetHit(HIT_TYPE type, const CHit& hit);
	CHit GetHit(HIT_TYPE type);

	void SetTopViewOnly(bool tv_only) { TopViewOnly=tv_only; }

	// 初期化，終了
	static void Init(LPDIRECT3DDEVICE9 device);
	static void Uninit();

	// 表示モード，デバイス状態の設定
	static void SetViewType(VIEW_TYPE view_type) { ViewType=view_type; }
	static void SetDeviceState();
	static void SetRotation(float angle);
};




#endif
