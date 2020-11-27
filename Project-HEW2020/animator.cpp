//----------------------------------------------------------------------------
// 
// Project-HEW2020 [animator.cpp]
// アニメーション制御モジュール
// 
// Date:   2020/11/12
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------

#include "animator.h"

Animator::Animator()
{
	Init();
}

Animator::~Animator()
{
}

void Animator::Init(Sprite* pSprite)
{
	nFrame = 0;
	nAnimationCnt = 0;
	nMaxCntX = 0;
	nMaxCntY = 0;
	nInterval = 0;

	bOncePlayed = false;

	// メンバー変数のpSpriteは NULL じゃなかったら、テクスチャの切り取り座標をリセットする
	if (NULL != pSprite)
	{
		originalData[0] = pSprite->GetCutPos().x;
		originalData[1] = pSprite->GetCutPos().y;
	}
	else
	{
		originalData[0] = 0;
		originalData[1] = 0;
	}
}

void Animator::Preset(int nMaxCntX, int nMaxCntY, int nInterval)
{
	this->nMaxCntX = nMaxCntX;
	this->nMaxCntY = nMaxCntY;
	this->nInterval = nInterval;
}

void Animator::Reset(Sprite* pSprite)
{
	if (NULL == pSprite) return;
	pSprite->SetCutPos(originalData[0], originalData[1]);

	nFrame = 0;
	nAnimationCnt = 0;
	Preset(0, 0, 0);
	bOncePlayed = false;
}

void Animator::Play(Sprite* pSprite)
{
	if (NULL == pSprite) return;

	nFrame++;
	if (nFrame >= nInterval)
	{
		nAnimationCnt++;
		nFrame = 0;
	}
	if (nAnimationCnt > nMaxCntX * nMaxCntY - 1)
	{
		nAnimationCnt = 0;
	}
	pSprite->SetCutPos(pSprite->GetCutWidth() * (nAnimationCnt % nMaxCntX), pSprite->GetCutHeight() * (nAnimationCnt / nMaxCntY));
}

void Animator::PlayOnce(Sprite* pSprite)
{
	if (NULL == pSprite) return;
	if (bOncePlayed) return;

	nFrame++;
	if (nFrame >= nInterval)
	{
		nAnimationCnt++;
		nFrame = 0;
	}
	if (nAnimationCnt > nMaxCntX * nMaxCntY - 1)
	{
		nAnimationCnt = 0;
		bOncePlayed = true;
		return;
	}
	pSprite->SetCutPos(pSprite->GetCutWidth() * (nAnimationCnt % nMaxCntX), pSprite->GetCutHeight() * (nAnimationCnt / nMaxCntY));
}

void Animator::Pause(Sprite* pSprite)
{
	if (NULL == pSprite) return;
	pSprite->SetCutPos(pSprite->GetCutWidth() * (nAnimationCnt % nMaxCntX), pSprite->GetCutHeight() * (nAnimationCnt / nMaxCntY));
}