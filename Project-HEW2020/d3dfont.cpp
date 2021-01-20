//----------------------------------------------------------------------------
// 
// C++ Module [d3dfont.cpp]
// DirectX font render
// 
// Author: CycleDM (Jin Zhou) @HAL_Tokyo_95097_AT12D187_17
// Date:   2021/01/20
// Update: 2021/01/20
// 
//----------------------------------------------------------------------------
#include "d3dfont.h"
#include "d3dutility.h"
#include "config.h"

const UINT			D3DFont::DEFAULT_WIDTH = 1;
const UINT			D3DFont::DEFAULT_HEIGHT = 1;
const UINT			D3DFont::DEFAULT_WEIGHT = 500;

HWND				D3DFont::m_window;
LPDIRECT3DDEVICE9	D3DFont::m_pDevice;
LPD3DXSPRITE		D3DFont::m_pSprite;
D3DXFONT_DESC		D3DFont::m_d3dfd;
LPD3DXFONT			D3DFont::m_pFont;
char				D3DFont::m_fontFile[256];
BYTE				D3DFont::m_charSet;

void D3DFont::Init(HWND hWnd, BYTE charSet)
{
	Uninit();

	m_window = hWnd;

	memset(&m_d3dfd, 0, sizeof(m_d3dfd));
	m_charSet = charSet;

	m_d3dfd.Width = DEFAULT_WIDTH;
	m_d3dfd.Height = DEFAULT_HEIGHT;
	m_d3dfd.Weight = DEFAULT_WEIGHT;	// boldness, range 0(light) - 1000(bold)
	m_d3dfd.Italic = FALSE;
	m_d3dfd.CharSet = m_charSet;
	m_d3dfd.Quality = DEFAULT_QUALITY;

	m_pDevice = D3DUtility::GetDevice();
}

void D3DFont::Uninit()
{
	SAFE_RELEASE(m_pFont);
	SAFE_RELEASE(m_pSprite);
	RemoveFontResourceEx(m_fontFile, FR_PRIVATE, NULL);
}

void D3DFont::Draw(long posx, long posy, const char* text, const char* fontName, int size, D3DCOLOR color)
{
	RECT rect;
	GetClientRect(m_window, &rect);
	rect.left = posx;
	rect.top = posy;

	m_d3dfd.Width = DEFAULT_WIDTH * size;
	m_d3dfd.Height = DEFAULT_HEIGHT * size;
	strcpy_s(m_d3dfd.FaceName, fontName);
	D3DXCreateFontIndirect(m_pDevice, &m_d3dfd, &m_pFont);

	m_pFont->DrawText(
		m_pSprite,
		text,
		-1,
		&rect,
		DT_TOP | DT_LEFT,
		color
	);

	SAFE_RELEASE(m_pFont);
}

void D3DFont::LoadFontFromFile(const char* fileName)
{
	strcpy_s(m_fontFile, fileName);
	AddFontResourceEx(m_fontFile, FR_PRIVATE, NULL);
}