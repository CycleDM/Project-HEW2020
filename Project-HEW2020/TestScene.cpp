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
#include "game.h"

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
	SetGlobalScaling(3.3333333333f);
	SetDarkness(false);
	//SetDarkness(true);

	fBgScroll = D3DXVECTOR2(0.0f, 0.0f);
	fBgScrollMax = D3DXVECTOR2(264.0f, 0.0f);
	fGroundHeight = 64.0f;

	// �v���C���[�C���X�^���X
	pPlayer = new GamePlayer;
	// �v���C���[�̍��W
	pPlayer->SetGlobalPos(64.0f, (float)SCREEN_HEIGHT - fGroundHeight);

	// �w�i
	pOverlays[0] = new GameOverlay(TEXTURE_BG);
	pOverlays[0]->SetScreenPos((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2);
	pOverlays[0]->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	pOverlays[0]->GetSprite()->SetCutPos(0, 0);
	pOverlays[0]->GetSprite()->SetCutRange(384, 216);
	// �h�A�t���[���iOverlay�j
	pOverlays[1] = new GameOverlay(TEXTURE_BG_OVERLAY);
	pOverlays[1]->SetScreenPos((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2);
	pOverlays[1]->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	pOverlays[1]->GetSprite()->SetCutPos(0, 0);
	pOverlays[1]->GetSprite()->SetCutRange(384, 216);
	pOverlays[1]->GetSprite()->SetColor(D3DCOLOR_RGBA(255, 255, 255, 230));
	// �Q�[���I�u�W�F�N�g�E�C���X�^���X(s)
	// BED
	pObjects[0] = new GameObject(GameObject::OBJ_BED);
	pObjects[0]->SetGlobalPos(120.0f, 435.0f);
	// FLOOR
	pObjects[1] = new GameObject(GameObject::OBJ_FLOOR);
	pObjects[1]->SetGlobalPos(940.0f, 310.0f);
	// LADDER 1
	pObjects[2] = new GameObject(GameObject::OBJ_LADDER);
	pObjects[2]->SetGlobalPos(455.0f, 490.0f);
	// LADDER 2
	pObjects[3] = new GameObject(GameObject::OBJ_LADDER);
	pObjects[3]->SetGlobalPos(1255.0f, 490.0f);


	// �I�u�W�F�N�g�̃T�C�Y��C�ɏ�����
	for (GameObject* obj : pObjects)
	{
		if (NULL == obj) continue;
		obj->SetSize(obj->GetWidth() * fGlobalScaling, obj->GetHeight() * fGlobalScaling);
	}

	// FLOOR Overlay
	pOverlays[2] = new GameOverlay(TEXTURE_OBJ_FLOOR_OVERLAY);
	pOverlays[2]->SetSize(pOverlays[2]->GetWidth() * fGlobalScaling, pOverlays[2]->GetHeight() * fGlobalScaling);

	// ������͈� Overlay
	pOverlays[3] = new GameOverlay(TEXTURE_OVERLAY_RANGE);
	pOverlays[3]->SetScreenPos(pPlayer->GetScreenPos().x, pPlayer->GetScreenPos().y + pPlayer->GetCollision()->GetHalfHeight());
	pOverlays[3]->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	pOverlays[3]->GetSprite()->SetCutPos(640, 360);
	pOverlays[3]->GetSprite()->SetCutRange(SCREEN_WIDTH, SCREEN_HEIGHT);
	pOverlays[3]->SetSize(pOverlays[3]->GetWidth() * fGlobalScaling * 4.0f, pOverlays[3]->GetHeight() * fGlobalScaling * 4.0f);

	/*----------�����R�[�h-------------------------------------------------------------------------*/
	GameObject* test = NULL;
	test = new GameObject[2];
	test[0].Register(GameObject::OBJ_BED);
	test[0].SetGlobalPos(120.0f, 435.0f);
	test[0].SetSize(test[0].GetWidth() * fGlobalScaling, test[0].GetHeight() * fGlobalScaling);
	test[1].Register(GameObject::OBJ_LADDER);
	test[1].SetGlobalPos(120.0f, 435.0f);
	test[1].SetSize(test[1].GetWidth() * fGlobalScaling, test[1].GetHeight() * fGlobalScaling);

	delete[] test;
	test = NULL;
	/*----------�����R�[�h-------------------------------------------------------------------------*/
}

void TestScene::Uninit(void)
{
	// ���������
	delete pPlayer;
	pPlayer = NULL;
	for (GameObject* p : pObjects)
	{
		if (NULL == p) continue;
		delete p;
		p = NULL;
	}
	for (GameOverlay* p : pOverlays)
	{
		if (NULL == p) continue;
		delete p;
		p = NULL;
	}
}

void TestScene::Update(void)
{
	// �w�i�̃X�N���[��
	fBgScroll.x = pPlayer->GetGlobalPos().x - (float)SCREEN_WIDTH / 2;
	fBgScroll.x /= fGlobalScaling;

	// �X�N���[���C��
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
	if (isDarkness())
		pOverlays[3]->Draw();

	// �f�o�b�O�����̕\��
	if (Game::DebugMode()) this->Debug();
}

// �v���C���[�̍X�V����
void TestScene::UpdatePlayer(void)
{
	// �v���C���[�̃R���W�������擾
	Collision* collision = pPlayer->GetCollision();
	// �X�N���[�����W�ƃ��[���h���W�̓���
	float offsetX = fBgScroll.x * fGlobalScaling;
	float offsetY = 0.0f;
	// �w�i�̓X�N���[�����Ă��Ȃ���� -> �X�N���[�����W�͕ύX�ł���
	// �w�i�̓X�N���[�����Ă�����	-> �X�N���[�����W�͕ύX�ł��Ȃ�
	// �O���[�o�����W�i���E���W�j�͂�������ɕς��
	if (fBgScroll.x <= 0.0f || fBgScroll.x >= fBgScrollMax.x)
		pPlayer->SetScreenPos(pPlayer->GetGlobalPos().x - offsetX, pPlayer->GetGlobalPos().y);
	else
		pPlayer->SetScreenPos((float)SCREEN_WIDTH / 2, pPlayer->GetGlobalPos().y);

	// �v���C���[�͉�ʂ��o�邱�Ƃ�h�~
	float minimumX = 0.0f + collision->GetHalfWidth();
	float maximumX = (float)SCREEN_WIDTH - collision->GetHalfWidth() + offsetX;
	float minimumY = 0.0f + collision->GetHalfHeight();
	float maximumY = (float)SCREEN_HEIGHT - fGroundHeight - collision->GetHalfHeight();

	//
	do
	{
		// ��ԋ߂�FLOOR���擾
		GameObject* floor = GetNearestObject(collision->GetPosition(), GameObject::OBJ_FLOOR);
		// �擾�o���Ȃ������ꍇ�Abreak;
		if (NULL == floor) break;
		
		// �v���C���[�����Ɉړ�����ꍇ�Abreak;
		if (pPlayer->isClimbing() && pPlayer->GetDirection().y > 0.0f) break;

		// floor�̏㋫�E(Collision)
		float fTop = floor->GetCollision()->GetPosition().y - floor->GetCollision()->GetHalfHeight();
		// �v���C���[�̒��S���Wy > floor�̒��S���Wy ... break
		if (pPlayer->GetGlobalPos().y > floor->GetCollision()->GetPosition().y) break;

		maximumY = fTop - pPlayer->GetCollision()->GetHalfHeight();
		minimumX = floor->GetGlobalPos().x - floor->GetCollision()->GetHalfWidth() + pPlayer->GetCollision()->GetHalfWidth();
		maximumX = floor->GetGlobalPos().x + floor->GetCollision()->GetHalfWidth() - pPlayer->GetCollision()->GetHalfWidth();
	} while (0);
	
	// ����
	if (collision->GetPosition().x < minimumX)
		pPlayer->SetGlobalPos(minimumX, pPlayer->GetGlobalPos().y);
	// �E��
	if (collision->GetPosition().x > maximumX)
		pPlayer->SetGlobalPos(maximumX, pPlayer->GetGlobalPos().y);
	// �㋫�E
	if (collision->GetPosition().y < minimumY)
		pPlayer->SetGlobalPos(pPlayer->GetGlobalPos().x, minimumY);
	// �����E
	if (collision->GetPosition().y > maximumY)
		pPlayer->SetGlobalPos(pPlayer->GetGlobalPos().x, maximumY);

	// �����蔻��(�e�X�g�p)
	do
	{
		GameObject* obj = GetNearestObject(collision->GetPosition(), GameObject::OBJ_LADDER);
		if (NULL == obj) break;
		if (obj->GetGlobalPos().x - collision->GetPosition().x < obj->GetCollision()->GetHalfWidth() + collision->GetHalfWidth())
		{
			//pPlayer->SetGlobalPos(obj->GetGlobalPos().x - obj->GetCollision()->GetHalfWidth() - collision->GetHalfWidth(), pPlayer->GetGlobalPos().y);
		}
	} while (0);

	// �v���C���[�C���X�^���X���X�V
	pPlayer->Update();
}

// �I�u�W�F�N�g�̍X�V����
void TestScene::UpdateObject(void)
{
	float fGlobalPosOffset = fBgScroll.x * fGlobalScaling;
	for (GameObject* object : pObjects)
	{
		if (NULL == object) continue;
		object->SetScreenPos(object->GetGlobalPos().x - fGlobalPosOffset, object->GetGlobalPos().y);
		object->Update();
	}
}

// �I�[�o�[���C�̍X�V����
void TestScene::UpdateOverlay(void)
{
	pOverlays[0]->GetSprite()->SetCutPos((int)fBgScroll.x, (int)fBgScroll.y);
	pOverlays[1]->GetSprite()->SetCutPos((int)fBgScroll.x, (int)fBgScroll.y);

	float fGlobalPosOffset = fBgScroll.x * fGlobalScaling;
	pOverlays[2]->SetScreenPos(pObjects[1]->GetScreenPos().x + 120.0f, pObjects[1]->GetScreenPos().y - 24.0f);
	pOverlays[3]->SetScreenPos(pPlayer->GetScreenPos().x, pPlayer->GetScreenPos().y + pPlayer->GetCollision()->GetHalfHeight() + 32.0f);


	// ���������UI�̍X�V����
	do
	{
		// ...
		// ...
		// ...
	} while (0);
}

// �f�o�b�O�����̕\��
void TestScene::Debug(void)
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

	y += 64.0f;
	sprintf_s(buf, "[ObjectInfo]");
	DebugFont::Draw(0.0f, y, buf);
	y += 32.0f;
	sprintf_s(buf, ">FLOOR S(%.2f, %.2f) G(%.2f, %.2f) CollisionSize(%.2f, %.2f)",
		pObjects[1]->GetScreenPos().x, pObjects[1]->GetScreenPos().y,
		pObjects[1]->GetGlobalPos().x, pObjects[1]->GetGlobalPos().y,
		pObjects[1]->GetCollision()->GetWidth(), pObjects[1]->GetCollision()->GetHeight());
	DebugFont::Draw(0.0f, y, buf);
	y += 32.0f;
	sprintf_s(buf, ">LADDER1 S(%.2f, %.2f) G(%.2f, %.2f) CollisionPos(%.2f, %.2f)",
		pObjects[2]->GetScreenPos().x, pObjects[2]->GetScreenPos().y, 
		pObjects[2]->GetGlobalPos().x, pObjects[2]->GetGlobalPos().y,
		pObjects[2]->GetCollision()->GetPosition().x, pObjects[2]->GetCollision()->GetPosition().y);
	DebugFont::Draw(0.0f, y, buf);
	y += 32.0f;
	sprintf_s(buf, ">LADDER2 S(%.2f, %.2f) G(%.2f, %.2f) CollisionSize(%.2f, %.2f)",
		pObjects[3]->GetScreenPos().x, pObjects[3]->GetScreenPos().y,
		pObjects[3]->GetGlobalPos().x, pObjects[3]->GetGlobalPos().y,
		pObjects[3]->GetCollision()->GetWidth(), pObjects[2]->GetCollision()->GetHeight());
	DebugFont::Draw(0.0f, y, buf);
}