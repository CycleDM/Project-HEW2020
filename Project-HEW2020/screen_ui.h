//----------------------------------------------------------------------------
// 
// Project-HEW2020 [screen.h]
// ÉVÅ[Éì01àÍäKñ⁄ÇÃì‰
// 
// Date:   2021/01/28
// Author: AT12D187_17_é¸êi
// 
//----------------------------------------------------------------------------
#pragma once
#include "overlay.h"

class ScreenUI
{
public:
	ScreenUI();
	~ScreenUI();

	void Init(void);
	void Uninit(void);
	void Update(bool bPower, bool bColor);
	void Draw(void);

	void OpenUI(void);
	void QuitUI(void);

private:
	bool bActive;
	GameOverlay* pBgOverlay;
	GameOverlay* pBaseUI;
};