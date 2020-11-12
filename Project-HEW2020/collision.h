//----------------------------------------------------------------------------
// 
// Project-HEW2020 [collision.h]
// ÉRÉäÉWÉáÉìêßå‰
// 
// Date:   2020/11/12
// Author: AT12D187_17_é¸êi
// 
//----------------------------------------------------------------------------
#pragma once

#include <d3dx9.h>

class Collision
{
public:
	Collision();
	~Collision();

	void SetPosition(float, float);
	D3DXVECTOR2 GetPosition(void);

	void SetSize(float, float);
	float GetWidth(void);
	float GetHalfWidth(void);
	float GetHeight(void);
	float GetHalfHeight(void);
	void DebugDraw(void);

private:
	D3DXVECTOR2 centerPos;
	float width, height;
};