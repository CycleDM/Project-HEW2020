//----------------------------------------------------------------------------
// 
// Project-HEW2020 [scene.h]
// シーン基本クラス
// 
// Date:   2020/11/06
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#pragma once

#include <cmath>
#include "config.h"
#include "player.h"
#include "object.h"
#include "overlay.h"
#include "controller.h"
#include "input.h"
#include "d3dfont.h"

//-----------------------------------------------------------------------------
// ゲームシーン・基本クラス - 必ず派生を作ってください
//-----------------------------------------------------------------------------
class GameScene
{
public:
	GameScene();
	virtual ~GameScene();

	virtual void Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual void Debug(void) = 0;

	// プレイヤーのインスタンスを取得（ポインター）
	GamePlayer* GetPlayer(void);
	// 指定の座標に一番近く、特定のオブジェクトを取得
	// 引数:
	//	position	... 指定する座標
	//	objectType	... 特定のオブジェクトタイプ
	GameObject* GetNearestObject(D3DXVECTOR2 position, GameObject::ObjectType objectType);

	// 拡大・縮小参照データを設定
	static void SetGlobalScaling(float scaling);
	// 拡大・縮小参照データを取得
	static float GetGlobalScaling(void);

	static void Freeze(bool bFrozen);

protected:
	// プレイヤーの更新処理
	virtual void UpdatePlayer(void) = 0;
	// オブジェクトの更新処理
	virtual void UpdateObject(void) = 0;
	// オーバーレイの更新処理
	virtual void UpdateOverlay(void) = 0;
	// プレイヤー操作の処理
	virtual void PlayerControl(void);

	static bool isDarkness(void);
	static void isDarkness(bool bDarkness);

	static float fGlobalScaling;						// すべてのテクスチャの拡大・縮小参照データ
	GamePlayer* pPlayer;								// プレイヤーのインスタンス
	GameObject* pObjects[SINGLE_SCENE_OBJECT_MAX];		// ゲームオブジェクトのインスタンス
	GameOverlay* pOverlays[SINGLE_SCENE_OVERLAY_MAX];	// ゲームオーバーレイのインスタンス
	GameOverlay* pUI[UI_OVERLAY_MAX];
	D3DXVECTOR2 fBgScroll;								// シーン・背景の多重スクロールの参照データ
	D3DXVECTOR2 fBgScrollMax;							// シーン・背景の多重スクロールの参照データ（最大値）
	float fGroundHeight;								// 地面の高さ

	static bool bDarkness;
	static bool bFrozen;
};
