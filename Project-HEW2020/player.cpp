//----------------------------------------------------------------------------
// 
// Project-HEW2020 [player.cpp]
// プレイヤー制御モジュール
// 
// Date:   2020/10/28
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#include "config.h"
#include "player.h"
#include "sprite.h"

//-----------------------------------------------------------------------------
// 定数
//-----------------------------------------------------------------------------
#define PLAYER_WIDTH	(256.0f)
#define PLAYER_HEIGHT	(256.0f)

//-----------------------------------------------------------------------------
// グローバル変数宣言
//-----------------------------------------------------------------------------
static Sprite* g_pSpritePlayer = NULL;
static float g_fRotation = 0.0f;

GamePlayer::GamePlayer()
{
	this->Init();
}

GamePlayer::~GamePlayer()
{
	this->Uninit();
}

void GamePlayer::Init(void)
{
	pos = D3DXVECTOR2(64.0f, (float)SCREEN_HEIGHT - 256.0f);
	dirc = D3DXVECTOR2(0.0f, 9.8f);
	speed = 4.0f;
	velocity = 10.0f;
	hp = 3;
	score = 0;
	bJumping = false;

	g_fRotation = 0.0f;

	g_pSpritePlayer = new SpriteNormal;
	g_pSpritePlayer->LoadTexture(TEXTURE_PLAYER);
	g_pSpritePlayer->SetDrawPos(pos.x, pos.y);
	g_pSpritePlayer->SetCutPos(0, 0);
	//g_pSpritePlayer->SetPolygonSize(PLAYER_WIDTH, PLAYER_HEIGHT);
}

void GamePlayer::Uninit(void)
{
	delete g_pSpritePlayer;
	g_pSpritePlayer = NULL;
}

void GamePlayer::Update(void)
{
	// テクスチャの座標をプレイヤーの座標に更新
	g_pSpritePlayer->SetDrawPos(pos.x, pos.y);
	// 進行方向を長さ１にする
	//D3DXVec2Normalize(&dirc, &dirc);
	// プレイヤー座標の更新（移動方向ｘ速度）
	pos.x += dirc.x * speed;
	speed *= 0.85f;
	if (dirc.y < 9.8f) dirc.y += 0.98f;
	if (dirc.y > 9.8f) dirc.y = 9.8f;
	pos.y += dirc.y;
	// プレイヤー座標の修正
	if (pos.x <= 0.0f)
	{
		this->SetPosition(0.0f, pos.y);
	}
	if (SCREEN_WIDTH <= pos.x + g_pSpritePlayer->GetPolygonSize().x)
	{
		this->SetPosition(SCREEN_WIDTH - g_pSpritePlayer->GetPolygonSize().x, pos.y);
	}
	if (pos.y <= 0.0f)
	{
		this->SetPosition(pos.x, 0.0f);
	}
	if (SCREEN_HEIGHT <= pos.y + g_pSpritePlayer->GetPolygonSize().y)
	{
		this->SetPosition(pos.x, SCREEN_HEIGHT - g_pSpritePlayer->GetPolygonSize().y);
		// 地面に戻ったらジャンプ中の状態から回復
		bJumping = false;
	}
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

int GamePlayer::GetHealth(void)
{
	return this->hp;
}

int GamePlayer::GetScore(void)
{
	return this->score;
}

void GamePlayer::MoveLeft(void)
{
	dirc.x = -1.0f;
	speed = velocity;
}

void GamePlayer::MoveRight(void)
{
	dirc.x = 1.0f;
	speed = velocity;
}

void GamePlayer::SetJump(void)
{
	if (!bJumping)
	{
		// 上方向の速度をあげる
		dirc.y = -15.0f;
		// ジャンプ中の状態に設定（多重ジャンプ防止）
		bJumping = true;
	}
}