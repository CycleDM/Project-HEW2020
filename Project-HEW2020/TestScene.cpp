//----------------------------------------------------------------------------
// 
// Project-HEW2020 [TestScene.cpp]
// プロトタイプシーン
// 
// Date:   2020/11/06
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#include "TestScene.h"

TestScene::TestScene()
{
	this->Init();
}

TestScene::~TestScene()
{
	this->Uninit();
}

void TestScene::Init(void)
{
	fBgScroll = 0.0f;

	// プレイヤーインスタンス
	pPlayer = new GamePlayer;
	pPlayer->SetPosition((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2);

	// 背景
	pOverlays[0] = new GameOverlay(TEXTURE_BG);
	pOverlays[0]->SetPosition((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2);
	pOverlays[0]->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	pOverlays[0]->GetSprite()->SetCutPos(0, 0);
	pOverlays[0]->GetSprite()->SetCutRange(384, 216);
}

void TestScene::Uninit(void)
{
	delete pPlayer;
	pPlayer = NULL;

	delete[] pObjects;
	memset(pObjects, NULL, sizeof(pObjects));

	delete[] pOverlays;
	memset(pOverlays, NULL, sizeof(pOverlays));
}

void TestScene::Update(void)
{
	// プレイヤーインスタンスを更新
	pPlayer->Update();

	// 背景のスクロール
	do
	{
		if (pPlayer->GetPosition().x > (float)SCREEN_WIDTH / 2 && pPlayer->GetMovingStatus())
		{
			if (fBgScroll >= 264.0f)
			{
				fBgScroll = 264.0f;
				break;
			}
			pPlayer->SetPosition((float)SCREEN_WIDTH / 2, pPlayer->GetPosition().y);
			fBgScroll += pPlayer->GetSpeed() / 2;
		}
		if (pPlayer->GetPosition().x < (float)SCREEN_WIDTH / 2 && pPlayer->GetMovingStatus() && fBgScroll > 0.0f)
		{
			if (fBgScroll <= 0.0f)
			{
				fBgScroll = 0.0f;
				break;
			}
			pPlayer->SetPosition((float)SCREEN_WIDTH / 2, pPlayer->GetPosition().y);
			fBgScroll -= pPlayer->GetSpeed() / 2;
		}
	} while (0);

	pOverlays[0]->GetSprite()->SetCutPos((int)fBgScroll, 0);
}

void TestScene::Draw(void)
{
	pOverlays[0]->Draw();

	for (GameObject* pO : pObjects)
	{
		if (NULL == pO) continue;
		pO->Draw();
	}

	pPlayer->Draw();
}