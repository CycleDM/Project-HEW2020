//----------------------------------------------------------------------------
// 
// Project-HEW2020 [control.cpp]
// キーボードとコントローラー操作のモジュール
// 
// Date:   2020/10/29
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include "keyboard.h"
#include "controller.h"

//-----------------------------------------------------------------------------
// グローバル変数宣言
//-----------------------------------------------------------------------------
KeyMapType Controller::currentKeyState = 0; // そのフレームでキーの状態保持用
KeyMapType Controller::prevKeyState = 0;    // 前フレームでのキーの状態保持用
KeyMapType Controller::triggerKeyState = 0; // トリガー状態の確認用
KeyMapType Controller::releaseKeyState = 0; // リリース状態の確認用

// キーの変換表
static const Keyboard_Keys g_KKs[Controller::MAX] = {
    KK_W,
    KK_S,
    KK_A,
    KK_D,
    KK_SPACE,
    KK_F3,
};

void Controller::Init(void)
{
    currentKeyState = 0;
    prevKeyState = 0;
    triggerKeyState = 0;
    releaseKeyState = 0;
}

void Controller::Uninit(void)
{

}

void Controller::Update(void)
{
    // 前フレームのキー状態を保存しておく
    prevKeyState = currentKeyState;

    currentKeyState = 0;

    // キーの状態取得
    for (int i = 0; i < MAX; i++)
    {
        if (Keyboard_IsKeyDown(g_KKs[i]))
        {
            currentKeyState |= 1u << i;
        }
    }

    // 押した瞬間と離した瞬間のキーを取得
    triggerKeyState = (prevKeyState ^ currentKeyState) & currentKeyState;
    releaseKeyState = (prevKeyState ^ currentKeyState) & prevKeyState;
}

bool Controller::GetKeyPress(KeyMap key)
{
    return currentKeyState & (1u << key);
}

bool Controller::GetKeyTrigger(KeyMap key)
{
    return triggerKeyState & (1u << key);
}

bool Controller::GetKeyRelease(KeyMap key)
{
    return releaseKeyState & (1u << key);
}