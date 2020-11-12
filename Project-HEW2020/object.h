//----------------------------------------------------------------------------
// 
// Project-HEW2020 [object.h]
// ゲームオブジェクト制御
// 
// Date:   2020/11/06
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#pragma once

#include "sprite.h"

//----------------------------------------------------------------------------
// 基本クラス
//----------------------------------------------------------------------------
class Object
{
public:
	Object();
	~Object();

	void Init(void);
	void Uninit(void);
	void Draw(void);

	// オブジェクトのサイズを指定
	void SetSize(float, float);
	// オブジェクトの中心座標を指定
	void SetPosition(float, float);

	D3DXVECTOR2 GetPosition(void);
	float GetWidth(void);
	float GetHeight(void);

	Sprite* GetSprite(void);

protected:
	Sprite* pSprite;
	D3DXVECTOR2 globalPos;
	float width, height;
};

//----------------------------------------------------------------------------
// 派生クラス - GameObject
//----------------------------------------------------------------------------
class GameObject : public Object
{
public:
	enum ObjectType
	{
		NONE = -1,
		BED,
		FLOOR,
		LADDER,
		DOOR,
		KEY,
		MAX
	};
	GameObject();
	GameObject(ObjectType type);
	~GameObject();

	void Register(ObjectType type);
};