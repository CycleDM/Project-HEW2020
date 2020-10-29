//----------------------------------------------------------------------------
// 
// Project-HEW2020 [player.cpp]
// �v���C���[���䃂�W���[��
// 
// Date:   2020/10/28
// Author: AT12D187_17_���i
// 
//----------------------------------------------------------------------------
#include "config.h"
#include "player.h"
#include "sprite.h"

//-----------------------------------------------------------------------------
// �萔
//-----------------------------------------------------------------------------
#define PLAYER_WIDTH	(256.0f)
#define PLAYER_HEIGHT	(256.0f)

//-----------------------------------------------------------------------------
// �O���[�o���ϐ��錾
//-----------------------------------------------------------------------------
static Sprite* g_pSpritePlayer = NULL;
static float g_fRotation = 0.0f;

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
	pos = D3DXVECTOR2(64.0f, (float)SCREEN_HEIGHT - 256.0f);
	dirc = D3DXVECTOR2(0.0f, 9.8f);
	speed = 4.0f;
	velocity = 10.0f;
	hp = 3;
	score = 0;
	bJumping = false;

	g_fRotation = 0.0f;

	g_pSpritePlayer = new SpriteNormal;
	g_pSpritePlayer->LoadTexture(TEXTURE_PLAYER);
	g_pSpritePlayer->SetDrawPos(pos.x, pos.y);
	g_pSpritePlayer->SetCutPos(0, 0);
	//g_pSpritePlayer->SetPolygonSize(PLAYER_WIDTH, PLAYER_HEIGHT);
}

void GamePlayer::Uninit(void)
{
	delete g_pSpritePlayer;
	g_pSpritePlayer = NULL;
}

void GamePlayer::Update(void)
{
	// �e�N�X�`���̍��W���v���C���[�̍��W�ɍX�V
	g_pSpritePlayer->SetDrawPos(pos.x, pos.y);
	// �i�s�����𒷂��P�ɂ���
	//D3DXVec2Normalize(&dirc, &dirc);
	// �v���C���[���W�̍X�V�i�ړ����������x�j
	pos.x += dirc.x * speed;
	speed *= 0.85f;
	if (dirc.y < 9.8f) dirc.y += 0.98f;
	if (dirc.y > 9.8f) dirc.y = 9.8f;
	pos.y += dirc.y;
	// �v���C���[���W�̏C��
	if (pos.x <= 0.0f)
	{
		this->SetPosition(0.0f, pos.y);
	}
	if (SCREEN_WIDTH <= pos.x + g_pSpritePlayer->GetPolygonSize().x)
	{
		this->SetPosition(SCREEN_WIDTH - g_pSpritePlayer->GetPolygonSize().x, pos.y);
	}
	if (pos.y <= 0.0f)
	{
		this->SetPosition(pos.x, 0.0f);
	}
	if (SCREEN_HEIGHT <= pos.y + g_pSpritePlayer->GetPolygonSize().y)
	{
		this->SetPosition(pos.x, SCREEN_HEIGHT - g_pSpritePlayer->GetPolygonSize().y);
		// �n�ʂɖ߂�����W�����v���̏�Ԃ����
		bJumping = false;
	}
}

void GamePlayer::Draw(void)
{
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

int GamePlayer::GetHealth(void)
{
	return this->hp;
}

int GamePlayer::GetScore(void)
{
	return this->score;
}

void GamePlayer::MoveLeft(void)
{
	dirc.x = -1.0f;
	speed = velocity;
}

void GamePlayer::MoveRight(void)
{
	dirc.x = 1.0f;
	speed = velocity;
}

void GamePlayer::SetJump(void)
{
	if (!bJumping)
	{
		// ������̑��x��������
		dirc.y = -15.0f;
		// �W�����v���̏�Ԃɐݒ�i���d�W�����v�h�~�j
		bJumping = true;
	}
}