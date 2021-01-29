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

#define LIFTING_SPEED_INIT 0.1f

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
	GameScene::Freeze(false);
	// Init Screen
	SetGlobalScaling(2.0f);
	isDarkness(true);
#ifdef _DEBUG
	isDarkness(false);
#endif // _DEBUG


	fBgScroll = D3DXVECTOR2(0.0f, 0.0f);
	fBgScrollMax = D3DXVECTOR2(2310.0f, (float)3000 - (720 / 2 + 1));
	fGroundHeight = 230.0f;

	memset(bCodeTaken, false, sizeof(bCodeTaken));
	memset(bDoorUnlockded, false, sizeof(bDoorUnlockded));
	memset(bBodyTaken, false, sizeof(bBodyTaken));
	bIdea = false;
	bIdeaHand = false;
	bTalking = false;
	bLCTaken = false;
	bVCTaken = false;
	bLifting = false;
	bSecondFloor = false;
	bEndScene = false;

	fLiftingSpeed = LIFTING_SPEED_INIT;

	// Init Player
	pPlayer = new GamePlayer;
	pPlayer->SetGlobalPos(1050.0f, (float)SCREEN_HEIGHT - fGroundHeight);
	pPlayer->SetWalkingSpeed(5.0f);
	pPlayer->SetStatusFlag(1, 0, 1, 1);

#ifdef _DEBUG
	pPlayer->SetWalkingSpeed(15.0f);
