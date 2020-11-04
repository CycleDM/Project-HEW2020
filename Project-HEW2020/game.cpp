//----------------------------------------------------------------------------
// 
// Project-HEW2020 [game.cpp]
// ゲーム制御モジュール
// 
// Date:   2020/10/28
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#include "config.h"
#include "sprite.h"
#include "player.h"
#include "background.h"
#include "controller.h"

//-----------------------------------------------------------------------------
// グローバル変数宣言
//-----------------------------------------------------------------------------
static Controller* g_pController = NULL;
static GameBackground* g_pBackground = NULL;
static GamePlayer* g_pPlayer = NULL;

// ゲームの初期化
void Game_Init(void)
{
	g_pController = new Controller;			// コントローラーのインスタンスを作成
	g_pBackground = new GameBackground;		// 背景のインスタンスを作成
	g_pPlayer = new GamePlayer;				//　プレイヤーのインスタンスを作成
}

// ゲームの更新
void Game_Update(void)
{
	// プレイヤー操作
	if (g_pController->GetKeyPress(Controller::LEFT))
	{
		g_pPlayer->MoveLeft();
	}
	if (g_pController->GetKeyPress(Controller::RIGHT))
	{
		g_pPlayer->MoveRight();
	}
	//if (g_pController->GetKeyPress(Controller::JUMP))
	//{
	//	g_pPlayer->SetJump();
	//}

	g_pController->Update();
	g_pBackground->Update();
	g_pPlayer->Update();
}

// ゲームの描画
void Game_Draw(void)
{
	g_pBackground->Draw();
	g_pPlayer->Draw();
}

// ゲームの終了処理
void Game_Uninit(void)
{
	delete g_pPlayer;
	delete g_pBackground;
	delete g_pController;

	g_pController = NULL;
	g_pPlayer = NULL;
	g_pBackground = NULL;
}

// プレイヤーのインスタンスを取得
GamePlayer* Game_GetPlayer(void)
{
	return g_pPlayer;
}