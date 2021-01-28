//----------------------------------------------------------------------------
// 
// Project-HEW2020 [overlay.cpp]
// ˆê”Ô‘Oi”wŒij‹y‚Ñˆê”ÔŒã‚É•`‰æ‚·‚é‚à‚Ì
// 
// Date:   2020/11/11
// Author: AT12D187_17_Žüi
// 
//----------------------------------------------------------------------------
#include "overlay.h"

GameOverlay::GameOverlay()
{
	this->Init();
}

GameOverlay::GameOverlay(const char* pFileName)
{
	this->LoadTexture(pFileName);
}

GameOverlay::~GameOverlay()
{
	this->Uninit();
}

void GameOverlay::LoadTexture(const char* pFileName)
{
	pSprite = new SpriteNormal;
	pSprite->LoadTexture(pFileName);

	width = (float)pSprite->GetTextureWidth();
	height = (float)pSprite->GetTextureHeight();
	if (pSprite->GetCutWidth() != 0)
	{
		width = (float)pSprite->GetCutWidth();
	}
	if (pSprite->GetCutHeight() != 0)
	{
		height = (float)pSprite->GetCutHeight();
	}
}