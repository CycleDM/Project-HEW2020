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
#include "game.h"
#include "d3dutility.h"
#include "fade.h"

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
	GameScene::Freeze(false);
	SetGlobalScaling(1.0f);
	fBgScroll = D3DXVECTOR2(0.0f, 0.0f);
	fGroundHeight = 64.0f;

	// BG
	pOverlays[0] = new GameOverlay(TEXTURE_TITLE_BG);
	pOverlays[0]->SetScreenPos((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2);
	pOverlays[0]->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	pOverlays[0]->GetSprite()->SetCutPos(0, 0);
	pOverlays[0]->GetSprite()->SetCutRange(640, 360);
	pAnimator = new Animator;
	pAnimator->Init(pOverlays[0]->GetSprite());
	pAnimator->Preset(2, 1, 24);

	// LOGO
	pOverlays[1] = new GameOverlay(TEXTURE_TITLE_LOGO);
	pOverlays[1]->SetScreenPos((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2);
	pOverlays[1]->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);

	// BUTTON1
	pOverlays[2] = new GameOverlay(TEXTURE_TITLE_BUTTON01);
	pOverlays[2]->SetScreenPos((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2);
	pOverlays[2]->SetScale(1.5f);
	pOverlays[2]->GetSprite()->SetColor(D3DCOLOR_RGBA(255, 255, 255, 155));
	//pOverlays[2]->SetSize((float)pOverlays[2]->GetSprite()->GetTextureWidth() / 2, (float)pOverlays[2]->GetSprite()->GetTextureHeight() / 2);

	// BUTTON2
	pOverlays[3] = new GameOverlay(TEXTURE_TITLE_BUTTON02);
	pOverlays[3]->SetScreenPos((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2 + 100);
	pOverlays[3]->SetScale(1.5f);
	pOverlays[3]->GetSprite()->SetColor(D3DCOLOR_RGBA(255, 255, 255, 155));
	//pOverlays[3]->SetSize((float)pOverlays[3]->GetSprite()->GetTextureWidth() / 2, (float)pOverlays[3]->GetSprite()->GetTextureHeight() / 2);

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
	pAnimator->Play(pOverlays[0]->GetSprite());

	if (FadeEffect::IsFading()) return;
	UpdateTitleButton();
}

void TitleScene::Draw(void)
{
	for (GameOverlay* p : pOverlays)
	{
		if (NULL == p) continue;
		p->Draw();
	}
#ifdef _DEBUG
	// デバッグ文字の表示
	if (Game::DebugMode()) this->Debug();
#endif // _DEBUG
}

#ifdef _DEBUG
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
#endif // _DEBUG

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
	if (bFrozen) return;
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

	pOverlays[2]->GetSprite()->SetColor(D3DCOLOR_RGBA(255, 255, 255, 155));
	pOverlays[3]->GetSprite()->SetColor(D3DCOLOR_RGBA(255, 255, 255, 155));
	switch (buttonSelected)
	{
	case 0:
		pOverlays[2]->GetSprite()->SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
		break;
	case 1:
		pOverlays[3]->GetSprite()->SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
		break;
	case -1:
	default:
		break;
	}

	if (buttonSelected == 0 && Input::GetMouseButtonTrigger(0))
	{
		Game::LoadNextScene(Game::SCENE_01);
	}
	if (buttonSelected == 1 && Input::GetMouseButtonTrigger(0))
	{
		SendMessage(Game::GetWindow(), WM_CLOSE, 0, 0);
	}
}
