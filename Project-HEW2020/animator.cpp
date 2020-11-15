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

	// クラス内のpSpriteは NULL じゃなかったら、テクスチャの切り取り座標をリセットする
	if (NULL != this->pSprite)
	{
		this->pSprite->SetCutPos(0, 0);
		this->pSprite = NULL;
	}
	// 引数のpSpriteは NULL じゃなかったら、引数のスプライトを使う
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