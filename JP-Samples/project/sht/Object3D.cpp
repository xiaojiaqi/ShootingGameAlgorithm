#include "Object3D.h"


typedef struct {
	float x, y, z, r, g, b, a;
} XYZRGBA;


float CObject3D::RotationRad=0;
void CObject3D::SetRotation(float angle) {
	RotationRad=D3DX_PI*2*angle;
}


//==============================================================
// ��CObject3D���\�����[�h
VIEW_TYPE CObject3D::ViewType=VIEW_TOP;


//==============================================================
// ��CObject3D���f�o�C�X
LPDIRECT3DDEVICE9 CObject3D::Device=NULL;


//==============================================================
// ��CObject3D��������
void CObject3D::Init(LPDIRECT3DDEVICE9 device) {
	Device=device;
}


//==============================================================
// ��CObject3D���I��
void CObject3D::Uninit() {
}


//==============================================================
// ��CObject3D�������蔻��̐ݒ�
CObject3D* CObject3D::SetHit(
	HIT_TYPE type, const CHit& hit
) {
	if (type<0 || sizeof(HIT_TYPE)<=type) return this;
	Hit[type]=hit;
	return this;
}


//==============================================================
// ��CObject3D�������蔻��̎擾
CHit CObject3D::GetHit(HIT_TYPE type) {
	if (type<0 || sizeof(HIT_TYPE)<=type) 
		return CHit(0, 0, 0, 0);
	return Hit[type];
}


//==============================================================
// ��CObject3D���R���X�g���N�^
CObject3D::CObject3D()
:	Mesh(NULL), NumMaterials(0), 
	Materials(NULL), Textures(NULL),
	TopViewOnly(true)
{}


//==============================================================
// ��CObject3D���f�X�g���N�^
CObject3D::~CObject3D() {
	if (Textures) {
		for (DWORD i=0; i<NumMaterials; i++) {
			if (Textures[i]) Textures[i]->Release();
		}
		delete[] Textures;
	}
	if (Materials) delete[] Materials;
	if (Mesh) Mesh->Release();
}


//==============================================================
// ��CObject3D���t�@�C���̃��[�h
CObject3D* CObject3D::LoadFromFile(string file) {

	// �g���q�������ꍇ�ɂ�.x�ɂ���
	//	if (!EndsWith(file, ".x")) file+=".x";
	
	// �t�@�C����ǂݍ���
	LPD3DXBUFFER buf_materials=NULL;
	if (FAILED(D3DXLoadMeshFromX(
			file.c_str(), D3DXMESH_SYSTEMMEM, 
			Device, NULL, &buf_materials, NULL, &NumMaterials,
			&Mesh))
	) {
		return this;
	}
	
	// �}�e���A�������o��
	D3DXMATERIAL* materials=
		(D3DXMATERIAL*)buf_materials->GetBufferPointer();
	Materials=new D3DMATERIAL9[NumMaterials];
	Textures=new LPDIRECT3DTEXTURE9[NumMaterials];

	for (DWORD i=0; i<NumMaterials; i++ ) {

		// �}�e���A�����R�s�[����
		Materials[i]=materials[i].MatD3D;

		// �A���r�G���g�F��ݒ肷��
		Materials[i].Ambient=Materials[i].Diffuse;

		// �e�N�X�`����ǂݍ���
		Textures[i]=NULL;
		char* texture_file=materials[i].pTextureFilename;
		if (texture_file && lstrlen(texture_file)>0) {
			if (FAILED(D3DXCreateTextureFromFile(
				Device, texture_file, &Textures[i]))) continue;
		}
	}
	
	// ��ЂÂ�
	buf_materials->Release();
	return this;
}


//==============================================================
// ��CObject3D���`��i���W���w��j
void CObject3D::Draw(float x, float y, float z) {
	D3DXMATRIX mat;
	D3DXMatrixTranslation(&mat, x, y, z);
	Device->SetTransform(D3DTS_WORLD, &mat);
	Draw(1, false);
}


//==============================================================
// ��CObject3D�����C�g�̏�����
void CObject3D::InitLight(
	D3DLIGHT9& light, D3DLIGHTTYPE type, 
	FLOAT x, FLOAT y, FLOAT z
) {
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
	light.Range=1000.0f;
}


//==============================================================
// ��CObject3D���f�o�C�X��Ԃ̐ݒ�i���ʁj
void CObject3D::SetDeviceState_Common() {
	RotationRad=0;

	// �����_�����O�̐ݒ�
	Device->SetRenderState(D3DRS_DITHERENABLE, FALSE);
	Device->SetRenderState(D3DRS_SPECULARENABLE, FALSE);
	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	Device->SetRenderState(D3DRS_LIGHTING, TRUE);
	Device->SetRenderState(D3DRS_ZENABLE, TRUE);
	Device->SetRenderState(D3DRS_AMBIENT, 0x006F6F6F);

	// �e�N�X�`���������@�̐ݒ�F
	Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	Device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	Device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	
	// ���`��Ԃ��g�����߂̐ݒ�
	Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	// ���[���h�}�g���N�X
	D3DXMATRIX mat_world;
	D3DXMatrixIdentity(&mat_world);
	Device->SetTransform(D3DTS_WORLD, &mat_world);
}


