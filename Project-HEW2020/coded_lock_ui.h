#pragma once

#include "overlay.h"

#define CLUI_ITEM	(8)
#define CLUI_KEY_H	(69)

class CodedLockUI
{
public:
	CodedLockUI();
	~CodedLockUI();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void OpenUI(void);
	void QuitUI(void);
	void SetPassword(int a, int b, int c);
	bool isUnlocked(void);

private:
	void ResetPos(void);
	void TryToUnlock(void);

	GameOverlay* pBgOverlay;
	GameOverlay* pLockUI[CLUI_ITEM];
	float fOffsetX[CLUI_ITEM];
	float fOffsetY[CLUI_ITEM];
	float fScale;
	bool bActive;
	bool bOpening;
	bool bQuiting;

	bool bUnlocked;
	bool bTrying;
	bool bSwitching;

	int nFrame;
	int nHSelected;
	int nInput[3];
	int nPassword[3];
	int nKeyCut[3];
};

