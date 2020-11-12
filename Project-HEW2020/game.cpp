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
#include "config.h"
#include "sprite.h"
#include "player.h"
#include "controller.h"
#include "scene.h"
#include "TestScene.h"

//-----------------------------------------------------------------------------
// グローバル変数宣言
//-----------------------------------------------------------------------------
static Controller* g_pController = NULL;
static GameScene* g_pScene = NULL;
static bool g_bDebugMode = false;

// ゲームの初期化
void Game_Init(void)
{
	g_pController = new Controller;			// コントローラーのインスタンスを作成
	g_pScene = new TestScene;
}

// ゲームの更新
void Game_Update(void)
{
	// プレイヤー操作
	GamePlayer* player = g_pScene->GetPlayer();
	if (g_pController->GetKeyPress(Controller::LEFT))
	{
		player->MoveLeft();
	}
	if (g_pController->GetKeyPress(Controller::RIGHT))
	{
		player->MoveRight();
	}
	// Climb up
	if (g_pController->GetKeyPress(Controller::UP))
	{
		GameObject* obj = g_pScene->GetNearestObject(GameObject::OBJ_LADDER);
		player->SetGlobalPos(obj->GetGlobalPos().x, obj->GetGlobalPos().y);
	}
	if (g_pController->GetKeyRelease(Controller::UP))
	{
	}
	// Climb down
	if (g_pController->GetKeyPress(Controller::DOWN))
	{
	}
	if (g_pController->GetKeyRelease(Controller::DOWN))
	{
	}
	// Switch Debug Mode
	if (g_pController->GetKeyTrigger(Controller::DEBUG))
	{
		g_bDebugMode = g_bDebugMode ? false : true;
	}
	//if (g_pController->GetKeyPress(Controller::JUMP))
	//{
	//	player->Jump();
	//}

	g_pController->Update();
	g_pScene->Update();
}

// ゲームの描画
void Game_Draw(void)
{
	g_pScene->Draw();
}

// ゲームの終了処理
void Game_Uninit(void)
{
	delete g_pScene;
	g_pScene = NULL;

	delete g_pController;
	g_pController = NULL;
}

// デバッグの状態を取得
bool Game_IsDebugMode(void)
{
	return g_bDebugMode;
}