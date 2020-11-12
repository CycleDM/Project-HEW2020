//----------------------------------------------------------------------------
// 
// Project-HEW2020 [collision.cpp]
// コリジョン制御・基本クラス
// 
// Date:   2020/11/12
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#include "collision.h"

Collision::Collision()
{
	centerPos.x = 0.0f;
	centerPos.y = 0.0f;
	width = 0.0f;
	height = 0.0f;
}

Collision::~Collision()
{

}

void Collision::SetPosition(float x, float y)
{
	centerPos.x = x;
	centerPos.y = y;
}

D3DXVECTOR2 Collision::GetPosition(void)
{
	return centerPos;
}

void Collision::SetSize(float width, float height)
{
	this->width = width;
	this->height = height;
}

float Collision::GetWidth(void)
{
	return width;
}

float Collision::GetHalfWidth(void)
{
	return width / 2;
}

float Collision::GetHeight(void)
{
	return height;
}

float Collision::GetHalfHeight(void)
{
	return height / 2;
}

void Collision::DebugDraw(void)
{

}