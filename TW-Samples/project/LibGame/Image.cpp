#include "Image.h"
#include <d3dx9.h>


//==============================================================
// ＜CImage＞static成員
LPDIRECT3DDEVICE9 CImage::Device=NULL;
LPDIRECT3DVERTEXBUFFER9 CImage::VertexBuffer=NULL;


//==============================================================
// ＜CImage＞初始化
void CImage::Init(LPDIRECT3DDEVICE9 device) {
	Device=device;

	// 建立頂點緩衝區
	if (!VertexBuffer) {
		Device->CreateVertexBuffer(
			4*sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX, 
			D3DPOOL_MANAGED, &VertexBuffer, NULL);
	}
}


//==============================================================
// ＜CImage＞結束
void CImage::Uninit() {
	if (VertexBuffer) {
		VertexBuffer->Release();
		VertexBuffer=NULL;
	}
}


//==============================================================
// 取得Back Buffer的大小
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
// ＜CImage＞裝置狀態的設定
void CImage::SetDeviceState() {

	// 裝置設定頂點緩衝區
	Device->SetStreamSource(
		0, VertexBuffer, 0, sizeof(CUSTOMVERTEX));
	Device->SetFVF(D3DFVF_CUSTOMVERTEX);

	// 貼圖設定
	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	Device->SetRenderState(D3DRS_ZENABLE, FALSE);

	// ALPHA貼圖的有效化
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// 材質處理方法的設定
	Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	Device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	Device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	// 不使用線形插值的設定
	Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

	// 視埠
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
// ＜CImage＞材質的描繪
void CImage::Draw(
	int dx, int dy, int sx, int sy, int w, int h,
	D3DCOLOR color
) {
	// 描繪開始
//	if (FAILED(Device->BeginScene())) return;
	
	// 鋪上256x256材質磚
	int sl=sx, st=sy, sr=sx+w, sb=sy+h;
	for (int yc=0, i=0; yc<YCount; yc++) {
		for (int xc=0; xc<XCount; xc++, i++) {
			if (!Textures[i]) continue;

			// 繪畫的材質磚四角的座標計算：
			// 如果材質磚內沒有描繪對象範圍，
			// 那就轉移到下個的材質磚
			int l=xc*256, t=yc*256, r=l+256, b=t+256;
			if (r<=sl || sr<=l || b<=st || sb<=t) continue;

			// 頂點緩衝區的鎖定
			CUSTOMVERTEX* v;
			if (SUCCEEDED(VertexBuffer->Lock(
				0, 4*sizeof(CUSTOMVERTEX), 
				(void**)&v, 0))
			) {
				// 頂點座標和材質座標的計算：
				// 對描繪對象範圍內部沒有材質磚時，
				// 則調整頂點座標和材質座標。
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

				// 頂點座標的設定
				v[0].X=vl; v[0].Y=vt; v[0].TU=tl; v[0].TV=tt;
				v[1].X=vr; v[1].Y=vt; v[1].TU=tr; v[1].TV=tt;
				v[2].X=vl; v[2].Y=vb; v[2].TU=tl; v[2].TV=tb;
				v[3].X=vr; v[3].Y=vb; v[3].TU=tr; v[3].TV=tb;

				// Z, RHW, 頂點色的設定
				for (int j=0; j<4; j++) {
					v[j].Z=0; v[j].RHW=1; 
					v[j].Color=color;
				}

				// 釋放頂點緩衝區，材質的選擇，描繪
				VertexBuffer->Unlock();
				Device->SetTexture(0, Textures[i]);
				Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
			}
		}
	}

	// �`���I��
//	Device->EndScene();
}


//==============================================================
// ＜CImage＞影像載入：
// 建立大的表面並載入影像，
// 將它分割成256x256像素複製貼到材質上。
// 因為UpdateSurface與StretchRect不能使用，
// （將D3DPOOL_DEFAULT的材質複製來用，
// 在這個類別中使用D3DPOOL_MANAGED）
// 使用LockRect與memcpy來複製使用
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
// ＜CImage＞建構式
// 建立材質
// 放大到指定的大小，
// 以256x256像素的材質來鋪排
CImage::CImage(
	int width, int height)
:	Width(width), Height(height)
{
	XCount=(width+255)/256;
	YCount=(height+255)/256;

	// �e�N�X�`?������
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
// ＜CImage＞解構式
// 刪除材質
CImage::~CImage() {
	for (int i=0, n=XCount*YCount; i<n; i++) {
		if (Textures[i]) Textures[i]->Release();
	}
	delete[] Textures;
}


//==============================================================
// ＜CText＞建構式
CText::CText(int width, int height)
:	CImage(width, height), TextSurface(NULL)
{
	// 建立表面讓文字描繪
	Device->CreateOffscreenPlainSurface(
		XCount*256, YCount*256, D3DFMT_X8R8G8B8, 
		D3DPOOL_SYSTEMMEM, &TextSurface, NULL);
}


//==============================================================
// ＜CText＞解構式
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
// ＜CText＞文字的描繪：
// 在材質上描繪文字，
// 使用GDI在表面上描繪文字，
// 複製到材質上。
// 當alpha在表面上時GDI不能使用，
// （GetDC會失敗）
// 會碰到這樣麻煩的程序。
// 從表面向材質拷貝時，
// 像文字的背景脫落一樣地設定Alpha。
void CText::DrawText(
	string text, int x, int y, 
	D3DCOLOR color, HFONT font,
	ALIGN_TYPE halign, ALIGN_TYPE valign,
	SIZE* psize
) {
	if (!TextSurface) return;

	// DC取得與字型的設定
	HDC hdc;
	if (SUCCEEDED(TextSurface->GetDC(&hdc))) {
		HGDIOBJ prev_obj;
		if (font) prev_obj=SelectObject(hdc, font);

		// 在表面的左上角描繪文字，
		// 文字是白的，背景為黑色。
		SetBkColor(hdc, 0x00000000);
		SetTextColor(hdc, 0x00ffffff);
		TextOut(hdc, 0, 0, text.c_str(), text.length());

		// 取得文字描繪的範圍
		SIZE size;
		if (!psize) psize=&size;
		GetTextExtentPoint32(
			hdc, text.c_str(), text.length(), psize);
		int w=psize->cx, h=psize->cy;

		// 字型還原與DC的釋放
		if (font) SelectObject(hdc, prev_obj);
		TextSurface->ReleaseDC(hdc);
		if (w==0 || h==0) return;

		// 決定材質上文字的顯示位置
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

		// 表面複製材質磚
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

					// 文字描繪範圍在材質磚外時，
					// 不能描繪
					int tl=xc*256, tt=yc*256, tr=tl+256, tb=tt+256;
					if (tr<=sl || sr<=tl || tb<=st || sb<=tt) continue;

					// 
					// 文字為白，背景是黑色
					// 使用位元運算來設定alpha值
					// 只有文字部份被鎖定。
					// 當整個材質被鎖定時會很慢。
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

							// 計算材質與表面的位置
							// 材質只鎖定變更的部份，�����A
							// tlr.pBits會指到變更部份的左上角。
							DWORD *tp=(DWORD*)((char*)tlr.pBits+
								tlr.Pitch*line);
							DWORD *sp=(DWORD*)((char*)slr.pBits+
								(tl+dl-x)*4+slr.Pitch*(tt+dt-y+line));
							
							for (int col=0; col<dw; col++) {

								// B元素設到alpha
								// RGB指定一個顏色
								// 以alpha表現反鋸齒狀�������B
								int a=ca*(sp[col]&0xff)/0xff;
								if (a) tp[col]=a<<24|crgb;

								/*
								// 試著也寫入支援ClearType方法，
								// 建立字體時是反鋸齒狀
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





