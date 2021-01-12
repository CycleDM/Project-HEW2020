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
};