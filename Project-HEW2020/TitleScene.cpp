//----------------------------------------------------------------------------
// 
// Project-HEW2020 [TitleScene.cpp]
// タイトル画面シーン
// 
// Date:   2020/11/27
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#include <stdio.h>
#include "TitleScene.h"
#include "controller.h"
#include "game.h"
#include "fade.h"
#include "d3dutility.h"

static DIMOUSESTATE g_MouseState = { 0 };

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
	pOverlays[2]->SetSize((float)pOverlays[2]->GetSprite()->GetTextureWidth() / 2, (float)pOverlays[2]->GetSprite()->GetTextureHeight() / 2);

	// BUTTON2
	pOverlays[3] = new GameOverlay("assets/texture/title_button2.png");
	pOverlays[3]->SetScreenPos((float)SCREEN_WIDTH / 2, 550.0f);
	pOverlays[3]->SetSize((float)pOverlays[3]->GetSprite()->GetTextureWidth() / 2, (float)pOverlays[3]->GetSprite()->GetTextureHeight() / 2);

	FadeEffect::Start(FADE_IN, 0.0f, 0.0f, 0.0f, 30);

	buttonSelected = -1;
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

	UpdateTitleButton();

	if (buttonSelected == 0 && Input::GetMouseButtonTrigger(0) || GameControl::GetKeyTrigger(GameControl::JUMP))
	{
		Game::SwitchScene(Game::SCENE_01);
	}
	if (buttonSelected == 1 && Input::GetMouseButtonTrigger(0))
	{
		SendMessage(Game::GetWindow(), WM_CLOSE, 0, 0);
	}
}

void TitleScene::Draw(void)
{
	for (GameOverlay* p : pOverlays)
	{
		if (NULL == p) continue;
		p->Draw();
	}

	// デバッグ文字の表示
	if (Game::DebugMode()) this->Debug();
}

void TitleScene::Debug(void)
{
	char buf[1024];
	int y = 32;

	sprintf_s(buf, "Button1 = (%.2f, %.2f)", pOverlays[2]->GetScreenPos().x, pOverlays[2]->GetScreenPos().y);
	y += 32;
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);
	sprintf_s(buf, "Button2 = (%.2f, %.2f)", pOverlays[3]->GetScreenPos().x, pOverlays[3]->GetScreenPos().y);
	y += 32;
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);
	sprintf_s(buf, "[Mouse States]");
	y += 32;
	D3DFont::Draw(0, y, buf, FONT_NAME, 32, D3DCOLOR_RGBA(100, 220, 255, 255));
	sprintf_s(buf, ">LB = %d", Input::GetMouseButtonPress(0));
	y += 32;
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);
	sprintf_s(buf, ">RB = %d", Input::GetMouseButtonPress(1));
	y += 32;
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);
	sprintf_s(buf, ">MB = %d", Input::GetMouseButtonPress(2));
	y += 32;
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);
	sprintf_s(buf, ">deltaX = %d", Input::GetMouseDeltaX());
	y += 32;
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);
	sprintf_s(buf, ">deltaY = %d", Input::GetMouseDeltaY());
	y += 32;
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);
	sprintf_s(buf, ">deltaWheel = %d", Input::GetMouseDeltaWheel());
	y += 32;
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);
	sprintf_s(buf, ">PosX = %d", Input::GetMouseX());
	y += 32;
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);
	sprintf_s(buf, ">PosY = %d", Input::GetMouseY());
	y += 32;
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);
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

void TitleScene::UpdateTitleButton(void)
{
	for (int i = 0; i < 2; i++)
	{
		GameOverlay* po = pOverlays[2 + i];
		if (Input::GetMouseX() > po->GetScreenPos().x - po->GetWidth() / 2 &&
			Input::GetMouseX() < po->GetScreenPos().x + po->GetWidth() / 2 &&
			Input::GetMouseY() > po->GetScreenPos().y - po->GetHeight() / 2 &&
			Input::GetMouseY() < po->GetScreenPos().y + po->GetHeight() / 2)
		{
			buttonSelected = i;
			break;
		}
		else
		{
			buttonSelected = -1;
		}
	}

	pOverlays[2]->SetSize((float)pOverlays[2]->GetSprite()->GetTextureWidth() / 2, (float)pOverlays[2]->GetSprite()->GetTextureHeight() / 2);
	pOverlays[3]->SetSize((float)pOverlays[3]->GetSprite()->GetTextureWidth() / 2, (float)pOverlays[3]->GetSprite()->GetTextureHeight() / 2);
	switch (buttonSelected)
	{
	case 0:
		pOverlays[2]->SetSize((float)pOverlays[2]->GetSprite()->GetTextureWidth() / 2 * 1.2f, (float)pOverlays[2]->GetSprite()->GetTextureHeight() / 2 * 1.2f);
		break;
	case 1:
		pOverlays[3]->SetSize((float)pOverlays[3]->GetSprite()->GetTextureWidth() / 2 * 1.2f, (float)pOverlays[3]->GetSprite()->GetTextureHeight() / 2 * 1.2f);
		break;
	case -1:
	default:
		break;
	}
}
