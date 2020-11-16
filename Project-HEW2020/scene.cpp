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

//----------------------------------------------------------------------------
// グローバル変数
//----------------------------------------------------------------------------
float GameScene::fGlobalScaling = 1.0f;	// すべてのテクスチャの拡大・縮小参照データ

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