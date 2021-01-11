//----------------------------------------------------------------------------
// 
// Project-HEW2020 [TitleScene.cpp]
// タイトル画面シーン
// 
// Date:   2020/11/27
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#include "TitleScene.h"
#include "controller.h"
#include "game.h"
#include "fade.h"

TitleScene::TitleScene()
{
	Init();
}

TitleScene::~TitleScene()
{
	Uninit();
}

void TitleScene::Init(void)
{
	SetGlobalScaling(1.0f);
	fBgScroll = D3DXVECTOR2(0.0f, 0.0f);
	fGroundHeight = 64.0f;

	// BG
	pOverlays[0] = new GameOverlay("assets/texture/title_testbg.jpg");
	pOverlays[0]->SetScreenPos((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2);
	pOverlays[0]->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	pOverlays[0]->GetSprite()->SetColor(D3DCOLOR_RGBA(150, 150, 150, 255));

	// ICON
	pOverlays[1] = new GameOverlay("assets/texture/title_icon.png");
	pOverlays[1]->SetScreenPos((float)SCREEN_WIDTH / 2, 300.0f);
	pOverlays[1]->GetSprite()->SetCutPos(0, 0);
	pOverlays[1]->GetSprite()->SetCutRange(1280, 720);
	pOverlays[1]->SetSize(1280.0f, 720.0f);
	pAnimator = new Animator;
	pAnimator->Init(pOverlays[1]->GetSprite());
	pAnimator->Preset(7, 1, 8);

	// BUTTON1
	pOverlays[2] = new GameOverlay("assets/texture/title_button1.png");
	pOverlays[2]->SetScreenPos((float)SCREEN_WIDTH / 2, 450.0f);
	pOverlays[2]->SetSize(pOverlays[2]->GetSprite()->GetTextureWidth() / 2, pOverlays[2]->GetSprite()->GetTextureHeight() / 2);

	// BUTTON2
	pOverlays[3] = new GameOverlay("assets/texture/title_button2.png");
	pOverlays[3]->SetScreenPos((float)SCREEN_WIDTH / 2, 550.0f);
	pOverlays[3]->SetSize(pOverlays[3]->GetSprite()->GetTextureWidth() / 2, pOverlays[3]->GetSprite()->GetTextureHeight() / 2);

	FadeEffect::Start(FADE_IN, 0.0f, 0.0f, 0.0f, 30);
}

void TitleScene::Uninit(void)
{
	for (GameOverlay* p : pOverlays)
	{
		delete p;
	}
	memset(pOverlays, NULL, sizeof(pOverlays));
}

void TitleScene::Update(void)
{
	pAnimator->Play(pOverlays[1]->GetSprite());

	if (GameControl::GetKeyTrigger(GameControl::JUMP))
	{
		Game::ChangeScene(Game::SCENE_TEST);
	}
}

void TitleScene::Draw(void)
{
	for (GameOverlay* p : pOverlays)
	{
		if (NULL == p) continue;
		p->Draw();
	}
}

void TitleScene::Debug(void)
{

}

void TitleScene::UpdatePlayer(void)
{

}

void TitleScene::UpdateObject(void)
{

}

void TitleScene::UpdateOverlay(void)
{

}
