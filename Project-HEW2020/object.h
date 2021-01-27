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
#include "animator.h"

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
	virtual void SetSize(float, float);
	virtual void SetScale(float);
	// オブジェクトの中心座標を指定
	void SetScreenPos(float, float);
	void SetGlobalPos(float, float);
	// オブジェクトの中心座標を取得
	D3DXVECTOR2 GetScreenPos(void);
	D3DXVECTOR2 GetGlobalPos(void);

	float GetWidth(void);
	float GetHeight(void);

	// オブジェクトのテクスチャポインターを取得
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
		OBJ_DOOR1,
		OBJ_DIGITAL_DOOR,
		OBJ_KEY,
		OBJ_CODED_LOCK,
		OBJ_TRASH_STACK,
		OBJ_TRASH_LEG,
		OBJ_CRASH_ROBOT,
		OBJ_CRASH_ROBOT2,
		OBJ_GENERATOR,
		OBJ_SCREEN,
		OBJ_LANGUAGE_CHIP,
		OBJ_INTERACTABLE,
		OBJ_UNINTERACTABLE,
		OBJ_MAX
	};

	GameObject();
	GameObject(ObjectType type);
	~GameObject();

	void Register(ObjectType type);
	void Update(void);
	// オブジェクトのサイズを指定
	void SetSize(float, float);

	Collision* GetCollision(void);
	Animator* GetAnimator(void);
	ObjectType GetType(void);

private:
	ObjectType type;			// 自分のタイプを保存する所
	Collision* pCollision;		// コリジョン
	Animator* pAnimator;		// アニメーター
	bool bCustomized;
};