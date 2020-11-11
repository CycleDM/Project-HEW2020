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
#include "sprite.h"
#include "game.h"

//-----------------------------------------------------------------------------
// �萔
//-----------------------------------------------------------------------------
#define PLAYER_WIDTH	(64.0f * 3.3f)
#define PLAYER_HEIGHT	(64.0f * 3.3f)

//-----------------------------------------------------------------------------
// �O���[�o���ϐ��錾
//-----------------------------------------------------------------------------
static Sprite* g_pSpritePlayer = NULL;
static int g_nMoveFrame = 0;
static int g_nMoveAnimeCnt = 0;

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
	pos = D3DXVECTOR2(64.0f, (float)SCREEN_HEIGHT);
	dirc = D3DXVECTOR2(0.0f, 9.8f);
	speed = 0.0f;
	velocity = 5.0f;
	isMoving = false;
	isJumping = false;
	isClimbingUp = false;

	g_nMoveFrame = 0;
	g_nMoveAnimeCnt = 0;

	g_pSpritePlayer = new SpriteNormal;
	g_pSpritePlayer->LoadTexture(TEXTURE_PLAYER);
	g_pSpritePlayer->SetDrawPos(pos.x - PLAYER_WIDTH / 2, pos.y - PLAYER_HEIGHT / 2);
	g_pSpritePlayer->SetCutPos(0, 0);
	g_pSpritePlayer->SetCutRange(64, 64);
	g_pSpritePlayer->SetPolygonSize(PLAYER_WIDTH, PLAYER_HEIGHT);
	//g_pSpritePlayer->SetColor(D3DCOLOR_RGBA(255, 255, 255, 100));
}

void GamePlayer::Uninit(void)
{
	delete g_pSpritePlayer;
	g_pSpritePlayer = NULL;
}

void GamePlayer::Update(void)
{
	// �i�s�����𒷂��P�ɂ���
	//D3DXVec2Normalize(&dirc, &dirc);
	// �v���C���[���W�̍X�V�i�ړ����������x�j
	pos.x += dirc.x * speed;
	speed *= 0.8f;
	if (speed < 0.3f)
	{
		speed = 0.0f;
		isMoving = false;
	}
	if (dirc.y < 9.8f && !isClimbingUp) dirc.y += 0.98f;
	if (dirc.y > 9.8f) dirc.y = 9.8f;
	pos.y += dirc.y;
	// �v���C���[���W�̏C��
	if (pos.x <= 0.0f + PLAYER_WIDTH / 2)
	{
		this->SetPosition(0.0f + PLAYER_WIDTH / 2, pos.y);
	}
	if ((float)SCREEN_WIDTH <= pos.x + PLAYER_WIDTH / 2)
	{
		this->SetPosition(SCREEN_WIDTH - PLAYER_WIDTH / 2, pos.y);
	}
	if (pos.y <= 0.0f + PLAYER_HEIGHT / 2)
	{
		this->SetPosition(pos.x, 0.0f + PLAYER_HEIGHT / 2);
	}
	if ((float)SCREEN_HEIGHT - 64.0f <= pos.y + PLAYER_HEIGHT / 2)
	{
		this->SetPosition(pos.x, (float)SCREEN_HEIGHT - 64.0f - PLAYER_HEIGHT / 2);
		// �n�ʂɖ߂�����W�����v���̏�Ԃ����
		this->isJumping = false;
		this->isClimbingUp = false;
	}

	// Animation
	if (speed > 0.0f)
	{
		g_nMoveFrame++;
		if (g_nMoveFrame >= 8)
		{
			g_nMoveAnimeCnt++;
			g_nMoveFrame = 0;
		}
		if (g_nMoveAnimeCnt > 7)
		{
			g_nMoveAnimeCnt = 0;
		}
	}
	else 
	{
		g_nMoveFrame = 0;
		g_nMoveAnimeCnt = 0;
	}
	g_pSpritePlayer->SetCutPos(64 * (g_nMoveAnimeCnt % 4), 64 * (g_nMoveAnimeCnt / 2));
}

void GamePlayer::Draw(void)
{
	// �e�N�X�`���̍��W���v���C���[�̍��W�ɍX�V
	g_pSpritePlayer->SetDrawPos(pos.x - PLAYER_WIDTH / 2, pos.y - PLAYER_HEIGHT / 2);
	g_pSpritePlayer->Draw();
}

void GamePlayer::SetPosition(float x, float y)
{
	this->pos.x = x;
	this->pos.y = y;
}

D3DXVECTOR2 GamePlayer::GetPosition(void)
{
	return this->pos;
}

float GamePlayer::GetPolygonWidth(void)
{
	return g_pSpritePlayer->GetPolygonWidth();
}

float GamePlayer::GetPolygonHeight(void)
{
	return g_pSpritePlayer->GetPolygonHeight();
}

float GamePlayer::GetSpeed(void)
{
	return this->speed;
}

D3DXVECTOR2 GamePlayer::GetDirection(void)
{
	return this->dirc;
}

bool GamePlayer::GetMovingStatus(void)
{
	return this->isMoving;
}

void GamePlayer::MoveLeft(void)
{
	isMoving = true;
	dirc.x = -1.0f;
	speed = velocity;
	g_pSpritePlayer->SetHorizontalFlip(true);
}

void GamePlayer::MoveRight(void)
{
	isMoving = true;
	dirc.x = 1.0f;
	speed = velocity;
	g_pSpritePlayer->SetHorizontalFlip(false);
}

void GamePlayer::Jump(void)
{
	if (!isJumping)
	{
		// ������̑��x��������
		dirc.y = -15.0f;
		// �W�����v���̏�Ԃɐݒ�i���d�W�����v�h�~�j
		isJumping = true;
	}
}