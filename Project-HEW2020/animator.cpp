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
	bFlip = false;

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

void Animator::Preset(int nMaxCntX, int nMaxCntY, int nInterval, bool bFlip)
{
	this->nMaxCntX = nMaxCntX;
	this->nMaxCntY = nMaxCntY;
	this->nInterval = nInterval;
	this->bFlip = bFlip;
	if (bFlip)
	{
		this->nAnimationCnt = nMaxCntX * nMaxCntY - 1;
	}
}

void Animator::Reset(Sprite* pSprite)
{
	if (NULL == pSprite) return;
	pSprite->SetCutPos(originalData[0], originalData[1]);

	nFrame = 0;
	nAnimationCnt = 0;
	Preset(0, 0, 0);
	bOncePlayed = false;
	if (bFlip)
	{
		this->nAnimationCnt = nMaxCntX * nMaxCntY - 1;
	}
}

void Animator::Play(Sprite* pSprite)
{
	nFrame++;
	// no flip
	do
	{
		if (bFlip) break;
		if (nFrame >= nInterval)
		{
			nAnimationCnt++;
			nFrame = 0;
		}
		if (nAnimationCnt > nMaxCntX * nMaxCntY - 1)
		{
			nAnimationCnt = 0;
		}
	} while (0);

	// flip
	do
	{
		if (!bFlip) break;
		if (nFrame >= nInterval)
		{
			nAnimationCnt--;
			nFrame = 0;
		}
		if (nAnimationCnt < 0)
		{
			nAnimationCnt = nMaxCntX * nMaxCntY - 1;
		}
	} while (0);
	
	pSprite->SetCutPos(pSprite->GetCutWidth() * (nAnimationCnt % nMaxCntX), pSprite->GetCutHeight() * (nAnimationCnt / nMaxCntX));
}

void Animator::PlayOnce(Sprite* pSprite)
{
	if (bOncePlayed) return;

	nFrame++;
	// no flip
	do
	{
		if (bFlip) break;
		if (nFrame >= nInterval)
		{
			nAnimationCnt++;
			nFrame = 0;
		}
		if (nAnimationCnt > nMaxCntX * nMaxCntY - 1)
		{
			//nAnimationCnt = 0;
			bOncePlayed = true;
		}
	} while (0);
	// flip
	do
	{
		if (!bFlip) break;
		if (nFrame >= nInterval)
		{
			nAnimationCnt--;
			nFrame = 0;
		}
		if (nAnimationCnt < 0)
		{
			//nAnimationCnt = nMaxCntX * nMaxCntY - 1;
			bOncePlayed = true;
		}
	} while (0);
	
	if (bOncePlayed) return;
	pSprite->SetCutPos(pSprite->GetCutWidth() * (nAnimationCnt % nMaxCntX), pSprite->GetCutHeight() * (nAnimationCnt / nMaxCntX));
}

void Animator::Pause(Sprite* pSprite)
{
	if (NULL == pSprite) return;
	pSprite->SetCutPos(pSprite->GetCutWidth() * (nAnimationCnt % nMaxCntX), pSprite->GetCutHeight() * (nAnimationCnt / nMaxCntX));
}