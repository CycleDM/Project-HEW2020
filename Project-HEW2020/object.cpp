//----------------------------------------------------------------------------
// 
// Project-HEW2020 [object.cpp]
// ゲームオブジェクト制御
// 
// Date:   2020/11/06
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#include <stdio.h>
#include "object.h"
#include "config.h"
#include "scene.h"

//----------------------------------------------------------------------------
// 基本クラス
//----------------------------------------------------------------------------
Object::Object()
{
	this->Init();
}

Object::~Object()
{
	this->Uninit();
}

void Object::Init(void)
{
	pSprite = NULL;
	width = 0.0f;
	height = 0.0f;
	screenPos = D3DXVECTOR2(0.0f, 0.0f);
	globalPos = D3DXVECTOR2(0.0f, 0.0f);
}

void Object::Uninit(void)
{
	// メモリ解放
	delete pSprite;
	pSprite = NULL;
}

void Object::Update(void)
{

}

void Object::Draw(void)
{
	// オブジェクトの座標はポリゴンの中心
	// 描画座標はポリゴンの右上指定
	pSprite->SetDrawPos(screenPos.x - pSprite->GetPolygonWidth() / 2, screenPos.y - pSprite->GetPolygonHeight() / 2);
	pSprite->Draw();
}

void Object::SetSize(float width, float height)
{
	this->width = width;
	this->height = height;
	if (pSprite)
		pSprite->SetPolygonSize(width, height);
}

float Object::GetWidth(void)
{
	return width;
}

float Object::GetHeight(void)
{
	return height;
}

D3DXVECTOR2 Object::GetScreenPos(void)
{
	return screenPos;
}

D3DXVECTOR2 Object::GetGlobalPos(void)
{
	return globalPos;
}

void Object::SetScreenPos(float x, float y)
{
	screenPos = D3DXVECTOR2(x, y);
}

void Object::SetGlobalPos(float x, float y)
{
	globalPos = D3DXVECTOR2(x, y);
}

Sprite* Object::GetSprite(void)
{
	return pSprite;
}

//----------------------------------------------------------------------------
// 派生クラス - GameObject
//----------------------------------------------------------------------------
GameObject::GameObject()
{
	type = OBJ_NONE;
	pCollision = NULL;
	bCustomized = false;
	Register(type);
}

GameObject::GameObject(ObjectType type)
{
	this->type = type;
	pCollision = NULL;
	pAnimator = NULL;
	Register(type);
}

GameObject::~GameObject()
{
	delete pCollision;
	pCollision = NULL;
	delete pAnimator;
	pAnimator = NULL;
}

void GameObject::Register(ObjectType type)
{
	if (type == GameObject::OBJ_NONE) return;

	this->type = type;
	pSprite = new SpriteNormal;
	switch (type)
	{
	case GameObject::OBJ_BED:
		pSprite->LoadTexture(TEXTURE_OBJ_BED);
		break;
	case GameObject::OBJ_FLOOR:
		pSprite->LoadTexture(TEXTURE_OBJ_FLOOR);
		pCollision = new Collision;
		break;
	case GameObject::OBJ_LADDER:
		pSprite->LoadTexture(TEXTURE_OBJ_LADDER);
		pCollision = new Collision;
		break;
	case GameObject::OBJ_DOOR1:
		pSprite->LoadTexture(TEXTURE_OBJ_DOOR1);
		pCollision = new Collision;
		pSprite->SetCutPos(0, 0);
		pSprite->SetCutRange(17, 91);
		width = pSprite->GetCutWidth();
		height = pSprite->GetCutHeight();
		pAnimator = new Animator();
		pAnimator->Init(pSprite);
		pAnimator->Preset(6, 1, 8);
		bCustomized = true;
		break;
	case GameObject::OBJ_KEY:
		break;
	case GameObject::OBJ_CODED_LOCK:
		pSprite->LoadTexture(TEXTURE_OBJ_CODED_LOCK_ITEM);
		pCollision = new Collision;
		break;
	default:
		break;
	}

	if (!bCustomized && NULL != pSprite)
	{
		width = (float)pSprite->GetTextureWidth();
		height = (float)pSprite->GetTextureHeight();
	}

	if (NULL != pCollision)
	{
		pCollision->SetSize(width, height);
	}
}

Collision* GameObject::GetCollision(void)
{
	return pCollision;
}

Animator* GameObject::GetAnimator(void)
{
	return pAnimator;
}

GameObject::ObjectType GameObject::GetType(void)
{
	return this->type;
}

void GameObject::Update(void)
{
	if (!bCustomized && NULL != pCollision)
	{
		pCollision->SetPosition(globalPos.x, globalPos.y);
	}
}

void GameObject::SetSize(float width, float height)
{
	Object::SetSize(width, height);

	if (NULL != pCollision)
	{
		pCollision->SetSize(width, height);
	}
}