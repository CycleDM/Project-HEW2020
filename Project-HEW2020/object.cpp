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

void Object::SetScale(float scaling)
{
	width *= scaling;
	height *= scaling;
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
		pSprite->SetCutRange(11, 97);
		width = pSprite->GetCutWidth();
		height = pSprite->GetCutHeight();
		pAnimator = new Animator();
		pAnimator->Init(pSprite);
		pAnimator->Preset(7, 1, 5);
		bCustomized = true;
		break;
	case GameObject::OBJ_DIGITAL_DOOR:
		pSprite->LoadTexture(TEXTURE_OBJ_DIGITAL_DOOR);
		pCollision = new Collision;
		pSprite->SetCutPos(0, 0);
		pSprite->SetCutRange(32, 32);
		width = pSprite->GetCutWidth();
		height = pSprite->GetCutHeight();
		pAnimator = new Animator();
		pAnimator->Init(pSprite);
		pAnimator->Preset(5, 1, 6);
		bCustomized = true;
		break;
	case GameObject::OBJ_KEY:
		break;
	case GameObject::OBJ_CODED_LOCK:
		pSprite->LoadTexture(TEXTURE_OBJ_CODED_LOCK_ITEM);
		pCollision = new Collision;
		break;
	case GameObject::OBJ_TRASH_STACK:
		pSprite->LoadTexture(TEXTURE_OBJ_TRASH1);
		break;
	case GameObject::OBJ_TRASH_LEG:
		pSprite->LoadTexture(TEXTURE_OBJ_TRASH2);
		break;
	case GameObject::OBJ_CRASH_ROBOT:
		pSprite->LoadTexture(TEXTURE_OBJ_CRASH_ROBOT);
		break;
	case GameObject::OBJ_CRASH_ROBOT2:
		pSprite->LoadTexture(TEXTURE_OBJ_CRASH_ROBOT2);
		break;
	case GameObject::OBJ_GENERATOR:
		pSprite->LoadTexture(TEXTURE_OBJ_GENERATOR);
		break;
	case GameObject::OBJ_SCREEN:
		pSprite->LoadTexture(TEXTURE_OBJ_SCREEN);
		pSprite->SetCutRange(64, 64);
		width = pSprite->GetCutWidth();
		height = pSprite->GetCutHeight();
		bCustomized = true;
		break;
	case GameObject::OBJ_LANGUAGE_CHIP:
		pSprite->LoadTexture(TEXTURE_OBJ_LANGUAGE);
		break;
	case GameObject::OBJ_LIFT:
		pSprite->LoadTexture(TEXTURE_OBJ_LIFT_BOX);
		break;
	case GameObject::OBJ_LIFT_PANEL:
		pSprite->LoadTexture(TEXTURE_OBJ_LIFT_PANEL);
		break;
	case GameObject::OBJ_MAKER:
		pSprite->LoadTexture(TEXTURE_OBJ_MAKER);
		break;
	case GameObject::OBJ_NEW_ROBOT:
		pSprite->LoadTexture(TEXTURE_OBJ_NEW_ROBOT);
		break;
	case GameObject::OBJ_COMPUTER:
		pSprite->LoadTexture(TEXTURE_OBJ_COMPUTER);
		break;
	case GameObject::OBJ_ITEM_HAND:
		pSprite->LoadTexture(TEXTURE_ITEM_HAND);
		break;
	case GameObject::OBJ_VISUAL_CHIP:
		pSprite->LoadTexture(TEXTURE_OBJ_VISUAL);
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