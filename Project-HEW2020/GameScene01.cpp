//----------------------------------------------------------------------------
// 
// Project-HEW2020 [GameScene01.cpp]
// �V�[��01
// 
// Date:   2021/01/10
// Author: AT12D187_17_���i
// 
//----------------------------------------------------------------------------
#include <stdio.h>
#include "GameScene01.h"
#include "debug_font.h"
#include "game.h"

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
	fBgScrollMax = D3DXVECTOR2(4719.0f, 5279.0f);
	fGroundHeight = 230.0f;

	// Init Player
	pPlayer = new GamePlayer;
	pPlayer->SetGlobalPos(600.0f, (float)SCREEN_HEIGHT - fGroundHeight);

	// Init BG
	pOverlays[0] = new GameOverlay(TEXTURE_SCENE01_BG);
	pOverlays[0]->SetScreenPos((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2);
	pOverlays[0]->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	pOverlays[0]->GetSprite()->SetCutPos(0, 5279);
	pOverlays[0]->GetSprite()->SetCutRange(1280, 720);

	pOverlays[1] = new GameOverlay(TEXTURE_SCENE01_BG_OVERLAY);
	pOverlays[1]->SetScreenPos((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2);
	pOverlays[1]->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	pOverlays[1]->GetSprite()->SetCutPos(0, 5279);
	pOverlays[1]->GetSprite()->SetCutRange(1280, 720);
	pOverlays[1]->GetSprite()->SetColor(D3DCOLOR_RGBA(255, 255, 255, 230));

	// Init OBJ
	pObjects[0] = new GameObject(GameObject::OBJ_TRASH_STACK);
	pObjects[0]->SetGlobalPos(900.0f, 310.0f);
	pObjects[1] = new GameObject(GameObject::OBJ_TRASH_CORE);
	pObjects[1]->SetGlobalPos(900.0f, 310.0f);
	// DOOR1
	pObjects[2] = new GameObject(GameObject::OBJ_DOOR1);
	pObjects[2]->SetGlobalPos(3100.0f, 415.0f);

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
}

void GameScene01::Update()
{
	fBgScroll.x = pPlayer->GetGlobalPos().x - (float)SCREEN_WIDTH / 2;
	//fBgScroll.x /= fGlobalScaling;

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

	// �f�o�b�O�����̕\��
	if (Game::DebugMode()) this->Debug();

	pOverlays[1]->Draw();
}

void GameScene01::UpdateObject()
{
	float fGlobalPosOffset = fBgScroll.x;
	//fGlobalPosOffset *= fGlobalScaling;
	for (GameObject* object : pObjects)
	{
		if (NULL == object) continue;
		object->SetScreenPos(object->GetGlobalPos().x - fGlobalPosOffset, object->GetGlobalPos().y);
		object->Update();
	}
}

void GameScene01::UpdateOverlay()
{
	pOverlays[0]->GetSprite()->SetCutPos((int)fBgScroll.x, 5279 - (int)fBgScroll.y);
	pOverlays[1]->GetSprite()->SetCutPos((int)fBgScroll.x, 5279 - (int)fBgScroll.y);

	// ���������UI�̍X�V����
	do
	{
		// ...
		// ...
		// ...
	} while (0);
}

void GameScene01::UpdatePlayer()
{
	this->PlayerControl();
	// �v���C���[�C���X�^���X���X�V
	pPlayer->Update();

	// �v���C���[�̃R���W�������擾
	Collision* pPC = pPlayer->GetCollision();
	// �X�N���[�����W�ƃ��[���h���W�̓���
	float offsetX = fBgScroll.x;
	float offsetY = fBgScroll.y;
	// �w�i�̓X�N���[�����Ă��Ȃ���� -> �X�N���[�����W�͕ύX�ł���
	// �w�i�̓X�N���[�����Ă�����	-> �X�N���[�����W�͕ύX�ł��Ȃ�
	// �O���[�o�����W�i���E���W�j�͂�������ɕς��
	if (fBgScroll.x <= 0.0f || fBgScroll.x >= fBgScrollMax.x)
		pPlayer->SetScreenPos(pPlayer->GetGlobalPos().x - offsetX, pPlayer->GetGlobalPos().y);
	else
		pPlayer->SetScreenPos((float)SCREEN_WIDTH / 2, pPlayer->GetGlobalPos().y);

	// �v���C���[�͉�ʂ��o�邱�Ƃ�h�~
	float minimumX = 400.0f + pPC->GetHalfWidth();
	float maximumX = (float)SCREEN_WIDTH - pPC->GetHalfWidth() + offsetX - 180.0f;
	float minimumY = 0.0f + pPC->GetHalfHeight();
	float maximumY = (float)SCREEN_HEIGHT - fGroundHeight - pPC->GetHalfHeight();
	//	�v���C���[��2F�ȏ�̏ꍇ
	do
	{
		// ��ԋ߂�FLOOR���擾
		GameObject* floor = GetNearestObject(pPlayer->GetGlobalPos(), GameObject::OBJ_FLOOR);
		// �擾�o���Ȃ������ꍇ�Abreak;
		if (NULL == floor) break;

		// �v���C���[�����Ɉړ�����ꍇ�Abreak;
		if (pPlayer->isClimbing() && pPlayer->GetDirection().y > 0.0f) break;

		// floor�̏㋫�E(Collision)
		float fTop = floor->GetCollision()->GetPosition().y - floor->GetCollision()->GetHalfHeight();
		// �v���C���[�̒��S���Wy > floor�̒��S���Wy ... break
		if (pPlayer->GetGlobalPos().y > floor->GetCollision()->GetPosition().y) break;

		maximumY = fTop - pPC->GetHalfHeight();
		minimumX = floor->GetGlobalPos().x - floor->GetCollision()->GetHalfWidth() + pPC->GetHalfWidth();
		maximumX = floor->GetGlobalPos().x + floor->GetCollision()->GetHalfWidth() - pPC->GetHalfWidth();
	} while (0);
	// �v���C���[�͉�ʂ��o�邱�Ƃ�h�~
	// ����
	if (pPC->GetPosition().x < minimumX)
		pPlayer->SetGlobalPos(minimumX, pPlayer->GetGlobalPos().y);
	// �E��
	if (pPC->GetPosition().x > maximumX)
		pPlayer->SetGlobalPos(maximumX, pPlayer->GetGlobalPos().y);
	// �㋫�E
	if (pPC->GetPosition().y < minimumY)
		pPlayer->SetGlobalPos(pPlayer->GetGlobalPos().x, minimumY);
	// �����E
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
	float y = 0.0f;

	sprintf_s(buf, "BgScroll(%.2f, %.2f)", fBgScroll.x, fBgScroll.y);
	y += 32.0f;
	DebugFont::Draw(0.0f, y, buf);

	y += 64.0f;
	sprintf_s(buf, "[PlayerInfo]");
	DebugFont::Draw(0.0f, y, buf);
	y += 32.0f;
	sprintf_s(buf, ">MoveSpeed = %.2f", pPlayer->GetSpeed());
	DebugFont::Draw(0.0f, y, buf);
	y += 32.0f;
	sprintf_s(buf, ">ScreenPos(%.2f, %.2f)", pPlayer->GetScreenPos().x, pPlayer->GetScreenPos().y);
	DebugFont::Draw(0.0f, y, buf);
	y += 32.0f;
	sprintf_s(buf, ">GlobalPos(%.2f, %.2f)", pPlayer->GetGlobalPos().x, pPlayer->GetGlobalPos().y);
	DebugFont::Draw(0.0f, y, buf);
	y += 32.0f;
	sprintf_s(buf, ">CollisionCenter(%.2f, %.2f)", pPlayer->GetCollision()->GetPosition().x, pPlayer->GetCollision()->GetPosition().y);
	DebugFont::Draw(0.0f, y, buf);
	y += 32.0f;
	sprintf_s(buf, ">CollisionSize(%.2f, %.2f)", pPlayer->GetCollision()->GetWidth(), pPlayer->GetCollision()->GetHeight());
	DebugFont::Draw(0.0f, y, buf);
	y += 32.0f;
	sprintf_s(buf, ">isOnLadder = %d", pPlayer->isOnLadder());
	DebugFont::Draw(0.0f, y, buf);
	y += 32.0f;
	sprintf_s(buf, ">isClimbing = %d", pPlayer->isClimbing());
	DebugFont::Draw(0.0f, y, buf);
}