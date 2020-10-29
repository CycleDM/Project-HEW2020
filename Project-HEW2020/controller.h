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
class Controller
{
public:
	enum KeyMap
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		JUMP,
		MAX
	};

	Controller();
	~Controller();

	void Init(void);
	void Uninit(void);
	void Update(void);
	// �L�[���͏�Ԃ̎擾
	// ����:
	//	key	... �L�[�}�b�v�̃L�[
	bool GetKeyPress(KeyMap key);
	// �L�[���͏�Ԃ̎擾�i�������u�ԁj
	// ����:
	//	key	... �L�[�}�b�v�̃L�[
	bool GetKeyTrigger(KeyMap key);
	// �L�[���͏�Ԃ̎擾�i�������u�ԁj
	// ����:
	//	key	... �L�[�}�b�v�̃L�[
	bool GetKeyRelease(KeyMap key);
private:
	static KeyMapType currentKeyState; // ���̃t���[���ŃL�[�̏�ԕێ��p
	static KeyMapType prevKeyState;    // �O�t���[���ł̃L�[�̏�ԕێ��p
	static KeyMapType triggerKeyState; // �g���K�[��Ԃ̊m�F�p
	static KeyMapType releaseKeyState; // �����[�X��Ԃ̊m�F�p
};