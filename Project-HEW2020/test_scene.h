//----------------------------------------------------------------------------
// 
// Project-HEW2020 [test_scene.h]
// ƒV[ƒ“0
// 
// Date:   2020/10/28
// Author: AT12D187_17_Žüi
// 
//----------------------------------------------------------------------------
#pragma once

#include "sprite.h"
#include "object.h"
#include "player.h"

class TestScene
{
public:
	TestScene()
	{
		this->Init();
	}
	~TestScene()
	{
		this->Uninit();
	}

	void Init(void);
	void Update(void);
	void Draw(void);
	void Uninit(void);
	GameObject* GetNearestLadder(void);
	GameObject* GetNearestFloor(void);
	GamePlayer* GetPlayer(void);
};