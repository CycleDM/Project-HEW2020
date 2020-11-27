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
#include "game.h"
#include "scene.h"

//-----------------------------------------------------------------------------
// 定数
//-----------------------------------------------------------------------------
// プレイヤーのテクスチャのサイズ（フレーム一個分）
#define PLAYER_TEXTURE_CUT_WIDTH	(64)
#define PLAYER_TEXTURE_CUT_HEIGHT	(64)
// 描画サイズ
#define PLAYER_DRAW_WIDTH	((float)PLAYER_TEXTURE_CUT_WIDTH * GameScene::GetGlobalScaling())
#define PLAYER_DRAW_HEIGHT	((float)PLAYER_TEXTURE_CUT_HEIGHT * GameScene::GetGlobalScaling())
// 実際のサイズ（コリジョンサイズ）
#define PLAYER_WIDTH		(((float)PLAYER_TEXTURE_CUT_WIDTH - 32.0f) * GameScene::GetGlobalScaling())
#define PLAYER_HEIGHT		(((float)PLAYER_TEXTURE_CUT_HEIGHT - 0.0f) * GameScene::GetGlobalScaling())

//-----------------------------------------------------------------------------
// グローバル変数宣言
//-----------------------------------------------------------------------------
static Sprite* pActiveSprite = NULL;	// 使用中のスプライトのポインター

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
	screenPos = globalPos = D3DXVECTOR2(64.0f, (float)SCREEN_HEIGHT);
	dirc = D3DXVECTOR2(0.0f, GAME_GRAVITY);
	speed = 0.0f;
	velocity = 6.0f;
	currentFloor = 1;

	bWalking = false;
	bJumping = false;
	bClimbingUp = false;
	bOnLadder = false;

	// プレイヤーのテクスチャ(Sprite)を作成
	int n = 3;
	pSprite = new SpriteNormal[n];
	(pSprite + 0)->LoadTexture(TEXTURE_PLAYER);
	(pSprite + 1)->LoadTexture(TEXTURE_PLAYER_CLIMBING);
	(pSprite + 2)->LoadTexture(TEXTURE_PLAYER_CLIMBING_PAUSED);
	for (int i = 0; i < n; i++)
	{
		(pSprite + i)->SetDrawPos(screenPos.x - PLAYER_DRAW_WIDTH / 2, screenPos.y - PLAYER_DRAW_HEIGHT / 2);
		(pSprite + i)->SetCutPos(0, 0);
		(pSprite + i)->SetCutRange(PLAYER_TEXTURE_CUT_WIDTH, PLAYER_TEXTURE_CUT_HEIGHT);
		(pSprite + i)->SetPolygonSize(PLAYER_DRAW_WIDTH, PLAYER_DRAW_HEIGHT);
	}

	pActiveSprite = pSprite;

	/*----------実験コード-------------------------------------------------------------------------*/
	Sprite* test = NULL;
	test = new SpriteNormal[2];
	test->LoadTexture(TEXTURE_PLAYER);
	test->SetDrawPos(screenPos.x - PLAYER_DRAW_WIDTH / 2, screenPos.y - PLAYER_DRAW_HEIGHT / 2);
	test->SetCutPos(0, 0);
	test->SetCutRange(PLAYER_TEXTURE_CUT_WIDTH, PLAYER_TEXTURE_CUT_HEIGHT);
	test->SetPolygonSize(PLAYER_DRAW_WIDTH, PLAYER_DRAW_HEIGHT);
	
	(test+1)->LoadTexture(TEXTURE_PLAYER);
	(test+1)->SetDrawPos(screenPos.x - PLAYER_DRAW_WIDTH / 2, screenPos.y - PLAYER_DRAW_HEIGHT / 2);
	(test+1)->SetCutPos(0, 0);
	(test+1)->SetCutRange(PLAYER_TEXTURE_CUT_WIDTH, PLAYER_TEXTURE_CUT_HEIGHT);
	(test+1)->SetPolygonSize(PLAYER_DRAW_WIDTH, PLAYER_DRAW_HEIGHT);
	
	delete[] test;
	test = NULL;
	/*----------実験コード-------------------------------------------------------------------------*/

	// コリジョンを作成
	pCollision = new Collision;
	pCollision->SetSize(PLAYER_WIDTH, PLAYER_HEIGHT);
	pCollision->SetPosition(globalPos.x, globalPos.y);

	// アニメーション制御用のインスタンスを作成
	pAnimator = new Animator;
	pAnimator->Init(pActiveSprite);
	pAnimator->Preset(4, 2, 8);
}

