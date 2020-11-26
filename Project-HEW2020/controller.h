//----------------------------------------------------------------------------
// 
// Project-HEW2020 [control.h]
// �L�[�{�[�h�ƃR���g���[���[����̃��W���[��
// 
// Date:   2020/10/29
// Author: AT12D187_17_���i
// 
//----------------------------------------------------------------------------
#pragma once

typedef unsigned long long KeyMapType;
typedef unsigned int ControllerIndex;

// KeyboardKey
enum class KK : ControllerIndex
{
	W,
	A,
	S,
	D,
	SPACE,
	F3,
	MAX
};

// XboxButton
enum class XB : ControllerIndex
{
	UP = (int)KK::MAX + 1,
	DOWN,
	LEFT,
	RIGHT,
	A,
	B,
	X,
	Y,
	MAX
};

class GameControl
{
public:
	enum KeyMap
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		USE,
		QUIT,
		JUMP,
		DEBUG,
		MAX
	};

	static void Init(void);
	static void Update(void);
	// �L�[���͏�Ԃ̎擾
	// ����:
	//	key	... �L�[�}�b�v�̃L�[
	static bool GetKeyPress(KeyMap key);
	// �L�[���͏�Ԃ̎擾�i�������u�ԁj
	// ����:
	//	key	... �L�[�}�b�v�̃L�[
	static bool GetKeyTrigger(KeyMap key);
	// �L�[���͏�Ԃ̎擾�i�������u�ԁj
	// ����:
	//	key	... �L�[�}�b�v�̃L�[
	static bool GetKeyRelease(KeyMap key);
private:
	static KeyMapType currentKeyState; // ���̃t���[���ŃL�[�̏�ԕێ��p
	static KeyMapType prevKeyState;    // �O�t���[���ł̃L�[�̏�ԕێ��p
	static KeyMapType triggerKeyState; // �g���K�[��Ԃ̊m�F�p
	static KeyMapType releaseKeyState; // �����[�X��Ԃ̊m�F�p
};