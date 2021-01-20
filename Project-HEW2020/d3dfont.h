//----------------------------------------------------------------------------
// 
// C++ Module [d3dfont.h]
// DirectX font render
// 
// Author: CycleDM (Jin Zhou) @HAL_Tokyo_95097_AT12D187_17
// Date:   2021/01/20
// Update: 2021/01/20
// 
//----------------------------------------------------------------------------
#pragma once
#include <d3dx9.h>

class D3DFont
{
public:
	static void Init(HWND hWnd, BYTE charSet = DEFAULT_CHARSET);
	static void Uninit();
	static void Draw(long posx, long posy, const char* text, const char* fontName = "Arial", int size = 12, D3DCOLOR color = 0xffffffff);

	static void LoadFontFromFile(const char* fileName);
private:
	static HWND m_window;			// Stores the window handle
	static LPDIRECT3DDEVICE9 m_pDevice;
	static LPD3DXSPRITE m_pSprite;
	static D3DXFONT_DESC m_d3dfd;
	static LPD3DXFONT m_pFont;

	static char m_fontFile[256];
	static BYTE m_charSet;

	static const UINT DEFAULT_WIDTH;
	static const UINT DEFAULT_HEIGHT;
	static const UINT DEFAULT_WEIGHT;
};