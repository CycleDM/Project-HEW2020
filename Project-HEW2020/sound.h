//=============================================================================
//
// サウンド処理 [sound.h]
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include <windows.h>
#include "xaudio2.h"						// サウンド処理で必要

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000,				// BGM0
	SOUND_LABEL_BGM001,				// BGM1
	SOUND_LABEL_SE_WALK,
	SOUND_LABEL_SE_TITLE_BUTTON,
	SOUND_LABEL_SE_PICKUP,
	SOUND_LABEL_SE_PICKUP_LEG,
	SOUND_LABEL_SE_DOOR_OPEN1,
	SOUND_LABEL_SE_DOOR_OPEN2,
	SOUND_LABEL_SE_GENERATOR_UI,
	SOUND_LABEL_SE_GENERATOR_POWER,
	SOUND_LABEL_SE_SCREEN_OPEN,
	SOUND_LABEL_SE_LANGUAGE,
	SOUND_LABEL_SE_VISUAL,
	SOUND_LABEL_SE_LIFT_OPEN,
	SOUND_LABEL_SE_LIFT_LIFTING,
	SOUND_LABEL_SE_BUTTON,
	SOUND_LABEL_SE_CORRECT,
	SOUND_LABEL_SE_WRONG,
	SOUND_LABEL_SE_ITEM_DROP,
	SOUND_LABEL_SE_KEYBOARD,
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
bool InitSound(HWND hWnd);
void UninitSound(void);
void PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);
void SetVolume(SOUND_LABEL label, float fVolume);

#endif
