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
	}
	if (g_pController->GetKeyRelease(Controller::UP))
	{
	}
	// Climb down
	if (g_pController->GetKeyPress(Controller::DOWN))
	{
	}
	if (g_pController->GetKeyRelease(Controller::DOWN))
	{
	}
	//if (g_pController->GetKeyPress(Controller::JUMP))
	//{
	//	g_pPlayer->Jump();
	//}

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
	g_pScene->Uninit();

	delete g_pController;
	g_pController = NULL;
}