//----------------------------------------------------------------------------
// 
// Project-HEW2020 [control.h]
// キーボードとコントローラー操作のモジュール
// 
// Date:   2020/10/29
// Author: AT12D187_17_周進
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
	// キー入力状態の取得
	// 引数:
	//	key	... キーマップのキー
	static bool GetKeyPress(KeyMap key);
	// キー入力状態の取得（押した瞬間）
	// 引数:
	//	key	... キーマップのキー
	static bool GetKeyTrigger(KeyMap key);
	// キー入力状態の取得（離した瞬間）
	// 引数:
	//	key	... キーマップのキー
	static bool GetKeyRelease(KeyMap key);
private:
	static KeyMapType currentKeyState; // そのフレームでキーの状態保持用
	static KeyMapType prevKeyState;    // 前フレームでのキーの状態保持用
	static KeyMapType triggerKeyState; // トリガー状態の確認用
	static KeyMapType releaseKeyState; // リリース状態の確認用
};