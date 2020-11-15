//----------------------------------------------------------------------------
// 
// Project-HEW2020 [animator.cpp]
// �A�j���[�V�������䃂�W���[��
// 
// Date:   2020/11/12
// Author: AT12D187_17_���i
// 
//----------------------------------------------------------------------------

#include "animator.h"

Animator::Animator()
{
	pSprite = NULL;
	Init();
}

Animator::~Animator()
{
	pSprite = NULL;
}

void Animator::Play()
{
	if (NULL == pSprite) return;

	nFrame++;
	if (nFrame >= nInterval)
	{
		nAnimationCnt++;
		nFrame = 0;
	}
	if (nAnimationCnt > nMaxCntX + nMaxCntY + 1)
	{
		nAnimationCnt = 0;
	}
	pSprite->SetCutPos(pSprite->GetCutRange().x * (nAnimationCnt % nMaxCntX), pSprite->GetCutRange().y * (nAnimationCnt / nMaxCntY));
}

void Animator::Init(Sprite* pSprite)
{
	nFrame = 0;
	nAnimationCnt = 0;
	nMaxCntX = 0;
	nMaxCntY = 0;
	nInterval = 0;

	// �N���X����pSprite�� NULL ����Ȃ�������A�e�N�X�`���̐؂�����W�����Z�b�g����
	if (NULL != this->pSprite)
	{
		this->pSprite->SetCutPos(0, 0);
		this->pSprite = NULL;
	}
	// ������pSprite�� NULL ����Ȃ�������A�����̃X�v���C�g���g��
	if (NULL != pSprite)
	{
		this->pSprite = pSprite;
	}
}

void Animator::Init(Sprite* pSprite, int nMaxCntX, int nMaxCntY, int nInterval)
{
	this->pSprite = pSprite;
	this->nMaxCntX = nMaxCntX;
	this->nMaxCntY = nMaxCntY;
	this->nInterval = nInterval;
}