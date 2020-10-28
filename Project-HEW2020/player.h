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

class Player
{
public:
	Player();
	~Player();

	void Init(void);
	void Update(void);
	void Draw(void);
	void SetPos(float x, float y);
	D3DXVECTOR2 GetPos(void);

private:
	D3DXVECTOR2 pos;	// 座標
	D3DXVECTOR2 dirc;	// 方向
	float speed;		// 速度
	int hp;				// 体力
	int score;			// スコア
};