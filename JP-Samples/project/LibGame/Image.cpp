#include "Image.h"
#include <d3dx9.h>


//==============================================================
// ＜CImage＞staticメンバ
LPDIRECT3DDEVICE9 CImage::Device=NULL;
LPDIRECT3DVERTEXBUFFER9 CImage::VertexBuffer=NULL;


//==============================================================
// ＜CImage＞初期化
void CImage::Init(LPDIRECT3DDEVICE9 device) {
	Device=device;

	// 頂点バッファの作成
	if (!VertexBuffer) {
		Device->CreateVertexBuffer(
			4*sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX, 
			D3DPOOL_MANAGED, &VertexBuffer, NULL);
	}
}


//==============================================================
// ＜CImage＞終了
void CImage::Uninit() {
	if (VertexBuffer) {
		VertexBuffer->Release();
		VertexBuffer=NULL;
	}
}


//==============================================================
// バックバッファのサイズを得る
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
// ＜CImage＞デバイス状態の設定
void CImage::SetDeviceState() {

	// 頂点バッファをデバイスに設定
	Device->SetStreamSource(
		0, VertexBuffer, 0, sizeof(CUSTOMVERTEX));
	Device->SetFVF(D3DFVF_CUSTOMVERTEX);

	// レンダリングの設定
	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	Device->SetRenderState(D3DRS_ZENABLE, FALSE);

	// アルファブレンディングの有効化
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// テクスチャ処理方法の設定
	Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	Device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	Device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	// 線形補間を使わないための設定
	Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

	// ビューポート
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
// ＜CImage＞テクスチャの描画
void CImage::Draw(
	int dx, int dy, int sx, int sy, int w, int h,
	D3DCOLOR color
) {
	// 描画開始
//	if (FAILED(Device->BeginScene())) return;
	
	// 256x256のテクスチャをタイル状に敷き詰める
	int sl=sx, st=sy, sr=sx+w, sb=sy+h;
	for (int yc=0, i=0; yc<YCount; yc++) {
		for (int xc=0; xc<XCount; xc++, i++) {
			if (!Textures[i]) continue;

			// 描画するタイルの四隅の座標計算：
			// このタイル内に描画対象範囲がなければ，
			// 次のタイルに移る。
			int l=xc*256, t=yc*256, r=l+256, b=t+256;
			if (r<=sl || sr<=l || b<=st || sb<=t) continue;

			// 頂点バッファのロック
			CUSTOMVERTEX* v;
			if (SUCCEEDED(VertexBuffer->Lock(
				0, 4*sizeof(CUSTOMVERTEX), 
				(void**)&v, 0))
			) {
				// 頂点座標とテクスチャ座標の計算：
				// タイルが描画対象範囲の内部にないときには，
				// 頂点座標とテクスチャ座標を調整する。
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

				// 頂点座標の設定
				v[0].X=vl; v[0].Y=vt; v[0].TU=tl; v[0].TV=tt;
				v[1].X=vr; v[1].Y=vt; v[1].TU=tr; v[1].TV=tt;
				v[2].X=vl; v[2].Y=vb; v[2].TU=tl; v[2].TV=tb;
				v[3].X=vr; v[3].Y=vb; v[3].TU=tr; v[3].TV=tb;

				// Z, RHW, 頂点色の設定
				for (int j=0; j<4; j++) {
					v[j].Z=0; v[j].RHW=1; 
					v[j].Color=color;
				}

				// 頂点バッファの解放，テクスチャの選択，描画
				VertexBuffer->Unlock();
				Device->SetTexture(0, Textures[i]);
				Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
			}
		}
	}

	// 描画終了
//	Device->EndScene();
}


//==============================================================
// ＜CImage＞画像をロードする：
// 大きなサーフェイスを作成して画像をロードし，
// これを256x256ピクセルずつに分割してテクスチャ上にコピーする。
// UpdateSurfaceやStretchRectは使えないので，
// （D3DPOOL_DEFAULTのテクスチャへのコピーには使えるが，
// 　このクラスではD3DPOOL_MANAGEDを使うため。）
// LockRectとmemcpyを使ってコピーする。
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
// ＜CImage＞コンストラクタ：
// テクスチャを作成する。
// 指定されたサイズより大きくなるように，
// 256x256ピクセルのテクスチャを並べる。
CImage::CImage(
	int width, int height)
:	Width(width), Height(height)
{
	XCount=(width+255)/256;
	YCount=(height+255)/256;

	// テクスチャの作成
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
// ＜CImage＞デストラクタ：
// テクスチャを削除する。
CImage::~CImage() {
	for (int i=0, n=XCount*YCount; i<n; i++) {
		if (Textures[i]) Textures[i]->Release();
	}
	delete[] Textures;
}


//==============================================================
// ＜CText＞コンストラクタ
CText::CText(int width, int height)
:	CImage(width, height), TextSurface(NULL)
{
	// テキスト描画用サーフェイスの作成
	Device->CreateOffscreenPlainSurface(
		XCount*256, YCount*256, D3DFMT_X8R8G8B8, 
		D3DPOOL_SYSTEMMEM, &TextSurface, NULL);
}


//==============================================================
// ＜CText＞デストラクタ
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
// ＜CText＞テキストの描画：
// テクスチャ上にテキストを描くために、
// GDIを使ってサーフェイスにテキストを描き、
// それをテクスチャ上にコピーする。
// サーフェイスにアルファがあるとGDIが使えないので，
// （GetDCに失敗する）
// このように面倒な手順になっている。
// サーフェイスからテクスチャへのコピーの際に，
// 自前でテキストの背景が抜けるようにアルファを設定する。
void CText::DrawText(
	string text, int x, int y, 
	D3DCOLOR color, HFONT font,
	ALIGN_TYPE halign, ALIGN_TYPE valign,
	SIZE* psize
) {
	if (!TextSurface) return;

	// DCの取得とフォントの設定
	HDC hdc;
	if (SUCCEEDED(TextSurface->GetDC(&hdc))) {
		HGDIOBJ prev_obj;
		if (font) prev_obj=SelectObject(hdc, font);

		// サーフェイスの左上隅にテキストを描く：
		// 文字を白，背景を黒で描く。
		SetBkColor(hdc, 0x00000000);
		SetTextColor(hdc, 0x00ffffff);
		TextOut(hdc, 0, 0, text.c_str(), text.length());

		// テキストの描画範囲を得る
		SIZE size;
		if (!psize) psize=&size;
		GetTextExtentPoint32(
			hdc, text.c_str(), text.length(), psize);
		int w=psize->cx, h=psize->cy;

		// フォントの復帰とDCの解放
		if (font) SelectObject(hdc, prev_obj);
		TextSurface->ReleaseDC(hdc);
		if (w==0 || h==0) return;

		// テクスチャ上のテキストの表示位置を決める
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

		// サーフェイスをテクスチャのタイルにコピーする
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

					// テキスト描画範囲がタイルの範囲外のときには
					// 描画しない
					int tl=xc*256, tt=yc*256, tr=tl+256, tb=tt+256;
					if (tr<=sl || sr<=tl || tb<=st || sb<=tt) continue;

					// テキストの背景が抜けるようにコピーする：
					// 文字が白，背景が黒なので，
					// ビット演算を使ってアルファ値を設定する。
					// テキストの部分だけをロックするようにした。
					// テクスチャ全体をロックするととても遅くなる。
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

							// テクスチャとサーフェイスのアドレス計算：
							// テクスチャは変更する領域のみロックしているため、
							// tlr.pBitsは変更領域の左上を指している。
							DWORD *tp=(DWORD*)((char*)tlr.pBits+
								tlr.Pitch*line);
							DWORD *sp=(DWORD*)((char*)slr.pBits+
								(tl+dl-x)*4+slr.Pitch*(tt+dt-y+line));
							
							for (int col=0; col<dw; col++) {

								// B成分をアルファに設定し，
								// RGBは指定された色にする。
								// アンチエイリアスをアルファで表現するため。
								int a=ca*(sp[col]&0xff)/0xff;
								if (a) tp[col]=a<<24|crgb;

								/*
								// ClearTypeに対応した方法も書いてみたが，
								// フォント作成時に通常のアンチエイリアスを
								// 指定した方が良い結果になる。
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





