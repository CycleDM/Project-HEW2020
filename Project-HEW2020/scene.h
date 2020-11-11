//----------------------------------------------------------------------------
// 
// Project-HEW2020 [scene.h]
// シーン基本クラス
// 
// Date:   2020/11/06
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#pragma once

#include "config.h"
#include "player.h"
#include "object.h"
#include "overlay.h"

class GameScene
{
public:
	GameScene()
	{
		pPlayer = NULL;
		memset(pObjects, NULL, sizeof(pObjects));
		memset(pOverlays, NULL, sizeof(pOverlays));
	}
	virtual ~GameScene()
	{
	}

	virtual void Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	GamePlayer* GetPlayer(void)
	{
		return pPlayer;
	}

protected:
	GamePlayer* pPlayer;
	GameObject* pObjects[SINGLE_SCENE_OBJECT_MAX];
	GameOverlay* pOverlays[SINGLE_SCENE_OVERLAY_MAX];
};
