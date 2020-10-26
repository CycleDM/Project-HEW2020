//----------------------------------------------------------------------------
// 
// Project-HEW2020 [sprite.cpp]
// テクスチャー、スプライト制御
// 
// Date:   2020/10/25
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include "sprite.h"
#include "d3dutility.h"

// 頂点構造体
typedef struct Vertex2D_tag
{
	D3DXVECTOR4 Position;
	D3DCOLOR Color;
	D3DXVECTOR2 TextCoord;
} Vertex2D;
#define FVF_VERTEX2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//----------------------------------------------------------------------------
// スプライトの基本クラス
//----------------------------------------------------------------------------
Sprite::Sprite()
{
	pDevice = D3DUtility_GetDevice();
	pVertexBuffer = NULL;
	pIndexBuffer = NULL;
	if (!pDevice)
	{
		MessageBox(NULL, "Direct3Dデバイスの取得に失敗しました", "エラー", MB_OK);
	}
	pDevice->CreateVertexBuffer(
		sizeof(Vertex2D) * 4,   // 頂点バッファの量（バイト）
		D3DUSAGE_WRITEONLY,     // 使い方
		FVF_VERTEX2D,           // FVF
		D3DPOOL_DEFAULT,        // メモリの管理方法
		&pVertexBuffer,			// 取得したインターフェースのアドレスを記録するためのポインタのアドレス
		NULL
	);

	pDevice->CreateIndexBuffer(
		sizeof(WORD) * 6,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_DEFAULT,
		&pIndexBuffer,
		NULL
	);
	color = 0xffffffff;
	pTexture = NULL;
	txWidth = 0;
	txHeight = 0;
	filename[0] = 0;
}

Sprite::~Sprite()
{
	if (pVertexBuffer)
	{
		pVertexBuffer->Release();
		pVertexBuffer = NULL;
	}
	pTexture->Release();
	pTexture = NULL;
	filename[0] = 0;
	txWidth = 0;
	txHeight = 0;
}

void Sprite::LoadTexture(const char* pFileName)
{
	strcpy(filename, pFileName);

	// テクスチャの読み込み
	HRESULT hr = D3DXCreateTextureFromFile(pDevice, filename, &pTexture);
	if (SUCCEEDED(hr))
	{
		// テクスチャの解像度（幅・高さ）の調査
		D3DXIMAGE_INFO info;
		D3DXGetImageInfoFromFile(filename, &info);
		txWidth = info.Width;
		txHeight = info.Height;
	}
	else
	{
		const char* msg = strcpy(filename, "\nテクスチャの読み込みに失敗しました");
		MessageBox(NULL, msg, "エラー", MB_OK);
	}
}

unsigned long Sprite::GetTextureWidth()
{
	return txWidth;
}
unsigned long Sprite::GetTextureHeight()
{
	return txHeight;
}

LPDIRECT3DTEXTURE9 Sprite::GetTexture()
{
	return pTexture;
}

void Sprite::SetColor(D3DCOLOR color_to_set)
{
	color = color_to_set;
}


//----------------------------------------------------------------------------
// スプライト派生クラス - SpriteNormal
//----------------------------------------------------------------------------
SpriteNormal::SpriteNormal()
{
	dx = dy = tcx = tcy = tcw = tch = 0;
}

void SpriteNormal::Draw(void)
{
	// デバイスにFVFの設定をする
	pDevice->SetFVF(FVF_VERTEX2D);

	// デバイスにテクスチャの設定をする
	pDevice->SetTexture(0, GetTexture());

	// ポリゴンのサイズはテクスチャサイズ
	unsigned long w = GetTextureWidth();
	unsigned long h = GetTextureHeight();

	// テクスチャ切り取りUV座標
	float u0 = (float)tcx / w;
	float v0 = (float)tcy / h;
	float u1 = (float)(tcx + tcw) / w;
	float v1 = (float)(tcy + tch) / h;

	// 頂点データ
	Vertex2D v[] = {
		{D3DXVECTOR4(dx - 0.5f, dy - 0.5f, 1.0f, 1.0f), color, D3DXVECTOR2(u0, v0)},
		{D3DXVECTOR4(dx + tcw - 0.5f, dy - 0.5f, 1.0f, 1.0f), color, D3DXVECTOR2(u1, v0)},
		{D3DXVECTOR4(dx - 0.5f, dy + tch - 0.5f, 1.0f, 1.0f), color, D3DXVECTOR2(u0, v1)},
		{D3DXVECTOR4(dx + tcw - 0.5f, dy + tch - 0.5f, 1.0f, 1.0f), color, D3DXVECTOR2(u1, v1)} };

	Vertex2D* pV;
	pVertexBuffer->Lock(0, 0, (void**)&pV, 0);
	memcpy(pV, v, sizeof(v));
	pVertexBuffer->Unlock();

	// デバイスに利用する頂点バッファを指定する
	pDevice->SetStreamSource(0, pVertexBuffer, 0, sizeof(Vertex2D));

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

void SpriteNormal::SetDrawPos(float x, float y)
{
	dx = x;
	dy = y;
}

void SpriteNormal::SetCutPos(float x, float y)
{
	tcx = x;
	tcy = y;
}

void SpriteNormal::SetCutSize(float width, float height)
{
	tcw = width;
	tch = height;
}