#endif // _DEBUG

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
	// TALKING TEXT
	pOverlays[6] = new GameOverlay(TEXTURE_TALKING_TEXT);
	pOverlays[6]->SetSize(224, 58);
	pOverlays[6]->GetSprite()->SetCutPos(0, 0);
	pOverlays[6]->GetSprite()->SetCutRange(224, 58);
	// LIFT OVERLAY DOOR
	pOverlays[7] = new GameOverlay(TEXTURE_LIFT_DOOR);
	pOverlays[7]->SetGlobalPos(3330.0f, 335.0f);
	pOverlays[7]->GetSprite()->SetCutPos(0, 0);
	pOverlays[7]->GetSprite()->SetCutRange(111, 147);
	pOverlays[7]->SetSize(111.0f * fGlobalScaling, 147.0f * fGlobalScaling);
	// Animator
	pAnimator = new Animator;
	pAnimator->Init(pOverlays[7]->GetSprite());
	// LIFT OVERLAY FRAME
	pOverlays[8] = new GameOverlay(TEXTURE_LIFT_FRAME);
	pOverlays[8]->SetScreenPos((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2);
	pOverlays[8]->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	pOverlays[8]->GetSprite()->SetCutPos(0, 3000 - (720 / 2 + 1));
	pOverlays[8]->GetSprite()->SetCutRange(1280 / 2, 720 / 2);

	// 見える範囲 Overlay
	pOverlays[63] = new GameOverlay(TEXTURE_OVERLAY_RANGE);
	pOverlays[63]->SetScreenPos(pPlayer->GetScreenPos().x, pPlayer->GetScreenPos().y + pPlayer->GetCollision()->GetHalfHeight());
	pOverlays[63]->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	pOverlays[63]->GetSprite()->SetCutPos(640, 360);
	pOverlays[63]->GetSprite()->SetCutRange(SCREEN_WIDTH, SCREEN_HEIGHT);
	pOverlays[63]->SetSize(pOverlays[63]->GetWidth() * fGlobalScaling * 5.5f, pOverlays[63]->GetHeight() * fGlobalScaling * 5.5f);

	// Init OBJ
	pObjects[0] = new GameObject(GameObject::OBJ_TRASH_STACK);
	pObjects[0]->SetGlobalPos(1000.0f, 310.0f);
	pObjects[0]->GetSprite()->SetColor(D3DCOLOR_RGBA(155, 155, 155, 255));
	pObjects[1] = new GameObject(GameObject::OBJ_TRASH_LEG);
	pObjects[1]->SetGlobalPos(1000.0f, 310.0f);
	// DOOR1
	pObjects[2] = new GameObject(GameObject::OBJ_DOOR1);
	pObjects[2]->SetGlobalPos(3113.0f, 410.0f);
	// CRASH_ROBOT
	pObjects[3] = new GameObject(GameObject::OBJ_CRASH_ROBOT);
	pObjects[3]->SetGlobalPos(1800.0f, 426.0f);
	pObjects[3]->GetSprite()->SetColor(D3DCOLOR_RGBA(155, 155, 155, 255));
	// ANYWHERE_DOOR
	pObjects[4] = new GameObject(GameObject::OBJ_DIGITAL_DOOR);
	pObjects[4]->SetGlobalPos(2735.0f, -1160.0f);
	pObjects[4]->SetSize(64.0f, 64.0f);
	// GENERATOR
	pObjects[5] = new GameObject(GameObject::OBJ_GENERATOR);
	pObjects[5]->SetGlobalPos(5600.0f, 440.0f);
	// CRASH_ROBOT2
	pObjects[6] = new GameObject(GameObject::OBJ_CRASH_ROBOT2);
	pObjects[6]->SetGlobalPos(2500.0f, 470.0f);
	pObjects[6]->GetSprite()->SetColor(D3DCOLOR_RGBA(155, 155, 155, 255));
	// 1F SCREEN
	pObjects[7] = new GameObject(GameObject::OBJ_SCREEN);
	pObjects[7]->SetGlobalPos(5260.0f, 430.0f);
	// LANGUAGE CHIP
	pObjects[8] = new GameObject(GameObject::OBJ_LANGUAGE_CHIP);
	pObjects[8]->SetGlobalPos(5430.0f, 460.0f);
	pObjects[8]->SetSize(32.0f, 32.0f);
	// LIFT
	pObjects[9] = new GameObject(GameObject::OBJ_LIFT);
	pObjects[9]->SetGlobalPos(3330.0f, 342.0f);
	// LIFT PANEL
	pObjects[10] = new GameObject(GameObject::OBJ_LIFT_PANEL);
	pObjects[10]->SetGlobalPos(3618.0f, 330.0f);
	pObjects[10]->SetScale(0.1f);
	// MAKER
	pObjects[11] = new GameObject(GameObject::OBJ_MAKER);
	pObjects[11]->SetGlobalPos(5310.0f, -1270.0f);
	// NEW_ROBOT1
	pObjects[12] = new GameObject(GameObject::OBJ_NEW_ROBOT);
	pObjects[12]->SetGlobalPos(5100.0f, -1210.0f);
	// NEW_ROBOT2
	pObjects[13] = new GameObject(GameObject::OBJ_NEW_ROBOT);
	pObjects[13]->SetGlobalPos(5350.0f, -1210.0f);
	// NEW_ROBOT3
	pObjects[14] = new GameObject(GameObject::OBJ_NEW_ROBOT);
	pObjects[14]->SetGlobalPos(5600.0f, -1210.0f);
	// COMPUTER
	pObjects[15] = new GameObject(GameObject::OBJ_COMPUTER);
	pObjects[15]->SetGlobalPos(4700.0f, -1180.0f);
	// VISUAL CHIP
	pObjects[16] = new GameObject(GameObject::OBJ_VISUAL_CHIP);
	pObjects[16]->SetGlobalPos(4500.0f, -1130.0f);
	pObjects[16]->SetSize(32.0f, 32.0f);
	// ITEM HAND
	pObjects[17] = new GameObject(GameObject::OBJ_ITEM_HAND);
	pObjects[17]->SetGlobalPos(5230.0f, -1170.0f);
	pObjects[17]->GetSprite()->SetColor(D3DCOLOR_RGBA(255, 255, 255, 0));

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

	// Create UI
	pGeneratorUI = new GeneratorUI;
	pScreenUI = new ScreenUI;
	pPanelUI = new PanelUI;
	pComputerUI = new ComputerUI;

	// TEXT
	pText = new GameText[3];
	pTextNotice = new GameText;
}

