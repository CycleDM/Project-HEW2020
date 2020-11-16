//----------------------------------------------------------------------------
// 
// Project-HEW2020 [player.cpp]
// �v���C���[���䃂�W���[��
// 
// Date:   2020/10/28
// Author: AT12D187_17_���i
// 
//----------------------------------------------------------------------------
#include <cmath>
#include "config.h"
#include "player.h"
#include "game.h"
#include "scene.h"

//-----------------------------------------------------------------------------
// �萔
//-----------------------------------------------------------------------------
// �v���C���[�̃e�N�X�`���̃T�C�Y�i�t���[������j
#define PLAYER_TEXTURE_CUT_WIDTH	(64)
#define PLAYER_TEXTURE_CUT_HEIGHT	(64)
// �`��T�C�Y
#define PLAYER_DRAW_WIDTH	((float)PLAYER_TEXTURE_CUT_WIDTH * GameScene::GetGlobalScaling())
#define PLAYER_DRAW_HEIGHT	((float)PLAYER_TEXTURE_CUT_HEIGHT * GameScene::GetGlobalScaling())
// ���ۂ̃T�C�Y�i�R���W�����T�C�Y�j
#define PLAYER_WIDTH		(((float)PLAYER_TEXTURE_CUT_WIDTH - 32.0f) * GameScene::GetGlobalScaling())
#define PLAYER_HEIGHT		(((float)PLAYER_TEXTURE_CUT_HEIGHT - 0.0f) * GameScene::GetGlobalScaling())

//-----------------------------------------------------------------------------
// �O���[�o���ϐ��錾
//-----------------------------------------------------------------------------
static Sprite* pActiveSprite = NULL;	// �g�p���̃X�v���C�g�̃|�C���^�[

GamePlayer::GamePlayer()
{
	this->Init();
}
GamePlayer::~GamePlayer()
{
	this->Uninit();
}

void GamePlayer::Init(void)
{
	screenPos = globalPos = D3DXVECTOR2(64.0f, (float)SCREEN_HEIGHT);
	dirc = D3DXVECTOR2(0.0f, GAME_GRAVITY);
	speed = 0.0f;
	velocity = 6.0f;

	bMoving = false;
	bJumping = false;
	bClimbingUp = false;
	bOnFloor = false;

	// �v���C���[�̃e�N�X�`��(Sprite)���쐬
	pSprite = new SpriteNormal[2];

	pSprite->LoadTexture(TEXTURE_PLAYER);
	pSprite->SetDrawPos(screenPos.x - PLAYER_DRAW_WIDTH / 2, screenPos.y - PLAYER_DRAW_HEIGHT / 2);
	pSprite->SetCutPos(0, 0);
	pSprite->SetCutRange(PLAYER_TEXTURE_CUT_WIDTH, PLAYER_TEXTURE_CUT_HEIGHT);
	pSprite->SetPolygonSize(PLAYER_DRAW_WIDTH, PLAYER_DRAW_HEIGHT);

	(pSprite + 1)->LoadTexture(TEXTURE_PLAYER_CLIMBING);
	(pSprite + 1)->SetDrawPos(screenPos.x - PLAYER_DRAW_WIDTH / 2, screenPos.y - PLAYER_DRAW_HEIGHT / 2);
	(pSprite + 1)->SetCutPos(0, 0);
	(pSprite + 1)->SetCutRange(PLAYER_TEXTURE_CUT_WIDTH, PLAYER_TEXTURE_CUT_HEIGHT);
	(pSprite + 1)->SetPolygonSize(PLAYER_DRAW_WIDTH, PLAYER_DRAW_HEIGHT);

	pActiveSprite = pSprite;

	/*----------�����R�[�h-------------------------------------------------------------------------*/
	Sprite* test = NULL;
	test = new SpriteNormal[2];
	test->LoadTexture(TEXTURE_PLAYER);
	test->SetDrawPos(screenPos.x - PLAYER_DRAW_WIDTH / 2, screenPos.y - PLAYER_DRAW_HEIGHT / 2);
	test->SetCutPos(0, 0);
	test->SetCutRange(PLAYER_TEXTURE_CUT_WIDTH, PLAYER_TEXTURE_CUT_HEIGHT);
	test->SetPolygonSize(PLAYER_DRAW_WIDTH, PLAYER_DRAW_HEIGHT);
	
	(test+1)->LoadTexture(TEXTURE_PLAYER);
	(test+1)->SetDrawPos(screenPos.x - PLAYER_DRAW_WIDTH / 2, screenPos.y - PLAYER_DRAW_HEIGHT / 2);
	(test+1)->SetCutPos(0, 0);
	(test+1)->SetCutRange(PLAYER_TEXTURE_CUT_WIDTH, PLAYER_TEXTURE_CUT_HEIGHT);
	(test+1)->SetPolygonSize(PLAYER_DRAW_WIDTH, PLAYER_DRAW_HEIGHT);
	
	delete[] test;
	test = NULL;
	/*----------�����R�[�h-------------------------------------------------------------------------*/

	// �R���W�������쐬
	pCollision = new Collision;
	pCollision->SetSize(PLAYER_WIDTH, PLAYER_HEIGHT);
	pCollision->SetPosition(globalPos.x, globalPos.y);

	// �A�j���[�V��������p�̃C���X�^���X���쐬
	pAnimator = new Animator;
	pAnimator->Init(pSprite, 4, 2, 8);
}

