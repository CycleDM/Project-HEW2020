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
#include <thread>
#include "game.h"
#include "config.h"
#include "sprite.h"
#include "player.h"
#include "input.h"
#include "d3dfont.h"
#include "fade.h"
#include "TitleScene.h"
#include "TestScene.h"
#include "GameScene01.h"
#include "FinalScene.h"
#include "sound.h"

using namespace std;

//-----------------------------------------------------------------------------
// グローバル変数宣言
//-----------------------------------------------------------------------------
Game::SceneType Game::eNowScene = SCENE_TITLE;
Game::SceneType Game::eNextScene = eNowScene;
GameScene* Game::pActScene = NULL;
LoadingScreen* Game::pLoadingScreen = NULL;

HWND Game::hWnd = NULL;
int Game::window_width = 0;
int Game::window_height = 0;
bool Game::onFocus = true;

bool Game::bLoadingFlag = false;
bool Game::bDebugMode = false;

thread Game::lt;

// ゲームの初期化
void Game::Init(void)
{
	Uninit();

	eNowScene = SCENE_TITLE;
	eNextScene = eNowScene;
	pLoadingScreen = new LoadingScreen;
	bLoadingFlag = false;

	LoadNextScene(eNowScene);

	// VOLUMES
	SetVolume(SOUND_LABEL_BGM000, 0.1f);
	SetVolume(SOUND_LABEL_SE_GENERATOR_POWER, 0.5f);
	SetVolume(SOUND_LABEL_SE_GENERATOR_UI, 0.5f);
	SetVolume(SOUND_LABEL_SE_PICKUP_LEG, 0.5f);
	SetVolume(SOUND_LABEL_SE_DOOR_OPEN1, 0.3f);
	SetVolume(SOUND_LABEL_SE_DOOR_OPEN2, 1.0f);
	SetVolume(SOUND_LABEL_SE_SCREEN_OPEN, 1.0f);
	SetVolume(SOUND_LABEL_SE_LANGUAGE, 1.0f);
	SetVolume(SOUND_LABEL_SE_VISUAL, 1.0f);
	SetVolume(SOUND_LABEL_SE_LIFT_OPEN, 1.0f);
	SetVolume(SOUND_LABEL_SE_LIFT_LIFTING, 1.0f);
	SetVolume(SOUND_LABEL_SE_BUTTON, 1.0f);
	SetVolume(SOUND_LABEL_SE_CORRECT, 1.0f);
	SetVolume(SOUND_LABEL_SE_WRONG, 1.0f);
	SetVolume(SOUND_LABEL_SE_ITEM_DROP, 0.8f);
	SetVolume(SOUND_LABEL_SE_KEYBOARD, 1.0f);
}

// ゲームの終了処理
void Game::Uninit(void)
{
	// メモリ解放
	delete pActScene;
	pActScene = NULL;
	delete pLoadingScreen;
	pLoadingScreen = NULL;
}

void Game::InitSceneThread(GameScene** pTarget, bool* flag)
{
	if (NULL != flag) *flag = true;
	GameScene* pScene = NULL;

	switch (eNextScene)
	{
	case Game::SCENE_TITLE:
		pScene = new TitleScene;
		break;
	case Game::SCENE_01:
		pScene = new GameScene01;
		break;
	case Game::SCENE_02:
		break;
	case Game::SCENE_03:
		break;
	case Game::SCENE_TEST:
		pScene = new TestScene;
		break;
	case Game::SCENE_FINAL:
		pScene = new FinalScene;
		break;
	default:
		break;
	}

	if (NULL == pScene) return;

	if (NULL != pTarget) *pTarget = pScene;
	if (NULL != flag) *flag = false;

	FadeEffect::Start(FADE_IN, 0.0f, 0.0f, 0.0f, 30);
}

void Game::UninitScene()
{
	delete pActScene;
	pActScene = NULL;
}

// ゲームの更新
void Game::Update(void)
{
	if (bLoadingFlag) pLoadingScreen->Show();
	else pLoadingScreen->Hide();

	if (eNowScene != eNextScene && !bLoadingFlag)
	{
		eNowScene = eNextScene;
	}

	pLoadingScreen->Update();
	if (NULL == pActScene) return;
	pActScene->Update();

	// Switching Debug Mode
	if (Input::GetKeyTrigger(DIK_F3))
	{
		bDebugMode = !bDebugMode;
	}
}

// ゲームの描画
void Game::Draw(void)
{
	pLoadingScreen->Draw();
	if (NULL == pActScene) return;
	pActScene->Draw();
	
#ifdef _DEBUG
	D3DFont::Draw(
		Input::GetMouseX() + 16,
		Input::GetMouseY(), 
		"DEBUG\nデバッグ\nProject-HEW2020", 
		FONT_NAME, 
		32, 
		D3DCOLOR_RGBA(200, 200, 200, 155)
	);
#endif // _DEBUG
}

// デバッグの状態を取得
bool Game::DebugMode(void)
{
	return bDebugMode;
}

void Game::LoadNextScene(Game::SceneType type)
{
	UninitScene();
	eNextScene = type;

	/*** LOADING THREAD ***/
	//lt = thread(&Game::InitSceneThread, &pActScene, &bLoadingFlag);
	//lt.detach();
	InitSceneThread(&pActScene);

	// BGM
	switch (type)
	{
	case Game::SCENE_TITLE:
		StopSound();
		PlaySound(SOUND_LABEL_BGM000);
		break;
	case Game::SCENE_FINAL:
		StopSound();
		PlaySound(SOUND_LABEL_BGM001);
		break;
	default:
		break;
	}
}

void Game::BindWindow(HWND hWnd, int window_width, int window_height)
{
	Game::hWnd = hWnd;
	Game::window_width = window_width;
	Game::window_height = window_height;
}

HWND Game::GetWindow(void)
{
	return hWnd;
}

void Game::SetFocus(bool onFocus)
{
	Game::onFocus = onFocus;
}