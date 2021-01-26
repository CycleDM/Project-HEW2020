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
	// プレイヤーのテクスチャの幅を取得（コリジョンは別）
	float GetPolygonWidth(void);
	float GetPolygonHeight(void);

	Collision* GetCollision(void);
	D3DXVECTOR2 GetDirection(void);
	float GetSpeed(void);

	bool isWalking(void);
	void isWalking(bool bState);
	bool isClimbing(void);
	void isClimbing(bool bState);
	bool isOnLadder(void);
	void isOnLadder(bool bState);

	void MoveLeft(void);
	void MoveRight(void);
	void MoveUp(void);
	void MoveDown(void);
	void Jump(void);
	void SetWalkingSpeed(float speed);

private:
	Sprite* pSprite;
	D3DXVECTOR2 screenPos;			// スクリーン座標
	D3DXVECTOR2 globalPos;			// ワールド座標
	D3DXVECTOR2 dirc;				// 方向
	float speed;					// 速度
	float velocity;					// 加速度
	int currentFloor;				// プレイヤーが何階目にいる

	bool bWalking;					// 移動中の判定
	bool bJumping;					// ジャンプ中の判定
	bool bClimbingUp;
	bool bClimbingDown;
	bool bOnLadder;

	Collision* pCollision;			// プレイヤーのコリジョン
	Animator* pAnimator;			// アニメーション制御
};