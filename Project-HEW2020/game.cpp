//----------------------------------------------------------------------------
// 
// Project-HEW2020 [game.cpp]
// ゲーム制御モジュール
// 
// Date:   2020/10/28
// Author: AT12D187_17_周進
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
// グローバル変数宣言
//-----------------------------------------------------------------------------
Game::SceneType Game::eNowScene = SCENE_TITLE;
GameScene* Game::pActScene = NULL;
LoadingScreen* Game::pLoadingScreen = NULL;

HWND Game::hWnd = NULL;
POINT Game::mousePosition = { 0, 0 };
int Game::window_width = 0;
int Game::window_height = 0;
bool Game::onFocus = true;

bool Game::bLoadingFlag = false;
bool Game::bDebugMode = false;

thread Game::lt = {};

void func(void)
{
	int a = 0;
	while (1)
	{
		a++;
	}
}

// ゲームの初期化
void Game::Init(void)
{
	Uninit();

	eNowScene = SCENE_TITLE;
	pLoadingScreen = new LoadingScreen;
	bLoadingFlag = false;

	//SwitchScene(eNowScene);
	InitScene(NULL);
}

// ゲームの終了処理
void Game::Uninit(void)
{
	// Check loading thread
	if (lt.joinable()) lt.join();

	// メモリ解放
	delete pActScene;
	pActScene = NULL;
	delete pLoadingScreen;
	pLoadingScreen = NULL;
}

void Game::InitScene(bool* flag)
{
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

	if (NULL == flag) return;
	if (NULL != pActScene)
	{
		*flag = false;
		pLoadingScreen->Hide();
		return;
	}
}

void Game::UninitScene()
{
	delete pActScene;
	pActScene = NULL;
}

// ゲームの更新
void Game::Update(void)
{
	if (!bLoadingFlag && lt.joinable()) lt.join();

	pLoadingScreen->Update();
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

// ゲームの描画
void Game::Draw(void)
{
	pLoadingScreen->Draw();
	if (NULL == pActScene) return;
	pActScene->Draw();
}

// デバッグの状態を取得
bool Game::DebugMode(void)
{
	return bDebugMode;
}

void Game::SwitchScene(Game::SceneType type)
{
	UninitScene();

	eNowScene = type;
	bLoadingFlag = true;

	// Set loading screen visible
	pLoadingScreen->Show();

	/*** LOADING THREAD ***/
	//lt = thread(&Game::InitScene, &bLoadingFlag);
	lt = thread(func);
	lt.detach();

	//InitScene(NULL);
	//bLoadingFlag = false;
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

// LOADING SCREEN
LoadingScreen::LoadingScreen()
{
	pSprite = new SpriteNormal(TEXTURE_LOADING);
	pAnimator = new Animator();
	pSprite->SetPolygonSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	pSprite->SetCutPos(0, 0);
	pSprite->SetCutRange(SCREEN_WIDTH, SCREEN_HEIGHT);
	pAnimator->Init(pSprite);
	pAnimator->Preset(3, 3, 8);

	isHidden = true;
}

LoadingScreen::~LoadingScreen()
{
	delete pSprite;
	pSprite = NULL;
	delete pAnimator;
	pAnimator = NULL;
}

void LoadingScreen::Update()
{
	if (isHidden) return;
	pAnimator->Play(pSprite);
}

void LoadingScreen::Draw()
{
	if (isHidden) return;
	pSprite->Draw();
}

void LoadingScreen::Hide()
{
	if (isHidden) return;
	pSprite->SetColor(D3DCOLOR_RGBA(255, 255, 255, 0));
	isHidden = true;
}

void LoadingScreen::Show()
{
	pSprite->SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
	pAnimator->Preset(3, 3, 8);
	isHidden = false;
}