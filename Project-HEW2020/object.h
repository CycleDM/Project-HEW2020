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
#include "collision.h"

//----------------------------------------------------------------------------
// 基本クラス
//----------------------------------------------------------------------------
class Object
{
public:
	Object();
	~Object();

	virtual void Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	// オブジェクトのサイズを指定
	void SetSize(float, float);
	// オブジェクトの中心座標を指定
	void SetScreenPos(float, float);
	void SetGlobalPos(float, float);

	D3DXVECTOR2 GetScreenPos(void);
	D3DXVECTOR2 GetGlobalPos(void);

	float GetWidth(void);
	float GetHeight(void);

	Sprite* GetSprite(void);

protected:
	Sprite* pSprite;
	D3DXVECTOR2 screenPos, globalPos;
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
		OBJ_NONE = -1,
		OBJ_BED,
		OBJ_FLOOR,
		OBJ_LADDER,
		OBJ_DOOR,
		OBJ_KEY,
		OBJ_MAX
	};

	GameObject(ObjectType type);
	~GameObject();

	void Update(void);
	
	void Register(ObjectType type);
	Collision* GetCollision(void);
	ObjectType GetType(void);

private:
	ObjectType type;
	Collision* collision;
};