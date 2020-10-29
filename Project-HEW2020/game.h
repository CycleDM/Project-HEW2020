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

#include "player.h"

//----------------------------------------------------------------------------
// Game-基本クラス
//----------------------------------------------------------------------------

// ゲームの初期化
void Game_Init(void);
// ゲームの更新
void Game_Update(void);
// ゲームの描画
void Game_Draw(void);
// ゲームの終了処理
void Game_Uninit(void);
// プレイヤーのインスタンスを取得
GamePlayer* Game_GetPlayer(void);