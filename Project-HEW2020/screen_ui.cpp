//----------------------------------------------------------------------------
// 
// Project-HEW2020 [screen.cpp]
// ƒV[ƒ“01ˆêŠK–Ú‚Ì“ä
// 
// Date:   2021/01/28
// Author: AT12D187_17_Žüi
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
}

void ScreenUI::Uninit(void)
{
	delete pBgOverlay;
	pBgOverlay = NULL;
	delete pBaseUI;
	pBaseUI = NULL;
}

void ScreenUI::Update(bool bPower, bool bColor)
{
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
		QuitUI();
	}
}

void ScreenUI::Draw(void)
{
	if (!bActive) return;
	pBgOverlay->Draw();
	pBaseUI->Draw();
}

void ScreenUI::OpenUI(void)
{
	bActive = true;
	GameScene::Freeze(true);
}

void ScreenUI::QuitUI(void)
{
	bActive = false;
	GameScene::Freeze(false);
}