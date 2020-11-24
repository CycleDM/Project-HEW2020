//----------------------------------------------------------------------------
// 
// Project-HEW2020 [debug_font.h]
// デバッグ文字の表示
// 
// Date:   2020/11/04
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#pragma once

#include "sprite.h"

class DebugFont
{
public:
	static void Init(void);
	static void Uninit(void);
	static void Draw(float dx, float dy, const char* pString);
private:
	static Sprite* pSpriteDebug;
};

