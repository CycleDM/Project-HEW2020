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
}

GameScene::~GameScene()
{

}

GamePlayer* GameScene::GetPlayer(void)
{
	return pPlayer;
}

void GameScene::SetGlobalScaling(float scaling)
{
	fGlobalScaling = scaling;
}

float GameScene::GetGlobalScaling(void)
{
	return fGlobalScaling;
}

GameObject* GameScene::GetNearestObject(GameObject::ObjectType type)
{
	GameObject* target = NULL;
	for (GameObject* obj : pObjects)
	{
		if (NULL == pPlayer) break;
		if (NULL == obj) continue;
		if (type != obj->GetType()) continue;
		if (NULL != obj && NULL == target)
		{
			target = obj;
			continue;
		}
		
		D3DXVECTOR2 pos1, pos2, length1, length2;
		pos1 = obj->GetGlobalPos();
		pos2 = target->GetGlobalPos();
		
		length1 = pos1 - pPlayer->GetGlobalPos();
		length2 = pos2 - pPlayer->GetGlobalPos();
		if (D3DXVec2LengthSq(&length1) < D3DXVec2LengthSq(&length2))
		{
			target = obj;
		}
	}
	return target;
}