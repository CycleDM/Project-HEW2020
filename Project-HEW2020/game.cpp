//----------------------------------------------------------------------------
// 
// Project-HEW2020 [game.cpp]
// �Q�[�����䃂�W���[��
// 
// Date:   2020/10/28
// Author: AT12D187_17_���i
// 
//----------------------------------------------------------------------------
#include "config.h"
#include "sprite.h"
#include "player.h"
#include "background.h"
#include "controller.h"

//-----------------------------------------------------------------------------
// �O���[�o���ϐ��錾
//-----------------------------------------------------------------------------
static Controller* g_pController = NULL;
static GameBackground* g_pBackground = NULL;
static GamePlayer* g_pPlayer = NULL;

// �Q�[���̏�����
void Game_Init(void)
{
	g_pController = new Controller;			// �R���g���[���[�̃C���X�^���X���쐬
	g_pBackground = new GameBackground;		// �w�i�̃C���X�^���X���쐬
	g_pPlayer = new GamePlayer;				//�@�v���C���[�̃C���X�^���X���쐬
}

// �Q�[���̍X�V
void Game_Update(void)
{
	// �v���C���[����
	if (g_pController->GetKeyPress(Controller::LEFT))
	{
		g_pPlayer->MoveLeft();
	}
	if (g_pController->GetKeyPress(Controller::RIGHT))
	{
		g_pPlayer->MoveRight();
	}
	//if (g_pController->GetKeyPress(Controller::JUMP))
	//{
	//	g_pPlayer->SetJump();
	//}

	g_pController->Update();
	g_pBackground->Update();
	g_pPlayer->Update();
}

// �Q�[���̕`��
void Game_Draw(void)
{
	g_pBackground->Draw();
	g_pPlayer->Draw();
}

// �Q�[���̏I������
void Game_Uninit(void)
{
	delete g_pPlayer;
	delete g_pBackground;
	delete g_pController;

	g_pController = NULL;
	g_pPlayer = NULL;
	g_pBackground = NULL;
}

// �v���C���[�̃C���X�^���X���擾
GamePlayer* Game_GetPlayer(void)
{
	return g_pPlayer;
}