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
#include "sprite.h"
#include "player.h"
#include "TestScene.h"

//-----------------------------------------------------------------------------
// グローバル変数宣言
//-----------------------------------------------------------------------------
GameScene* Game::pScene = NULL;
GameScene* Game::pActiveScene = NULL;
bool Game::bDebugMode = false;

// ゲームの初期化
void Game::Init(void)
{
	GameControl::Init();

	delete pScene;
	pScene = new TestScene;
}

// ゲームの更新
void Game::Update(void)
{
	// プレイヤー操作
	GamePlayer* player = pScene->GetPlayer();
	if (!player->isOnLadder() && GameControl::GetKeyPress(GameControl::LEFT))
	{
		player->MoveLeft();
	}
	if (!player->isOnLadder() && GameControl::GetKeyPress(GameControl::RIGHT))
	{
		player->MoveRight();
	}

	// はしごを登る・降りる
	do
	{
		// 一番近い梯子のインスタンスを取得
		GameObject* ladder = pScene->GetNearestObject(player->GetGlobalPos(), GameObject::OBJ_LADDER);
		if (NULL == ladder) break;
		// はしごを登れる範囲を限定する
		if (abs(ladder->GetGlobalPos().x - player->GetGlobalPos().x) > 64.0f) break;
		// 登る
		if (GameControl::GetKeyPress(GameControl::UP))
		{
			// はしごの中心座標y　< プレイヤーの足y（一番下の座標）
			// はしごを登れることを判断する
			if (ladder->GetCollision()->GetPosition().y < player->GetGlobalPos().y + player->GetCollision()->GetHalfHeight())
			{
				player->isOnLadder(true);
			}
			// プレイヤーの足y < 梯子の上境界y
			// はしごを離れる
			if (player->GetGlobalPos().y + player->GetCollision()->GetHalfHeight() < ladder->GetCollision()->GetPosition().y - ladder->GetCollision()->GetHalfHeight())
			{
				player->isOnLadder(false);
				player->isClimbing(false);
			}
			// はしごを登る
			if (player->isOnLadder())
			{
				player->MoveUp();
				// x座標の限定
				player->SetGlobalPos(ladder->GetGlobalPos().x, player->GetGlobalPos().y);
			}	
		}
		// 降りる
		if (GameControl::GetKeyPress(GameControl::DOWN))
		{
			// はしごの中心座標y　> プレイヤーの頭y（一番上の座標）
			// はしごを登れることを判断する
			if (ladder->GetCollision()->GetPosition().y > player->GetGlobalPos().y - player->GetCollision()->GetHalfHeight())
			{
				player->isOnLadder(true);
			}
			// プレイヤーの足y（一番下の座標） > はしごの下境界
			// はしごを離れる
			if (player->GetGlobalPos().y + player->GetCollision()->GetHalfHeight() > ladder->GetCollision()->GetPosition().y + ladder->GetCollision()->GetHalfHeight())
			{
				player->isOnLadder(false);
				player->isClimbing(false);
			}
			// はしごを降りる
			if (player->isOnLadder())
			{
				// 降りる前に初の座標に移動
				float startPos = ladder->GetCollision()->GetPosition().y - ladder->GetCollision()->GetHalfHeight();
				if (player->GetGlobalPos().y < startPos) player->SetGlobalPos(ladder->GetGlobalPos().x, startPos);

				player->MoveDown();
				// x座標の限定
				player->SetGlobalPos(ladder->GetGlobalPos().x, player->GetGlobalPos().y);
			}
		}
		// キーを離した時
		if (!player->isOnLadder()) break;
		if (GameControl::GetKeyRelease(GameControl::UP) || GameControl::GetKeyRelease(GameControl::DOWN))
		{
			player->isClimbing(false);
		}
	} while (0);

	// Switch Debug Mode
	if (GameControl::GetKeyTrigger(GameControl::DEBUG))
	{
		bDebugMode = bDebugMode ? false : true;
	}

	GameControl::Update();
	pScene->Update();
}

// ゲームの描画
void Game::Draw(void)
{
	pScene->Draw();
}

// ゲームの終了処理
void Game::Uninit(void)
{
	// メモリ解放
	delete pScene;
	pScene = NULL;

}

// デバッグの状態を取得
bool Game::DebugMode(void)
{
	return bDebugMode;
}