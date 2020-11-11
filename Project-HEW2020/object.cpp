//----------------------------------------------------------------------------
// 
// Project-HEW2020 [object.cpp]
// �Q�[���I�u�W�F�N�g����
// 
// Date:   2020/11/06
// Author: AT12D187_17_���i
// 
//----------------------------------------------------------------------------
#include "object.h"
#include "config.h"

//----------------------------------------------------------------------------
// ��{�N���X
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
	pos = D3DXVECTOR2(0.0f, 0.0f);
}

void Object::Uninit(void)
{
	delete pSprite;
	pSprite = NULL;
}

void Object::Draw(void)
{
	// �I�u�W�F�N�g�̍��W�̓|���S���̒��S�̂��߁A����ɏC�����܂�
	pSprite->SetDrawPos(pos.x - pSprite->GetPolygonWidth() / 2, pos.y - pSprite->GetPolygonHeight() / 2);
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

void Object::SetPosition(float x, float y)
{
	pos = D3DXVECTOR2(x, y);
}

Sprite* Object::GetSprite(void)
{
	return pSprite;
}

//----------------------------------------------------------------------------
// �h���N���X - GameObject
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
		pSprite->LoadTexture(TEXTURE_OBJECT_BED);
		break;
	case GameObject::FLOOR:
		pSprite->LoadTexture(TEXTURE_OBJECT_FLOOR);
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

	// �e�N�X�`���̏�����
	//do
	//{
	//	pSprite->SetCutPos(0.0f, 0.0f);
	//	pSprite->SetCutRange(pSprite->GetTextureWidth(), pSprite->GetTextureHeight());
	//} while (0);	
}