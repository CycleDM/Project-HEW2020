//----------------------------------------------------------------------------
// 
// Project-HEW2020 [animator.h]
// アニメーション制御モジュール
// 
// Date:   2020/11/12
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#pragma once

#include "sprite.h"

class Animator
{
public:
	Animator();
	~Animator();

	// アニメーションを再生する
	void Play();
	// 初期化
	void Init(Sprite* pSprite = NULL);
	// 初期化・指定した値を代入する
	// 引数:
	//	pSprite		... 操作されるスプライト
	//	nMaxCntX	... テクスチャの切り取りXの最大値
	//	nMaxCntY	... テクスチャの切り取りYの最大値
	//	nInterval	... テクスチャ切り替えの間隔（フレーム）
	void Init(Sprite* pSprite, int nMaxCntX, int nMaxCntY, int nInterval);

private:
	Sprite* pSprite;	// アニメーションとして使われるスプライト
	int nFrame;			// フレーム計測用の変数
	int nAnimationCnt;	// テクスチャの切り取り番号

	int nMaxCntX;		// テクスチャの切り取りXの最大値
	int nMaxCntY;		// テクスチャの切り取りYの最大値
	int nInterval;		// テクスチャ切り替えの間隔（フレーム）
};

