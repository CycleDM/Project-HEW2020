//----------------------------------------------------------------------------
// 
// Project-HEW2020 [generator_ui.cpp]
// ƒV[ƒ“01ˆêŠK–Ú‚Ì“ä
// 
// Date:   2021/01/15
// Author: AT12D187_17_Žüi
// 
//----------------------------------------------------------------------------
#include "generator_ui.h"
#include "config.h"
#include "scene.h"
#include "d3dutility.h"
#include "game.h"
#include "input.h"

// Correct Rotation
const int GeneratorUI::correctRotation[GENERATOR_UI_SLOT_MAX] = 
{
		 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		 1,  3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1,  0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1,  0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1,  1,  1,  1,  3, -1, -1, -1, -1,  2,  1,  3, -1, -1,
		-1, -1, -1, -1,  1,  3, -1, -1,  2,  0, -1,  0, -1, -1,
		-1, -1, -1, -1, -1,  1,  1,  1,  0, -1, -1,  1,  1,  3
};

GeneratorUI::GeneratorUI()
{
	Init();
}

GeneratorUI::~GeneratorUI()
{
	Uninit();
}

void GeneratorUI::Init()
{
	fScale = 1.5f;
	bActive = false;
	bUnlocked = false;
	memset(pLineUI, NULL, sizeof(pLineUI));

	pBgOverlay = new GameOverlay(TEXTURE_FADE);
	pBgOverlay->SetScreenPos((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2);
	pBgOverlay->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	pBgOverlay->GetSprite()->SetColor(D3DCOLOR_RGBA(0, 0, 0, 200));

	pBaseUI = new GameOverlay(TEXTURE_GENERATOR_UI_BASE);
	pBaseUI->SetScreenPos((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2);
	pBaseUI->SetSize(pBaseUI->GetWidth() * fScale, pBaseUI->GetHeight() * fScale);

	pLineUI[0] = new GameOverlay(TEXTURE_GENERATOR_UI_LINE1);
	pLineUI[0]->SetSize(pLineUI[0]->GetWidth() * fScale, pLineUI[0]->GetHeight() * fScale);
	pLineUI[1] = new GameOverlay(TEXTURE_GENERATOR_UI_LINE2);
	pLineUI[1]->SetSize(pLineUI[1]->GetWidth() * fScale, pLineUI[1]->GetHeight() * fScale);

	// Slots
	// Type
	int slotMap1[GENERATOR_UI_SLOT_MAX] = 
	{
		0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1,
		1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1,
		1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0,
		1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1,
		1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1,
		1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1,
	};
	// Rotation
	int slotMap2[GENERATOR_UI_SLOT_MAX] =
	{
		0, 2, 3, 1, 0, 1, 2, 3, 2, 1, 1, 1, 2, 3,
		3, 2, 0, 1, 2, 3, 0, 2, 3, 1, 2, 0, 2, 3,
		2, 3, 3, 2, 0, 3, 3, 2, 1, 2, 0, 3, 2, 0,
		2, 1, 0, 2, 3, 1, 2, 0, 3, 2, 0, 0, 3, 0,
		0, 1, 2, 3, 2, 3, 0, 1, 0, 2, 1, 2, 3, 0,
		3, 2, 1, 0, 2, 1, 3, 2, 0, 2, 1, 3, 2, 0,
		3, 2, 1, 2, 0, 1, 2, 1, 0, 2, 3, 2, 1, 2,
	};
	// Enabled
	int slotMap3[GENERATOR_UI_SLOT_MAX] =
	{
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1,
		1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1
	};
	for (int i = 0; i < GENERATOR_UI_SLOT_MAX; i++)
	{
		gUISlots[i].nType = slotMap1[i];
		gUISlots[i].nRotation = slotMap2[i];
		gUISlots[i].bEnable = (bool)slotMap3[i];
		gUISlots[i].bSelected = false;
		gUISlots[i].bHighlight = false;

		int n = gUISlots[i].nType;
		int offsetX = i % GENERATOR_UI_SLOT_X;
		int offsetY = i / GENERATOR_UI_SLOT_X;
		float sizeX = pLineUI[n]->GetWidth();
		float sizeY = pLineUI[n]->GetHeight();
		gUISlots[i].posX = 327.0f + offsetX * sizeX;
		gUISlots[i].posY = 215.0f + offsetY * sizeY;
	}
}

void GeneratorUI::Uninit()
{
	delete pBgOverlay;
	pBgOverlay = NULL;
	delete pBaseUI;
	pBaseUI = NULL;
	for (GameOverlay* p : pLineUI)
	{
		delete p;
	}
	memset(pLineUI, NULL, sizeof(pLineUI));
}

void GeneratorUI::Update()
{
	if (!bActive) return;
	// Control
	do
	{
		if (bUnlocked) break;
		D3DXVECTOR2 mPos = { (float)Input::GetMouseX(), (float)Input::GetMouseY() };
		for (int i = 0; i < GENERATOR_UI_SLOT_MAX; i++)
		{
			if (!gUISlots[i].bEnable) continue;
			int n = gUISlots[i].nType;
			if (abs(gUISlots[i].posX - mPos.x) > pLineUI[n]->GetWidth() / 2)
			{
				gUISlots[i].bSelected = false;
				continue;
			}
			if (abs(gUISlots[i].posY - mPos.y) > pLineUI[n]->GetHeight() / 2)
			{
				gUISlots[i].bSelected = false;
				continue;
			}
			gUISlots[i].bSelected = true;
		}
		// Rotate
		if (Input::GetMouseButtonTrigger(0))
		{
			for (int i = 0; i < GENERATOR_UI_SLOT_MAX; i++)
			{
				if (gUISlots[i].bSelected)
				{
					gUISlots[i].nRotation++;
					if (gUISlots[i].nRotation > 3) gUISlots[i].nRotation = 0;
				}
			}
			TryToUnlock();
		}
	} while (0);
	
	// Quit
	do
	{
		if (Input::GetKeyPress(DIK_Q) || Input::GetKeyTrigger(DIK_E))
		{
			QuitUI();
		}
	} while (0);
}

void GeneratorUI::Draw()
{
	if (!bActive) return;
	pBgOverlay->Draw();
	pBaseUI->Draw();

	for (int i = 0; i < GENERATOR_UI_SLOT_MAX; i++)
	{
		if (!gUISlots[i].bEnable) continue;

		int n = gUISlots[i].nType;
		int offsetX = i % GENERATOR_UI_SLOT_X;
		int offsetY = i / GENERATOR_UI_SLOT_X;
		float sizeX = pLineUI[n]->GetWidth();
		float sizeY = pLineUI[n]->GetHeight();
		pLineUI[n]->SetScreenPos(gUISlots[i].posX, gUISlots[i].posY);
		pLineUI[n]->GetSprite()->SetRotation(sizeX / 2, sizeY / 2, D3DXToRadian(90 * gUISlots[i].nRotation));
		D3DCOLOR color = (gUISlots[i].bSelected || gUISlots[i].bHighlight) ? D3DCOLOR_RGBA(255, 255, 255, 255) : D3DCOLOR_RGBA(155, 155, 155, 255);
		pLineUI[n]->GetSprite()->SetColor(color);
		if (gUISlots[i].bSelected)
		{
			pLineUI[n]->SetSize(sizeX * 1.2f, sizeY * 1.2f);
			pLineUI[n]->GetSprite()->SetRotation(pLineUI[n]->GetWidth() / 2, pLineUI[n]->GetHeight() / 2, D3DXToRadian(90 * gUISlots[i].nRotation));
			pLineUI[n]->GetSprite()->SetColor(color);
			pLineUI[n]->Draw();
			pLineUI[n]->SetSize(sizeX, sizeY);
			continue;
		}
		pLineUI[n]->Draw();
	}
}

void GeneratorUI::OpenUI()
{
	bActive = true;
	GameScene::Freeze(true);
}

void GeneratorUI::QuitUI()
{
	bActive = false;
	GameScene::Freeze(false);
}

bool GeneratorUI::isUnlocked(void)
{
	return bUnlocked;
}

void GeneratorUI::TryToUnlock(void)
{
	// Is it correct?
	for (int i = 0; i < GENERATOR_UI_SLOT_MAX; i++)
	{
		if (-1 == correctRotation[i]) continue;

		int n = gUISlots[i].nRotation;
		if (0 == gUISlots[i].nType && 2 == gUISlots[i].nRotation) n = 0;
		if (0 == gUISlots[i].nType && 3 == gUISlots[i].nRotation) n = 1;

		bUnlocked = true;
		if (correctRotation[i] != n)
		{
			bUnlocked = false;
			break;
		}
	}
	if (bUnlocked)
	{
		PlaySound(SOUND_LABEL_SE_GENERATOR_POWER);
	}

	if (!bUnlocked) return;
	for (int i = 0; i < GENERATOR_UI_SLOT_MAX; i++)
	{
		if (-1 == correctRotation[i]) continue;
		gUISlots[i].bHighlight = true;
	}
}