//----------------------------------------------------------------------------
// 
// Project-HEW2020 [sprite.h]
// テクスチャー、スプライト制御
// 
// Date:   2020/10/25
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#pragma once

#include <d3dx9.h>

#define TEXTURE_FILENAME_MAX (64)	// テクスチャファイル名最大文字数
#define TEXTURE_MAX (1024)			// テクスチャ管理最大数

class Sprite
{
public:
	Sprite();
	virtual ~Sprite();

	void LoadTexture(const char* pFileName);
	unsigned long GetTextureWidth(void);
	unsigned long GetTextureHeight(void);
	LPDIRECT3DTEXTURE9 GetTexture(void);

	// スプライトを描画に関連する関数（純粋仮想関数を利用すれば、必ずオーバライドしてください）
	virtual void Draw(void) = 0;
	virtual void SetDrawPos(float x, float y) = 0;
	virtual void SetCutPos(float x, float y) = 0;
	virtual void SetCutSize(float width, float height) = 0;
	virtual void SetColor(D3DCOLOR color_to_set);

protected:
	LPDIRECT3DDEVICE9 pDevice;
	LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;
	LPDIRECT3DINDEXBUFFER9 pIndexBuffer;
	LPDIRECT3DTEXTURE9 pTexture;
	D3DCOLOR color;
	unsigned long txWidth, txHeight;
	char filename[TEXTURE_FILENAME_MAX];
};

class SpriteNormal : public Sprite
{
public:
	//SpriteNormal();
	//~SpriteNormal();

	// スプライト描画の各種値を指定
	//
	// 引数:
	//	dx		... 描画座標x（左上指定）
	//	dy		... 描画座標y（左上指定）
	//	tcx		... テクスチャの切り取り座標x
	//	tcy		... テクスチャの切り取り座標y
	//	tcw		... テクスチャの切り取り幅
	//	tch		... テクスチャの切り取り高さ
	void SetDrawPos(float x, float y);
	void SetCutPos(float x, float y);
	void SetCutSize(float width, float height);
	void Draw(void);
private:
	float dx, dy;
	int tcx,tcy, tcw, tch;
};