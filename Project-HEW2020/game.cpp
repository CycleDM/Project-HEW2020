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

//-----------------------------------------------------------------------------
// �O���[�o���ϐ��錾
//-----------------------------------------------------------------------------
static Player* g_pPlayer = NULL;

// �Q�[���̏�����
void Game_Init(void)
{
	g_pPlayer = new Player;
}

// �Q�[���̍X�V
void Game_Update(void)
{

}

// �Q�[���̕`��
void Game_Draw(void)
{
	g_pPlayer->Draw();
}

// �Q�[���̏I������
void Game_Uninit(void)
{
	delete g_pPlayer;
	g_pPlayer = NULL;
}