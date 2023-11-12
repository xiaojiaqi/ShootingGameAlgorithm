#include "Image.h"
#include <d3dx9.h>


//==============================================================
// ��CImage��static����
LPDIRECT3DDEVICE9 CImage::Device=NULL;
LPDIRECT3DVERTEXBUFFER9 CImage::VertexBuffer=NULL;


//==============================================================
// ��CImage�֪�l��
void CImage::Init(LPDIRECT3DDEVICE9 device) {
	Device=device;

	// �إ߳��I�w�İ�
	if (!VertexBuffer) {
		Device->CreateVertexBuffer(
			4*sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX, 
			D3DPOOL_MANAGED, &VertexBuffer, NULL);
	}
}


//==============================================================
// ��CImage�ֵ���
void CImage::Uninit() {
	if (VertexBuffer) {
		VertexBuffer->Release();
		VertexBuffer=NULL;
	}
}


//==============================================================
// ���oBack Buffer���j�p
static SIZE GetBackBufferSize(LPDIRECT3DDEVICE9 device) {
	LPDIRECT3DSURFACE9 back_buffer;
	D3DSURFACE_DESC desc;
	SIZE size={0, 0};
	if (SUCCEEDED(device->GetBackBuffer(
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
// ��CImage�ָ˸m���A���]�w
void CImage::SetDeviceState() {

	// �˸m�]�w���I�w�İ�
	Device->SetStreamSource(
		0, VertexBuffer, 0, sizeof(CUSTOMVERTEX));
	Device->SetFVF(D3DFVF_CUSTOMVERTEX);

	// �K�ϳ]�w
	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	Device->SetRenderState(D3DRS_ZENABLE, FALSE);

	// ALPHA�K�Ϫ����Ĥ�
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ����B�z��k���]�w
	Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	Device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	Device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	// ���ϥνu�δ��Ȫ��]�w
	Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

	// ����
	D3DVIEWPORT9 viewport;
	SIZE size=GetBackBufferSize(Device);
	int w=size.cx, h=size.cy;
	viewport.X=0;
	viewport.Y=0;
	viewport.Width=w;
	viewport.Height=h;
	viewport.MinZ=0;
	viewport.MaxZ=1;
	Device->SetViewport(&viewport);
}


//==============================================================
// ��CImage�֧��誺�yø
void CImage::Draw(
	int dx, int dy, int sx, int sy, int w, int h,
	D3DCOLOR color
) {
	// �yø�}�l
//	if (FAILED(Device->BeginScene())) return;
	
	// �Q�W256x256����j
	int sl=sx, st=sy, sr=sx+w, sb=sy+h;
	for (int yc=0, i=0; yc<YCount; yc++) {
		for (int xc=0; xc<XCount; xc++, i++) {
			if (!Textures[i]) continue;

			// ø�e������j�|�����y�Эp��G
			// �p�G����j���S���yø��H�d��A
			// ���N�ಾ��U�Ӫ�����j
			int l=xc*256, t=yc*256, r=l+256, b=t+256;
			if (r<=sl || sr<=l || b<=st || sb<=t) continue;

			// ���I�w�İϪ���w
			CUSTOMVERTEX* v;
			if (SUCCEEDED(VertexBuffer->Lock(
				0, 4*sizeof(CUSTOMVERTEX), 
				(void**)&v, 0))
			) {
				// ���I�y�ЩM����y�Ъ��p��G
				// ��yø��H�d�򤺳��S������j�ɡA
				// �h�վ㳻�I�y�ЩM����y�СC
				float 
					vl=(float)((l<sl)?sl-l:0), 
					vt=(float)((t<st)?st-t:0),
					vr=(float)((sr<r)?sr-l:256),
					vb=(float)((sb<b)?sb-t:256);
				float 
					tl=vl/256, tt=vt/256, 
					tr=vr/256, tb=vb/256;
				vl+=l+dx-sx; vr+=l+dx-sx; 
				vt+=t+dy-sy; vb+=t+dy-sy;

				// ���I�y�Ъ��]�w
				v[0].X=vl; v[0].Y=vt; v[0].TU=tl; v[0].TV=tt;
				v[1].X=vr; v[1].Y=vt; v[1].TU=tr; v[1].TV=tt;
				v[2].X=vl; v[2].Y=vb; v[2].TU=tl; v[2].TV=tb;
				v[3].X=vr; v[3].Y=vb; v[3].TU=tr; v[3].TV=tb;

				// Z, RHW, ���I�⪺�]�w
				for (int j=0; j<4; j++) {
					v[j].Z=0; v[j].RHW=1; 
					v[j].Color=color;
				}

				// �����I�w�İϡA���誺��ܡA�yø
				VertexBuffer->Unlock();
				Device->SetTexture(0, Textures[i]);
				Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
			}
		}
	}

	// �`��I��
//	Device->EndScene();
}


//==============================================================
// ��CImage�ּv�����J�G
// �إߤj�����ø��J�v���A
// �N�����Φ�256x256�����ƻs�K�����W�C
// �]��UpdateSurface�PStretchRect����ϥΡA
// �]�ND3DPOOL_DEFAULT������ƻs�ӥΡA
// �b�o�����O���ϥ�D3DPOOL_MANAGED�^
// �ϥ�LockRect�Pmemcpy�ӽƻs�ϥ�
void CImage::LoadFromFile(string file_name) {
	LPDIRECT3DSURFACE9 surface;
	D3DLOCKED_RECT slr;
	if (SUCCEEDED(Device->CreateOffscreenPlainSurface(
			XCount*256, YCount*256, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, 
			&surface, NULL))
	) {
		if (SUCCEEDED(D3DXLoadSurfaceFromFile(
				surface, NULL, NULL, file_name.c_str(), NULL, 
				D3DX_FILTER_NONE, 0, NULL)) &&
			SUCCEEDED(surface->LockRect(
				&slr, NULL, D3DLOCK_READONLY))
		) {
			for (int yc=0, i=0; yc<YCount; yc++) {
				for (int xc=0; xc<XCount; xc++, i++) {
					if (!Textures[i]) continue;
					D3DLOCKED_RECT tlr;
					if (SUCCEEDED(Textures[i]->LockRect(0, &tlr, NULL, 0))) {
						int x=xc*256, y=yc*256;
						for (int line=0; line<256; line++) {
							memcpy(
								(char*)tlr.pBits+tlr.Pitch*line, 
								(char*)slr.pBits+x*4+slr.Pitch*(y+line), 
								256*4);
						}
						Textures[i]->UnlockRect(0);
					}
				}
			}
			surface->UnlockRect();
		}
		surface->Release();
	}
}


//==============================================================
// ��CImage�֫غc��
// �إߧ���
// ��j����w���j�p�A
// �H256x256����������ӾQ��
CImage::CImage(
	int width, int height)
:	Width(width), Height(height)
{
	XCount=(width+255)/256;
	YCount=(height+255)/256;

	// �e�N�X�`?�̍쐬
	Textures=new LPDIRECT3DTEXTURE9[XCount*YCount];
	for (int i=0, n=XCount*YCount; i<n; i++) {
		Textures[i]=NULL;
		Device->CreateTexture(
			256, 256, 1, 0, 
			D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
			&Textures[i], NULL);
	}
}


//==============================================================
// ��CImage�ָѺc��
// �R������
CImage::~CImage() {
	for (int i=0, n=XCount*YCount; i<n; i++) {
		if (Textures[i]) Textures[i]->Release();
	}
	delete[] Textures;
}


//==============================================================
// ��CText�֫غc��
CText::CText(int width, int height)
:	CImage(width, height), TextSurface(NULL)
{
	// �إߪ�����r�yø
	Device->CreateOffscreenPlainSurface(
		XCount*256, YCount*256, D3DFMT_X8R8G8B8, 
		D3DPOOL_SYSTEMMEM, &TextSurface, NULL);
}


//==============================================================
// ��CText�ָѺc��
CText::~CText() {
	if (TextSurface) TextSurface->Release();
}



void CImage::Clear(D3DCOLOR color) {
	D3DLOCKED_RECT tlr;
	for (int yc=0, i=0; yc<YCount; yc++) {
		for (int xc=0; xc<XCount; xc++, i++) {
			if (SUCCEEDED(Textures[i]->LockRect(0, &tlr, NULL, 0))) {
				for (int line=0; line<256; line++) {
					DWORD *tp=(DWORD*)((char*)tlr.pBits+tlr.Pitch*line);
					for (int col=0; col<256; col++) tp[col]=color;
				}
				Textures[i]->UnlockRect(0);
			}
		}
	}
}



//==============================================================
// ��CText�֤�r���yø�G
// �b����W�yø��r�A
// �ϥ�GDI�b���W�yø��r�A
// �ƻs�����W�C
// ��alpha�b���W��GDI����ϥΡA
// �]GetDC�|���ѡ^
// �|�I��o�˳·Ъ��{�ǡC
// �q���V��������ɡA
// ����r���I���渨�@�˦a�]�wAlpha�C
void CText::DrawText(
	string text, int x, int y, 
	D3DCOLOR color, HFONT font,
	ALIGN_TYPE halign, ALIGN_TYPE valign,
	SIZE* psize
) {
	if (!TextSurface) return;

	// DC���o�P�r�����]�w
	HDC hdc;
	if (SUCCEEDED(TextSurface->GetDC(&hdc))) {
		HGDIOBJ prev_obj;
		if (font) prev_obj=SelectObject(hdc, font);

		// �b�������W���yø��r�A
		// ��r�O�ժ��A�I�����¦�C
		SetBkColor(hdc, 0x00000000);
		SetTextColor(hdc, 0x00ffffff);
		TextOut(hdc, 0, 0, text.c_str(), text.length());

		// ���o��r�yø���d��
		SIZE size;
		if (!psize) psize=&size;
		GetTextExtentPoint32(
			hdc, text.c_str(), text.length(), psize);
		int w=psize->cx, h=psize->cy;

		// �r���٭�PDC������
		if (font) SelectObject(hdc, prev_obj);
		TextSurface->ReleaseDC(hdc);
		if (w==0 || h==0) return;

		// �M�w����W��r����ܦ�m
		switch (halign) {
			case ALIGN_LEFT: break;
			case ALIGN_CENTER: x-=w/2; break;
			case ALIGN_RIGHT: x-=w; break;
		}
		switch (valign) {
			case ALIGN_TOP: break;
			case ALIGN_CENTER: y-=h/2; break;
			case ALIGN_BOTTOM: y-=h; break;
		}

		// ���ƻs����j
		D3DLOCKED_RECT slr;
		RECT sdr={0, 0, w, h};
		if (SUCCEEDED(TextSurface->LockRect(
				&slr, &sdr, D3DLOCK_READONLY))
		) {
			int ca=color>>24&0xff, crgb=color&0x00ffffff;
			int sl=x, st=y, sr=sl+w, sb=st+h;
			for (int yc=0, i=0; yc<YCount; yc++) {
				for (int xc=0; xc<XCount; xc++, i++) {
					if (!Textures[i]) continue;

					// ��r�yø�d��b����j�~�ɡA
					// ����yø
					int tl=xc*256, tt=yc*256, tr=tl+256, tb=tt+256;
					if (tr<=sl || sr<=tl || tb<=st || sb<=tt) continue;

					// 
					// ��r���աA�I���O�¦�
					// �ϥΦ줸�B��ӳ]�walpha��
					// �u����r�����Q��w�C
					// ���ӧ���Q��w�ɷ|�ܺC�C
					int 
						dl=(tl<sl)?sl-tl:0,
						dt=(tt<st)?st-tt:0,
						dr=(sr<tr)?sr-tl:256,
						db=(sb<tb)?sb-tt:256;
					RECT tdr={dl, dt, dr, db};
					D3DLOCKED_RECT tlr;
					if (SUCCEEDED(Textures[i]->LockRect(0, &tlr, &tdr, 0))) {
						int dw=dr-dl, dh=db-dt;
						for (int line=0; line<dh; line++) {

							// �p�����P������m
							// ����u��w�ܧ󪺳����A���߁A
							// tlr.pBits�|�����ܧ󳡥������W���C
							DWORD *tp=(DWORD*)((char*)tlr.pBits+
								tlr.Pitch*line);
							DWORD *sp=(DWORD*)((char*)slr.pBits+
								(tl+dl-x)*4+slr.Pitch*(tt+dt-y+line));
							
							for (int col=0; col<dw; col++) {

								// B�����]��alpha
								// RGB���w�@���C��
								// �Halpha��{�Ͽ������邽�߁B
								int a=ca*(sp[col]&0xff)/0xff;
								if (a) tp[col]=a<<24|crgb;

								/*
								// �յۤ]�g�J�䴩ClearType��k�A
								// �إߦr��ɬO�Ͽ�����
								DWORD c=sp[col], r=c>>16&255, 
									g=c>>8&255, b=c&255;
								DWORD a=(r+g+b)/3;
								tp[col]=a<<24|color;
								*/

							}
						}
						Textures[i]->UnlockRect(0);
					}
				}
			}
			TextSurface->UnlockRect();
		}
	}
}





