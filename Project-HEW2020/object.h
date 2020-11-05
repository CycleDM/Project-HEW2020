//----------------------------------------------------------------------------
// 
// Project-HEW2020 [object.h]
// �Q�[���I�u�W�F�N�g����
// 
// Date:   2020/11/05
// Author: AT12D187_17_���i
// 
//----------------------------------------------------------------------------
#pragma once

#include <d3dx9.h>
#include "sprite.h"

class GameObject
{
public:
	enum OType
	{
		NONE,
		FLOOR,
		LADDER,
		KEY,
		DOOR,
		BED,
		MAX
	};

	GameObject()
	{
		this->Init(NONE);
	}
	GameObject(OType type)
	{
		this->Init(type);
	}
	~GameObject()
	{
		this->Uninit();
	}

	virtual void Init(OType type);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	void SetPosition(float, float);
	D3DXVECTOR2 GetPosition(void);
	float GetPolygonWidth(void);
	float GetPolygonHeight(void);
	void SetType(OType);
	GameObject::OType GetType(void);

private:
	OType type;
	D3DXVECTOR2 pos;	// ���W
	Sprite* pSprite;
	float dw, dh;
};