//----------------------------------------------------------------------------
// 
// Project-HEW2020 [computer_ui.h]
// ÉVÅ[Éì01ìÒäKñ⁄ÇÃì‰
// 
// Date:   2021/01/28
// Author: AT12D187_17_é¸êi
// 
//----------------------------------------------------------------------------
#pragma once
#include "overlay.h"
#include "text.h"

class ComputerUI
{
public:
	ComputerUI();
	~ComputerUI();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void OpenUI(void);
	void QuitUI(void);

	bool isUnlocked(void);
	void TryToUnlock(void);

private:
	bool bActive;
	bool bUnlocked;
	bool bSelected[12];
	int nInput[4];
	GameOverlay* pBgOverlay;
	GameOverlay* pBaseUI;
	GameOverlay* pButtonBase;
	GameOverlay* pButton;
	GameText* pText;

	static const float INIT_POS_X;
	static const float INIT_POS_Y;
	static const int CORRECT_PASS[4];
};