void GamePlayer::Uninit(void)
{
	// ���������
	delete[] pSprite;
	pSprite = NULL;

	delete pCollision;
	pCollision = NULL;

	delete pAnimator;
	pAnimator = NULL;
}

void GamePlayer::Update(void)
{
	// �A�j���[�V����
	if (isMoving())
	{
		pActiveSprite = pSprite;
		pAnimator->Init(pSprite, 4, 2, 8);
		pAnimator->Play();
	}
	else if (isClimbing())
	{
		pActiveSprite = pSprite + 1;
		pAnimator->Init(pActiveSprite, 5, 5, 5);
		pAnimator->Play();
	}
	else
	{
		pActiveSprite = pSprite;
		pAnimator->Init(pSprite);
	}

	// �v���C���[���W�̍X�V�i�ړ����������x�j
	globalPos.x += dirc.x * speed;
	// ���x�̌���
	speed *= 0.8f;
	if (speed < 0.3f)
	{
		speed = 0.0f;
		bMoving = false;
	}

	// �P���ȏd�̓V�X�e��
	if (dirc.y < GAME_GRAVITY && !isClimbing()) dirc.y += GAME_GRAVITY;
	if (dirc.y > GAME_GRAVITY) dirc.y = GAME_GRAVITY;
	globalPos.y += dirc.y;

	// �R���W�����̍��W�ƃv���C���[���W�̓���
	pCollision->SetPosition(globalPos.x, globalPos.y);
}

void GamePlayer::Draw(void)
{
	// �e�N�X�`���̍��W���v���C���[�̃X�N���[�����W�ɍX�V
	pActiveSprite->SetDrawPos(screenPos.x - PLAYER_DRAW_WIDTH / 2, screenPos.y - PLAYER_DRAW_HEIGHT / 2);

	pActiveSprite->Draw();
}

void GamePlayer::SetScreenPos(float x, float y)
{
	this->screenPos.x = x;
	this->screenPos.y = y;
}

void GamePlayer::SetGlobalPos(float x, float y)
{
	this->globalPos.x = x;
	this->globalPos.y = y;
}

D3DXVECTOR2 GamePlayer::GetScreenPos(void)
{
	return this->screenPos;
}

D3DXVECTOR2 GamePlayer::GetGlobalPos(void)
{
	return this->globalPos;
}

float GamePlayer::GetPolygonWidth(void)
{
	return pSprite->GetPolygonWidth();
}

float GamePlayer::GetPolygonHeight(void)
{
	return pSprite->GetPolygonHeight();
}

Collision* GamePlayer::GetCollision(void)
{
	return this->pCollision;
}

float GamePlayer::GetSpeed(void)
{
	return this->speed;
}

D3DXVECTOR2 GamePlayer::GetDirection(void)
{
	return this->dirc;
}

bool GamePlayer::isMoving(void)
{
	return this->bMoving;
}

void GamePlayer::isMoving(bool bState) 
{
	bMoving = bState;
}

bool GamePlayer::isClimbing(void)
{
	return bClimbingUp ? true : bClimbingDown;
}

void GamePlayer::isClimbing(bool bState)
{
	if (bState) return;
	
	bClimbingUp = bClimbingDown = bState;
}

bool GamePlayer::isOnFloor(void)
{
	return bOnFloor;
}

void GamePlayer::isOnFloor(bool bState)
{
	bOnFloor = bState;
}

void GamePlayer::MoveLeft(void)
{
	bMoving = true;
	dirc.x = -1.0f;
	speed = velocity;
	pSprite->SetHorizontalFlip(true);
}

void GamePlayer::MoveRight(void)
{
	bMoving = true;
	dirc.x = 1.0f;
	speed = velocity;
	pSprite->SetHorizontalFlip(false);
}

void GamePlayer::ClimbUp(void)
{
	bClimbingUp = true;
	dirc.y = -2.0f;
}

void GamePlayer::ClimbDown(void)
{
	bClimbingDown = true;
	dirc.y = 4.0f;
}

void GamePlayer::Jump(void)
{
	if (!bJumping)
	{
		// ������̑��x��������
		dirc.y = -15.0f;
		// �W�����v���̏�Ԃɐݒ�i���d�W�����v�h�~�j
		bJumping = true;
	}
}