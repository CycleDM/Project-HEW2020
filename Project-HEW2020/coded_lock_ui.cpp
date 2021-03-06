#include "coded_lock_ui.h"
#include "config.h"
#include "scene.h"

CodedLockUI::CodedLockUI()
{
	Init();
}
CodedLockUI::~CodedLockUI()
{
	Uninit();
}

void CodedLockUI::Init(void)
{
	fScale = 1.5f;

	nFrame = 0;
	bActive = false;
	bOpening = false;
	bQuiting = false;
	bUnlocked = false;
	bTrying = false;
	bSwitching = false;

	nHSelected = 0;
	for (int i = 0; i < 3; i++)
	{
		nInput[i] = 0;
		nPassword[i] = 0;
		nKeyCut[i] = -CLUI_KEY_H;
	}
	memset(fOffsetX, 0.0f, sizeof(fOffsetX));
	memset(fOffsetY, 0.0f, sizeof(fOffsetY));

	pBgOverlay = NULL;
	memset(pLockUI, NULL, sizeof(pLockUI));

	pBgOverlay = new GameOverlay(TEXTURE_FADE);
	pBgOverlay->SetScreenPos((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2);
	pBgOverlay->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	pBgOverlay->GetSprite()->SetColor(D3DCOLOR_RGBA(0, 0, 0, 200));

	int n = 0;
	// BASE 0
	pLockUI[n] = new GameOverlay(TEXTURE_CLUI_BASE);
	fOffsetY[n] = pLockUI[n]->GetSprite()->GetTextureHeight() / 2;
	n++;
	// SHADOW 1
	pLockUI[n] = new GameOverlay(TEXTURE_CLUI_SHADOW);
	n++;
	// KEY 2-4
	for (int i = 0; i < 3; i++, n++)
	{
		fOffsetX[n] = 62.0f;
		fOffsetY[n] = 0.0f;
		pLockUI[n] = new GameOverlay(TEXTURE_CLUI_KEY);
		pLockUI[n]->SetSize((float)50, (float)207);
		pLockUI[n]->GetSprite()->SetCutPos(0, -CLUI_KEY_H);
		pLockUI[n]->GetSprite()->SetCutRange(50, 207);
	}
	// LIGHT 5-7
	for (int i = 0; i < 3; i++, n++)
	{
		fOffsetX[n] = 60.5f;
		fOffsetY[n] = 107.5f;
		pLockUI[n] = new GameOverlay(TEXTURE_CLUI_LIGHT);
	}
	this->ResetPos();

	for (GameOverlay* p : pLockUI)
	{
		if (NULL == p) continue;
		p->SetSize(p->GetWidth() * fScale, p->GetHeight() * fScale);
	}
}

void CodedLockUI::Uninit(void)
{
	delete pBgOverlay;
	pBgOverlay = NULL;

	for (GameOverlay* p : pLockUI)
	{
		delete p;
	}
	memset(pLockUI, NULL, sizeof(pLockUI));
}

void CodedLockUI::Update(void)
{
	nFrame = (bActive || bOpening || bQuiting) ? ++nFrame : 0;

	if (nFrame >= 3000) nFrame = 0;

	if (bOpening)
	{
		pLockUI[0]->SetScreenPos(pLockUI[0]->GetScreenPos().x, pLockUI[0]->GetScreenPos().y - (float)nFrame * 2.0f);
		if (pLockUI[0]->GetScreenPos().y <= (float)SCREEN_HEIGHT / 2) bOpening = false;

		int n = 0;
		for (GameOverlay* p : pLockUI) n++;
		for (int i = 1; i < n; i++)
		{
			pLockUI[i]->SetScreenPos(pLockUI[i]->GetScreenPos().x, pLockUI[0]->GetScreenPos().y - fOffsetY[i] * fScale);
		}
	}
	else if (bQuiting)
	{
		pLockUI[0]->SetScreenPos(pLockUI[0]->GetScreenPos().x, pLockUI[0]->GetScreenPos().y + (float)nFrame * 2.0f);
		if (pLockUI[0]->GetScreenPos().y >= (float)SCREEN_HEIGHT + fOffsetY[0] * fScale)
		{
			bQuiting = false;
			bActive = false;
			ResetPos();
			GameScene::Freeze(false);
		}

		int n = 0;
		for (GameOverlay* p : pLockUI) n++;
		for (int i = 1; i < n; i++)
		{
			pLockUI[i]->SetScreenPos(pLockUI[i]->GetScreenPos().x, pLockUI[0]->GetScreenPos().y - fOffsetY[i] * fScale);
		}
	}

	if (!bActive) return;
	// Input
	do
	{
		if (!bActive || bOpening || bQuiting || bTrying) break;
		// KEYBOARD
		if (!bSwitching && Input::GetKeyTrigger(DIK_A))
		{
			nHSelected--;
			if (nHSelected < 0) nHSelected = 0;
		}
		if (!bSwitching && Input::GetKeyTrigger(DIK_D))
		{
			nHSelected++;
			if (nHSelected > 2) nHSelected = 2;
		}
		// MOUSE
		long mPosX = Input::GetMouseX();
		long mPosY = Input::GetMouseY();
		long mWheel = Input::GetMouseDeltaWheel();
		do
		{
			if (mPosY < 206 || mPosY > 517) break;
			if (mPosX >= 510 && mPosX <= 584)
			{
				nHSelected = 0;
			}
			if (mPosX >= 602 && mPosX <= 676)
			{
				nHSelected = 1;
			}
			if (mPosX >= 693 && mPosX <= 767)
			{
				nHSelected = 2;
			}
		} while (0);

		// -69 ~ 552
		int index = CLUI_KEY_H * nInput[nHSelected] - CLUI_KEY_H;;
		if (!bSwitching && (Input::GetKeyPress(DIK_W) || mWheel < 0))
		{
			nInput[nHSelected]--;
			if (nInput[nHSelected] < 0) nInput[nHSelected] = 9;
			index = CLUI_KEY_H * nInput[nHSelected] - CLUI_KEY_H;
			if (index == 8 * CLUI_KEY_H) nKeyCut[nHSelected] = index + CLUI_KEY_H;
			PlaySound(SOUND_LABEL_SE_PICKUP);
		}
		if (!bSwitching && (Input::GetKeyPress(DIK_S) || mWheel > 0))
		{
			nInput[nHSelected]++;
			if (nInput[nHSelected] > 9) nInput[nHSelected] = 0;
			index = CLUI_KEY_H * nInput[nHSelected] - CLUI_KEY_H;
			if (index == -CLUI_KEY_H) nKeyCut[nHSelected] = index - CLUI_KEY_H;
			PlaySound(SOUND_LABEL_SE_PICKUP);
		}
		if (nKeyCut[nHSelected] >= 9 * CLUI_KEY_H) nKeyCut[nHSelected] - CLUI_KEY_H;
		if (nKeyCut[nHSelected] < index) nKeyCut[nHSelected] += 3;
		if (nKeyCut[nHSelected] > index) nKeyCut[nHSelected] -= 3;

		// trueだったら他の処理を受けない
		bSwitching = true;
		// ロックの数字により動画処理
		pLockUI[2 + nHSelected]->GetSprite()->SetCutPos(0, nKeyCut[nHSelected]);
		// falseだったら他の処理を正常に受ける
		if (nKeyCut[nHSelected] == index) bSwitching = false;
	} while (0);

	// Light Switch
	for (int i = 5, n = 0; i < 8; i++, n++)
	{
		if (n == nHSelected)
			pLockUI[i]->GetSprite()->SetColor(D3DCOLOR_RGBA(0, 255, 255, 255));
		else
			pLockUI[i]->GetSprite()->SetColor(D3DCOLOR_RGBA(41, 36, 33, 255));
	}

	// Touch
	do
	{
		if (bOpening || bQuiting) break;
		if (!bTrying && (Input::GetKeyTrigger(DIK_E) || Input::GetMouseButtonTrigger(0)))
		{
			nFrame = 0;
			bTrying = true;	
		}
		TryToUnlock();
	} while (0);

	// Quit
	do
	{
		if (bOpening || bQuiting || bTrying || bSwitching) break;
		if (Input::GetKeyPress(DIK_Q) || Input::GetKeyTrigger(DIK_ESCAPE))
		{
			QuitUI();
		}
	} while (0);
}

void CodedLockUI::OpenUI(void)
{
	bActive = true;
	bOpening = true;
	nFrame = 0;
	GameScene::Freeze(true);
	ResetPos();
}

void CodedLockUI::QuitUI(void)
{
	bQuiting = true;
	nFrame = 0;
}

void CodedLockUI::Draw(void)
{
	if (!bActive) return;
	pBgOverlay->Draw();
	// 描画順番
	int number[] = { 2, 3, 4, 0, 1, 5, 6, 7 };
	for (int i = 0; i < sizeof(number) / sizeof(number[0]); i++)
	{
		pLockUI[number[i]]->Draw();
	}
}

void CodedLockUI::ResetPos(void)
{
	int n = 0;
	// BASE
	fOffsetY[n] = pLockUI[n]->GetSprite()->GetTextureHeight() / 2;
	if (pLockUI[n])
	{
		pLockUI[n]->SetScreenPos((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT + fOffsetY[n] * fScale);
		n++;
	}
	// SHADOW
	if (pLockUI[n])
	{
		pLockUI[n++]->SetScreenPos(pLockUI[0]->GetScreenPos().x, pLockUI[0]->GetScreenPos().y);
	}
	// KEY
	for (int i = 0; i < 3; i++, n++)
	{
		if (pLockUI[n]) 
			pLockUI[n]->SetScreenPos(pLockUI[0]->GetScreenPos().x + fOffsetX[n] * (i - 1) * fScale, pLockUI[0]->GetScreenPos().y - fOffsetY[n] * fScale);
	}
	// LIGHT
	for (int i = 0; i < 3; i++, n++)
	{
		if (pLockUI[n]) 
			pLockUI[n]->SetScreenPos(pLockUI[0]->GetScreenPos().x + fOffsetX[n] * (i - 1) * fScale, pLockUI[0]->GetScreenPos().y - fOffsetY[n] * fScale);
	}
}

void CodedLockUI::SetPassword(int a, int b, int c)
{
	nPassword[0] = a;
	nPassword[1] = b;
	nPassword[2] = c;
}

bool CodedLockUI::isUnlocked(void)
{
	return bUnlocked;
}

void CodedLockUI::TryToUnlock(void)
{
	if (!bTrying) return;

	bool bCorrect = false;
	for (int i = 0; i < 3; i++)
	{
		bCorrect = (nInput[i] == nPassword[i]);
		if (!bCorrect) break;
	}
	do
	{
		if (!bCorrect) break;
		if (nFrame <= 120)
		{
			pLockUI[5]->GetSprite()->SetColor(D3DCOLOR_RGBA(0, 255, 0, 255));
			pLockUI[6]->GetSprite()->SetColor(D3DCOLOR_RGBA(0, 255, 0, 255));
			pLockUI[7]->GetSprite()->SetColor(D3DCOLOR_RGBA(0, 255, 0, 255));
		}
		else
		{
			nFrame = 0;
			bTrying = false;
			bUnlocked = true;
			QuitUI();
		}
	} while (0);

	do
	{
		if (bCorrect) break;
		if (nFrame <= 75)
		{
			if (nFrame <= 15 || (nFrame >= 30 && nFrame <= 45) || nFrame >= 60)
			{
				pLockUI[5]->GetSprite()->SetColor(D3DCOLOR_RGBA(255, 0, 0, 255));
				pLockUI[6]->GetSprite()->SetColor(D3DCOLOR_RGBA(255, 0, 0, 255));
				pLockUI[7]->GetSprite()->SetColor(D3DCOLOR_RGBA(255, 0, 0, 255));
			}
			else
			{
				pLockUI[5]->GetSprite()->SetColor(D3DCOLOR_RGBA(41, 36, 33, 255));
				pLockUI[6]->GetSprite()->SetColor(D3DCOLOR_RGBA(41, 36, 33, 255));
				pLockUI[7]->GetSprite()->SetColor(D3DCOLOR_RGBA(41, 36, 33, 255));
			}
		}
		else
		{
			nFrame = 0;
			bTrying = false;
		}
	} while (0);
}
