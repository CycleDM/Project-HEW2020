//----------------------------------------------------------------------------
// 
// Project-HEW2020 [loadingscreen.cpp]
// ƒ[ƒh’†‚Ì‰æ–Ê
// 
// Date:   2021/01/26
// Author: AT12D187_17_üi
// 
//----------------------------------------------------------------------------
#include "loadingscreen.h"
#include "config.h"

LoadingScreen::LoadingScreen()
{
	pSprite = new SpriteNormal(TEXTURE_LOADING);
	pAnimator = new Animator();
	pSprite->SetPolygonSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	pSprite->SetCutPos(0, 0);
	pSprite->SetCutRange(SCREEN_WIDTH, SCREEN_HEIGHT);
	pAnimator->Init(pSprite);
	pAnimator->Preset(3, 3, 8);

	isHidden = true;
}

LoadingScreen::~LoadingScreen()
{
	delete pSprite;
	pSprite = NULL;
	delete pAnimator;
	pAnimator = NULL;
}

void LoadingScreen::Update()
{
	if (isHidden) return;
	pAnimator->Play(pSprite);
}

void LoadingScreen::Draw()
{
	if (isHidden) return;
	pSprite->Draw();
}

void LoadingScreen::Hide()
{
	if (isHidden) return;
	pSprite->SetColor(D3DCOLOR_RGBA(255, 255, 255, 0));
	isHidden = true;
}

void LoadingScreen::Show()
{
	pSprite->SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
	pAnimator->Preset(3, 3, 8);
	isHidden = false;
}