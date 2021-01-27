//----------------------------------------------------------------------------
// 
// Project-HEW2020 [GameScene01.h]
// ÉVÅ[Éì01
// 
// Date:   2021/01/10
// Author: AT12D187_17_é¸êi
// 
//----------------------------------------------------------------------------
#pragma once

#include <d3dx9.h>
#include "scene.h"
#include "generator_ui.h"
#include "text.h"

class GameScene01 : public GameScene
{
public:
	GameScene01();
	~GameScene01();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Debug(void);

private:
	void UpdatePlayer(void);
	void UpdateObject(void);
	void UpdateOverlay(void);
	void PlayerControl(void);

	bool bIdea;
	bool bIdeaHand;
	bool bCodeTaken[2];
	bool bBodyTaken[3];
	bool bDoorUnlockded[2];
	bool bTalking;
	bool bLCToken;	// Language chip
	bool bEndScene;

	GeneratorUI* pGeneratorUI;
	GameText* pText;
	GameText* pTextNotice;
};