//==============================================================
// ��CObject3D���o�b�N�o�b�t�@�̃T�C�Y�𓾂�
SIZE CObject3D::GetBackBufferSize() {
	LPDIRECT3DSURFACE9 back_buffer;
	D3DSURFACE_DESC desc;
	SIZE size={0, 0};
	if (SUCCEEDED(Device->GetBackBuffer(
			0, 0, D3DBACKBUFFER_TYPE_MONO, &back_buffer))
	) {
		if (SUCCEEDED(back_buffer->GetDesc(&desc))) {
			size.cx=desc.Width; size.cy=desc.Height;	
		}
		back_buffer->Release();
	}
	return size;
}


//==============================================================
// ��CObject3D���f�o�C�X��Ԃ̐ݒ�i�g�b�v�r���[�j
void CObject3D::SetDeviceState_TopView() {

	// ���ʂ̐ݒ�
	SetDeviceState_Common();

	// ����}�g���N�X
	D3DXMATRIX mat_view;
	D3DXVECTOR3 vec_from=D3DXVECTOR3(37.5f, 50.0f, 100);
	D3DXVECTOR3 vec_lookat=D3DXVECTOR3(37.5f, 50.0f, 0);
	D3DXVECTOR3 vec_up=D3DXVECTOR3(0, -1, 0);
	D3DXMatrixLookAtLH(&mat_view, &vec_from, &vec_lookat, &vec_up);
	Device->SetTransform(D3DTS_VIEW, &mat_view);
	
	// ���e�}�g���N�X
	D3DXMATRIX mat_proj;
	D3DXMatrixOrthoLH(&mat_proj, 75, 100, 1, 1000);
	Device->SetTransform(D3DTS_PROJECTION, &mat_proj);

	// ���C�e�B���O
	D3DLIGHT9 light;
	InitLight(light, D3DLIGHT_DIRECTIONAL, -1.0f, -1.0f, -1.0f);
	Device->SetLight(0, &light);
	Device->LightEnable(0, TRUE);
	Device->SetRenderState(D3DRS_LIGHTING, TRUE);

	// �r���[�|�[�g
	D3DVIEWPORT9 viewport;
	SIZE size=GetBackBufferSize();
	int w=size.cx, h=size.cy;
	viewport.X=(unsigned long)((w-h*0.75)/2);
	viewport.Y=0;
	viewport.Width=(unsigned long)(h*0.75);
	viewport.Height=h;
	viewport.MinZ=0;
	viewport.MaxZ=1;
	Device->SetViewport(&viewport);
}


//==============================================================
// ��CObject3D���f�o�C�X��Ԃ̐ݒ�i�T�C�h�r���[�j
void CObject3D::SetDeviceState_SideView() {

	// ���ʂ̐ݒ�
	SetDeviceState_Common();

	// ����}�g���N�X
	D3DXMATRIX mat_view;
	D3DXVECTOR3 vec_from=D3DXVECTOR3(50.0f, 37.5f, 100);
	D3DXVECTOR3 vec_lookat=D3DXVECTOR3(50.0f, 37.5f, 0);
	D3DXVECTOR3 vec_up=D3DXVECTOR3(0, -1, 0);
	D3DXMatrixLookAtLH(&mat_view, &vec_from, &vec_lookat, &vec_up);
	Device->SetTransform(D3DTS_VIEW, &mat_view);
	
	// ���e�}�g���N�X
	D3DXMATRIX mat_proj;
	D3DXMatrixOrthoLH(&mat_proj, 100, 75, 1, 1000);
	Device->SetTransform(D3DTS_PROJECTION, &mat_proj);

	// ���C�e�B���O
	D3DLIGHT9 light;
	InitLight(light, D3DLIGHT_DIRECTIONAL, -1.0f, 1.0f, -1.0f);
	Device->SetLight(0, &light);
	Device->LightEnable(0, TRUE);
	Device->SetRenderState(D3DRS_LIGHTING, TRUE);

	// �r���[�|�[�g
	D3DVIEWPORT9 viewport;
	SIZE size=GetBackBufferSize();
	int w=size.cx, h=size.cy;
	viewport.X=0;
	viewport.Y=(unsigned long)((h-w*0.75)/2);
	viewport.Width=w;
	viewport.Height=(unsigned long)(w*0.75);
	viewport.MinZ=0;
	viewport.MaxZ=1;
	Device->SetViewport(&viewport);
}


//==============================================================
// ��CObject3D���f�o�C�X��Ԃ̐ݒ�
void CObject3D::SetDeviceState() {
	switch (ViewType) {
		case VIEW_TOP: SetDeviceState_TopView(); break;
		case VIEW_SIDE: SetDeviceState_SideView(); break;
	}
}


