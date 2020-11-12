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
#include "game.h"
#include "scene.h"

//-----------------------------------------------------------------------------
// 定数
//-----------------------------------------------------------------------------
// プレイヤーのテクスチャのサイズ（フレーム一個分）
#define PLAYER_TEXTURE_WIDTH	(64)
#define PLAYER_TEXTURE_HEIGHT	(64)
// 描画サイズ
#define PLAYER_DRAW_WIDTH	((float)PLAYER_TEXTURE_WIDTH * GameScene::GetGlobalScaling())
#define PLAYER_DRAW_HEIGHT	((float)PLAYER_TEXTURE_HEIGHT * GameScene::GetGlobalScaling())
// 実際のサイズ・コリジョンのサイズ
#define PLAYER_WIDTH		(PLAYER_DRAW_WIDTH - 96.0f)
#define PLAYER_HEIGHT		(PLAYER_DRAW_HEIGHT)

//-----------------------------------------------------------------------------
// グローバル変数宣言
//-----------------------------------------------------------------------------
static Sprite* g_pSpritePlayer = NULL;
static int g_nMoveFrame = 0;
static int g_nMoveAnimeCnt = 0;

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
	g_nMoveFrame = 0;
	g_nMoveAnimeCnt = 0;

	screenPos = D3DXVECTOR2(64.0f, (float)SCREEN_HEIGHT);
	globalPos = D3DXVECTOR2(64.0f, (float)SCREEN_HEIGHT);
	dirc = D3DXVECTOR2(0.0f, 9.8f);
	speed = 0.0f;
	velocity = 5.0f;
	isMoving = false;
	isJumping = false;
	isClimbingUp = false;

	g_pSpritePlayer = new SpriteNormal;
	g_pSpritePlayer->LoadTexture(TEXTURE_PLAYER);
	g_pSpritePlayer->SetDrawPos(screenPos.x - PLAYER_DRAW_WIDTH / 2, screenPos.y - PLAYER_DRAW_HEIGHT / 2);
	g_pSpritePlayer->SetCutPos(0, 0);
	g_pSpritePlayer->SetCutRange(64, 64);
	g_pSpritePlayer->SetPolygonSize(PLAYER_DRAW_WIDTH, PLAYER_DRAW_HEIGHT);

	// コリジョンを作成
	collision = new Collision;
	collision->SetSize(PLAYER_WIDTH, PLAYER_HEIGHT);
	collision->SetPosition(globalPos.x, globalPos.y);
}

void GamePlayer::Uninit(void)
{
	delete g_pSpritePlayer;
	g_pSpritePlayer = NULL;
}

void GamePlayer::Update(void)
{
	// 進行方向を長さ１にする
	//D3DXVec2Normalize(&dirc, &dirc);
	// プレイヤー座標の更新（移動方向ｘ速度）
	globalPos.x += dirc.x * speed;
	speed *= 0.8f;
	if (speed < 0.3f)
	{
		speed = 0.0f;
		isMoving = false;
	}
	if (dirc.y < 9.8f && !isClimbingUp) dirc.y += 0.98f;
	if (dirc.y > 9.8f) dirc.y = 9.8f;
	globalPos.y += dirc.y;

	// コリジョンの座標をプレイヤーの座標に更新
	collision->SetPosition(globalPos.x, globalPos.y);

	// Animation
	if (isMoving)
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
	// テクスチャの座標をプレイヤーのスクリーン座標に更新
	g_pSpritePlayer->SetDrawPos(screenPos.x - PLAYER_DRAW_WIDTH / 2, screenPos.y - PLAYER_DRAW_HEIGHT / 2);
	g_pSpritePlayer->Draw();
}

void GamePlayer::SetScreenPos(float x, float y)
{
	this->screenPos.x = x;
	this->screenPos.y = y;
}

void GamePlayer::SetGlobalPos(float x, float y)
{
	this->globalPos.x = x;
	this->globalPos.y = y;
}

D3DXVECTOR2 GamePlayer::GetScreenPos(void)
{
	return this->screenPos;
}

D3DXVECTOR2 GamePlayer::GetGlobalPos(void)
{
	return this->globalPos;
}

float GamePlayer::GetPolygonWidth(void)
{
	return g_pSpritePlayer->GetPolygonWidth();
}

float GamePlayer::GetPolygonHeight(void)
{
	return g_pSpritePlayer->GetPolygonHeight();
}

float GamePlayer::GetSpeed(void)
{
	return this->speed;
}

D3DXVECTOR2 GamePlayer::GetDirection(void)
{
	return this->dirc;
}

bool GamePlayer::GetMovingStatus(void)
{
	return this->isMoving;
}

Collision* GamePlayer::GetCollision(void)
{
	return this->collision;
}

void GamePlayer::MoveLeft(void)
{
	isMoving = true;
	dirc.x = -1.0f;
	speed = velocity;
	g_pSpritePlayer->SetHorizontalFlip(true);
}

void GamePlayer::MoveRight(void)
{
	isMoving = true;
	dirc.x = 1.0f;
	speed = velocity;
	g_pSpritePlayer->SetHorizontalFlip(false);
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