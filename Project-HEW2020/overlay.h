//----------------------------------------------------------------------------
// 
// Project-HEW2020 [overlay.h]
// ��ԑO�i�w�i�j�y�ш�Ԍ�ɕ`�悷�����
// 
// Date:   2020/11/11
// Author: AT12D187_17_���i
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