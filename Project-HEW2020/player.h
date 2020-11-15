//----------------------------------------------------------------------------
// 
// Project-HEW2020 [player.h]
// プレイヤー制御モジュール
// 
// Date:   2020/10/28
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#pragma once

#include <d3dx9.h>
#include "collision.h"
#include "sprite.h"
#include "animator.h"

class GamePlayer
{
public:
	GamePlayer();
	~GamePlayer();

	void Init(void);
	void Update(void);
	void Draw(void);
	void Uninit(void);
	// プレイヤーの座標を設定
	void SetScreenPos(float x, float y);
	void SetGlobalPos(float x, float y);
	// プレイヤーの座標を取得
	D3DXVECTOR2 GetScreenPos(void);
	D3DXVECTOR2 GetGlobalPos(void);
	float GetPolygonWidth(void);
	float GetPolygonHeight(void);

	Collision* GetCollision(void);
	D3DXVECTOR2 GetDirection(void);
	float GetSpeed(void);

	bool isMoving(void);
	void isMoving(bool bState);
	bool isClimbing(void);
	void isClimbing(bool bState);
	bool isOnFloor(void);
	void isOnFloor(bool bState);

	void MoveLeft(void);
	void MoveRight(void);
	void ClimbUp(void);
	void ClimbDown(void);
	void Jump(void);

private:
	Sprite* pSprite;
	D3DXVECTOR2 screenPos;			// スクリーン座標
	D3DXVECTOR2 globalPos;			// ワールド座標
	D3DXVECTOR2 dirc;				// 方向
	float speed;					// 速度
	float velocity;					// 加速度

	bool bMoving;					// 移動中の判定
	bool bJumping;					// ジャンプ中の判定
	bool bClimbingUp;
	bool bClimbingDown;
	bool bOnFloor;

	Collision* pCollision;			// プレイヤーのコリジョン
	Animator* pAnimator;			// アニメーション制御
};