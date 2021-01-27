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

#include <thread>
#include "scene.h"
#include "loadingscreen.h"

using namespace std;

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
	static void InitSceneThread(GameScene** pTarget = NULL, bool* flag = NULL);
	static void Uninit(void);
	static void UninitScene(void);

	static void Update(void);
	static void Draw(void);

	static bool DebugMode(void);

	static void LoadNextScene(Game::SceneType type);

	static void BindWindow(HWND hWnd, int window_width, int window_height);
	static void SetFocus(bool onFocus);
	static HWND GetWindow(void);
private:
	static HWND hWnd;
	static GameScene* pActScene;
	static SceneType eNowScene;
	static SceneType eNextScene;
	static LoadingScreen* pLoadingScreen;

	static bool onFocus;
	static int window_width;
	static int window_height;

	static bool bLoadingFlag;
	static bool bDebugMode;

	static thread lt;
};