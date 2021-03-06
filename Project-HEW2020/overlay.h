//----------------------------------------------------------------------------
// 
// Project-HEW2020 [overlay.h]
// 一番前（背景）及び一番後に描画するもの
// 
// Date:   2020/11/11
// Author: AT12D187_17_周進
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