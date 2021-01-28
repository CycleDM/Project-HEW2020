//----------------------------------------------------------------------------
// 
// Project-HEW2020 [computer_ui.cpp]
// ƒV[ƒ“01“ñŠK–Ú‚Ì“ä
// 
// Date:   2021/01/28
// Author: AT12D187_17_Žüi
// 
//----------------------------------------------------------------------------
#include "computer_ui.h"
#include "scene.h"
#include "config.h"
#include "input.h"

const float ComputerUI::INIT_POS_X = 854.0f;
const float ComputerUI::INIT_POS_Y = 403.0f;
const int ComputerUI::CORRECT_PASS[4] = { 8, 3, 2, 6 };

ComputerUI::ComputerUI()
{
	Init();
}

ComputerUI::~ComputerUI()
{
	Uninit();
}

void ComputerUI::Init(void)
{
	bActive = false;
	bUnlocked = false;
	memset(bSelected, false, sizeof(bSelected));
	memset(nInput, -1, sizeof(nInput));

	pBgOverlay = new GameOverlay(TEXTURE_FADE);
	pBgOverlay->SetScreenPos((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2);
	pBgOverlay->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	pBgOverlay->GetSprite()->SetColor(D3DCOLOR_RGBA(0, 0, 0, 200));

	pBaseUI = new GameOverlay(TEXTURE_COMPUTER_UI_BASE);
	pBaseUI->SetScreenPos((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2);
	pBaseUI->SetScale(4.0f);

	pButtonBase = new GameOverlay(TEXTURE_COMPUTER_UI_KEYS_OVER);
	pButtonBase->SetScreenPos(927.0f, 510.0f);
	pButtonBase->SetScale(1.5f);
	pButtonBase->GetSprite()->SetColor(D3DCOLOR_RGBA(155, 155, 155, 255));

	pButton = new GameOverlay(TEXTURE_COMPUTER_UI_KEYS);
	pButton->SetScreenPos(INIT_POS_X, INIT_POS_Y);
	pButton->GetSprite()->SetCutPos(0, 0);
	pButton->GetSprite()->SetCutRange(48, 48);
	pButton->SetScale(0.5f);

	// TEXT
	pText = new GameText;
}

void ComputerUI::Uninit(void)
{
	delete pText;
	pText = NULL;
	delete pBgOverlay;
	pBgOverlay = NULL;
	delete pBaseUI;
	pBaseUI = NULL;
	delete pButtonBase;
	pButtonBase = NULL;
	delete pButton;
	pButton = NULL;
}

void ComputerUI::Update()
{
	if (!bActive) return;

	pText->Update();

	// BUTTONS
	long mPosX = Input::GetMouseX();
	long mPosY = Input::GetMouseY();

	memset(bSelected, false, sizeof(bSelected));
	int nIndex = -1;
	for (int i = 0; i < 12; i++)
	{
		if (mPosX >= (long)(INIT_POS_X + 72.0f * (i % 3) - pButton->GetWidth() / 2) &&
			mPosX <= (long)(INIT_POS_X + 72.0f * (i % 3) + pButton->GetWidth() / 2) &&
			mPosY >= (long)(INIT_POS_Y + 71.0f * (i / 3) - pButton->GetHeight() / 2) &&
			mPosY <= (long)(INIT_POS_Y + 71.0f * (i / 3) + pButton->GetHeight() / 2))
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
			if (nIndex == 11)
			{
				for (int i = 3; i >= 0; i--)
				{
					if (nInput[i] == -1) continue;
					nInput[i] = -1;
					break;
				}
			}
			// CLEAR
			else if (nIndex == 9)
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

void ComputerUI::Draw(void)
{
	if (!bActive) return;
	pBgOverlay->Draw();
	pBaseUI->Draw();
	pButtonBase->Draw();
	pText->Draw();

	for (int i = 0; i < 12; i++)
	{
		if (bSelected[i])
		{
			pButton->GetSprite()->SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
		}
		else
		{
			pButton->GetSprite()->SetColor(D3DCOLOR_RGBA(255, 255, 255, 0));
		}
		pButton->GetSprite()->SetCutPos(48 * (i % 3), 48 * (i / 3));
		pButton->SetScreenPos(INIT_POS_X + 72.0f * (i % 3), INIT_POS_Y + 71.0f * (i / 3));
		pButton->Draw();
	}

	// SHOW INPUT NUMBERS
	do
	{
		for (int i = 0; i < 4; i++)
		{
			if (nInput[i] == -1) continue;

			pButton->GetSprite()->SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
			pButton->GetSprite()->SetCutPos(48 * (nInput[i] % 3), 48 * (nInput[i] / 3));
			pButton->SetScreenPos(453.0f + 123.0f * (i % 4), 220.0f);
			pButton->Draw();
		}
	} while (0);
}

void ComputerUI::OpenUI(void)
{
	bActive = true;
	GameScene::Freeze(true);
}

void ComputerUI::QuitUI(void)
{
	bActive = false;
	GameScene::Freeze(false);
}

bool ComputerUI::isUnlocked(void)
{
	return bUnlocked;
}

void ComputerUI::TryToUnlock(void)
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
			pText->CreateText(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 250,
				64, "UNLOCKED!", -1, 1, D3DCOLOR_RGBA(0, 255, 155, 255));
			bUnlocked = true;
			break;
		}
		if (nInput[3] == -1)
		{
			pText->Init();
			break;
		}
		pText->CreateText(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 250,
			64, "WRONG!", -1, 1, D3DCOLOR_RGBA(255, 0, 0, 255));
	} while (0);
}
