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
#include "config.h"
#include "sprite.h"
#include "player.h"
#include "controller.h"
#include "scene.h"
#include "TestScene.h"

//-----------------------------------------------------------------------------
// �O���[�o���ϐ��錾
//-----------------------------------------------------------------------------
static Controller* g_pController = NULL;
static GameScene* g_pScene = NULL;
static bool g_bDebugMode = false;

// �Q�[���̏�����
void Game_Init(void)
{
	g_pController = new Controller;			// �R���g���[���[�̃C���X�^���X���쐬
	g_pScene = new TestScene;
}

// �Q�[���̍X�V
void Game_Update(void)
{
	// �v���C���[����
	GamePlayer* player = g_pScene->GetPlayer();
	if (!player->isOnLadder() && g_pController->GetKeyPress(Controller::LEFT))
	{
		player->MoveLeft();
	}
	if (!player->isOnLadder() && g_pController->GetKeyPress(Controller::RIGHT))
	{
		player->MoveRight();
	}

	// �͂�����o��E�~���
	do
	{
		// ��ԋ߂���q�̃C���X�^���X���擾
		GameObject* ladder = g_pScene->GetNearestObject(player->GetGlobalPos(), GameObject::OBJ_LADDER);
		if (NULL == ladder) break;
		// �͂�����o���͈͂����肷��
		if (abs(ladder->GetGlobalPos().x - player->GetGlobalPos().x) > 64.0f) break;
		// �o��
		if (g_pController->GetKeyPress(Controller::UP))
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
		if (g_pController->GetKeyPress(Controller::DOWN))
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
		if (g_pController->GetKeyRelease(Controller::UP) || g_pController->GetKeyRelease(Controller::DOWN))
		{
			player->isClimbing(false);
		}
	} while (0);

	// Switch Debug Mode
	if (g_pController->GetKeyTrigger(Controller::DEBUG))
	{
		g_bDebugMode = g_bDebugMode ? false : true;
	}

	g_pController->Update();
	g_pScene->Update();
}

// �Q�[���̕`��
void Game_Draw(void)
{
	g_pScene->Draw();
}

// �Q�[���̏I������
void Game_Uninit(void)
{
	// ���������
	delete g_pScene;
	g_pScene = NULL;

	delete g_pController;
	g_pController = NULL;
}

// �f�o�b�O�̏�Ԃ��擾
bool Game_IsDebugMode(void)
{
	return g_bDebugMode;
}