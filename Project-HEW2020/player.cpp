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
#define PLAYER_WIDTH	(109)
#define PLAYER_HEIGHT	(106)

//-----------------------------------------------------------------------------
// グローバル変数宣言
//-----------------------------------------------------------------------------
static SpriteNormal* g_pPlayerSprite = NULL;

Player::Player()
{
	this->Init();
}

Player::~Player()
{
	delete g_pPlayerSprite;
	g_pPlayerSprite = NULL;
}

void Player::Init(void)
{
	pos = D3DXVECTOR2(10.0f, (float)SCREEN_HEIGHT - 128.0f);
	dirc = D3DXVECTOR2(0.0f, 0.0f);
	speed = 4.0f;
	hp = 3;
	score = 0;

	g_pPlayerSprite = new SpriteNormal;
	g_pPlayerSprite->LoadTexture(TEXTURE_PLAYER);
	g_pPlayerSprite->SetDrawPos(pos.x, pos.y);
	g_pPlayerSprite->SetCutPos(0, 0);
}

void Player::Update(void)
{

}

void Player::Draw(void)
{
	g_pPlayerSprite->Draw();
}

void Player::SetPos(float x, float y)
{
	this->pos.x = x;
	this->pos.y = y;
}

D3DXVECTOR2 Player::GetPos(void)
{
	return this->pos;
}