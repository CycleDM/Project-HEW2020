//----------------------------------------------------------------------------
// 
// Project-HEW2020 [player.cpp]
// プレイヤー制御モジュール
// 
// Date:   2020/10/28
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#include <cmath>
#include "config.h"
#include "player.h"
#include "sprite.h"
#include "object.h"
#include "test_scene.h"
#include "game.h"

//-----------------------------------------------------------------------------
// 定数
//-----------------------------------------------------------------------------
#define PLAYER_WIDTH	(64.0f * 3.3f)
#define PLAYER_HEIGHT	(64.0f * 3.3f)

//-----------------------------------------------------------------------------
// グローバル変数宣言
//-----------------------------------------------------------------------------
static Sprite* g_pSpritePlayer = NULL;
static int g_nMoveFrame = 0;
static int g_nMoveAnimeCnt = 0;

void GamePlayer::Init(void)
{
	pos = D3DXVECTOR2(64.0f, (float)SCREEN_HEIGHT);
	dirc = D3DXVECTOR2(0.0f, 9.8f);
	speed = 0.0f;
	velocity = 5.0f;
	hp = 3;
	score = 0;
	isJumping = false;
	isClimbingUp = false;

	g_nMoveFrame = 0;
	g_nMoveAnimeCnt = 0;

	g_pSpritePlayer = new SpriteNormal;
	g_pSpritePlayer->LoadTexture(TEXTURE_PLAYER);
	g_pSpritePlayer->SetDrawPos(pos.x - PLAYER_WIDTH / 2, pos.y - PLAYER_HEIGHT / 2);
	g_pSpritePlayer->SetCutPos(0, 0);
	g_pSpritePlayer->SetCutRange(64, 64);
	g_pSpritePlayer->SetPolygonSize(PLAYER_WIDTH, PLAYER_HEIGHT);
	//g_pSpritePlayer->SetColor(D3DCOLOR_RGBA(255, 255, 255, 100));
}

void GamePlayer::Uninit(void)
{
	delete g_pSpritePlayer;
	g_pSpritePlayer = NULL;
}

void GamePlayer::Update(void)
{
	// テクスチャの座標をプレイヤーの座標に更新
	g_pSpritePlayer->SetDrawPos(pos.x - PLAYER_WIDTH / 2, pos.y - PLAYER_HEIGHT / 2);
	// 進行方向を長さ１にする
	//D3DXVec2Normalize(&dirc, &dirc);
	// プレイヤー座標の更新（移動方向ｘ速度）
	pos.x += dirc.x * speed;
	speed *= 0.8f;
	if (speed < 0.3f) speed = 0.0f;
	//if (dirc.y < 9.8f && !isClimbingUp) dirc.y += 0.98f;
	if (dirc.y > 9.8f) dirc.y = 9.8f;
	pos.y += dirc.y;
	// プレイヤー座標の修正
	if (pos.x <= 0.0f + PLAYER_WIDTH / 2)
	{
		this->SetPosition(0.0f + PLAYER_WIDTH / 2, pos.y);
	}
	if ((float)SCREEN_WIDTH <= pos.x + PLAYER_WIDTH / 2)
	{
		this->SetPosition(SCREEN_WIDTH - PLAYER_WIDTH / 2, pos.y);
	}
	if (pos.y <= 0.0f + PLAYER_HEIGHT / 2)
	{
		this->SetPosition(pos.x, 0.0f + PLAYER_HEIGHT / 2);
	}
	if ((float)SCREEN_HEIGHT - 64.0f <= pos.y + PLAYER_HEIGHT / 2)
	{
		this->SetPosition(pos.x, (float)SCREEN_HEIGHT - 64.0f - PLAYER_HEIGHT / 2);
		// 地面に戻ったらジャンプ中の状態から回復
		this->isJumping = false;
		this->isClimbingUp = false;
	}
	if (pos.y < (float)SCREEN_HEIGHT - 64.0f)
	{
		TestScene* scene = Game_GetScene();
		GameObject* floor = scene->GetNearestFloor();
		do
		{
			if (NULL == floor) break;

			// Climb to floor
			if (this->isClimbingUp && this->pos.y < floor->GetPosition().y)
			{
				this->pos.y = floor->GetPosition().y - 100.0f;
			}
			// Climb down
			if (this->isClimbingDown)
			{
				break;
			}
			// Stand on floor
			if (!this->isClimbingDown && floor->GetPosition().y - floor->GetPolygonHeight() <= pos.y + g_pSpritePlayer->GetPolygonHeight())
			{
				this->SetPosition(pos.x, 200.0f);
			}
			// Edge
			if (this->pos.x < floor->GetPosition().x - 600.0f)
			{
				this->SetPosition(floor->GetPosition().x - 600.0f, pos.y);
			}
			if (this->pos.x > floor->GetPosition().x + 500.0f)
			{
				this->SetPosition(floor->GetPosition().x + 500.0f, pos.y);
			}

		} while (0);
		
	}

	// Animation
	if (speed > 0.0f)
	{
		g_nMoveFrame++;
		if (g_nMoveFrame >= 8)
		{
			g_nMoveAnimeCnt++;
			g_nMoveFrame = 0;
		}
		if (g_nMoveAnimeCnt > 7)
		{
			g_nMoveAnimeCnt = 0;
		}
	}
	else 
	{
		g_nMoveFrame = 0;
		g_nMoveAnimeCnt = 0;
	}
	g_pSpritePlayer->SetCutPos(64 * (g_nMoveAnimeCnt % 4), 64 * (g_nMoveAnimeCnt / 2));
}

void GamePlayer::Draw(void)
{
	g_pSpritePlayer->Draw();
}

void GamePlayer::SetPosition(float x, float y)
{
	this->pos.x = x;
	this->pos.y = y;
}

D3DXVECTOR2 GamePlayer::GetPosition(void)
{
	return this->pos;
}

float GamePlayer::GetPolygonWidth(void)
{
	return g_pSpritePlayer->GetPolygonWidth();
}

float GamePlayer::GetPolygonHeight(void)
{
	return g_pSpritePlayer->GetPolygonHeight();
}

int GamePlayer::GetHealth(void)
{
	return this->hp;
}

int GamePlayer::GetScore(void)
{
	return this->score;
}

float GamePlayer::GetSpeed(void)
{
	return this->speed;
}

D3DXVECTOR2 GamePlayer::GetDirection(void)
{
	return this->dirc;
}

void GamePlayer::MoveLeft(void)
{
	dirc.x = -1.0f;
	speed = velocity;
	g_pSpritePlayer->SetHorizontalFlip(true);
}

void GamePlayer::MoveRight(void)
{
	dirc.x = 1.0f;
	speed = velocity;
	g_pSpritePlayer->SetHorizontalFlip(false);
}

void GamePlayer::ClimbUp(void)
{
	dirc.y = -5.0f;
}

void GamePlayer::ClimbDown(void)
{
	dirc.y = 5.0f;
}

void GamePlayer::SetClimbUpStatus(bool isClimbing)
{
	this->isClimbingUp = isClimbing;
}

void GamePlayer::SetClimbDownStatus(bool isClimbing)
{
	this->isClimbingDown = isClimbing;
}

void GamePlayer::Jump(void)
{
	if (!isJumping)
	{
		// 上方向の速度をあげる
		dirc.y = -15.0f;
		// ジャンプ中の状態に設定（多重ジャンプ防止）
		isJumping = true;
	}
}