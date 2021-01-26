//----------------------------------------------------------------------------
// 
// Project-HEW2020 [GameScene01.cpp]
// シーン01
// 
// Date:   2021/01/10
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#include <stdio.h>
#include "GameScene01.h"
#include "game.h"
#include "d3dutility.h"

GameScene01::GameScene01()
{
	this->Init();
}

GameScene01::~GameScene01()
{
	this->Uninit();
}

void GameScene01::Init()
{
	// Init Screen
	SetGlobalScaling(2.0f);
	isDarkness(false);

	fBgScroll = D3DXVECTOR2(0.0f, 0.0f);
	fBgScrollMax = D3DXVECTOR2(2310.0f, (float)3000 - (720 / 2 + 1));
	fGroundHeight = 230.0f;

	bIdea[0] = bIdea[1] = bIdea[2] = false;
	bIdeaHand[0] = bIdeaHand[1] = false;
	bCodeTaken[0] = bCodeTaken[1] = false;
	bDoorUnlockded[0] = bDoorUnlockded[1] = false;
	bEndScene = false;

	// Init Player
	pPlayer = new GamePlayer;
	pPlayer->SetGlobalPos(910.0f, (float)SCREEN_HEIGHT - fGroundHeight);
	pPlayer->SetWalkingSpeed(5.0f);

	// Init BG
	pOverlays[0] = new GameOverlay(TEXTURE_SCENE01_BG);
	pOverlays[0]->SetScreenPos((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2);
	pOverlays[0]->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	pOverlays[0]->GetSprite()->SetCutPos(0, 3000 - (720 / 2 + 1));
	pOverlays[0]->GetSprite()->SetCutRange(1280 / 2, 720 / 2);

	pOverlays[1] = new GameOverlay(TEXTURE_SCENE01_BG_OVERLAY);
	pOverlays[1]->SetScreenPos((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2);
	pOverlays[1]->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	pOverlays[1]->GetSprite()->SetCutPos(0, 3000 - (720 / 2 + 1));
	pOverlays[1]->GetSprite()->SetCutRange(1280 / 2, 720 / 2);
	pOverlays[1]->GetSprite()->SetColor(D3DCOLOR_RGBA(255, 255, 255, 230));

	// IDEA
	pOverlays[2] = new GameOverlay(TEXTURE_PLAYER_IDEA);
	pOverlays[3] = new GameOverlay(TEXTURE_PLAYER_IDEA_HAND);
	
	// ITEM
	pOverlays[4] = new GameOverlay(TEXTURE_ITEM_CODE_CUT1);
	pOverlays[4]->SetScreenPos(64.0f, (float)SCREEN_HEIGHT - 65.0f);
	pOverlays[4]->SetSize(pOverlays[4]->GetWidth() * 0.3f, pOverlays[4]->GetHeight() * 0.3f);
	pOverlays[5] = new GameOverlay(TEXTURE_ITEM_CODE_CUT2);
	pOverlays[5]->SetScreenPos(64.0f, (float)SCREEN_HEIGHT - 30.0f);
	pOverlays[5]->SetSize(pOverlays[5]->GetWidth() * 0.3f, pOverlays[5]->GetHeight() * 0.3f);

	// Init OBJ
	pObjects[0] = new GameObject(GameObject::OBJ_TRASH_STACK);
	pObjects[0]->SetGlobalPos(1000.0f, 310.0f);
	pObjects[1] = new GameObject(GameObject::OBJ_TRASH_LEG);
	pObjects[1]->SetGlobalPos(1000.0f, 310.0f);
	// DOOR1
	pObjects[2] = new GameObject(GameObject::OBJ_DOOR1);
	pObjects[2]->SetGlobalPos(3111.0f, 412.0f);
	// CRASH_ROBOT
	pObjects[3] = new GameObject(GameObject::OBJ_CRASH_ROBOT);
	pObjects[3]->SetGlobalPos(1800.0f, 426.0f);
	pObjects[3]->GetSprite()->SetColor(D3DCOLOR_RGBA(155, 155, 155, 255));
	// DIGITAL_DOOR
	pObjects[4] = new GameObject(GameObject::OBJ_DIGITAL_DOOR);
	pObjects[4]->SetGlobalPos(5345.0f, 420.0f);
	pObjects[4]->SetSize(64.0f, 64.0f);
	// GENERATOR
	pObjects[5] = new GameObject(GameObject::OBJ_GENERATOR);
	pObjects[5]->SetGlobalPos(5615.0f, 440.0f);

	// OBJ Size
	for (GameObject* obj : pObjects)
	{
		if (NULL == obj) continue;
		if (GameObject::OBJ_DOOR1 == obj->GetType())
		{
			obj->SetSize(obj->GetWidth() * 1.5f, obj->GetHeight() * 2.0f);
			continue;
		}
		obj->SetSize(obj->GetWidth() * fGlobalScaling, obj->GetHeight() * fGlobalScaling);
	}
	pObjects[2]->SetSize(pObjects[2]->GetWidth(), pObjects[2]->GetHeight() * 1.1f);

	// Create UI
	pGeneratorUI = new GeneratorUI;
}

void GameScene01::Uninit()
{
	delete pPlayer;
	pPlayer = NULL;
	for (GameObject* p : pObjects)
	{
		delete p;
	}
	memset(pObjects, NULL, sizeof(pObjects));
	for (GameOverlay* p : pOverlays)
	{
		delete p;
	}
	memset(pOverlays, NULL, sizeof(pOverlays));

	delete pGeneratorUI;
	pGeneratorUI = NULL;
}

void GameScene01::Update()
{
	fBgScroll.x = pPlayer->GetGlobalPos().x - (float)SCREEN_WIDTH / 2;
	fBgScroll.x /= fGlobalScaling;

	if (fBgScroll.x > fBgScrollMax.x)
		fBgScroll.x = fBgScrollMax.x;
	if (fBgScroll.x < 0.0f)
		fBgScroll.x = 0.0f;
	if (fBgScroll.y > fBgScrollMax.y)
		fBgScroll.y = fBgScrollMax.y;
	if (fBgScroll.y < 0.0f)
		fBgScroll.y = 0.0f;

	UpdatePlayer();
	UpdateObject();
	UpdateOverlay();

	// UI
	pGeneratorUI->Update();

	if (bEndScene) Game::LoadNextScene(Game::SCENE_TEST);
}

void GameScene01::Draw()
{
	pOverlays[0]->Draw();

	for (GameObject* object : pObjects)
	{
		if (NULL == object) continue;
		object->Draw();
	}
	pPlayer->Draw();

	if (bIdea[0] || bIdea[1] || bIdea[2]) pOverlays[2]->Draw();
	if (bIdeaHand[0] || bIdeaHand[1]) pOverlays[3]->Draw();
	if (bCodeTaken[0]) pOverlays[4]->Draw();
	if (bCodeTaken[1]) pOverlays[5]->Draw();
	
	pOverlays[1]->Draw();

	// UI
	pGeneratorUI->Draw();

	// デバッグ文字の表示
	if (Game::DebugMode()) this->Debug();
}

void GameScene01::UpdateObject()
{
	float fGlobalPosOffset = fBgScroll.x * fGlobalScaling;
	for (GameObject* object : pObjects)
	{
		if (NULL == object) continue;
		object->SetScreenPos(object->GetGlobalPos().x - fGlobalPosOffset, object->GetGlobalPos().y);
		object->Update();
	}

	if (bDoorUnlockded[0])
	{
		pObjects[2]->GetAnimator()->PlayOnce(pObjects[2]->GetSprite());
	}
	if (bDoorUnlockded[1])
	{
		pObjects[4]->GetAnimator()->PlayOnce(pObjects[4]->GetSprite());
	}

	// コリジョンにより当たり判定
	Collision* pPC = pPlayer->GetCollision();

	// DOOR1
	GameObject* obj = GetNearestObject(pPC->GetPosition(), GameObject::OBJ_DOOR1);
	Collision* pOC = obj->GetCollision();
	do
	{
		if (NULL == obj) break;
		if (NULL == pOC) break;
		if (bDoorUnlockded[0]) break;

		if (abs(obj->GetGlobalPos().x - pPlayer->GetGlobalPos().x) <= 64.0f)
		{
			bIdeaHand[0] = true;
			// FBI Open the door!
			if (bCodeTaken[0] && bCodeTaken[1] && GameControl::GetKeyTrigger(GameControl::USE))
			{
				bDoorUnlockded[0] = true;
				bIdeaHand[0] = false;
				break;
			}
		}
		else
		{
			bIdeaHand[0] = false;
		}

		if (obj->GetGlobalPos().x - pPC->GetPosition().x < pOC->GetHalfWidth() + pPC->GetHalfWidth())
		{
			pPlayer->SetGlobalPos(obj->GetGlobalPos().x - pOC->GetHalfWidth() - pPC->GetHalfWidth(), pPlayer->GetGlobalPos().y);
		}
	} while (0);

	obj = GetNearestObject(pPC->GetPosition(), GameObject::OBJ_DIGITAL_DOOR);
	pOC = obj->GetCollision();
	// DIGITAL_DOOR
	do
	{
		if (NULL == obj) break;
		if (NULL == pOC) break;
		
		if (abs(obj->GetGlobalPos().x - pPlayer->GetGlobalPos().x) <= 64.0f)
		{
			if (GameControl::GetKeyTrigger(GameControl::UP) && bDoorUnlockded[1])
			{
				bEndScene = true;
				return;
			}
			if (bDoorUnlockded[1]) break;
			bIdeaHand[1] = true;
			// FBI Open the door!
			if (GameControl::GetKeyTrigger(GameControl::USE) && pGeneratorUI->isUnlocked())
			{
				bDoorUnlockded[1] = true;
				bIdeaHand[1] = false;
				break;
			}
		}
		else
		{
			bIdeaHand[1] = false;
		}
	} while (0);

	// CODE01
	obj = GetNearestObject(pPC->GetPosition(), GameObject::OBJ_TRASH_LEG);
	do
	{
		if (bCodeTaken[0]) break;
		if (abs(obj->GetGlobalPos().x - pPlayer->GetGlobalPos().x) <= 64.0f)
		{
			bIdea[0] = true;
			if (GameControl::GetKeyTrigger(GameControl::USE))
			{
				bCodeTaken[0] = true;
				bIdea[0] = false;
			}
		}
		else
		{
			bIdea[0] = false;
		}
	} while (0);

	// CODE02
	obj = GetNearestObject(pPC->GetPosition(), GameObject::OBJ_CRASH_ROBOT);
	do
	{
		if (bCodeTaken[1]) break;
		if (abs(obj->GetGlobalPos().x - pPlayer->GetGlobalPos().x) <= 64.0f)
		{
			bIdea[1] = true;
			if (GameControl::GetKeyTrigger(GameControl::USE))
			{
				bCodeTaken[1] = true;
				bIdea[1] = false;
			}
		}
		else
		{
			bIdea[1] = false;
		}
	} while (0);

	// GENERATOR
	obj = GetNearestObject(pPC->GetPosition(), GameObject::OBJ_GENERATOR);
	do
	{
		if (abs(obj->GetGlobalPos().x - pPlayer->GetGlobalPos().x) <= 64.0f)
		{
			bIdea[2] = true;
			if (GameControl::GetKeyTrigger(GameControl::USE))
			{
				pGeneratorUI->OpenUI();
			}
		}
		else
		{
			bIdea[2] = false;
		}
	} while (0);
}

void GameScene01::UpdateOverlay()
{
	float fGlobalPosOffset = fBgScroll.x * fGlobalScaling;
	pOverlays[0]->GetSprite()->SetCutPos((int)fBgScroll.x, 3000 - (720 / 2 + 1) - (int)fBgScroll.y);
	pOverlays[1]->GetSprite()->SetCutPos((int)fBgScroll.x, 3000 - (720 / 2 + 1) - (int)fBgScroll.y);

	// ここからはUIの更新処理
	do
	{
		pOverlays[2]->SetScreenPos(pPlayer->GetScreenPos().x, pPlayer->GetScreenPos().y - 100.0f);
		pOverlays[3]->SetScreenPos(pPlayer->GetScreenPos().x, pPlayer->GetScreenPos().y - 100.0f);
	} while (0);
}

void GameScene01::UpdatePlayer()
{
	this->PlayerControl();
	// プレイヤーインスタンスを更新
	pPlayer->Update();

	// プレイヤーのコリジョンを取得
	Collision* pPC = pPlayer->GetCollision();
	// スクリーン座標とワールド座標の同期
	float offsetX = fBgScroll.x * fGlobalScaling;
	float offsetY = fBgScroll.y;
	// 背景はスクロールしていない状態 -> スクリーン座標は変更できる
	// 背景はスクロールしている状態	-> スクリーン座標は変更できない
	// グローバル座標（世界座標）はいつも正常に変わる
	if (fBgScroll.x <= 0.0f || fBgScroll.x >= fBgScrollMax.x)
	{
		pPlayer->SetScreenPos(pPlayer->GetGlobalPos().x - offsetX, pPlayer->GetGlobalPos().y);
		//pPlayer->SetWalkingSpeed(5.0f);
	}
	else
	{
		pPlayer->SetScreenPos((float)SCREEN_WIDTH / 2, pPlayer->GetGlobalPos().y);
		//pPlayer->SetWalkingSpeed(2.5f);
	}

	// プレイヤーは画面を出ることを防止
	float minimumX = 400.0f + pPC->GetHalfWidth();
	float maximumX = (float)SCREEN_WIDTH - pPC->GetHalfWidth() + offsetX - 80.0f;
	float minimumY = 0.0f + pPC->GetHalfHeight();
	float maximumY = (float)SCREEN_HEIGHT - fGroundHeight - pPC->GetHalfHeight();
	//	プレイヤーが2F以上の場合
	do
	{
		// 一番近いFLOORを取得
		GameObject* floor = GetNearestObject(pPlayer->GetGlobalPos(), GameObject::OBJ_FLOOR);
		// 取得出来なかった場合、break;
		if (NULL == floor) break;

		// プレイヤーが下に移動する場合、break;
		if (pPlayer->isClimbing() && pPlayer->GetDirection().y > 0.0f) break;

		// floorの上境界(Collision)
		float fTop = floor->GetCollision()->GetPosition().y - floor->GetCollision()->GetHalfHeight();
		// プレイヤーの中心座標y > floorの中心座標y ... break
		if (pPlayer->GetGlobalPos().y > floor->GetCollision()->GetPosition().y) break;

		maximumY = fTop - pPC->GetHalfHeight();
		minimumX = floor->GetGlobalPos().x - floor->GetCollision()->GetHalfWidth() + pPC->GetHalfWidth();
		maximumX = floor->GetGlobalPos().x + floor->GetCollision()->GetHalfWidth() - pPC->GetHalfWidth();
	} while (0);
	// プレイヤーは画面を出ることを防止
	// 左壁
	if (pPC->GetPosition().x < minimumX)
		pPlayer->SetGlobalPos(minimumX, pPlayer->GetGlobalPos().y);
	// 右壁
	if (pPC->GetPosition().x > maximumX)
		pPlayer->SetGlobalPos(maximumX, pPlayer->GetGlobalPos().y);
	// 上境界
	if (pPC->GetPosition().y < minimumY)
		pPlayer->SetGlobalPos(pPlayer->GetGlobalPos().x, minimumY);
	// 下境界
	if (pPC->GetPosition().y > maximumY)
		pPlayer->SetGlobalPos(pPlayer->GetGlobalPos().x, maximumY);
}

void GameScene01::PlayerControl()
{
	GameScene::PlayerControl();
}

void GameScene01::Debug()
{
	char buf[1024];
	int y = 32;

	sprintf_s(buf, "BgScroll(%.2f, %.2f)", fBgScroll.x, fBgScroll.y);
	y += 32;
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);
	y += 32;
	sprintf_s(buf, "[PlayerInfo]");
	D3DFont::Draw(0, y, buf, FONT_NAME, 32, D3DCOLOR_RGBA(100, 220, 255, 255));
	y += 32;
	sprintf_s(buf, ">MoveSpeed = %.2f", pPlayer->GetSpeed());
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);
	y += 32;
	sprintf_s(buf, ">ScreenPos(%.2f, %.2f)", pPlayer->GetScreenPos().x, pPlayer->GetScreenPos().y);
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);
	y += 32;
	sprintf_s(buf, ">GlobalPos(%.2f, %.2f)", pPlayer->GetGlobalPos().x, pPlayer->GetGlobalPos().y);
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);
	y += 32;
	sprintf_s(buf, ">CollisionCenter(%.2f, %.2f)", pPlayer->GetCollision()->GetPosition().x, pPlayer->GetCollision()->GetPosition().y);
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);
	y += 32;
	sprintf_s(buf, ">CollisionSize(%.2f, %.2f)", pPlayer->GetCollision()->GetWidth(), pPlayer->GetCollision()->GetHeight());
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);

	sprintf_s(buf, "[Mouse States]");
	y += 32;
	D3DFont::Draw(0, y, buf, FONT_NAME, 32, D3DCOLOR_RGBA(100, 220, 255, 255));
	sprintf_s(buf, ">LB = %d", Input::GetMouseButtonPress(0));
	y += 32;
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);
	sprintf_s(buf, ">RB = %d", Input::GetMouseButtonPress(1));
	y += 32;
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);
	sprintf_s(buf, ">MB = %d", Input::GetMouseButtonPress(2));
	y += 32;
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);
	sprintf_s(buf, ">deltaX = %d", Input::GetMouseDeltaX());
	y += 32;
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);
	sprintf_s(buf, ">deltaY = %d", Input::GetMouseDeltaY());
	y += 32;
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);
	sprintf_s(buf, ">deltaZ = %d", Input::GetMouseDeltaWheel());
	y += 32;
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);
	sprintf_s(buf, ">PosX = %d", Input::GetMouseX());
	y += 32;
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);
	sprintf_s(buf, ">PosY = %d", Input::GetMouseY());
	y += 32;
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);
}