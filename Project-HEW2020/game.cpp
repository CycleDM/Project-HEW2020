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
#include "GameScene01.h"

//-----------------------------------------------------------------------------
// �O���[�o���ϐ��錾
//-----------------------------------------------------------------------------
Game::SceneType Game::eNowScene = SCENE_TITLE;
GameScene* Game::pActScene = NULL;

HWND Game::hWnd = NULL;
POINT Game::mousePosition = { 0, 0 };
int Game::window_width = 0;
int Game::window_height = 0;
bool Game::onFocus = true;

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
	case Game::SCENE_01:
		pActScene = new GameScene01;
		break;
	case Game::SCENE_02:
		break;
	case Game::SCENE_03:
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
		bDebugMode = !bDebugMode;
	}

	//Mouse Position
	GetCursorPos(&mousePosition);
	ScreenToClient(hWnd, &mousePosition);
	
	//do
	//{
	//	if (!onFocus) break;
	//
	//	POINT new_pos = { mousePosition.x, mousePosition.y };
	//	if (mousePosition.x > SCREEN_WIDTH)
	//	{
	//		new_pos = { 1280, mousePosition.y };
	//	}
	//	if (mousePosition.x < 0)
	//	{
	//		new_pos = { 0, mousePosition.y };
	//	}
	//	if (mousePosition.y > SCREEN_HEIGHT)
	//	{
	//		new_pos = { mousePosition.x, SCREEN_HEIGHT };
	//	}
	//	if (mousePosition.y < SCREEN_HEIGHT - window_height)
	//	{
	//		new_pos = { mousePosition.x, SCREEN_HEIGHT - window_height };
	//	}
	//	ClientToScreen(hWnd, &new_pos);
	//	SetCursorPos(new_pos.x, new_pos.y);
	//} while (0);
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

void Game::BindWindow(HWND hWnd, int window_width, int window_height)
{
	Game::hWnd = hWnd;
	Game::window_width = window_width;
	Game::window_height = window_height;
}

long Game::GetMouseX(void)
{
	return mousePosition.x;
}

long Game::GetMouseY(void)
{
	return mousePosition.y;
}

void Game::SetFocus(bool onFocus)
{
	Game::onFocus = onFocus;
}

HWND Game::GetWindow(void)
{
	return hWnd;
}