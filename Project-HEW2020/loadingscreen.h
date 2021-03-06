//----------------------------------------------------------------------------
// 
// Project-HEW2020 [loadingscreen.h]
// ロード中の画面
// 
// Date:   2021/01/26
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#pragma once

#include "sprite.h"
#include "animator.h"

class LoadingScreen
{
public:
	LoadingScreen();
	~LoadingScreen();

	void Update(void);
	void Draw(void);
	void Show(void);
	void Hide(void);

private:
	Sprite* pSprite;
	Animator* pAnimator;
	bool isHidden;
};