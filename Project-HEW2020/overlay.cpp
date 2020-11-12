//----------------------------------------------------------------------------
// 
// Project-HEW2020 [overlay.cpp]
// 一番前（背景）及び一番後に描画するもの
// 
// Date:   2020/11/11
// Author: AT12D187_17_周進
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

	width = pSprite->GetTextureWidth();
	height = pSprite->GetTextureHeight();
}