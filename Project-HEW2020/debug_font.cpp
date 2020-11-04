//----------------------------------------------------------------------------
// 
// Project-HEW2020 [debug_font.cpp]
// デバッグ文字の表示
// 
// Date:   2020/11/04
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#include <string.h>
#include "debug_font.h"
#include "sprite.h"
#include "config.h"

#define DEBUG_FONT_WIDTH (32)
#define DEBUG_FONT_HEIGHT (64)
#define DEBUG_FONT_START_CHAR_CODE (32)
#define DEBUG_FONT_ONE_LINE_CHAR_COUNT (16)

//-----------------------------------------------------------------------------
// グローバル変数宣言
//-----------------------------------------------------------------------------
static Sprite* g_pSpriteDebug = NULL;

// デバッグフォントモジュールの初期化
void DebugFont_Init(void)
{
    g_pSpriteDebug = new SpriteNormal(TEXTURE_DEBUG);
    g_pSpriteDebug->SetCutRange(DEBUG_FONT_WIDTH, DEBUG_FONT_HEIGHT);
    g_pSpriteDebug->SetPolygonSize(32.0f, 64.0f);
    g_pSpriteDebug->SetColor(D3DCOLOR_RGBA(155, 155, 255, 255));
}

// デバッグフォントモジュールの終了処理
void DebugFont_Uninit(void)
{
    delete g_pSpriteDebug;
    g_pSpriteDebug = NULL;
}

void DebugFont_Draw(float dx, float dy, const char *pString)
{
    for (int i = 0; i < strlen(pString); i++)
    {
        int offset = pString[i] - ' ';
        int tcx = offset % DEBUG_FONT_START_CHAR_CODE * DEBUG_FONT_WIDTH;
        int tcy = offset / DEBUG_FONT_ONE_LINE_CHAR_COUNT * DEBUG_FONT_HEIGHT;

        g_pSpriteDebug->SetCutPos(tcx, tcy);
        g_pSpriteDebug->SetDrawPos(dx + i * DEBUG_FONT_WIDTH, dy);
        g_pSpriteDebug->Draw();
    }
}