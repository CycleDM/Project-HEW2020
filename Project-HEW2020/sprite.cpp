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

//----------------------------------------------------------------------------
// グローバル変数宣言、初期化
//----------------------------------------------------------------------------
LPDIRECT3DDEVICE9 Sprite::pDevice = NULL;
LPDIRECT3DVERTEXBUFFER9 Sprite::pVertexBuffer = NULL;
LPDIRECT3DINDEXBUFFER9 Sprite::pIndexBuffer = NULL;
bool Sprite::isDeviceInit = false;

//----------------------------------------------------------------------------
// 構造体宣言
//----------------------------------------------------------------------------
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
	do
	{
		// デバイスとバッファの初期化は一回だけ行う
		if (!isDeviceInit)
		{
			pDevice = D3DUtility::GetDevice();
			if (!pDevice)
			{
				MessageBox(NULL, "Direct3Dデバイスの取得に失敗しました", "エラー", MB_OK);
				// デバイスの取得に失敗のため、進まない
				break;
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

			// 初期化完成
			isDeviceInit = true;
		}
	} while (0);

	color = 0xffffffff;
	pTexture = NULL;
	txWidth = 0;
	txHeight = 0;
	filename[0] = 0;

	dx = dy = dw = dh = 0.0f;
	cx = cy = angle = 0.0f;
	tcx = tcy = 0;
	tcw = tch = 0;
	bHorizontalFlip = bVerticalFlip = false;
}

Sprite::~Sprite()
{
	if (pVertexBuffer)
	{
		pVertexBuffer->Release();
		pVertexBuffer = NULL;
	}
	if (pIndexBuffer)
	{
		pIndexBuffer->Release();
		pIndexBuffer = NULL;
	}
	if (pTexture)
	{
		pTexture->Release();
		pTexture = NULL;
	}
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
		char msg[128] = {};
		strcat(msg, "テクスチャの読み込みに失敗しました\nファイル名：");
		strcat(msg, filename);
		MessageBox(NULL, msg, "エラー", MB_OK);
	}
}

unsigned long Sprite::GetTextureWidth(void)
{
	return txWidth;
}
unsigned long Sprite::GetTextureHeight(void)
{
	return txHeight;
}

LPDIRECT3DTEXTURE9 Sprite::GetTexture(void)
{
	return pTexture;
}

void Sprite::SetColor(D3DCOLOR color)
{
	this->color = color;
}

//----------------------------------------------------------------------------
// スプライト派生クラス - SpriteNormal
//----------------------------------------------------------------------------
SpriteNormal::SpriteNormal()
{
	// 初期化処理
	Init();
}
// オーバロード
SpriteNormal::SpriteNormal(const char* pFileName)
{
	// 初期化処理
	Init();
	// テクスチャの読み込み
	LoadTexture(pFileName);
}

SpriteNormal::~SpriteNormal()
{

}

void SpriteNormal::Init(void)
{
	dx = dy = dw = dh = 0.0f;
	cx = cy = angle = 0.0f;
	tcx = tcy = 0;
	tcw = tch = 0;
	bHorizontalFlip = bVerticalFlip = false;
}

void SpriteNormal::Draw(void)
{
	// デバイスにFVFの設定をする
	pDevice->SetFVF(FVF_VERTEX2D);

	// デバイスにテクスチャの設定をする
	pDevice->SetTexture(0, pTexture);

	// ポリゴンのサイズはテクスチャサイズ
	unsigned long w = GetTextureWidth();
	unsigned long h = GetTextureHeight();

	// 切り取り座標は0だったらテクスチャのデフォルトサイズに設定
	if (!tcw || !tch)
	{
		tcw = GetTextureWidth();
		tch = GetTextureHeight();
	}
	// ポリゴンサイズは0だったらテクスチャのデフォルトサイズに設定
	if (!dw || !dh)
	{
		dw = (float)GetTextureWidth();
		dh = (float)GetTextureHeight();
	}

	// テクスチャ切り取りUV座標
	float u0, u1, v0, v1;
	u0 = (float)tcx / w;
	u1 = (float)(tcx + tcw) / w;
	v0 = (float)tcy / h;
	v1 = (float)(tcy + tch) / h;
	// UV反転処理
	if (bHorizontalFlip)
	{
		u0 = (float)(tcx + tcw) / w;
		u1 = (float)tcx / w;
	}
	if (bVerticalFlip)
	{
		v0 = (float)(tcy + tch) / h;
		v1 = (float)tcy / h;
	}

	// 頂点データ
	Vertex2D v[] = {
		{D3DXVECTOR4(-0.5f, -0.5f, 1.0f, 1.0f), color, D3DXVECTOR2(u0, v0)},
		{D3DXVECTOR4(dw - 0.5f, -0.5f, 1.0f, 1.0f), color, D3DXVECTOR2(u1, v0)},
		{D3DXVECTOR4(-0.5f, dh - 0.5f, 1.0f, 1.0f), color, D3DXVECTOR2(u0, v1)},
		{D3DXVECTOR4(dw - 0.5f, dh - 0.5f, 1.0f, 1.0f), color, D3DXVECTOR2(u1, v1)} };

	// 平行移動行列
	D3DXMATRIX mtxTranslationC;
	D3DXMatrixTranslation(&mtxTranslationC, -cx, -cy, 0.0f);

	D3DXMATRIX mtxTranslationI;
	D3DXMatrixTranslation(&mtxTranslationI, cx + dx, cy + dy, 0.0f);

	// 回転行列
	D3DXMATRIX mtxRotation;
	D3DXMatrixRotationZ(&mtxRotation, angle);

	D3DXMATRIX mtxScale;
	D3DXMatrixScaling(&mtxScale, 1.0f, 1.0f, 1.0f);

	// 行列の合成
	D3DXMATRIX mtxWorld;
	mtxWorld = mtxTranslationC * mtxScale * mtxRotation * mtxTranslationI;

	// 座標変換
	for (int i = 0; i < 4; i++)
	{
		D3DXVec4Transform(&v[i].Position, &v[i].Position, &mtxWorld);
	}

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2D));
}

void SpriteNormal::SetDrawPos(float dx, float dy)
{
	this->dx = dx;
	this->dy = dy;
}
void SpriteNormal::SetCutPos(int tcx, int tcy)
{
	this->tcx = tcx;
	this->tcy = tcy;
}
void SpriteNormal::SetCutRange(int tcw, int tch)
{
	this->tcw = tcw;
	this->tch = tch;
}

int SpriteNormal::GetCutWidth(void)
{
	return tcw;
}

int SpriteNormal::GetCutHeight(void)
{
	return tch;
}

void SpriteNormal::SetPolygonSize(float dw, float dh)
{
	this->dw = dw;
	this->dh = dh;
}
float SpriteNormal::GetPolygonWidth(void)
{
	return dw;
}
float SpriteNormal::GetPolygonHeight(void)
{
	return dh;
}

void SpriteNormal::SetRotation(float cx, float cy, float angle)
{
	this->cx = cx;
	this->cy = cy;
	this->angle = angle;
}
void SpriteNormal::SetHorizontalFlip(bool bFlip)
{
	this->bHorizontalFlip = bFlip;
}
void SpriteNormal::SetVerticalFlip(bool bFlip)
{
	this->bVerticalFlip = bFlip;
}