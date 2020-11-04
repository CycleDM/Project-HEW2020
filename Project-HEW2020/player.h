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
	void SetPosition(float x, float y);
	// プレイヤーの座標を取得
	D3DXVECTOR2 GetPosition(void);
	// プレイヤーの体力を取得
	int GetHealth(void);
	// プレイヤーのスコアを取得
	int GetScore(void);

	float GetSpeed(void);
	D3DXVECTOR2 GetDirection(void);

	void MoveLeft(void);
	void MoveRight(void);
	void SetJump(void);

private:
	D3DXVECTOR2 pos;	// 座標
	D3DXVECTOR2 dirc;	// 方向
	float speed;		// 速度
	float velocity;		// 加速度
	int hp;				// 体力
	int score;			// スコア
	bool bJumping;		// ジャンプ中の判定
};