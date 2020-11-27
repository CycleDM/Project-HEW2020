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
#include "controller.h"
#include "sprite.h"
#include "player.h"
#include "TitleScene.h"
#include "TestScene.h"

//-----------------------------------------------------------------------------
// �O���[�o���ϐ��錾
//-----------------------------------------------------------------------------
Game::SceneType Game::eNowScene = SCENE_TITLE;
GameScene* Game::pActScene = NULL;
bool Game::bDebugMode = false;

// �Q�[���̏�����
void Game::Init(void)
{
	delete pActScene;
	pActScene = NULL;

	switch (eNowScene)
	{
	case Game::SCENE_TITLE:
		pActScene = new TitleScene;
		break;
	case Game::SCENE_TEST:
		pActScene = new TestScene;
		break;
	case Game::SCENE_FINAL:
		break;
	default:
		break;
	}
}

// �Q�[���̍X�V
void Game::Update(void)
{
	if (NULL == pActScene) return;

	pActScene->Update();

	// Switch Debug Mode
	if (GameControl::GetKeyTrigger(GameControl::DEBUG))
	{
		bDebugMode = bDebugMode ? false : true;
	}
}

// �Q�[���̕`��
void Game::Draw(void)
{
	if (NULL == pActScene) return;
	pActScene->Draw();
}

// �Q�[���̏I������
void Game::Uninit(void)
{
	// ���������
	delete pActScene;
	pActScene = NULL;

}

// �f�o�b�O�̏�Ԃ��擾
bool Game::DebugMode(void)
{
	return bDebugMode;
}

void Game::ChangeScene(Game::SceneType type)
{
	eNowScene = type;
	Init();
}