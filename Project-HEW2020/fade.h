//----------------------------------------------------------------------------
// 
// Project-HEW2020 [fade.h]
// フェードエフェクト
// 
// Date:   2020/11/25
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#pragma once

#include <d3dx9.h>
#include "sprite.h"

enum FadeMode
{
	FADE_NONE,
	FADE_IN,
	FADE_OUT,
	FADE_MAX
};

class FadeEffect
{
public:
	static void Init(void);
	static void Uninit(void);
	static void Update(void);
	static void Draw(void);
	static void Start(FadeMode mode, float r, float g, float b, int frame);
	static bool IsFading(void);

private:
	static FadeMode fadeMode;
	static D3DXCOLOR color;
	static float fProp;
	static int nFadeFrame;
	static int nFrameCount;
	static int nFadeStartFrame;
	static Sprite* pSprite;
};

