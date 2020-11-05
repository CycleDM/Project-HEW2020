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
#include "test_scene.h"
#include "controller.h"
#include "object.h"

//-----------------------------------------------------------------------------
// �O���[�o���ϐ��錾
//-----------------------------------------------------------------------------
static Controller* g_pController = NULL;
static TestScene* g_pGameScene = NULL;

// �Q�[���̏�����
void Game_Init(void)
{
	g_pController = new Controller;			// �R���g���[���[�̃C���X�^���X���쐬
	g_pGameScene = new TestScene;			// �V�[���̃C���X�^���X���쐬
}

// �Q�[���̍X�V
void Game_Update(void)
{
	// �v���C���[����
	GamePlayer* player = g_pGameScene->GetPlayer();
	if (g_pController->GetKeyPress(Controller::LEFT))
	{
		player->MoveLeft();
	}
	if (g_pController->GetKeyPress(Controller::RIGHT))
	{
		player->MoveRight();
	}
	// Climb up
	if (g_pController->GetKeyPress(Controller::UP))
	{
		GameObject* ladder = g_pGameScene->GetNearestLadder();
		if (NULL != ladder)
		{
			D3DXVECTOR2 ladderPos = ladder->GetPosition();
			D3DXVECTOR2 playerPos = player->GetPosition();
			player->SetPosition(ladderPos.x, playerPos.y);
			player->ClimbUp();
			player->SetClimbUpStatus(true);
		}
		else
		{
			player->SetClimbUpStatus(false);
		}
	}
	if (g_pController->GetKeyRelease(Controller::UP))
	{
		player->SetClimbUpStatus(false);
	}
	// Climb down
	if (g_pController->GetKeyPress(Controller::DOWN))
	{
		GameObject* ladder = g_pGameScene->GetNearestLadder();
		if (NULL != ladder)
		{
			D3DXVECTOR2 ladderPos = ladder->GetPosition();
			D3DXVECTOR2 playerPos = player->GetPosition();
			player->SetPosition(ladderPos.x, playerPos.y);
			player->ClimbDown();
			player->SetClimbDownStatus(true);
		}
		else
		{
			player->SetClimbDownStatus(false);
		}
	}
	if (g_pController->GetKeyRelease(Controller::DOWN))
	{
		player->SetClimbDownStatus(false);
	}
	//if (g_pController->GetKeyPress(Controller::JUMP))
	//{
	//	g_pPlayer->Jump();
	//}

	g_pController->Update();
	g_pGameScene->Update();
	player->Update();
}

// �Q�[���̕`��
void Game_Draw(void)
{
	g_pGameScene->Draw();
}

// �Q�[���̏I������
void Game_Uninit(void)
{
	delete g_pGameScene;
	delete g_pController;

	g_pController = NULL;
	g_pGameScene = NULL;
}

TestScene* Game_GetScene(void)
{
	return g_pGameScene;
}