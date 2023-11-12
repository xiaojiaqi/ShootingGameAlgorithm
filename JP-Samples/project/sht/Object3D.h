#ifndef CObject3DH
#define CObject3DH


#include <d3dx9.h>
#include <string>
#include "Hit.h"
using namespace std;


//==============================================================
// �����蔻��̎��
typedef enum {
	HIT_ALL, HIT_CORE, NUM_HIT
} HIT_TYPE;


//==============================================================
// �r���[�̎��
typedef enum {
	VIEW_TOP, VIEW_SIDE
} VIEW_TYPE;


//==============================================================
// 3D�I�u�W�F�N�g�̕\�����s���N���X
class CObject3D {
private:

	// ���b�V��
	ID3DXMesh* Mesh;

	// �}�e���A���̐��C�}�e���A��
	DWORD NumMaterials;
	D3DMATERIAL9* Materials;

	// �e�N�X�`��
	LPDIRECT3DTEXTURE9* Textures;

	// �����蔻��
	CHit Hit[NUM_HIT];

	// �\�����[�h
	static VIEW_TYPE ViewType;

	// �f�o�C�X
	static LPDIRECT3DDEVICE9 Device;

	// �f�o�C�X��Ԃ̐ݒ�
	static void SetDeviceState_Common();
	static void SetDeviceState_TopView();
	static void SetDeviceState_SideView();
	static float RotationRad;

	// ���C�g�̏�����
	static void InitLight(
		D3DLIGHT9& light, D3DLIGHTTYPE type, 
		FLOAT x, FLOAT y, FLOAT z);

	// �o�b�N�o�b�t�@�̃T�C�Y�𓾂�
	static SIZE GetBackBufferSize();

	// �g�b�v�r���[�݂̂��ǂ���
	bool TopViewOnly;

public:

	// �R���X�g���N�^�C�f�X�g���N�^
	CObject3D();
	~CObject3D();

	// �t�@�C���̓ǂݍ���
	CObject3D* LoadFromFile(string file);

	// �`��
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

	// �����蔻��
	CObject3D* SetHit(HIT_TYPE type, const CHit& hit);
	CHit GetHit(HIT_TYPE type);

	void SetTopViewOnly(bool tv_only) { TopViewOnly=tv_only; }

	// �������C�I��
	static void Init(LPDIRECT3DDEVICE9 device);
	static void Uninit();

	// �\�����[�h�C�f�o�C�X��Ԃ̐ݒ�
	static void SetViewType(VIEW_TYPE view_type) { ViewType=view_type; }
	static void SetDeviceState();
	static void SetRotation(float angle);
};




#endif
