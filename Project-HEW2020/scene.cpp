//----------------------------------------------------------------------------
// 
// Project-HEW2020 [scene.cpp]
// シーン基本クラス
// 
// Date:   2020/11/06
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#include "scene.h"
#include "sound.h"

//----------------------------------------------------------------------------
// グローバル変数
//----------------------------------------------------------------------------
float GameScene::fGlobalScaling = 1.0f;	// すべてのテクスチャの拡大・縮小参照データ
bool GameScene::bDarkness = false;
bool GameScene::bFrozen = false;

GameScene::GameScene()
{
	pPlayer = NULL;
	memset(pObjects, NULL, sizeof(pObjects));
	memset(pOverlays, NULL, sizeof(pOverlays));

	fBgScroll = D3DXVECTOR2(0.0f, 0.0f);
	fBgScrollMax = D3DXVECTOR2(0.0f, 0.0f);
	fGroundHeight = 0.0f;
}

GameScene::~GameScene()
{

}

// プレイヤーのインスタンスを取得（ポインター）
GamePlayer* GameScene::GetPlayer(void)
{
	return pPlayer;
}

// 拡大・縮小参照データを設定
void GameScene::SetGlobalScaling(float scaling)
{
	fGlobalScaling = scaling;
}

// 拡大・縮小参照データを取得
float GameScene::GetGlobalScaling(void)
{
	return fGlobalScaling;
}

bool GameScene::isDarkness(void)
{
	return bDarkness;
}

void GameScene::isDarkness(bool bDarkness)
{
	GameScene::bDarkness = bDarkness;
}

void GameScene::Freeze(bool bFrozen)
{
	GameScene::bFrozen = bFrozen;
}

// 指定の座標に一番近く、特定のオブジェクトを取得
GameObject* GameScene::GetNearestObject(D3DXVECTOR2 position, GameObject::ObjectType objectType)
{
	GameObject* target = NULL;
	for (GameObject* obj : pObjects)
	{
		if (NULL == obj) continue;
		if (objectType != obj->GetType()) continue;
		if (NULL != obj && NULL == target)
		{
			target = obj;
			continue;
		}
		
		D3DXVECTOR2 pos1, pos2, length1, length2;
		pos1 = obj->GetGlobalPos();
		pos2 = target->GetGlobalPos();
		
		length1 = pos1 - position;
		length2 = pos2 - position;
		if (D3DXVec2LengthSq(&length1) < D3DXVec2LengthSq(&length2))
		{
			target = obj;
		}
	}
	return target;
}

void GameScene::PlayerControl(void)
{
	// プレイヤー操作
	GamePlayer* player = this->GetPlayer();
	if (NULL == player) return;
	if (bFrozen) return;

	// 移動に関する処理
	do
	{
		if (!player->isOnLadder() && Input::GetKeyPress(DIK_A))
		{
			player->MoveLeft();
		}
		if (!player->isOnLadder() && Input::GetKeyPress(DIK_D))
		{
			player->MoveRight();
		}
	} while (0);

	// はしごに関する処理
	do
	{
		// はしごを登る・降りる
		// 一番近い梯子のインスタンスを取得
		GameObject* ladder = this->GetNearestObject(player->GetGlobalPos(), GameObject::OBJ_LADDER);
		if (NULL == ladder) break;
		// はしごを登れる範囲を限定する
		if (32.0f < abs(ladder->GetGlobalPos().x - player->GetGlobalPos().x)) break;
		// 登る
		if (Input::GetKeyPress(DIK_W))
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
		if (Input::GetKeyPress(DIK_S))
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
		if (Input::GetKeyRelease(DIK_W) || Input::GetKeyRelease(DIK_S))
		{
			player->isClimbing(false);
		}
	} while (0);
}