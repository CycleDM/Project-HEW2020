//----------------------------------------------------------------------------
// 
// Project-HEW2020 [background.h]
// �w�i���䃂�W���[��
// 
// Date:   2020/10/28
// Author: AT12D187_17_���i
// 
//----------------------------------------------------------------------------
#pragma once

#include "sprite.h"

class GameBackground
{
public:
	GameBackground();
	~GameBackground();

	void Init(void);
	void Update(void);
	void Draw(void);
	void Uninit(void);
};