//==============================================================
// ��CObject3D���`��i�g�b�v�r���[�j
void CObject3D::DrawTopView(
	float x, float y, 
	float sx, float sy, 
	float yaw, float pitch, float roll,
	float alpha, bool alpha_addition
) {
	D3DXMATRIX mat, mat0;
	if (TopViewOnly || ViewType==VIEW_TOP) {
		D3DXMatrixRotationX(&mat, D3DX_PI/2);
		Draw(mat, x, y, 0, sx, sy, 1, 
			pitch, roll, yaw, alpha, alpha_addition);
	} else {
		D3DXMatrixRotationY(&mat, D3DX_PI/2);
		D3DXMatrixRotationX(&mat0, D3DX_PI);
		D3DXMatrixMultiply(&mat, &mat, &mat0);
		Draw(mat, x, y, 0, sx, sy, 1,
			roll, yaw, pitch, alpha, alpha_addition);
	}
}
void CObject3D::DrawTopView(
	float x, float y, float z,
	float sx, float sy, 
	float yaw, float pitch, float roll,
	float alpha, bool alpha_addition
) {
	D3DXMATRIX mat, mat0;
	if (TopViewOnly || ViewType==VIEW_TOP) {
		D3DXMatrixRotationX(&mat, D3DX_PI/2);
		Draw(mat, x, y, z, sx, sy, 1, 
			pitch, roll, yaw, alpha, alpha_addition);
	} else {
		D3DXMatrixRotationY(&mat, D3DX_PI/2);
		D3DXMatrixRotationX(&mat0, D3DX_PI);
		D3DXMatrixMultiply(&mat, &mat, &mat0);
		Draw(mat, x, y, z, sx, sy, 1,
			roll, yaw, pitch, alpha, alpha_addition);
	}
}


//==============================================================
// ��CObject3D���`��i3D���W�C�g�嗦�C��]���w��j
void CObject3D::Draw(
	D3DXMATRIX& mat,
	float x, float y, float z, 
	float sx, float sy, float sz,
	float rx, float ry, float rz,
	float alpha, bool alpha_addition
) {
	D3DXMATRIX mat0;
	
	// �g��k��
	D3DXMatrixScaling(&mat0, sx, sy, sz);
	D3DXMatrixMultiply(&mat, &mat, &mat0);
	
	// ��]
	if (ViewType==VIEW_TOP) {
		if (rz!=0) {
			D3DXMatrixRotationZ(&mat0, D3DX_PI*2*rz);
			D3DXMatrixMultiply(&mat, &mat, &mat0);
		}
		if (rx!=0) {
			D3DXMatrixRotationX(&mat0, D3DX_PI*2*rx);
			D3DXMatrixMultiply(&mat, &mat, &mat0);
		}
		if (ry!=0) {
			D3DXMatrixRotationY(&mat0, D3DX_PI*2*ry);
			D3DXMatrixMultiply(&mat, &mat, &mat0);
		}
	} else {
		if (rx!=0) {
			D3DXMatrixRotationX(&mat0, D3DX_PI*2*rx);
			D3DXMatrixMultiply(&mat, &mat, &mat0);
		}
		if (ry!=0) {
			D3DXMatrixRotationY(&mat0, D3DX_PI*2*ry);
			D3DXMatrixMultiply(&mat, &mat, &mat0);
		}
		if (rz!=0) {
			D3DXMatrixRotationZ(&mat0, D3DX_PI*2*rz);
			D3DXMatrixMultiply(&mat, &mat, &mat0);
		}
	}

	// ���W
	D3DXMatrixTranslation(&mat0, x, y, z);
	D3DXMatrixMultiply(&mat, &mat, &mat0);
	
	// ��]
	if (RotationRad!=0) {
		if (ViewType==VIEW_TOP) {
			D3DXMatrixTranslation(&mat0, -37.5f, -50, 0);
			D3DXMatrixMultiply(&mat, &mat, &mat0);
			D3DXMatrixRotationZ(&mat0, RotationRad);
			D3DXMatrixMultiply(&mat, &mat, &mat0);
			D3DXMatrixTranslation(&mat0, 37.5f, 50, 0);
			D3DXMatrixMultiply(&mat, &mat, &mat0);
		}
	}

	// �`��
	Device->SetTransform(D3DTS_WORLD, &mat);
	Draw(alpha, alpha_addition);
}


//==============================================================
// ��CObject3D�����ۂɃ��b�V����`�悷��
void CObject3D::Draw(float alpha, bool alpha_addition) {
	if (alpha<0) alpha=0; else if (alpha>1) alpha=1;
	D3DMATERIAL9 mat;
	for (DWORD i=0; i<NumMaterials; i++) {
		mat=Materials[i];
		if (alpha_addition) {
			Device->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE);
			Device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			Device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE);
		} else {
			Device->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE);
			Device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			Device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}
		mat.Diffuse.a*=alpha;
		mat.Ambient.a*=alpha;
		mat.Specular.a*=alpha;
		mat.Emissive.a*=alpha;
		Device->SetMaterial(&mat);
		Device->SetTexture(0, Textures[i]);
		Mesh->DrawSubset(i);
	}
}




