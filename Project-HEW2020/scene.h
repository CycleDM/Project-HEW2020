//----------------------------------------------------------------------------
// 
// Project-HEW2020 [scene.h]
// �V�[����{�N���X
// 
// Date:   2020/11/06
// Author: AT12D187_17_���i
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
	GameScene();
	virtual ~GameScene();

	virtual void Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual void Debug(void) = 0;

	virtual void UpdatePlayer(void) = 0;
	virtual void UpdateObject(void) = 0;
	virtual void UpdateOverlay(void) = 0;

	GamePlayer* GetPlayer(void);
	// �v���C���[�Ɉ�ԋ߂��A����̃I�u�W�F�N�g���擾
	GameObject* GetNearestObject(GameObject::ObjectType);

	static void SetGlobalScaling(float scaling);
	static float GetGlobalScaling(void);

protected:
	GamePlayer* pPlayer;
	GameObject* pObjects[SINGLE_SCENE_OBJECT_MAX];
	GameOverlay* pOverlays[SINGLE_SCENE_OVERLAY_MAX];
	static float fGlobalScaling;
};