void GamePlayer::Uninit(void)
{
	// メモリ解放
	delete[] pSprite;
	pSprite = NULL;

	delete pCollision;
	pCollision = NULL;

	delete pAnimator;
	pAnimator = NULL;
}

void GamePlayer::Update(void)
{
	/*----------アニメーション-------------------------------------------------------------------------*/
	if (isWalking())
	{
		pActiveSprite = pSprite;
		pAnimator->Preset(4, 2, 8);
		pAnimator->Play(pActiveSprite);
	}
	else if (bClimbingUp)
	{
		pActiveSprite = pSprite + 1;
		pAnimator->Preset(5, 5, 5);
		pAnimator->Play(pActiveSprite);
	}
	else if (bClimbingDown)
	{
		pActiveSprite = pSprite + 2;
		pAnimator->Preset(1, 1, 0);
		pAnimator->Play(pActiveSprite);
	}
	else if (!isClimbing() && isOnLadder())
	{
		pAnimator->Pause(pActiveSprite);
	}
	else
	{
		pActiveSprite = pSprite;
		pAnimator->Reset(pSprite);
	}
	/*----------アニメーション-------------------------------------------------------------------------*/

	// x座標の更新（移動方向ｘ速度）
	globalPos.x += dirc.x * speed;
	// 速度の減衰
	speed *= 0.8f;
	if (speed < 0.3f)
	{
		speed = 0.0f;
		bWalking = false;
	}

	// 単純な重力システム
	if (dirc.y < GAME_GRAVITY && !isClimbing())
		dirc.y += GAME_GRAVITY;

	if (dirc.y > GAME_GRAVITY)
		dirc.y = GAME_GRAVITY;

	// 特殊：プレイヤーがはしごに残る（移動しない）
	if (!isClimbing() && isOnLadder())
	{
		dirc.y = 0.0f;
	}
	// y座標の更新
	globalPos.y += dirc.y;

	// コリジョンの座標とプレイヤー座標の同期
	pCollision->SetPosition(globalPos.x, globalPos.y);
}

void GamePlayer::Draw(void)
{
	// テクスチャの座標をプレイヤーのスクリーン座標に更新
	pActiveSprite->SetDrawPos(screenPos.x - PLAYER_DRAW_WIDTH / 2, screenPos.y - PLAYER_DRAW_HEIGHT / 2);

	pActiveSprite->Draw();
}

//-----------------------------------------------------------------------------
// 数値の設定および取得
//-----------------------------------------------------------------------------
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
	return pSprite->GetPolygonWidth();
}

float GamePlayer::GetPolygonHeight(void)
{
	return pSprite->GetPolygonHeight();
}

Collision* GamePlayer::GetCollision(void)
{
	return this->pCollision;
}

float GamePlayer::GetSpeed(void)
{
	return this->speed;
}

D3DXVECTOR2 GamePlayer::GetDirection(void)
{
	return this->dirc;
}

//-----------------------------------------------------------------------------
// Boolean
//-----------------------------------------------------------------------------
bool GamePlayer::isWalking(void)
{
	return this->bWalking;
}

void GamePlayer::isWalking(bool bState) 
{
	bWalking = bState;
}

bool GamePlayer::isClimbing(void)
{
	return bClimbingUp ? true : bClimbingDown;
}

void GamePlayer::isClimbing(bool bState)
{
	if (bState) return;
	
	bClimbingUp = bClimbingDown = bState;
}

bool GamePlayer::isOnLadder(void)
{
	return bOnLadder;
}

void GamePlayer::isOnLadder(bool bState)
{
	bOnLadder = bState;
}

//-----------------------------------------------------------------------------
// プレイヤーの動き処理
//-----------------------------------------------------------------------------
void GamePlayer::MoveLeft(void)
{
	bWalking = true;
	dirc.x = -1.0f;
	speed = velocity;
	pSprite->SetHorizontalFlip(true);
}

void GamePlayer::MoveRight(void)
{
	bWalking = true;
	dirc.x = 1.0f;
	speed = velocity;
	pSprite->SetHorizontalFlip(false);
}

void GamePlayer::MoveUp(void)
{
	bWalking = false;
	bClimbingUp = true;
	dirc.y = -2.0f;
}

void GamePlayer::MoveDown(void)
{
	bWalking = false;
	bClimbingDown = true;
	dirc.y = 4.0f;
}

void GamePlayer::Jump(void)
{
	if (!bJumping)
	{
		// 上方向の速度をあげる
		dirc.y = -15.0f;
		// ジャンプ中の状態に設定（多重ジャンプ防止）
		bJumping = true;
	}
}