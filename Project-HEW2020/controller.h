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
	// キー入力状態の取得
	// 引数:
	//	key	... キーマップのキー
	bool GetKeyPress(KeyMap key);
	// キー入力状態の取得（押した瞬間）
	// 引数:
	//	key	... キーマップのキー
	bool GetKeyTrigger(KeyMap key);
	// キー入力状態の取得（離した瞬間）
	// 引数:
	//	key	... キーマップのキー
	bool GetKeyRelease(KeyMap key);
private:
	static KeyMapType currentKeyState; // そのフレームでキーの状態保持用
	static KeyMapType prevKeyState;    // 前フレームでのキーの状態保持用
	static KeyMapType triggerKeyState; // トリガー状態の確認用
	static KeyMapType releaseKeyState; // リリース状態の確認用
};