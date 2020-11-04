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

void DebugFont_Init(void);
void DebugFont_Uninit(void);
void DebugFont_Draw(float dx, float dy, const char *pString);

