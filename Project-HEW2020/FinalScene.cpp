//----------------------------------------------------------------------------
// 
// Project-HEW2020 [FinalScene.cpp]
// クレジット画面
// 
// Date:   2020/01/29
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#include "FinalScene.h"
#include "d3dfont.h"
#include "config.h"
#include "game.h"

const string FinalScene::strThanks = "THANKS FOR PLAYING!";
const string FinalScene::strPlaner[2] = {
	"LEADER & PLANER",
	"Zibin Wang"
};
const string FinalScene::strProgrammer[2] = {
	"LEAD PROGRAMMER",
	"Jin Zhou"
};

const string FinalScene::strDesigner[4] = {
	"DESIGNER",
	"Siufai Wong",
	"Sinong Huang",
	"Weilin Wen"
};

const string FinalScene::strSpecial[2] = {
	"AND SPECIAL THANKS",
	"Ghost, China"
};

FinalScene::FinalScene()
{
	Init();
}

FinalScene::~FinalScene()
{
	Uninit();
}

void FinalScene::Init(void)
{
	frameCnt = 0;
	nPosYIndex = SCREEN_HEIGHT + 50;
	bFinished = false;
	bEndScene = false;

	pBgOverlay = new GameOverlay(TEXTURE_FADE);
	pBgOverlay->SetScreenPos((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2);
	pBgOverlay->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	pBgOverlay->GetSprite()->SetColor(D3DCOLOR_RGBA(0, 0, 0, 255));
}

void FinalScene::Uninit(void)
{
	delete pBgOverlay;
	pBgOverlay = NULL;
}

void FinalScene::Update(void)
{
	frameCnt++;
	if (frameCnt > 300)
	{
		nPosYIndex -= 1;
	}
	if (bEndScene) Game::LoadNextScene(Game::SceneType::SCENE_TITLE);
}

void FinalScene::Draw(void)
{
	pBgOverlay->Draw();

	do
	{
		if (bFinished) break;
		string str = "";
		int nFontSize = 0;
		int nOffsetY = 0;
		if (frameCnt <= 300)
		{
			nFontSize = 80;
			str = strThanks;
			D3DFont::Draw(SCREEN_WIDTH / 2 - str.length() * nFontSize / 4, SCREEN_HEIGHT / 2 - nFontSize / 2, str.c_str(), FONT_NAME, nFontSize);
			return;
		}
		// PLANER
		str = strPlaner[0];
		nFontSize = 48;
		if (nPosYIndex - nFontSize / 2 + nOffsetY > 0)
		{
			D3DFont::Draw(SCREEN_WIDTH / 2 - str.length() * nFontSize / 4, nPosYIndex - nFontSize / 2 + nOffsetY, str.c_str(), FONT_NAME, nFontSize);
		}
		nOffsetY += nFontSize / 2;
		str = strPlaner[1];
		nFontSize = 36;
		nOffsetY += 20;
		if (nPosYIndex - nFontSize / 2 + nOffsetY > 0)
		{
			D3DFont::Draw(SCREEN_WIDTH / 2 - str.length() * nFontSize / 4, nPosYIndex - nFontSize / 2 + nOffsetY, str.c_str(), FONT_NAME, nFontSize);
		}
		// PROGRAMMER
		nOffsetY += 80;
		str = strProgrammer[0];
		nFontSize = 48;
		if (nPosYIndex - nFontSize / 2 + nOffsetY > 0)
		{
			D3DFont::Draw(SCREEN_WIDTH / 2 - str.length() * nFontSize / 4, nPosYIndex - nFontSize / 2 + nOffsetY, str.c_str(), FONT_NAME, nFontSize);
		}
		nOffsetY += nFontSize / 2;
		str = strProgrammer[1];
		nFontSize = 36;
		nOffsetY += 20;
		if (nPosYIndex - nFontSize / 2 + nOffsetY > 0)
		{
			D3DFont::Draw(SCREEN_WIDTH / 2 - str.length() * nFontSize / 4, nPosYIndex - nFontSize / 2 + nOffsetY, str.c_str(), FONT_NAME, nFontSize);
		}
		nOffsetY += nFontSize / 2;

		// DESIGNER
		nOffsetY += 80;
		str = strDesigner[0];
		nFontSize = 48;
		if (nPosYIndex - nFontSize / 2 + nOffsetY > 0)
		{
			D3DFont::Draw(SCREEN_WIDTH / 2 - str.length() * nFontSize / 4, nPosYIndex - nFontSize / 2 + nOffsetY, str.c_str(), FONT_NAME, nFontSize);
		}
		nOffsetY += nFontSize / 2;
		str = strDesigner[1];
		nFontSize = 36;
		nOffsetY += 20;
		if (nPosYIndex - nFontSize / 2 + nOffsetY > 0)
		{
			D3DFont::Draw(SCREEN_WIDTH / 2 - str.length() * nFontSize / 4, nPosYIndex - nFontSize / 2 + nOffsetY, str.c_str(), FONT_NAME, nFontSize);
		}
		nOffsetY += nFontSize / 2;
		str = strDesigner[2];
		nFontSize = 36;
		nOffsetY += 20;
		if (nPosYIndex - nFontSize / 2 + nOffsetY > 0)
		{
			D3DFont::Draw(SCREEN_WIDTH / 2 - str.length() * nFontSize / 4, nPosYIndex - nFontSize / 2 + nOffsetY, str.c_str(), FONT_NAME, nFontSize);
		}
		nOffsetY += nFontSize / 2;
		str = strDesigner[3];
		nFontSize = 36;
		nOffsetY += 20;
		if (nPosYIndex - nFontSize / 2 + nOffsetY > 0)
		{
			D3DFont::Draw(SCREEN_WIDTH / 2 - str.length() * nFontSize / 4, nPosYIndex - nFontSize / 2 + nOffsetY, str.c_str(), FONT_NAME, nFontSize);
		}

		nOffsetY += 200;
		str = strSpecial[0];
		nFontSize = 48;
		if (nPosYIndex - nFontSize / 2 + nOffsetY > 0)
		{
			D3DFont::Draw(SCREEN_WIDTH / 2 - str.length() * nFontSize / 4, nPosYIndex - nFontSize / 2 + nOffsetY, str.c_str(), FONT_NAME, nFontSize);
		}
		nOffsetY += nFontSize / 2;
		str = strSpecial[1];
		nFontSize = 36;
		nOffsetY += 20;
		if (nPosYIndex - nFontSize / 2 + nOffsetY > 0)
		{
			D3DFont::Draw(SCREEN_WIDTH / 2 - str.length() * nFontSize / 4, nPosYIndex - nFontSize / 2 + nOffsetY, str.c_str(), FONT_NAME, nFontSize);
		}
		else
		{
			bFinished = true;
		}
	} while (0);
	

	if (!bFinished) return;
	string str = "Press Space";
	int nFontSize = 0;
	int nOffsetY = 0;
	nFontSize = 80;
	D3DFont::Draw(SCREEN_WIDTH / 2 - str.length() * nFontSize / 4, SCREEN_HEIGHT / 2 - nFontSize / 2, str.c_str(), FONT_NAME, nFontSize);

	if (Input::GetKeyPress(DIK_SPACE))
	{
		bEndScene = true;
	}
}

#ifdef _DEBUG
void FinalScene::Debug(void)
{

}
#endif // _DEBUG

void FinalScene::UpdatePlayer(void)
{
}
void FinalScene::UpdateObject(void)
{
}
void FinalScene::UpdateOverlay(void)
{
}