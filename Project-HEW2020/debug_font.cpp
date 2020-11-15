//----------------------------------------------------------------------------
// 
// Project-HEW2020 [debug_font.cpp]
// �f�o�b�O�����̕\��
// 
// Date:   2020/11/04
// Author: AT12D187_17_���i
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
// �O���[�o���ϐ��錾
//-----------------------------------------------------------------------------
static Sprite* g_pSpriteDebug = NULL;

// �f�o�b�O�t�H���g���W���[���̏�����
void DebugFont_Init(void)
{
    g_pSpriteDebug = new SpriteNormal(TEXTURE_DEBUG);
    g_pSpriteDebug->SetCutRange((float)DEBUG_FONT_WIDTH, (float)DEBUG_FONT_HEIGHT);
    g_pSpriteDebug->SetPolygonSize(DEBUG_FONT_DRAW_WIDTH, DEBUG_FONT_DRAW_HEIGHT);
    g_pSpriteDebug->SetColor(D3DCOLOR_RGBA(255, 200, 150, 255));
}

// �f�o�b�O�t�H���g���W���[���̏I������
void DebugFont_Uninit(void)
{
    // ���������
    delete g_pSpriteDebug;
    g_pSpriteDebug = NULL;
}

void DebugFont_Draw(float dx, float dy, const char *pString)
{
    for (int i = 0; i < strlen(pString); i++)
    {
        int offset = pString[i] - ' ';
        float tcx = (float)(offset % DEBUG_FONT_START_CHAR_CODE * DEBUG_FONT_WIDTH);
        float tcy = (float)(offset / DEBUG_FONT_ONE_LINE_CHAR_COUNT * DEBUG_FONT_HEIGHT);

        g_pSpriteDebug->SetCutPos(tcx, tcy);
        g_pSpriteDebug->SetDrawPos(dx + i * DEBUG_FONT_DRAW_WIDTH, dy);
        g_pSpriteDebug->Draw();
    }
}