void GameScene01::Uninit()
{
	delete pAnimator;
	pAnimator = NULL;
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
	delete pScreenUI;
	pScreenUI = NULL;
	delete pPanelUI;
	pPanelUI = NULL;
	delete pComputerUI;
	pComputerUI = NULL;
	delete[] pText;
	pText = NULL;
	delete pTextNotice;
	pTextNotice = NULL;
}

void GameScene01::Update()
{
	// UI
	pGeneratorUI->Update();
	pScreenUI->Update(pGeneratorUI->isUnlocked(), bVCTaken);
	pPanelUI->Update();
	pComputerUI->Update();

	fBgScroll.x = pPlayer->GetGlobalPos().x - (float)SCREEN_WIDTH / 2;
	fBgScroll.y = (float)SCREEN_HEIGHT / 2 - pPlayer->GetGlobalPos().y;
	fBgScroll.x /= fGlobalScaling;
	fBgScroll.y /= fGlobalScaling;

	if (fBgScroll.x > fBgScrollMax.x)
		fBgScroll.x = fBgScrollMax.x;
	if (fBgScroll.x < 0.0f)
		fBgScroll.x = 0.0f;
	if (fBgScroll.y > fBgScrollMax.y)
		fBgScroll.y = fBgScrollMax.y;
	if (fBgScroll.y < 0.0f)
		fBgScroll.y = 0.0f;

	do
	{
		if (bFrozen) break;
		UpdatePlayer();
		UpdateObject();
		UpdateOverlay();
	} while (0);

	// LIFT DOOR ANIMATION
	pAnimator->PlayOnce(pOverlays[7]->GetSprite());

	// TEXT
	for (int i = 0; i < 3; i++)
	{
		(pText + i)->Update();
	}
	pTextNotice->Update();

	if (bEndScene) Game::LoadNextScene(Game::SCENE_TEST);
}

void GameScene01::Draw()
{
	float fGlobalPosOffsetX = fBgScroll.x * fGlobalScaling;
	float fGlobalPosOffsetY = fBgScroll.y * fGlobalScaling;
	pOverlays[0]->Draw();

	for (GameObject* object : pObjects)
	{
		if (NULL == object) continue;
		object->Draw();
	}

	// エレベーター特別処理
	bool bShowTheDoor = false;
	do
	{
		if (bLifting || !pPanelUI->isUnlocked())
		{
			bShowTheDoor = true;
		}
		if (bLifting && bShowTheDoor)
		{
			pPlayer->Draw();

			pOverlays[7]->SetGlobalPos(3330.0f, 335.0f);
			pOverlays[7]->SetScreenPos(pOverlays[7]->GetGlobalPos().x - fGlobalPosOffsetX, pOverlays[7]->GetGlobalPos().y + fGlobalPosOffsetY);
			pOverlays[7]->Draw();
			pOverlays[7]->SetGlobalPos(3330.0f, -1250.0f);
			pOverlays[7]->SetScreenPos(pOverlays[7]->GetGlobalPos().x - fGlobalPosOffsetX, pOverlays[7]->GetGlobalPos().y + fGlobalPosOffsetY);
			pOverlays[7]->Draw();

			pOverlays[8]->Draw();
			break;
		}
		if (bShowTheDoor)
		{
			pOverlays[7]->SetGlobalPos(3330.0f, 335.0f);
			pOverlays[7]->SetScreenPos(pOverlays[7]->GetGlobalPos().x - fGlobalPosOffsetX, pOverlays[7]->GetGlobalPos().y + fGlobalPosOffsetY);
			pOverlays[7]->Draw();
			pOverlays[7]->SetGlobalPos(3330.0f, -1250.0f);
			pOverlays[7]->SetScreenPos(pOverlays[7]->GetGlobalPos().x - fGlobalPosOffsetX, pOverlays[7]->GetGlobalPos().y + fGlobalPosOffsetY);
			pOverlays[7]->Draw();
		}
		pOverlays[7]->SetGlobalPos(3330.0f, 335.0f);
		pOverlays[7]->SetScreenPos(pOverlays[7]->GetGlobalPos().x - fGlobalPosOffsetX, pOverlays[7]->GetGlobalPos().y + fGlobalPosOffsetY);
		pOverlays[7]->Draw();
		pOverlays[7]->SetGlobalPos(3330.0f, -1250.0f);
		pOverlays[7]->SetScreenPos(pOverlays[7]->GetGlobalPos().x - fGlobalPosOffsetX, pOverlays[7]->GetGlobalPos().y + fGlobalPosOffsetY);
		pOverlays[7]->Draw();

		pOverlays[8]->Draw();
		pPlayer->Draw();
	} while (0);
	
	pOverlays[1]->Draw();

	// TEXT
	for (int i = 0; i < 3; i++)
	{
		(pText + i)->Draw();
	}
	pTextNotice->Draw();

	if (isDarkness())
	{
		pOverlays[63]->Draw();
	}
	if (bIdea) pOverlays[2]->Draw();
	if (bIdeaHand) pOverlays[3]->Draw();
	if (bCodeTaken[0]) pOverlays[4]->Draw();
	if (bCodeTaken[1]) pOverlays[5]->Draw();
	if (bTalking) pOverlays[6]->Draw();

	// UI
	pGeneratorUI->Draw();
	pScreenUI->Draw();
	pPanelUI->Draw();
	pComputerUI->Draw();

#ifdef _DEBUG
	// デバッグ文字の表示
	if (Game::DebugMode()) this->Debug();
#endif // _DEBUG
}

