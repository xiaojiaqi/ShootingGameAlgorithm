#include "Image.h"
#include <d3dx9.h>


//==============================================================
// ¡ÕCImage¡Östatic¦¨­û
LPDIRECT3DDEVICE9 CImage::Device=NULL;
LPDIRECT3DVERTEXBUFFER9 CImage::VertexBuffer=NULL;


//==============================================================
// ¡ÕCImage¡Öªì©l¤Æ
void CImage::Init(LPDIRECT3DDEVICE9 device) {
	Device=device;

	// «Ø¥ß³»ÂI½w½Ä°Ï
	if (!VertexBuffer) {
		Device->CreateVertexBuffer(
			4*sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX, 
			D3DPOOL_MANAGED, &VertexBuffer, NULL);
	}
}


//==============================================================
// ¡ÕCImage¡Öµ²§ô
void CImage::Uninit() {
	if (VertexBuffer) {
		VertexBuffer->Release();
		VertexBuffer=NULL;
	}
}


//==============================================================
// ¨ú±oBack Bufferªº¤j¤p
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
// ¡ÕCImage¡Ö¸Ë¸mª¬ºAªº³]©w
void CImage::SetDeviceState() {

	// ¸Ë¸m³]©w³»ÂI½w½Ä°Ï
	Device->SetStreamSource(
		0, VertexBuffer, 0, sizeof(CUSTOMVERTEX));
	Device->SetFVF(D3DFVF_CUSTOMVERTEX);

	// ¶K¹Ï³]©w
	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	Device->SetRenderState(D3DRS_ZENABLE, FALSE);

	// ALPHA¶K¹Ïªº¦³®Ä¤Æ
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// §÷½è³B²z¤èªkªº³]©w
	Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	Device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	Device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	// ¤£¨Ï¥Î½u§Î´¡­Èªº³]©w
	Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

	// µø°ğ
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
// ¡ÕCImage¡Ö§÷½èªº´yÃ¸
void CImage::Draw(
	int dx, int dy, int sx, int sy, int w, int h,
	D3DCOLOR color
) {
	// ´yÃ¸¶}©l
//	if (FAILED(Device->BeginScene())) return;
	
	// ¾Q¤W256x256§÷½è¿j
	int sl=sx, st=sy, sr=sx+w, sb=sy+h;
	for (int yc=0, i=0; yc<YCount; yc++) {
		for (int xc=0; xc<XCount; xc++, i++) {
			if (!Textures[i]) continue;

			// Ã¸µeªº§÷½è¿j¥|¨¤ªº®y¼Ğ­pºâ¡G
			// ¦pªG§÷½è¿j¤º¨S¦³´yÃ¸¹ï¶H½d³ò¡A
			// ¨º´NÂà²¾¨ì¤U­Óªº§÷½è¿j
			int l=xc*256, t=yc*256, r=l+256, b=t+256;
			if (r<=sl || sr<=l || b<=st || sb<=t) continue;

			// ³»ÂI½w½Ä°ÏªºÂê©w
			CUSTOMVERTEX* v;
			if (SUCCEEDED(VertexBuffer->Lock(
				0, 4*sizeof(CUSTOMVERTEX), 
				(void**)&v, 0))
			) {
				// ³»ÂI®y¼Ğ©M§÷½è®y¼Ğªº­pºâ¡G
				// ¹ï´yÃ¸¹ï¶H½d³ò¤º³¡¨S¦³§÷½è¿j®É¡A
				// «h½Õ¾ã³»ÂI®y¼Ğ©M§÷½è®y¼Ğ¡C
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

				// ³»ÂI®y¼Ğªº³]©w
				v[0].X=vl; v[0].Y=vt; v[0].TU=tl; v[0].TV=tt;
				v[1].X=vr; v[1].Y=vt; v[1].TU=tr; v[1].TV=tt;
				v[2].X=vl; v[2].Y=vb; v[2].TU=tl; v[2].TV=tb;
				v[3].X=vr; v[3].Y=vb; v[3].TU=tr; v[3].TV=tb;

				// Z, RHW, ³»ÂI¦âªº³]©w
				for (int j=0; j<4; j++) {
					v[j].Z=0; v[j].RHW=1; 
					v[j].Color=color;
				}

				// ÄÀ©ñ³»ÂI½w½Ä°Ï¡A§÷½èªº¿ï¾Ü¡A´yÃ¸
				VertexBuffer->Unlock();
				Device->SetTexture(0, Textures[i]);
				Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
			}
		}
	}

	// •`‰æI—¹
//	Device->EndScene();
}


//==============================================================
// ¡ÕCImage¡Ö¼v¹³¸ü¤J¡G
// «Ø¥ß¤jªºªí­±¨Ã¸ü¤J¼v¹³¡A
// ±N¥¦¤À³Î¦¨256x256¹³¯À½Æ»s¶K¨ì§÷½è¤W¡C
// ¦]¬°UpdateSurface»PStretchRect¤£¯à¨Ï¥Î¡A
// ¡]±ND3DPOOL_DEFAULTªº§÷½è½Æ»s¨Ó¥Î¡A
// ¦b³o­ÓÃş§O¤¤¨Ï¥ÎD3DPOOL_MANAGED¡^
// ¨Ï¥ÎLockRect»Pmemcpy¨Ó½Æ»s¨Ï¥Î
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
// ¡ÕCImage¡Ö«Øºc¦¡
// «Ø¥ß§÷½è
// ©ñ¤j¨ì«ü©wªº¤j¤p¡A
// ¥H256x256¹³¯Àªº§÷½è¨Ó¾Q±Æ
CImage::CImage(
	int width, int height)
:	Width(width), Height(height)
{
	XCount=(width+255)/256;
	YCount=(height+255)/256;

	// ƒeƒNƒXƒ`?‚Ìì¬
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
// ¡ÕCImage¡Ö¸Ñºc¦¡
// §R°£§÷½è
CImage::~CImage() {
	for (int i=0, n=XCount*YCount; i<n; i++) {
		if (Textures[i]) Textures[i]->Release();
	}
	delete[] Textures;
}


//==============================================================
// ¡ÕCText¡Ö«Øºc¦¡
CText::CText(int width, int height)
:	CImage(width, height), TextSurface(NULL)
{
	// «Ø¥ßªí­±Åı¤å¦r´yÃ¸
	Device->CreateOffscreenPlainSurface(
		XCount*256, YCount*256, D3DFMT_X8R8G8B8, 
		D3DPOOL_SYSTEMMEM, &TextSurface, NULL);
}


//==============================================================
// ¡ÕCText¡Ö¸Ñºc¦¡
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
// ¡ÕCText¡Ö¤å¦rªº´yÃ¸¡G
// ¦b§÷½è¤W´yÃ¸¤å¦r¡A
// ¨Ï¥ÎGDI¦bªí­±¤W´yÃ¸¤å¦r¡A
// ½Æ»s¨ì§÷½è¤W¡C
// ·íalpha¦bªí­±¤W®ÉGDI¤£¯à¨Ï¥Î¡A
// ¡]GetDC·|¥¢±Ñ¡^
// ·|¸I¨ì³o¼Ë³Â·Ğªºµ{§Ç¡C
// ±qªí­±¦V§÷½è«ş¨©®É¡A
// ¹³¤å¦rªº­I´º²æ¸¨¤@¼Ë¦a³]©wAlpha¡C
void CText::DrawText(
	string text, int x, int y, 
	D3DCOLOR color, HFONT font,
	ALIGN_TYPE halign, ALIGN_TYPE valign,
	SIZE* psize
) {
	if (!TextSurface) return;

	// DC¨ú±o»P¦r«¬ªº³]©w
	HDC hdc;
	if (SUCCEEDED(TextSurface->GetDC(&hdc))) {
		HGDIOBJ prev_obj;
		if (font) prev_obj=SelectObject(hdc, font);

		// ¦bªí­±ªº¥ª¤W¨¤´yÃ¸¤å¦r¡A
		// ¤å¦r¬O¥Õªº¡A­I´º¬°¶Â¦â¡C
		SetBkColor(hdc, 0x00000000);
		SetTextColor(hdc, 0x00ffffff);
		TextOut(hdc, 0, 0, text.c_str(), text.length());

		// ¨ú±o¤å¦r´yÃ¸ªº½d³ò
		SIZE size;
		if (!psize) psize=&size;
		GetTextExtentPoint32(
			hdc, text.c_str(), text.length(), psize);
		int w=psize->cx, h=psize->cy;

		// ¦r«¬ÁÙ­ì»PDCªºÄÀ©ñ
		if (font) SelectObject(hdc, prev_obj);
		TextSurface->ReleaseDC(hdc);
		if (w==0 || h==0) return;

		// ¨M©w§÷½è¤W¤å¦rªºÅã¥Ü¦ì¸m
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

		// ªí­±½Æ»s§÷½è¿j
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

					// ¤å¦r´yÃ¸½d³ò¦b§÷½è¿j¥~®É¡A
					// ¤£¯à´yÃ¸
					int tl=xc*256, tt=yc*256, tr=tl+256, tb=tt+256;
					if (tr<=sl || sr<=tl || tb<=st || sb<=tt) continue;

					// 
					// ¤å¦r¬°¥Õ¡A­I´º¬O¶Â¦â
					// ¨Ï¥Î¦ì¤¸¹Bºâ¨Ó³]©walpha­È
					// ¥u¦³¤å¦r³¡¥÷³QÂê©w¡C
					// ·í¾ã­Ó§÷½è³QÂê©w®É·|«ÜºC¡C
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

							// ­pºâ§÷½è»Pªí­±ªº¦ì¸m
							// §÷½è¥uÂê©wÅÜ§óªº³¡¥÷¡A‚½‚ßA
							// tlr.pBits·|«ü¨ìÅÜ§ó³¡¥÷ªº¥ª¤W¨¤¡C
							DWORD *tp=(DWORD*)((char*)tlr.pBits+
								tlr.Pitch*line);
							DWORD *sp=(DWORD*)((char*)slr.pBits+
								(tl+dl-x)*4+slr.Pitch*(tt+dt-y+line));
							
							for (int col=0; col<dw; col++) {

								// B¤¸¯À³]¨ìalpha
								// RGB«ü©w¤@­ÓÃC¦â
								// ¥Halphaªí²{¤Ï¿÷¾¦ª¬‚é‚½‚ßB
								int a=ca*(sp[col]&0xff)/0xff;
								if (a) tp[col]=a<<24|crgb;

								/*
								// ¸ÕµÛ¤]¼g¤J¤ä´©ClearType¤èªk¡A
								// «Ø¥ß¦rÅé®É¬O¤Ï¿÷¾¦ª¬
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





