//----------------------------------------------------------------------------
// 
// Project-HEW2020 [object.cpp]
// ゲームオブジェクト制御
// 
// Date:   2020/11/06
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#include "object.h"
#include "config.h"

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
	width = 0;
	height = 0;
	globalPos = D3DXVECTOR2(0.0f, 0.0f);
}

void Object::Uninit(void)
{
	delete pSprite;
	pSprite = NULL;
}

void Object::Draw(void)
{
	// オブジェクトの座標はポリゴンの中心のため、左上に修正します
	pSprite->SetDrawPos(globalPos.x - pSprite->GetPolygonWidth() / 2, globalPos.y - pSprite->GetPolygonHeight() / 2);
	pSprite->Draw();
}

void Object::SetSize(float width, float height)
{
	this->width = width;
	this->height = height;
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

D3DXVECTOR2 Object::GetPosition(void)
{
	return globalPos;
}

void Object::SetPosition(float x, float y)
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
	this->Init();
}

GameObject::GameObject(ObjectType type)
{
	this->Register(type);
}

GameObject::~GameObject()
{
	this->Uninit();
}

void GameObject::Register(ObjectType type)
{
	pSprite = new SpriteNormal;
	switch (type)
	{
	case GameObject::BED:
		pSprite->LoadTexture(TEXTURE_OBJ_BED);
		break;
	case GameObject::FLOOR:
		pSprite->LoadTexture(TEXTURE_OBJ_FLOOR);
		break;
	case GameObject::LADDER:
		pSprite->LoadTexture(TEXTURE_OBJECT_LADDER);
		break;
	case GameObject::DOOR:

		break;
	case GameObject::KEY:

		break;
	case GameObject::NONE:
	case GameObject::MAX:
		break;
	}

	width = pSprite->GetTextureWidth();
	height = pSprite->GetTextureHeight();
}