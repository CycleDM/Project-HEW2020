//----------------------------------------------------------------------------
// 
// Project-HEW2020 [game.cpp]
// ゲーム制御モジュール
// 
// Date:   2020/10/28
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#include <cmath>
#include "game.h"
#include "config.h"
#include "controller.h"
#include "sprite.h"
#include "player.h"
#include "TitleScene.h"
#include "TestScene.h"

//-----------------------------------------------------------------------------
// グローバル変数宣言
//-----------------------------------------------------------------------------
Game::SceneType Game::eNowScene = SCENE_TITLE;
GameScene* Game::pActScene = NULL;
bool Game::bDebugMode = false;

// ゲームの初期化
void Game::Init(void)
{
	delete pActScene;
	pActScene = NULL;

	switch (eNowScene)
	{
	case Game::SCENE_TITLE:
		pActScene = new TitleScene;
		break;
	case Game::SCENE_TEST:
		pActScene = new TestScene;
		break;
	case Game::SCENE_FINAL:
		break;
	default:
		break;
	}
}

// ゲームの更新
void Game::Update(void)
{
	if (NULL == pActScene) return;

	pActScene->Update();

	// Switch Debug Mode
	if (GameControl::GetKeyTrigger(GameControl::DEBUG))
	{
		bDebugMode = bDebugMode ? false : true;
	}
}

// ゲームの描画
void Game::Draw(void)
{
	if (NULL == pActScene) return;
	pActScene->Draw();
}

// ゲームの終了処理
void Game::Uninit(void)
{
	// メモリ解放
	delete pActScene;
	pActScene = NULL;

}

// デバッグの状態を取得
bool Game::DebugMode(void)
{
	return bDebugMode;
}

void Game::ChangeScene(Game::SceneType type)
{
	eNowScene = type;
	Init();
}