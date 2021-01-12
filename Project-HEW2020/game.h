//----------------------------------------------------------------------------
// 
// Project-HEW2020 [game.h]
// ゲーム制御モジュール
// 
// Date:   2020/10/28
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#pragma once

#include "scene.h"

class Game
{
public:
	enum SceneType
	{
		SCENE_TITLE,
		SCENE_01,
		SCENE_02,
		SCENE_03,
		SCENE_TEST,
		SCENE_FINAL,
		SCENE_MAX
	};
	static void Init(void);
	static void Update(void);
	static void Draw(void);
	static void Uninit(void);
	static bool DebugMode(void);

	static void ChangeScene(Game::SceneType type);

	static void BindWindow(HWND hWnd, int window_width, int window_height);
	static long GetMouseX(void);
	static long GetMouseY(void);
	static void SetFocus(bool onFocus);
	static HWND GetWindow(void);
private:
	static HWND hWnd;
	static GameScene* pActScene;
	static SceneType eNowScene;

	static POINT mousePosition;
	static bool onFocus;
	static int window_width;
	static int window_height;

	static bool bDebugMode;
};