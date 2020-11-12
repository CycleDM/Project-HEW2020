//----------------------------------------------------------------------------
// 
// Project-HEW2020 [TestScene.cpp]
// �v���g�^�C�v�V�[��
// 
// Date:   2020/11/06
// Author: AT12D187_17_���i
// 
//----------------------------------------------------------------------------
#include <stdio.h>
#include "TestScene.h"
#include "debug_font.h"

#define TEST_SCENE_SCALE	(3.33333f)

TestScene::TestScene()
{
	this->Init();
}

TestScene::~TestScene()
{
	this->Uninit();
}

void TestScene::Init(void)
{
	fBgScroll.x = 0.0f;
	fBgScroll.y = 0.0f;

	// �v���C���[�C���X�^���X
	pPlayer = new GamePlayer;
	// �v���C���[�̍��W
	pPlayer->SetGlobalPos(0.0f, (float)SCREEN_HEIGHT);

	// �w�i
	pOverlays[0] = new GameOverlay(TEXTURE_BG);
	pOverlays[0]->SetPosition((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2);
	pOverlays[0]->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	pOverlays[0]->GetSprite()->SetCutPos(0, 0);
	pOverlays[0]->GetSprite()->SetCutRange(384, 216);
	// �h�A�t���[���iOverlay�j
	pOverlays[1] = new GameOverlay(TEXTURE_BG_OVERLAY);
	pOverlays[1]->SetPosition((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2);
	pOverlays[1]->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	pOverlays[1]->GetSprite()->SetCutPos(0, 0);
	pOverlays[1]->GetSprite()->SetCutRange(384, 216);
	pOverlays[1]->GetSprite()->SetColor(D3DCOLOR_RGBA(255, 255, 255, 230));
	// �Q�[���I�u�W�F�N�g�E�C���X�^���X
	// BED
	pObjects[0] = new GameObject(GameObject::BED);
	// FLOOR
	pObjects[1] = new GameObject(GameObject::FLOOR);
	// LADDER
	pObjects[2] = new GameObject(GameObject::LADDER);
	pObjects[3] = new GameObject(GameObject::LADDER);

	// �I�u�W�F�N�g�̃T�C�Y��C�ɏ�����
	for (GameObject* object : pObjects)
	{
		if (NULL == object) continue;
		object->SetSize(object->GetWidth() * TEST_SCENE_SCALE, object->GetHeight() * TEST_SCENE_SCALE);
	}

	// FLOOR Overlay
	pOverlays[2] = new GameOverlay(TEXTURE_OBJ_FLOOR_OVERLAY);
	pOverlays[2]->SetSize(pOverlays[2]->GetWidth() * TEST_SCENE_SCALE, pOverlays[2]->GetHeight() * TEST_SCENE_SCALE);
}

void TestScene::Uninit(void)
{
	delete pPlayer;
	pPlayer = NULL;

	delete[] pObjects;
	memset(pObjects, NULL, sizeof(pObjects));

	delete[] pOverlays;
	memset(pOverlays, NULL, sizeof(pOverlays));
}

void TestScene::Update(void)
{
	// �w�i�̃X�N���[��
	fBgScroll.x = pPlayer->GetGlobalPos().x - (float)SCREEN_WIDTH / 2;
	fBgScroll.x /= TEST_SCENE_SCALE;
	// �C��
	if (fBgScroll.x > 264.0f)
		fBgScroll.x = 264.0f;
	if (fBgScroll.x < 0.0f)
		fBgScroll.x = 0.0f;

	UpdatePlayer();
	UpdateObject();
	UpdateOverlay();
}

void TestScene::Draw(void)
{
	pOverlays[0]->Draw();

	for (GameObject* object : pObjects)
	{
		if (NULL == object) continue;
		object->Draw();
	}

	pPlayer->Draw();
	pOverlays[1]->Draw();
	pOverlays[2]->Draw();

	Debug();
}

void TestScene::UpdatePlayer(void)
{
	// �v���C���[�̃X�N���[�����W�̓���
	float fGlobalPosOffset = fBgScroll.x * TEST_SCENE_SCALE;
	if (fBgScroll.x <= 0.0f || fBgScroll.x >= 264.0f)
		pPlayer->SetScreenPos(pPlayer->GetGlobalPos().x - fGlobalPosOffset, pPlayer->GetGlobalPos().y);
	else
		pPlayer->SetScreenPos((float)SCREEN_WIDTH / 2, pPlayer->GetGlobalPos().y);

	// �v���C���[�̍��W���C���i��ʂ��o�邱�Ƃ�h�~�j
	// ����
	if (pPlayer->GetGlobalPos().x < 0.0f + 64.0f * TEST_SCENE_SCALE / 2)
		pPlayer->SetGlobalPos(0.0f + 64.0f * TEST_SCENE_SCALE / 2, pPlayer->GetGlobalPos().y);
	// �E��
	if (pPlayer->GetGlobalPos().x > (float)SCREEN_WIDTH - 64.0f * TEST_SCENE_SCALE / 2 + fGlobalPosOffset)
		pPlayer->SetGlobalPos((float)SCREEN_WIDTH - 64.0f * TEST_SCENE_SCALE / 2 + fGlobalPosOffset, pPlayer->GetGlobalPos().y);
	// �㋫�E
	if (pPlayer->GetGlobalPos().y < 0.0f + 64.0f * TEST_SCENE_SCALE / 2)
		pPlayer->SetGlobalPos(pPlayer->GetGlobalPos().x, 0.0f + 64.0f * TEST_SCENE_SCALE / 2);
	// �����E
	if (pPlayer->GetGlobalPos().y > (float)SCREEN_HEIGHT - 64.0f - 64.0f * TEST_SCENE_SCALE / 2)
		pPlayer->SetGlobalPos(pPlayer->GetGlobalPos().x, (float)SCREEN_HEIGHT - 64.0f - 64.0f * TEST_SCENE_SCALE / 2);

	// �v���C���[�C���X�^���X���X�V
	pPlayer->Update();
}

void TestScene::UpdateObject(void)
{
	float fGlobalPosOffset = fBgScroll.x * TEST_SCENE_SCALE;
	pObjects[0]->SetPosition(120.0f - fGlobalPosOffset, 435.0f);
	// FLOOR
	pObjects[1]->SetPosition(940.0f - fGlobalPosOffset, 310.0f);
	// LADDER
	pObjects[2]->SetPosition(455.0f - fGlobalPosOffset, 490.0f);
	pObjects[3]->SetPosition(1255.0f - fGlobalPosOffset, 490.0f);
}

void TestScene::UpdateOverlay(void)
{
	pOverlays[0]->GetSprite()->SetCutPos((int)fBgScroll.x, 0);
	pOverlays[1]->GetSprite()->SetCutPos((int)fBgScroll.x, 0);

	float fGlobalPosOffset = fBgScroll.x * TEST_SCENE_SCALE;
	pOverlays[2]->SetPosition(pObjects[1]->GetPosition().x + 120.0f, pObjects[1]->GetPosition().y - 24.0f);
}

void TestScene::Debug(void)
{
	char buf[64];
	sprintf_s(buf, "PlayerScreenPos=(%.2f, %.2f)", pPlayer->GetScreenPos().x, pPlayer->GetScreenPos().y);
	DebugFont_Draw(0.0f, 32.0f, buf);
	sprintf_s(buf, "PlayerGlobalPos=(%.2f, %.2f)", pPlayer->GetGlobalPos().x, pPlayer->GetGlobalPos().y);
	DebugFont_Draw(0.0f, 64.0f, buf);

	sprintf_s(buf, "BgScroll=(%.2f, %.2f)", fBgScroll.x, fBgScroll.y);
	DebugFont_Draw(0.0f, 96.0f, buf);
}