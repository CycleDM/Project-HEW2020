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

//----------------------------------------------------------------------------
// スプライト基本クラス（抽象クラス）
//----------------------------------------------------------------------------
class Sprite
{
public:
	Sprite();
	virtual ~Sprite();

	void LoadTexture(const char* pFileName);
	unsigned long GetTextureWidth(void);
	unsigned long GetTextureHeight(void);
	LPDIRECT3DTEXTURE9 GetTexture(void);

	// スプライトを描画に関連する関数
	// 純粋仮想関数は必ずオーバライドしてください
	// 新しい機能を利用したい場合、派生クラスから新しい関数を作ってください
	virtual void Draw(void) = 0;
	// スプライト描画の座標を指定
	virtual void SetDrawPos(float, float) = 0;
	// テクスチャの反転処理（左右）
	void SetHorizontalFlip(bool);
	// テクスチャの反転処理（上下）
	void SetVerticalFlip(bool);
	// 色設定
	virtual void SetColor(D3DCOLOR color_to_set);

protected:
	// 派生クラスと共通の変数なのでstaticに指定
	static LPDIRECT3DDEVICE9 pDevice;
	static LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;
	static LPDIRECT3DINDEXBUFFER9 pIndexBuffer;
	static bool isDeviceInit;

	LPDIRECT3DTEXTURE9 pTexture;
	D3DCOLOR color;
	unsigned long txWidth, txHeight;
	char filename[TEXTURE_FILENAME_MAX];
};

//----------------------------------------------------------------------------
// スプライト派生クラス - SpriteNormal - これを基本クラスとして派生してもOK
//----------------------------------------------------------------------------
class SpriteNormal : public Sprite
{
public:
	SpriteNormal();
	SpriteNormal(const char* pFileName);
	//~SpriteNormal();

	// スプライト描画の座標を指定
	// 引数:
	//	dx	... 描画座標x（左上指定）
	//	dy	... 描画座標y（左上指定）
	virtual void SetDrawPos(float dx, float dy);
	// テクスチャの切り取り座標座標を指定
	// 引数:
	//	tcx	... テクスチャの切り取り座標x
	//	tcy	... テクスチャの切り取り座標y
	virtual void SetCutPos(int tcx, int tcy);
	// テクスチャの切り取り幅を指定
	// 引数:
	//	tcw	... テクスチャの切り取り長さ
	//	tch	... テクスチャの切り取り高さ
	virtual void SetSize(int tcw, int tch);
	// テクスチャ反転の設定（左右）
	// 引数:
	//	true	... 反転する
	//	false	... 反転しない
	//	デフォルトは反転しない状態
	virtual void SetHorizontalFlip(bool boolean);
	// テクスチャ反転の設定（上下）
	// 引数:
	//	true	... 反転する
	//	false	... 反転しない
	//	デフォルトは反転しない状態
	virtual void SetVerticalFlip(bool boolean);
	// スプライト描画を実行
	virtual void Draw(void);

protected:
	float dx, dy;
	int tcx, tcy, tcw, tch;
	bool bHorizontalFlip, bVerticalFlip;
};
