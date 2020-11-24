//----------------------------------------------------------------------------
// 
// Project-HEW2020 [debug_font.h]
// �f�o�b�O�����̕\��
// 
// Date:   2020/11/04
// Author: AT12D187_17_���i
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

