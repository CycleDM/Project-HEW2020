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

private:
	static GameScene* pActScene;
	static SceneType eNowScene;
	static bool bDebugMode;
};