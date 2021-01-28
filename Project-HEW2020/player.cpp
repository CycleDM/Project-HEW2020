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
#include "sound.h"

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
	currentFloor = 1;

	bWalking = false;
	bJumping = false;
	bClimbingUp = false;
	bOnLadder = false;

	bLostLeg = false;
	bLostEye = false;
	bLostHandL = false;
	bLostHandR = false;

	// �v���C���[�̃e�N�X�`��(Sprite)���쐬
	int n = 6;
	pSprite = new SpriteNormal[n];
	(pSprite + 0)->LoadTexture(TEXTURE_PLAYER);
	(pSprite + 1)->LoadTexture(TEXTURE_PLAYER_CLIMBING);
	(pSprite + 2)->LoadTexture(TEXTURE_PLAYER_CLIMBING_PAUSED);
	(pSprite + 3)->LoadTexture(TEXTURE_PLAYER_LOST_HAND1);
	(pSprite + 4)->LoadTexture(TEXTURE_PLAYER_LOST_HAND2);
	(pSprite + 5)->LoadTexture(TEXTURE_PLAYER_LOST_LEG);

	for (int i = 0; i < n; i++)
	{
		(pSprite + i)->SetDrawPos(screenPos.x - PLAYER_DRAW_WIDTH / 2, screenPos.y - PLAYER_DRAW_HEIGHT / 2);
		(pSprite + i)->SetCutPos(0, 0);
		(pSprite + i)->SetCutRange(PLAYER_TEXTURE_CUT_WIDTH, PLAYER_TEXTURE_CUT_HEIGHT);
		(pSprite + i)->SetPolygonSize(PLAYER_DRAW_WIDTH, PLAYER_DRAW_HEIGHT);
	}

	pActiveSprite = pSprite;

	// �R���W�������쐬
	pCollision = new Collision;
	pCollision->SetSize(PLAYER_WIDTH, PLAYER_HEIGHT);
	pCollision->SetPosition(globalPos.x, globalPos.y);

	// �A�j���[�V��������p�̃C���X�^���X���쐬
	pAnimator = new Animator;
	pAnimator->Init(pActiveSprite);
	pAnimator->Preset(4, 2, 8);
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
	/*----------�A�j���[�V����-------------------------------------------------------------------------*/
	if (isWalking() && !bLostHandR)
	{
		pActiveSprite = pSprite;
		pAnimator->Preset(4, 2, 8);
		pAnimator->Play(pActiveSprite);
	}
	else if (isWalking() && bLostHandR && dirc.x > 0.0f)
	{
		pActiveSprite = pSprite + 3;
		pAnimator->Preset(4, 2, 8);
		pAnimator->Play(pActiveSprite);
	}
	else if (isWalking() && bLostHandR && dirc.x < 0.0f)
	{
		pActiveSprite = pSprite + 4;
		pAnimator->Preset(4, 2, 8);
		pAnimator->Play(pActiveSprite);
	}
	else if (bClimbingUp)
	{
		pActiveSprite = pSprite + 1;
		pAnimator->Preset(5, 5, 5);
		pAnimator->Play(pActiveSprite);
	}
	else if (bClimbingDown)
	{
		pActiveSprite = pSprite + 2;
		pAnimator->Preset(1, 1, 0);
		pAnimator->Play(pActiveSprite);
	}
	else if (!isClimbing() && isOnLadder())
	{
		//pAnimator->Pause(pActiveSprite);
	}
	else if (bLostLeg)
	{
		pActiveSprite = pSprite + 5;
	}
	else if (bLostHandR && dirc.x >= 0.0f)
	{
		pActiveSprite = pSprite + 3;
		pAnimator->Reset(pActiveSprite);
	}
	else if (bLostHandR && dirc.x <= 0.0f)
	{
		pActiveSprite = pSprite + 4;
		pAnimator->Reset(pActiveSprite);
	}
	else
	{
		pActiveSprite = pSprite;
		pAnimator->Reset(pActiveSprite);
	}
	/*----------�A�j���[�V����-------------------------------------------------------------------------*/

	// x���W�̍X�V�i�ړ����������x�j
	globalPos.x += dirc.x * speed;
	// ���x�̌���
	speed *= 0.8f;
	if (speed < 0.3f)
	{
		speed = 0.0f;
		bWalking = false;
	}

	// �P���ȏd�̓V�X�e��
	if (dirc.y < GAME_GRAVITY && !isClimbing())
		dirc.y += GAME_GRAVITY;

	if (dirc.y > GAME_GRAVITY)
		dirc.y = GAME_GRAVITY;

	// ����F�v���C���[���͂����Ɏc��i�ړ����Ȃ��j
	if (!isClimbing() && isOnLadder())
	{
		dirc.y = 0.0f;
	}
	// y���W�̍X�V
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

//-----------------------------------------------------------------------------
// ���l�̐ݒ肨��ю擾
//-----------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------
// Boolean
//-----------------------------------------------------------------------------
bool GamePlayer::isWalking(void)
{
	return this->bWalking;
}

void GamePlayer::isWalking(bool bState) 
{
	bWalking = bState;
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

bool GamePlayer::isOnLadder(void)
{
	return bOnLadder;
}

void GamePlayer::isOnLadder(bool bState)
{
	bOnLadder = bState;
}

void GamePlayer::SetStatusFlag(int bLostLeg, int bLostHandL, int bLostHandR, int bLostEye)
{
	if (bLostLeg >= 0) this->bLostLeg = (bool)bLostLeg;
	if (bLostEye >= 0) this->bLostEye = (bool)bLostEye;
	if (bLostHandL >= 0) this->bLostHandL = (bool)bLostHandL;
	if (bLostHandR >= 0) this->bLostHandR = (bool)bLostHandR;
}

//-----------------------------------------------------------------------------
// �v���C���[�̓�������
//-----------------------------------------------------------------------------
void GamePlayer::MoveLeft(void)
{
	if (bLostLeg) return;
	bWalking = true;
	dirc.x = -1.0f;
	speed = velocity;
	pSprite->SetHorizontalFlip(true);
}

void GamePlayer::MoveRight(void)
{
	if (bLostLeg) return;
	bWalking = true;
	dirc.x = 1.0f;
	speed = velocity;
	pSprite->SetHorizontalFlip(false);
}

void GamePlayer::MoveUp(void)
{
	if (bLostLeg) return;
	bWalking = false;
	bClimbingUp = true;
	dirc.y = -2.0f;
}

void GamePlayer::MoveDown(void)
{
	if (bLostLeg) return;
	bWalking = false;
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

void GamePlayer::SetWalkingSpeed(float speed)
{
	velocity = speed;
}