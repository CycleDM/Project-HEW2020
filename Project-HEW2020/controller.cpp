//----------------------------------------------------------------------------
// 
// Project-HEW2020 [control.cpp]
// �L�[�{�[�h�ƃR���g���[���[����̃��W���[��
// 
// Date:   2020/10/29
// Author: AT12D187_17_���i
// 
//----------------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include "keyboard.h"
#include "controller.h"

//-----------------------------------------------------------------------------
// �O���[�o���ϐ��錾
//-----------------------------------------------------------------------------
KeyMapType GameControl::currentKeyState = 0; // ���̃t���[���ŃL�[�̏�ԕێ��p
KeyMapType GameControl::prevKeyState = 0;    // �O�t���[���ł̃L�[�̏�ԕێ��p
KeyMapType GameControl::triggerKeyState = 0; // �g���K�[��Ԃ̊m�F�p
KeyMapType GameControl::releaseKeyState = 0; // �����[�X��Ԃ̊m�F�p

// �L�[�̕ϊ��\
static const Keyboard_Keys g_KKs[GameControl::KeyMap::MAX] = {
    KK_W,
    KK_S,
    KK_A,
    KK_D,
    KK_SPACE,
    KK_F3,
};

void GameControl::Init(void)
{
    currentKeyState = 0;
    prevKeyState = 0;
    triggerKeyState = 0;
    releaseKeyState = 0;
}

void GameControl::Update(void)
{
    // �O�t���[���̃L�[��Ԃ�ۑ����Ă���
    prevKeyState = currentKeyState;

    currentKeyState = 0;

    // �L�[�̏�Ԏ擾
    for (int i = 0; i < MAX; i++)
    {
        if (Keyboard_IsKeyDown(g_KKs[i]))
        {
            currentKeyState |= 1u << i;
        }
    }

    // �������u�ԂƗ������u�Ԃ̃L�[���擾
    triggerKeyState = (prevKeyState ^ currentKeyState) & currentKeyState;
    releaseKeyState = (prevKeyState ^ currentKeyState) & prevKeyState;
}

bool GameControl::GetKeyPress(KeyMap key)
{
    return currentKeyState & (1u << key);
}

bool GameControl::GetKeyTrigger(KeyMap key)
{
    return triggerKeyState & (1u << key);
}

bool GameControl::GetKeyRelease(KeyMap key)
{
    return releaseKeyState & (1u << key);
}