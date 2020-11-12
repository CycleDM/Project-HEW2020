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

	float GetSpeed(void);
	D3DXVECTOR2 GetDirection(void);
	bool GetMovingStatus(void);

	void MoveLeft(void);
	void MoveRight(void);
	void Jump(void);

private:
	D3DXVECTOR2 screenPos;	// スクリーン座標
	D3DXVECTOR2 globalPos;	// ワールド座標
	D3DXVECTOR2 dirc;		// 方向
	float speed;			// 速度
	float velocity;			// 加速度

	bool isMoving;			// 移動中の判定
	bool isJumping;			// ジャンプ中の判定
	bool isClimbingUp;
	bool isClimbingDown;
};