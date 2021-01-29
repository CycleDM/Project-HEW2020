//----------------------------------------------------------------------------
// 
// Project-HEW2020 [screen.cpp]
// シーン01一階目の謎
// 
// Date:   2021/01/28
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#include "screen_ui.h"
#include "scene.h"
#include "config.h"
#include "input.h"

ScreenUI::ScreenUI()
{
	Init();
}

ScreenUI::~ScreenUI()
{
	Uninit();
}

void ScreenUI::Init(void)
{
	bActive = false;
	bPower = false;
	bColor = false;
	pBgOverlay = new GameOverlay(TEXTURE_FADE);
	pBgOverlay->SetScreenPos((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2);
	pBgOverlay->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	pBgOverlay->GetSprite()->SetColor(D3DCOLOR_RGBA(0, 0, 0, 200));

	pBaseUI = new GameOverlay(TEXTURE_SCREEN_UI);
	pBaseUI->SetScreenPos((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2);
	pBaseUI->GetSprite()->SetCutPos(0, 0);
	pBaseUI->GetSprite()->SetCutRange(544, 416);
	pBaseUI->SetSize(544.0f, 416.0f);
	pBaseUI->SetScale(1.5f);

	pText = new GameText;
}

void ScreenUI::Uninit(void)
{
	delete pText;
	pText = NULL;
	delete pBgOverlay;
	pBgOverlay = NULL;
	delete pBaseUI;
	pBaseUI = NULL;
}

void ScreenUI::Update(bool bPower, bool bColor)
{
	this->bPower = bPower;
	this->bColor = bColor;
	if (!bActive) return;
	do
	{

		if (!bPower)
		{
			pBaseUI->GetSprite()->SetCutPos(0, 0);
			break;
		}
		if (!bColor)
		{
			pBaseUI->GetSprite()->SetCutPos(544, 0);
			break;
		}
		pBaseUI->GetSprite()->SetCutPos(1088, 0);
	} while (0);

	if (Input::GetKeyTrigger(DIK_Q) || Input::GetKeyTrigger(DIK_ESCAPE))
	{
		pText->Init();
		QuitUI();
	}

	pText->Update();
}

void ScreenUI::Draw(void)
{
	if (!bActive) return;
	pBgOverlay->Draw();
	pBaseUI->Draw();
	pText->Draw();
}

void ScreenUI::OpenUI(void)
{
	bActive = true;
	GameScene::Freeze(true);
	if (!bPower) return;
	if (bColor) return;
	pText->CreateText(SCREEN_WIDTH / 2 - 250, SCREEN_HEIGHT / 2 + 200, 50, "×色を認識できません", -1, 60, D3DCOLOR_RGBA(255, 0, 0, 255));
}

void ScreenUI::QuitUI(void)
{
	bActive = false;
	GameScene::Freeze(false);
}