void GameScene01::UpdateObject()
{
	float fGlobalPosOffsetX = fBgScroll.x * fGlobalScaling;
	float fGlobalPosOffsetY = fBgScroll.y * fGlobalScaling;
	for (GameObject* object : pObjects)
	{
		if (NULL == object) continue;
		object->SetScreenPos(object->GetGlobalPos().x - fGlobalPosOffsetX, object->GetGlobalPos().y + fGlobalPosOffsetY);
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
	if (pGeneratorUI->isUnlocked())
	{
		pObjects[7]->GetSprite()->SetCutPos(64, 0);
	}

	// コリジョンにより当たり判定
	Collision* pPC = pPlayer->GetCollision();

	bIdea = false;
	bIdeaHand = false;
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
			// FBI Open the door!
			if (bCodeTaken[0] && bCodeTaken[1] && Input::GetKeyTrigger(DIK_E))
			{
				bDoorUnlockded[0] = true;
				bCodeTaken[0] = bCodeTaken[1] = false;
				PlaySound(SOUND_LABEL_SE_DOOR_OPEN1);
				break;
			}
			bIdeaHand = true;
		}

		if (obj->GetGlobalPos().x - pPC->GetPosition().x < pOC->GetHalfWidth() + pPC->GetHalfWidth())
		{
			pPlayer->SetGlobalPos(obj->GetGlobalPos().x - pOC->GetHalfWidth() - pPC->GetHalfWidth(), pPlayer->GetGlobalPos().y);
		}
	} while (0);

	// LEG
	obj = GetNearestObject(pPC->GetPosition(), GameObject::OBJ_TRASH_LEG);
	do
	{
		if (bBodyTaken[0]) break;
		if (abs(obj->GetGlobalPos().x - pPlayer->GetGlobalPos().x) <= 64.0f)
		{
			if (Input::GetKeyTrigger(DIK_E))
			{
				pPlayer->SetStatusFlag(0, -1, -1, -1);
				obj->GetSprite()->SetColor(D3DCOLOR_RGBA(255, 255, 255, 0));
				bBodyTaken[0] = true;
				PlaySound(SOUND_LABEL_SE_PICKUP_LEG);
			}
			bIdea = true;
		}
	} while (0);

	// CODE01
	do
	{
		if (bDoorUnlockded[0] || bCodeTaken[0]) break;
		if (pPlayer->GetGlobalPos().x >= 700 - 32.0f && pPlayer->GetGlobalPos().x <= 700 + 32.0f)
		{
			if (Input::GetKeyTrigger(DIK_E))
			{
				bCodeTaken[0] = true;
				PlaySound(SOUND_LABEL_SE_PICKUP);
				break;
			}
			bIdea = true;
		}
	} while (0);
	// CODE02
	obj = GetNearestObject(pPC->GetPosition(), GameObject::OBJ_CRASH_ROBOT2);
	do
	{
		if (bDoorUnlockded[0] || bCodeTaken[1]) break;
		if (abs(obj->GetGlobalPos().x - pPlayer->GetGlobalPos().x) <= 64.0f)
		{
			if (Input::GetKeyTrigger(DIK_E))
			{
				bCodeTaken[1] = true;
				PlaySound(SOUND_LABEL_SE_PICKUP);
				break;
			}
			bIdea = true;
		}
	} while (0);

	// GENERATOR
	obj = GetNearestObject(pPC->GetPosition(), GameObject::OBJ_GENERATOR);
	do
	{
		if (pGeneratorUI->isUnlocked()) break;
		if (bSecondFloor) break;
		if (abs(obj->GetGlobalPos().x - pPlayer->GetGlobalPos().x) <= 64.0f)
		{
			if (Input::GetKeyTrigger(DIK_E))
			{
				pGeneratorUI->OpenUI();
				PlaySound(SOUND_LABEL_SE_GENERATOR_UI);
				break;
			}
			bIdea = true;
		}
	} while (0);

	// TALKING
	obj = GetNearestObject(pPC->GetPosition(), GameObject::OBJ_CRASH_ROBOT);
	do
	{
		if (bSecondFloor) break;
		if (abs(obj->GetGlobalPos().x - pPlayer->GetGlobalPos().x) <= 64.0f)
		{
			if (bTalking) break;
			if (Input::GetKeyTrigger(DIK_E))
			{
				bTalking = true;
				PlaySound(SOUND_LABEL_SE_KEYBOARD);
				if (bLCTaken)
				{
					pOverlays[6]->GetSprite()->SetCutPos(224, 0);
				}
				break;
			}
			bIdea = true;
		}
		else {
			bTalking = false;
		}
	} while (0);

	// LANGUAGE CHIP
	obj = GetNearestObject(pPC->GetPosition(), GameObject::OBJ_LANGUAGE_CHIP);
	do
	{
		if (bLCTaken) break;
		if (bSecondFloor) break;
		if (abs(obj->GetGlobalPos().x - pPlayer->GetGlobalPos().x) <= 64.0f)
		{
			if (Input::GetKeyTrigger(DIK_E))
			{
				bLCTaken = true;
				obj->GetSprite()->SetColor(D3DCOLOR_RGBA(255, 255, 255, 0));
				int offset = 32;
				if (bVCTaken) offset += 32;
				if (bBodyTaken[1]) offset += 32;
				pText->CreateText(0, SCREEN_HEIGHT - offset, 30, "+ 言語認識", -1, 60, D3DCOLOR_RGBA(100, 255, 155, 255));
				pTextNotice->CreateText((int)pPlayer->GetScreenPos().x - 33, (int)pPlayer->GetScreenPos().y - 128,
					30, "+ 言語認識", 60, 30, D3DCOLOR_RGBA(100, 255, 155, 255));
				PlaySound(SOUND_LABEL_SE_LANGUAGE);
				break;
			}
			bIdeaHand = true;
		}
	} while (0);
	// VISUAL CHIP
	obj = GetNearestObject(pPC->GetPosition(), GameObject::OBJ_VISUAL_CHIP);
	do
	{
		if (bVCTaken) break;
		if (!bSecondFloor) break;
		if (abs(obj->GetGlobalPos().x - pPlayer->GetGlobalPos().x) <= 64.0f)
		{
			if (Input::GetKeyTrigger(DIK_E))
			{
				bVCTaken = true;
				isDarkness(false);
				obj->GetSprite()->SetColor(D3DCOLOR_RGBA(255, 255, 255, 0));
				int offset = 32;
				if (bLCTaken) offset += 32;
				if (bBodyTaken[1]) offset += 32;
				(pText + 1)->CreateText(0, SCREEN_HEIGHT - offset, 30, "+ 視覚的強化（色認識）", -1, 60, D3DCOLOR_RGBA(255, 200, 50, 255));
				pTextNotice->CreateText((int)pPlayer->GetScreenPos().x - 98, (int)pPlayer->GetScreenPos().y - 128,
					30, "+ 視覚的強化", 60, 30, D3DCOLOR_RGBA(255, 200, 50, 255));
				PlaySound(SOUND_LABEL_SE_VISUAL);
				break;
			}
			bIdeaHand = true;
		}
	} while (0);

	// SCREEN UI
	obj = GetNearestObject(pPC->GetPosition(), GameObject::OBJ_SCREEN);
	do
	{
		if (bSecondFloor) break;
		if (abs(obj->GetGlobalPos().x - pPlayer->GetGlobalPos().x) <= 64.0f)
		{
			if (Input::GetKeyTrigger(DIK_E))
			{
				pScreenUI->OpenUI();
				if (pGeneratorUI->isUnlocked())
				{
					PlaySound(SOUND_LABEL_SE_SCREEN_OPEN);
				}
				break;
			}
			bIdea = true;
		}
	} while (0);

	// PANEL UI
	obj = GetNearestObject(pPC->GetPosition(), GameObject::OBJ_LIFT_PANEL);
	do
	{
		if (!pGeneratorUI->isUnlocked()) break;
		if (pPanelUI->isUnlocked()) break;
		if (abs(obj->GetGlobalPos().x - pPlayer->GetGlobalPos().x) <= 64.0f)
		{
			if (Input::GetKeyTrigger(DIK_E))
			{
				pPanelUI->OpenUI();
				PlaySound(SOUND_LABEL_SE_BUTTON);
				break;
			}
			bIdeaHand = true;
		}
	} while (0);

	// LIFT
	obj = GetNearestObject(pPC->GetPosition(), GameObject::OBJ_LIFT);
	do
	{
		if (!pPanelUI->isUnlocked()) break;
		if (bLifting) break;
		if (abs(obj->GetGlobalPos().x - pPlayer->GetGlobalPos().x) <= 64.0f)
		{
			if (Input::GetKeyTrigger(DIK_E))
			{
				bLifting = true;
				pAnimator->Reset(pOverlays[7]->GetSprite());
				pAnimator->Preset(4, 2, 5, true);
				PlaySound(SOUND_LABEL_SE_LIFT_LIFTING);
				break;
			}
			bIdeaHand = true;
		}
	} while (0);
	// *** LIFTING ***
	do
	{
		if (!bLifting) break;

		static const float fSpeedMax = 10.0f;
		if (!bSecondFloor)
		{
			obj->SetGlobalPos(obj->GetGlobalPos().x, obj->GetGlobalPos().y - fLiftingSpeed);
			fGroundHeight += fLiftingSpeed;
		}
		else
		{
			obj->SetGlobalPos(obj->GetGlobalPos().x, obj->GetGlobalPos().y + fLiftingSpeed);
			fGroundHeight -= fLiftingSpeed;
		}

		// limitation
		fLiftingSpeed += 0.1f;
		if (fLiftingSpeed > fSpeedMax) fLiftingSpeed = fSpeedMax;
		if (obj->GetGlobalPos().y < -1238.0f)
		{
			obj->SetGlobalPos(obj->GetGlobalPos().x, -1238.0f);
			bLifting = false;
			bSecondFloor = true;
			pAnimator->Reset(pOverlays[7]->GetSprite());
			pAnimator->Preset(4, 2, 5);
			StopSound(SOUND_LABEL_SE_LIFT_LIFTING);
			PlaySound(SOUND_LABEL_SE_LIFT_OPEN);
			fLiftingSpeed = LIFTING_SPEED_INIT;
		}
		if (obj->GetGlobalPos().y > 342.0f)
		{
			obj->SetGlobalPos(obj->GetGlobalPos().x, 342.0f);
			bLifting = false;
			bSecondFloor = false;
			pAnimator->Reset(pOverlays[7]->GetSprite());
			pAnimator->Preset(4, 2, 5);
			StopSound(SOUND_LABEL_SE_LIFT_LIFTING);
			PlaySound(SOUND_LABEL_SE_LIFT_OPEN);
			fLiftingSpeed = LIFTING_SPEED_INIT;
		}
	} while (0);

	// COMPUTER
	obj = GetNearestObject(pPC->GetPosition(), GameObject::OBJ_COMPUTER);
	do
	{
		if (!bSecondFloor) break;
		if (pComputerUI->isUnlocked()) break;
		if (!bVCTaken) break;
		if (abs(obj->GetGlobalPos().x - pPlayer->GetGlobalPos().x) <= 64.0f)
		{
			if (Input::GetKeyTrigger(DIK_E))
			{
				pComputerUI->OpenUI();
				PlaySound(SOUND_LABEL_SE_KEYBOARD);
				break;
			}
			bIdeaHand = true;
		}
	} while (0);
	// ITEM HAND
	obj = GetNearestObject(pPC->GetPosition(), GameObject::OBJ_ITEM_HAND);
	do
	{
		if (!bSecondFloor) break;
		if (bBodyTaken[1]) break;
		if (!pComputerUI->isUnlocked()) break;
		obj->GetSprite()->SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
		if (abs(obj->GetGlobalPos().x - pPlayer->GetGlobalPos().x) <= 64.0f)
		{
			if (Input::GetKeyTrigger(DIK_E))
			{
				bBodyTaken[1] = true;
				pPlayer->SetStatusFlag(-1, -1, 0, -1);
				obj->GetSprite()->SetColor(D3DCOLOR_RGBA(255, 255, 255, 0));
				int offset = 32;
				if (bLCTaken) offset += 32;
				if (bVCTaken) offset += 32;
				(pText + 2)->CreateText(0, SCREEN_HEIGHT - offset, 30, "+ 紛失した部品", -1, 60, D3DCOLOR_RGBA(0, 200, 255, 255));
				pTextNotice->CreateText((int)pPlayer->GetScreenPos().x - 113, (int)pPlayer->GetScreenPos().y - 128,
					30, "+ 紛失した部品", 60, 30, D3DCOLOR_RGBA(0, 200, 255, 255));
				PlaySound(SOUND_LABEL_SE_PICKUP_LEG);
				break;
			}
			bIdeaHand = true;
		}
	} while (0);

	// ANYWHERE DOOR
	obj = GetNearestObject(pPC->GetPosition(), GameObject::OBJ_DIGITAL_DOOR);
	do
	{
		if (!bSecondFloor) break;
		if (bDoorUnlockded[1]) break;
		if (abs(obj->GetGlobalPos().x - pPlayer->GetGlobalPos().x) <= 64.0f)
		{
			// FBI Open the door!
			if (Input::GetKeyTrigger(DIK_E))
			{
				if (!bBodyTaken[1])
				{
					pTextNotice->CreateText((int)pPlayer->GetScreenPos().x - 225, (int)pPlayer->GetScreenPos().y - 128,
						30, "×体の部品が一部紛失されました", 60, 30, D3DCOLOR_RGBA(255, 0, 0, 255));
					PlaySound(SOUND_LABEL_SE_WRONG);
					break;
				}
				bDoorUnlockded[1] = true;
				PlaySound(SOUND_LABEL_SE_DOOR_OPEN2);
				break;
			}
			bIdeaHand = true;
		}
	} while (0);
	// ANYWHERE DOOR
	obj = GetNearestObject(pPC->GetPosition(), GameObject::OBJ_DIGITAL_DOOR);
	do
	{
		if (!bSecondFloor) break;
		if (!bDoorUnlockded[1]) break;
		if (abs(obj->GetGlobalPos().x - pPlayer->GetGlobalPos().x) <= 64.0f)
		{
			// GO TO NEXT SCENE
			if ((Input::GetKeyTrigger(DIK_E) || Input::GetKeyTrigger(DIK_W)) && bDoorUnlockded[1])
			{
				bEndScene = true;
				return;
			}
			if (bDoorUnlockded[1]) break;
		}
	} while (0);
}

