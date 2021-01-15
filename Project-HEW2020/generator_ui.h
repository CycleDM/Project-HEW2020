//----------------------------------------------------------------------------
// 
// Project-HEW2020 [generator_ui.h]
// ÉVÅ[Éì01àÍäKñ⁄ÇÃì‰
// 
// Date:   2021/01/15
// Author: AT12D187_17_é¸êi
// 
//----------------------------------------------------------------------------
#pragma once
#include "overlay.h"

#define GENERATOR_UI_SLOT_X		14
#define GENERATOR_UI_SLOT_Y		7
#define GENERATOR_UI_SLOT_MAX	(GENERATOR_UI_SLOT_X * GENERATOR_UI_SLOT_Y)

typedef struct GeneratorUISlot_tag
{
	int nType;
	int nRotation;
	bool bEnable;
	bool bSelected;
	bool bHighlight;
	float posX, posY;
}GeneratorUISlot;

class GeneratorUI
{
public:
	GeneratorUI();
	~GeneratorUI();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void OpenUI(void);
	void QuitUI(void);
	bool isUnlocked(void);

private:
	void TryToUnlock(void);

	GameOverlay* pBgOverlay;
	GameOverlay* pBaseUI;
	GameOverlay* pLineUI[3];
	GeneratorUISlot gUISlots[GENERATOR_UI_SLOT_MAX];
	float fScale;
	bool bActive;
	bool bUnlocked;
	static const int correctRotation[GENERATOR_UI_SLOT_MAX];
};