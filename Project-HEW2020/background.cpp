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
#include "game.h"

//-----------------------------------------------------------------------------
// グローバル変数宣言
//-----------------------------------------------------------------------------
static Sprite* g_pSpriteBg[64];
static float g_fBgScroll = 0.0f;

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
	memset(g_pSpriteBg, NULL, sizeof(g_pSpriteBg));
	g_fBgScroll = 0.0f;

	g_pSpriteBg[0] = new SpriteNormal(TEXTURE_BG);
	g_pSpriteBg[0]->SetDrawPos(0.0f, 0.0f);
	g_pSpriteBg[0]->SetCutPos(0, 0);
	g_pSpriteBg[0]->SetCutRange(384, 216);
	g_pSpriteBg[0]->SetPolygonSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);

	g_pSpriteBg[1] = new SpriteNormal(TEXTURE_2FGROUND);
	g_pSpriteBg[2] = new SpriteNormal(TEXTURE_LADDER);
	g_pSpriteBg[3] = new SpriteNormal(TEXTURE_LADDER);
	
	g_pSpriteBg[1]->SetPolygonSize(g_pSpriteBg[1]->GetTextureWidth() * 3.2f, g_pSpriteBg[1]->GetTextureHeight() * 3.2f);
	g_pSpriteBg[2]->SetPolygonSize(g_pSpriteBg[2]->GetTextureWidth() * 3.2f, g_pSpriteBg[2]->GetTextureHeight() * 3.2f);
	g_pSpriteBg[3]->SetPolygonSize(g_pSpriteBg[3]->GetTextureWidth() * 3.2f, g_pSpriteBg[3]->GetTextureHeight() * 3.2f);
}

void GameBackground::Update(void)
{
	GamePlayer* player = Game_GetPlayer();
	if (player->GetPosition().x < (float)SCREEN_WIDTH / 2 + 10.0f && player->GetPosition().x > (float)SCREEN_WIDTH / 2 - 10.0f)
	{
		if (g_fBgScroll < 0.0f)
		{
			g_fBgScroll = 0.0f;
		}
		else if (g_fBgScroll > 264.0f)
		{
			g_fBgScroll = 264.0f;
		}
		else
		{
			player->SetPosition((float)SCREEN_WIDTH / 2, player->GetPosition().y);
			g_fBgScroll += (player->GetSpeed() * player->GetDirection().x) * 0.3f;
		}
	}
	g_pSpriteBg[0]->SetCutPos((int)g_fBgScroll, 0);
	g_pSpriteBg[1]->SetDrawPos(350.0f - g_fBgScroll / 0.3f, 250.0f);
	g_pSpriteBg[2]->SetDrawPos(430.0f - g_fBgScroll / 0.3f, 330.0f);
	g_pSpriteBg[3]->SetDrawPos(1220.0f - g_fBgScroll / 0.3f, 330.0f);
}

void GameBackground::Draw(void)
{
	for (Sprite* pS : g_pSpriteBg)
	{
		if (NULL != pS)
		{
			pS->Draw();
		}
	}
}

void GameBackground::Uninit(void)
{
	delete[] g_pSpriteBg;
	memset(g_pSpriteBg, NULL, sizeof(g_pSpriteBg));
}