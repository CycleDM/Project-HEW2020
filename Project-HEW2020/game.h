//----------------------------------------------------------------------------
// 
// Project-HEW2020 [game.h]
// �Q�[�����䃂�W���[��
// 
// Date:   2020/10/28
// Author: AT12D187_17_���i
// 
//----------------------------------------------------------------------------
#pragma once

#include "scene.h"

class Game
{
public:
	static void Init(void);
	static void Update(void);
	static void Draw(void);
	static void Uninit(void);
	static bool DebugMode(void);

private:
	static GameScene* pScene;
	static GameScene* pActiveScene;
	static bool bDebugMode;
};