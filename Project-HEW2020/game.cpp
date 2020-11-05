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
#include "test_scene.h"
#include "controller.h"
#include "object.h"

//-----------------------------------------------------------------------------
// グローバル変数宣言
//-----------------------------------------------------------------------------
static Controller* g_pController = NULL;
static TestScene* g_pGameScene = NULL;

// ゲームの初期化
void Game_Init(void)
{
	g_pController = new Controller;			// コントローラーのインスタンスを作成
	g_pGameScene = new TestScene;			// シーンのインスタンスを作成
}

// ゲームの更新
void Game_Update(void)
{
	// プレイヤー操作
	GamePlayer* player = g_pGameScene->GetPlayer();
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
		GameObject* ladder = g_pGameScene->GetNearestLadder();
		if (NULL != ladder)
		{
			D3DXVECTOR2 ladderPos = ladder->GetPosition();
			D3DXVECTOR2 playerPos = player->GetPosition();
			player->SetPosition(ladderPos.x, playerPos.y);
			player->ClimbUp();
			player->SetClimbUpStatus(true);
		}
		else
		{
			player->SetClimbUpStatus(false);
		}
	}
	if (g_pController->GetKeyRelease(Controller::UP))
	{
		player->SetClimbUpStatus(false);
	}
	// Climb down
	if (g_pController->GetKeyPress(Controller::DOWN))
	{
		GameObject* ladder = g_pGameScene->GetNearestLadder();
		if (NULL != ladder)
		{
			D3DXVECTOR2 ladderPos = ladder->GetPosition();
			D3DXVECTOR2 playerPos = player->GetPosition();
			player->SetPosition(ladderPos.x, playerPos.y);
			player->ClimbDown();
			player->SetClimbDownStatus(true);
		}
		else
		{
			player->SetClimbDownStatus(false);
		}
	}
	if (g_pController->GetKeyRelease(Controller::DOWN))
	{
		player->SetClimbDownStatus(false);
	}
	//if (g_pController->GetKeyPress(Controller::JUMP))
	//{
	//	g_pPlayer->Jump();
	//}

	g_pController->Update();
	g_pGameScene->Update();
	player->Update();
}

// ゲームの描画
void Game_Draw(void)
{
	g_pGameScene->Draw();
}

// ゲームの終了処理
void Game_Uninit(void)
{
	delete g_pGameScene;
	delete g_pController;

	g_pController = NULL;
	g_pGameScene = NULL;
}

TestScene* Game_GetScene(void)
{
	return g_pGameScene;
}