//----------------------------------------------------------------------------
// 
// Project-HEW2020 [overlay.h]
// ˆê”Ô‘Oi”wŒij‹y‚Ñˆê”ÔŒã‚É•`‰æ‚·‚é‚à‚Ì
// 
// Date:   2020/11/11
// Author: AT12D187_17_üi
// 
//----------------------------------------------------------------------------
#pragma once

#include "object.h"

class GameOverlay : public Object
{
public:
	GameOverlay();
	GameOverlay(const char* pFileName);
	~GameOverlay();

	void LoadTexture(const char* pFileName);
};