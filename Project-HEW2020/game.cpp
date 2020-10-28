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

//-----------------------------------------------------------------------------
// グローバル変数宣言
//-----------------------------------------------------------------------------
static Player* g_pPlayer = NULL;

// ゲームの初期化
void Game_Init(void)
{
	g_pPlayer = new Player;
}

// ゲームの更新
void Game_Update(void)
{

}

// ゲームの描画
void Game_Draw(void)
{
	g_pPlayer->Draw();
}

// ゲームの終了処理
void Game_Uninit(void)
{
	delete g_pPlayer;
	g_pPlayer = NULL;
}