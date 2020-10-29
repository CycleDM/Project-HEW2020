//----------------------------------------------------------------------------
// 
// Project-HEW2020 [background.cpp]
// 背景制御モジュール
// 
// Date:   2020/10/28
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#include "config.h"
#include "background.h"

//-----------------------------------------------------------------------------
// グローバル変数宣言
//-----------------------------------------------------------------------------
static Sprite* g_pSpriteBg = NULL;

GameBackground::GameBackground()
{
	this->Init();
}

GameBackground::~GameBackground()
{
	this->Uninit();
}

void GameBackground::Init(void)
{
	// （例）スプライトの設定
	g_pSpriteBg = new SpriteNormal;
	g_pSpriteBg->LoadTexture("assets/texture/sample.jpg");
	// ↓このように書いても良い
	//g_pSpriteBg = new SpriteNormal("assets/texture/sample.jpg");
	g_pSpriteBg->SetDrawPos(0.0f, 0.0f);
	g_pSpriteBg->SetCutPos(0, 0);
	g_pSpriteBg->SetCutRange(SCREEN_WIDTH, SCREEN_HEIGHT);
	//g_pSprite->SetHorizontalFlip(true);
	//g_pSprite->SetVerticalFlip(true);
}

void GameBackground::Update(void)
{

}

void GameBackground::Draw(void)
{
	g_pSpriteBg->Draw();
}

void GameBackground::Uninit(void)
{
	delete g_pSpriteBg;
	g_pSpriteBg = NULL;
}