void GameScene01::UpdateOverlay()
{
	float fGlobalPosOffsetX = fBgScroll.x * fGlobalScaling;
	float fGlobalPosOffsetY = fBgScroll.y * fGlobalScaling;
	pOverlays[0]->GetSprite()->SetCutPos((int)fBgScroll.x, 3000 - (720 / 2 + 1) - (int)fBgScroll.y);
	pOverlays[1]->GetSprite()->SetCutPos((int)fBgScroll.x, 3000 - (720 / 2 + 1) - (int)fBgScroll.y);
	pOverlays[8]->GetSprite()->SetCutPos((int)fBgScroll.x, 3000 - (720 / 2 + 1) - (int)fBgScroll.y);
	pOverlays[6]->SetScreenPos(pObjects[3]->GetScreenPos().x + 200.0f, pObjects[3]->GetScreenPos().y - 80.0f);
	pOverlays[63]->SetScreenPos(pPlayer->GetScreenPos().x, pPlayer->GetScreenPos().y + pPlayer->GetCollision()->GetHalfHeight() + 32.0f);

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
	float offsetY = fBgScroll.y * fGlobalScaling;
	// 背景はスクロールしていない状態 -> スクリーン座標は変更できる
	// 背景はスクロールしている状態	-> スクリーン座標は変更できない
	// グローバル座標（世界座標）はいつも正常に変わる
	if (fBgScroll.x <= 0.0f || fBgScroll.x >= fBgScrollMax.x)
	{
		pPlayer->SetScreenPos(pPlayer->GetGlobalPos().x - offsetX, pPlayer->GetGlobalPos().y + offsetY);
	}
	else
	{
		pPlayer->SetScreenPos((float)SCREEN_WIDTH / 2, pPlayer->GetGlobalPos().y);
	}
	if (fBgScroll.y <= 0.0f || fBgScroll.y >= fBgScrollMax.y)
	{
		pPlayer->SetScreenPos(pPlayer->GetGlobalPos().x - offsetX, pPlayer->GetGlobalPos().y + offsetY);
	}
	else
	{
		pPlayer->SetScreenPos(pPlayer->GetGlobalPos().x - offsetX, (float)SCREEN_HEIGHT / 2);
	}

	// プレイヤーは画面を出ることを防止
	float minimumX = 400.0f + pPC->GetHalfWidth();
	float maximumX = (float)SCREEN_WIDTH - pPC->GetHalfWidth() + offsetX - 80.0f;
	float minimumY = 0.0f + pPC->GetHalfHeight() - offsetY;
	float maximumY = (float)SCREEN_HEIGHT - fGroundHeight - pPC->GetHalfHeight();
	// *** LIFTING ***
	do
	{
		if (!bLifting) break;
		GameObject* obj = GetNearestObject(pPC->GetPosition(), GameObject::OBJ_LIFT);
		minimumX = obj->GetGlobalPos().x - 55.0f;
		maximumX = obj->GetGlobalPos().x + 55.0f;
		if (!bSecondFloor)
		{
			maximumY = obj->GetGlobalPos().y + 55.0f;
		}
		if (bSecondFloor)
		{
			maximumY = obj->GetGlobalPos().y + 70.0f;
		}
	} while (0);
	// 2F
	if (bSecondFloor && !bLifting)
	{
		minimumX = 2530.0f;
		maximumX = 5630.0f;
	}
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

#ifdef _DEBUG
void GameScene01::Debug()
{
	char buf[1024];
	int y = 32;

	sprintf_s(buf, "BgScroll(%.2f, %.2f)", fBgScroll.x, fBgScroll.y);
	y += 32;
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);
	sprintf_s(buf, "GroundHeight = %.2f", fGroundHeight);
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
	y += 32;
	sprintf_s(buf, "[ObjectInfo] LIFT");
	D3DFont::Draw(0, y, buf, FONT_NAME, 32, D3DCOLOR_RGBA(255, 155, 100, 255));
	y += 32;
	sprintf_s(buf, ">GlobalPos(%.2f, %.2f)", pObjects[9]->GetGlobalPos().x, pObjects[9]->GetGlobalPos().y);
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
#endif // _DEBUG