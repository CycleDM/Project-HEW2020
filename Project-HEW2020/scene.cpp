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
#include "sound.h"

//----------------------------------------------------------------------------
// �O���[�o���ϐ�
//----------------------------------------------------------------------------
float GameScene::fGlobalScaling = 1.0f;	// ���ׂẴe�N�X�`���̊g��E�k���Q�ƃf�[�^
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

void GameScene::PlayerControl(void)
{
	// �v���C���[����
	GamePlayer* player = this->GetPlayer();
	if (NULL == player) return;
	if (bFrozen) return;

	// �ړ��Ɋւ��鏈��
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

	// �͂����Ɋւ��鏈��
	do
	{
		// �͂�����o��E�~���
		// ��ԋ߂���q�̃C���X�^���X���擾
		GameObject* ladder = this->GetNearestObject(player->GetGlobalPos(), GameObject::OBJ_LADDER);
		if (NULL == ladder) break;
		// �͂�����o���͈͂����肷��
		if (32.0f < abs(ladder->GetGlobalPos().x - player->GetGlobalPos().x)) break;
		// �o��
		if (Input::GetKeyPress(DIK_W))
		{
			// �͂����̒��S���Wy�@< �v���C���[�̑�y�i��ԉ��̍��W�j
			// �͂�����o��邱�Ƃ𔻒f����
			if (ladder->GetCollision()->GetPosition().y < player->GetGlobalPos().y + player->GetCollision()->GetHalfHeight())
			{
				player->isOnLadder(true);
			}
			// �v���C���[�̑�y < ��q�̏㋫�Ey
			// �͂����𗣂��
			if (player->GetGlobalPos().y + player->GetCollision()->GetHalfHeight() < ladder->GetCollision()->GetPosition().y - ladder->GetCollision()->GetHalfHeight())
			{
				player->isOnLadder(false);
				player->isClimbing(false);
			}
			// �͂�����o��
			if (player->isOnLadder())
			{
				player->MoveUp();
				// x���W�̌���
				player->SetGlobalPos(ladder->GetGlobalPos().x, player->GetGlobalPos().y);
			}
		}
		// �~���
		if (Input::GetKeyPress(DIK_S))
		{
			// �͂����̒��S���Wy�@> �v���C���[�̓�y�i��ԏ�̍��W�j
			// �͂�����o��邱�Ƃ𔻒f����
			if (ladder->GetCollision()->GetPosition().y > player->GetGlobalPos().y - player->GetCollision()->GetHalfHeight())
			{
				player->isOnLadder(true);
			}
			// �v���C���[�̑�y�i��ԉ��̍��W�j > �͂����̉����E
			// �͂����𗣂��
			if (player->GetGlobalPos().y + player->GetCollision()->GetHalfHeight() > ladder->GetCollision()->GetPosition().y + ladder->GetCollision()->GetHalfHeight())
			{
				player->isOnLadder(false);
				player->isClimbing(false);
			}
			// �͂������~���
			if (player->isOnLadder())
			{
				// �~���O�ɏ��̍��W�Ɉړ�
				float startPos = ladder->GetCollision()->GetPosition().y - ladder->GetCollision()->GetHalfHeight();
				if (player->GetGlobalPos().y < startPos) player->SetGlobalPos(ladder->GetGlobalPos().x, startPos);

				player->MoveDown();
				// x���W�̌���
				player->SetGlobalPos(ladder->GetGlobalPos().x, player->GetGlobalPos().y);
			}
		}
		// �L�[�𗣂�����
		if (!player->isOnLadder()) break;
		if (Input::GetKeyRelease(DIK_W) || Input::GetKeyRelease(DIK_S))
		{
			player->isClimbing(false);
		}
	} while (0);
}