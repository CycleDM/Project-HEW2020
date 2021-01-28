//----------------------------------------------------------------------------
// 
// Project-HEW2020 [panel_ui.cpp]
// ƒV[ƒ“01ˆêŠK–Ú‚Ì“ä
// 
// Date:   2021/01/28
// Author: AT12D187_17_Žüi
// 
//----------------------------------------------------------------------------
#include "panel_ui.h"
#include "scene.h"
#include "config.h"
#include "input.h"

const float PanelUI::INIT_POS_X = 545.0f;
const float PanelUI::INIT_POS_Y = 288.0f;
const int PanelUI::CORRECT_PASS[4] = { 6, 7, 4, 3 };

PanelUI::PanelUI()
{
	Init();
}

PanelUI::~PanelUI()
{
	Uninit();
}

void PanelUI::Init(void)
{
	bActive = false;
	bUnlocked = false;
	memset(bSelected, false, sizeof(bSelected));
	memset(nInput, -1, sizeof(nInput));

	pBgOverlay = new GameOverlay(TEXTURE_FADE);
	pBgOverlay->SetScreenPos((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2);
	pBgOverlay->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	pBgOverlay->GetSprite()->SetColor(D3DCOLOR_RGBA(0, 0, 0, 200));

	pBaseUI = new GameOverlay(TEXTURE_OBJ_LIFT_PANEL);
	pBaseUI->SetScreenPos((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2);
	pBaseUI->SetScale(1.5f);

	pButtonBlue = new GameOverlay(TEXTURE_PANEL_BUTTON_BLUE);
	pButtonBlue->SetScreenPos(INIT_POS_X, INIT_POS_Y);
	pButtonBlue->GetSprite()->SetCutPos(0, 0);
	pButtonBlue->GetSprite()->SetCutRange(48, 48);
	pButtonBlue->SetScale(0.4f);

	// SPECIAL
	pButtonGreen = new GameOverlay(TEXTURE_PANEL_BUTTON_GREEN);
	pButtonGreen->SetScreenPos(INIT_POS_X, INIT_POS_Y);
	pButtonGreen->GetSprite()->SetCutPos(0, 0);
	pButtonGreen->GetSprite()->SetCutRange(48, 48);
	pButtonGreen->SetScale(0.4f);

	// TEXT
	pText = new GameText;
}

void PanelUI::Uninit(void)
{
	delete pText;
	pText = NULL;
	delete pBgOverlay;
	pBgOverlay = NULL;
	delete pBaseUI;
	pBaseUI = NULL;
	delete pButtonBlue;
	pButtonBlue = NULL;
	delete pButtonGreen;
	pButtonGreen = NULL;
}

void PanelUI::Update()
{
	if (!bActive) return;

	pText->Update();

	// BUTTONS
	long mPosX = Input::GetMouseX();
	long mPosY = Input::GetMouseY();
	long offsetX = 5;

	memset(bSelected, false, sizeof(bSelected));
	int nIndex = -1;
	for (int i = 0; i < 12; i++)
	{
		if (mPosX >= (long)(INIT_POS_X + 95.0f * (i % 3) - pButtonBlue->GetWidth() / 2 - offsetX) &&
			mPosX <= (long)(INIT_POS_X + 95.0f * (i % 3) + pButtonBlue->GetWidth() / 2 + offsetX) &&
			mPosY >= (long)(INIT_POS_Y + 85.0f * (i / 3) - pButtonBlue->GetHeight() / 2) &&
			mPosY <= (long)(INIT_POS_Y + 85.0f * (i / 3) + pButtonBlue->GetHeight() / 2))
		{
			bSelected[i] = true;
			nIndex = i;
			break;
		}
	}

	// INPUT
	do
	{
		if (bUnlocked) break;
		if (Input::GetMouseButtonTrigger(0))
		{
			if (nIndex == -1) break;

			// BACKSPACE
			if (nIndex == 9)
			{
				for (int i = 3; i >= 0; i--)
				{
					if (nInput[i] == -1) continue;
					nInput[i] = -1;
					break;
				}
			}
			// CLEAR
			else if (nIndex == 11)
			{
				for (int i = 0; i < 4; i++)
				{
					nInput[i] = -1;
				}
			}
			// INPUT PASSWORD
			else
			{
				for (int i = 0; i < 4; i++)
				{
					if (nInput[i] != -1) continue;
					nInput[i] = nIndex;
					break;
				}
			}
			TryToUnlock();
		}
	} while (0);

	// QUIT
	if (Input::GetKeyTrigger(DIK_Q) || Input::GetKeyTrigger(DIK_ESCAPE))
	{
		QuitUI();
	}
}

void PanelUI::Draw(void)
{
	if (!bActive) return;
	pBgOverlay->Draw();
	pBaseUI->Draw();
	pText->Draw();

	for (int i = 0; i < 12; i++)
	{
		GameOverlay* pTarget = pButtonBlue;
		if (bSelected[i] || bUnlocked) pTarget = pButtonGreen;

		pTarget->GetSprite()->SetCutPos(48 * (i % 3), 48 * (i / 3));
		pTarget->SetScreenPos(INIT_POS_X + 95.0f * (i % 3), INIT_POS_Y + 85.0f * (i / 3));
		pTarget->Draw();
	}

	// SHOW INPUT NUMBERS
	do
	{
		for (int i = 0; i < 4; i++)
		{
			if (nInput[i] == -1) continue;

			pButtonGreen->GetSprite()->SetCutPos(48 * (nInput[i] % 3), 48 * (nInput[i] / 3));
			pButtonGreen->SetScreenPos(INIT_POS_X - 16.0f + 73.0f * (i % 4), INIT_POS_Y - 135.0f);
			pButtonGreen->Draw();
		}
	} while (0);
}

void PanelUI::OpenUI(void)
{
	bActive = true;
	GameScene::Freeze(true);
}

void PanelUI::QuitUI(void)
{
	bActive = false;
	GameScene::Freeze(false);
}

bool PanelUI::isUnlocked(void)
{
	return bUnlocked;
}

void PanelUI::TryToUnlock(void)
{
	// CHECK PASSWORD
	do
	{
		bool bCorrect = true;
		for (int i = 0; i < 4; i++)
		{
			if (nInput[i] != CORRECT_PASS[i])
			{
				bCorrect = false;
				break;
			}
		}
		if (bCorrect)
		{
			pText->CreateText(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 300,
				64, "UNLOCKED!", -1, 1, D3DCOLOR_RGBA(0, 255, 155, 255));
			bUnlocked = true;
			break;
		}
		if (nInput[3] == -1)
		{
			pText->Init();
			break;
		}
		pText->CreateText(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 300,
			64, "WRONG!", -1, 1, D3DCOLOR_RGBA(255, 0, 0, 255));
	} while (0);
}
