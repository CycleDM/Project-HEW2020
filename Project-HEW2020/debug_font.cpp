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

#define DEBUG_FONT_WIDTH                (32)
#define DEBUG_FONT_HEIGHT               (64)
#define DEBUG_FONT_DRAW_WIDTH           (16.0f)
#define DEBUG_FONT_DRAW_HEIGHT          (32.0f)
#define DEBUG_FONT_START_CHAR_CODE      (32)
#define DEBUG_FONT_ONE_LINE_CHAR_COUNT  (16)

//-----------------------------------------------------------------------------
// グローバル変数宣言
//-----------------------------------------------------------------------------
Sprite* DebugFont::pSpriteDebug = NULL;

// デバッグフォントモジュールの初期化
void DebugFont::Init(void)
{
    delete pSpriteDebug;

    pSpriteDebug = new SpriteNormal(TEXTURE_DEBUG);
    pSpriteDebug->SetCutRange(DEBUG_FONT_WIDTH, DEBUG_FONT_HEIGHT);
    pSpriteDebug->SetPolygonSize(DEBUG_FONT_DRAW_WIDTH, DEBUG_FONT_DRAW_HEIGHT);
    pSpriteDebug->SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
}

// デバッグフォントモジュールの終了処理
void DebugFont::Uninit(void)
{
    // メモリ解放
    delete pSpriteDebug;
    pSpriteDebug = NULL;
}

void DebugFont::Draw(float dx, float dy, const char *pString)
{
    for (int i = 0; i < strlen(pString); i++)
    {
        int offset = pString[i] - ' ';
        int tcx = (offset % DEBUG_FONT_START_CHAR_CODE * DEBUG_FONT_WIDTH);
        int tcy = (offset / DEBUG_FONT_ONE_LINE_CHAR_COUNT * DEBUG_FONT_HEIGHT);

        pSpriteDebug->SetCutPos(tcx, tcy);
        pSpriteDebug->SetDrawPos(dx + i * DEBUG_FONT_DRAW_WIDTH, dy);
        pSpriteDebug->Draw();
    }
}