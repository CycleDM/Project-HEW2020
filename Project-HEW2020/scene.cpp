//----------------------------------------------------------------------------
// 
// Project-HEW2020 [scene.cpp]
// �V�[����{�N���X
// 
// Date:   2020/11/06
// Author: AT12D187_17_���i
// 
//----------------------------------------------------------------------------
#include "scene.h"

//----------------------------------------------------------------------------
// �O���[�o���ϐ�
//----------------------------------------------------------------------------
float GameScene::fGlobalScaling = 1.0f;	// ���ׂẴe�N�X�`���̊g��E�k���Q�ƃf�[�^

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

// �v���C���[�̃C���X�^���X���擾�i�|�C���^�[�j
GamePlayer* GameScene::GetPlayer(void)
{
	return pPlayer;
}

// �g��E�k���Q�ƃf�[�^��ݒ�
void GameScene::SetGlobalScaling(float scaling)
{
	fGlobalScaling = scaling;
}

// �g��E�k���Q�ƃf�[�^���擾
float GameScene::GetGlobalScaling(void)
{
	return fGlobalScaling;
}

// �w��̍��W�Ɉ�ԋ߂��A����̃I�u�W�F�N�g���擾
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