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
// スプライトクラス（抽象クラス）
//----------------------------------------------------------------------------
class Sprite
{
public:
	Sprite();
	virtual ~Sprite();

	void LoadTexture(const char*);
	unsigned long GetTextureWidth(void);
	unsigned long GetTextureHeight(void);
	LPDIRECT3DTEXTURE9 GetTexture(void);

	//----------------------------------------------------------
	// スプライトを描画に関連する関数
	// 純粋仮想関数は必ずオーバライドしてください
	// 新しい機能を利用したい場合、派生クラスから新しい関数を作ってください
	//----------------------------------------------------------
	// 色設定
	virtual void SetColor(D3DCOLOR);
	// スプライト描画を実行
	virtual void Draw(void) = 0;
	// スプライト描画の座標を指定
	// 引数:
	//	dx	... 描画座標x（左上指定）
	//	dy	... 描画座標y（左上指定）
	virtual void SetDrawPos(float dx, float dy) = 0;
	// テクスチャの切り取り座標座標を指定
	// 引数:
	//	tcx	... テクスチャの切り取り座標x
	//	tcy	... テクスチャの切り取り座標y
	virtual void SetCutPos(int tcx, int tcy) = 0;
	// テクスチャの切り取り幅を指定
	// 引数:
	//	tcw	... テクスチャの切り取り長さ
	//	tch	... テクスチャの切り取り高さ
	virtual void SetCutRange(int tcw, int tch) = 0;
	// テクスチャの切り取り幅を取得
	virtual D3DXVECTOR2 GetCutRange(void) = 0;
	// ポリゴンサイズを指定
	// 引数:
	//	dw	... ポリゴンサイズ長さ
	//	dh	... ポリゴンサイズ高さ
	virtual void SetPolygonSize(float dw, float dh) = 0;
	// ポリゴンサイズを取得
	virtual float GetPolygonWidth(void) = 0;
	virtual float GetPolygonHeight(void) = 0;
	// テクスチャの回転角度を指定
	// 引数:
	//	cx	... 回転の中心座標x
	//	cy	... 回転の中心座標y
	//	angle	... テクスチャの回転角度
	//	デフォルトはすべて 0.0f -> ポリゴンの左上
	virtual void SetRotation(float cx, float cy, float angle) = 0;
	// テクスチャの反転処理（左右）
	// 引数:
	//	true	... 反転する
	//	false	... 反転しない
	//	デフォルトは反転しない状態
	virtual void SetHorizontalFlip(bool bFlip) = 0;
	// テクスチャの反転処理（上下）
	// 引数:
	//	true	... 反転する
	//	false	... 反転しない
	//	デフォルトは反転しない状態
	virtual void SetVerticalFlip(bool bFlip) = 0;
	// メンバー変数の初期化処理
	virtual void Init(void) = 0;

protected:
	// 派生クラスと共通の変数なのでstaticに指定
	static LPDIRECT3DDEVICE9 pDevice;
	static LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;
	static LPDIRECT3DINDEXBUFFER9 pIndexBuffer;
	static bool isDeviceInit;

	LPDIRECT3DTEXTURE9 pTexture;
	D3DCOLOR color;
	char filename[TEXTURE_FILENAME_MAX];
	unsigned long txWidth, txHeight;

protected:
	float dx, dy;
	float dw, dh;
	float cx, cy;
	float angle;
	int tcx, tcy;
	int tcw, tch;
	bool bHorizontalFlip;
	bool bVerticalFlip;
};

//----------------------------------------------------------------------------
// スプライト派生クラス - SpriteNormal
//----------------------------------------------------------------------------
class SpriteNormal : public Sprite
{
public:
	SpriteNormal();
	SpriteNormal(const char* pFileName);
	~SpriteNormal();

	// スプライト描画の座標を指定
	virtual void SetDrawPos(float dx, float dy);
	// テクスチャの切り取り座標座標を指定
	virtual void SetCutPos(int tcx, int tcy);
	// テクスチャの切り取り幅を指定
	virtual void SetCutRange(int tcw, int tch);
	// ポリゴンサイズを指定
	virtual void SetPolygonSize(float dw, float dh);
	// テクスチャの切り取り幅を取得
	virtual D3DXVECTOR2 GetCutRange(void);
	// ポリゴンサイズを取得
	virtual float GetPolygonWidth(void);
	virtual float GetPolygonHeight(void);
	// テクスチャの回転角度を指定
	virtual void SetRotation(float cx, float cy, float angle);
	// テクスチャ反転の設定（左右）
	virtual void SetHorizontalFlip(bool bFlip);
	// テクスチャ反転の設定（上下）
	virtual void SetVerticalFlip(bool bFlip);
	// スプライト描画を実行
	virtual void Draw(void);
	// メンバー変数の初期化処理
	virtual void Init(void);
};
