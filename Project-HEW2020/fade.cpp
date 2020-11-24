//----------------------------------------------------------------------------
// 
// Project-HEW2020 [fade.cpp]
// フェードエフェクト
// 
// Date:   2020/11/25
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#include "fade.h"
#include "config.h"

//-----------------------------------------------------------------------------
// グローバル変数宣言
//-----------------------------------------------------------------------------
FadeMode FadeEffect::fadeMode = FADE_NONE;
D3DXCOLOR FadeEffect::color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
float FadeEffect::fProp = 0.0f;
int FadeEffect::nFadeFrame = 0;
int FadeEffect::nFrameCount = 0;
int FadeEffect::nFadeStartFrame = 0;
Sprite* FadeEffect::pSprite = NULL;

void FadeEffect::Init()
{
	fadeMode = FADE_NONE;
	color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	fProp = 0.0f;
	nFadeFrame = 0;
	nFrameCount = 0;
	nFadeStartFrame = 0;

	delete pSprite;
	pSprite = new SpriteNormal(TEXTURE_FADE);

	pSprite->SetCutPos(0, 0);
	pSprite->SetCutRange(8, 8);
	pSprite->SetDrawPos(0.0f, 0.0f);
	pSprite->SetPolygonSize(float(SCREEN_WIDTH), (float)SCREEN_HEIGHT);
}

void FadeEffect::Uninit()
{
	delete pSprite;
	pSprite = NULL;
}

void FadeEffect::Update()
{
	nFrameCount++;
	// フェードしてなっかったら何もすることはない
	if (fadeMode == FADE_NONE) return;

	// 現在の進行フレーム数を算出
	int frame = nFrameCount - nFadeStartFrame;

	// 最終フェードフレーム数空０～１の進行割合を算出する
	fProp = (float)frame / nFadeFrame;

	// フェードの割合が１００％を超えていたら、終了
	if (fProp > 1.0f)
	{
		fadeMode = FADE_NONE;
	}
}

void FadeEffect::Draw()
{
	if (fadeMode != FADE_NONE)
	{
		color.a = fadeMode == FADE_IN ? 1.0f - fProp : fProp;
	}

	// ほぼ透明なので描画しない
	if (color.a <= 0.0001f) return;

	pSprite->SetColor(color);
	pSprite->Draw();
}

void FadeEffect::Start(FadeMode mode, float r, float g, float b, int frame)
{
	fadeMode = mode;
	color = D3DXCOLOR(r, g, b, 0.0f);
	fProp = 0.0f;
	nFadeFrame = frame;
	nFadeStartFrame = nFrameCount;
}

bool FadeEffect::IsFading(void)
{
	return fadeMode != FADE_NONE;
}