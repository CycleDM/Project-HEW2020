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
	virtual ~Animator();

	// アニメーションを再生する
	virtual void Play(Sprite* pSprite);
	// アニメーションを再生する（一回だけ）
	virtual void PlayOnce(Sprite* pSprite);
	// アニメーションを一時的に中止する
	virtual void Pause(Sprite* pSprite);
	// 初期化
	virtual void Init(Sprite* pSprite = NULL);
	// アニメーターの各種パラメータを代入する
	// 引数:
	//	nMaxCntX	... テクスチャの切り取りXの最大数
	//	nMaxCntY	... テクスチャの切り取りYの最大数
	//	nInterval	... テクスチャ切り替えの間隔（フレーム）
	virtual void Preset(int nMaxCntX, int nMaxCntY, int nInterval);
	// テクスチャの状態を元に戻す（元データにより）
	virtual void Reset(Sprite* pSprite);

private:
	int nFrame;				// フレーム計測用の変数
	int nAnimationCnt;		// テクスチャの切り取り番号

	int nMaxCntX;			// テクスチャの切り取りXの最大値
	int nMaxCntY;			// テクスチャの切り取りYの最大値
	int nInterval;			// テクスチャ切り替えの間隔（フレーム）

	int originalData[2];	// テクスチャの元データを格納する所(tcx, tcy)

	bool bOncePlayed;		// PlayOnce()で使われるフラグ
};

