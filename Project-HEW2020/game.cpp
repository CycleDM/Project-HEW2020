//----------------------------------------------------------------------------
// 
// Project-HEW2020 [game.cpp]
// �Q�[�����䃂�W���[��
// 
// Date:   2020/10/28
// Author: AT12D187_17_���i
// 
//----------------------------------------------------------------------------
#include <cmath>
#include "game.h"
#include "config.h"
#include "sprite.h"
#include "player.h"
#include "TestScene.h"

//-----------------------------------------------------------------------------
// �O���[�o���ϐ��錾
//-----------------------------------------------------------------------------
GameScene* Game::pScene = NULL;
GameScene* Game::pActiveScene = NULL;
bool Game::bDebugMode = false;

// �Q�[���̏�����
void Game::Init(void)
{
	GameControl::Init();

	delete pScene;
	pScene = new TestScene;
}

// �Q�[���̍X�V
void Game::Update(void)
{
	// �v���C���[����
	GamePlayer* player = pScene->GetPlayer();
	if (!player->isOnLadder() && GameControl::GetKeyPress(GameControl::LEFT))
	{
		player->MoveLeft();
	}
	if (!player->isOnLadder() && GameControl::GetKeyPress(GameControl::RIGHT))
	{
		player->MoveRight();
	}

	// �͂�����o��E�~���
	do
	{
		// ��ԋ߂���q�̃C���X�^���X���擾
		GameObject* ladder = pScene->GetNearestObject(player->GetGlobalPos(), GameObject::OBJ_LADDER);
		if (NULL == ladder) break;
		// �͂�����o���͈͂����肷��
		if (abs(ladder->GetGlobalPos().x - player->GetGlobalPos().x) > 64.0f) break;
		// �o��
		if (GameControl::GetKeyPress(GameControl::UP))
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
		if (GameControl::GetKeyPress(GameControl::DOWN))
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

// �Q�[���̕`��
void Game::Draw(void)
{
	pScene->Draw();
}

// �Q�[���̏I������
void Game::Uninit(void)
{
	// ���������
	delete pScene;
	pScene = NULL;

}

// �f�o�b�O�̏�Ԃ��擾
bool Game::DebugMode(void)
{
	return bDebugMode;
}