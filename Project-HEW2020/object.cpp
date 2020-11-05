//----------------------------------------------------------------------------
// 
// Project-HEW2020 [object.cpp]
// ゲームオブジェクト制御
// 
// Date:   2020/11/05
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#include "object.h"
#include "config.h"
#include "game.h"

//-----------------------------------------------------------------------------
// グローバル変数宣言
//-----------------------------------------------------------------------------
static GamePlayer* g_pPlayer = NULL;

void GameObject::Init(OType type)
{
	this->type = type;
	pSprite = NULL;
	if (type == GameObject::NONE || type == GameObject::MAX) return;
	if(NULL == g_pPlayer) g_pPlayer = Game_GetScene()->GetPlayer();

	switch (type)
	{
	case GameObject::FLOOR:
		pSprite = new SpriteNormal(TEXTURE_2FGROUND);
		break;
	case GameObject::LADDER:
		pSprite = new SpriteNormal(TEXTURE_LADDER);
		break;
	case GameObject::KEY:
		pSprite = new SpriteNormal();
		break;
	case GameObject::DOOR:
		pSprite = new SpriteNormal();
		break;
	case GameObject::BED:
		pSprite = new SpriteNormal(TEXTURE_BED);
		break;
	default:
		break;
	}

	pos = D3DXVECTOR2(0.0f, 0.0f);
	dw = pSprite->GetPolygonWidth();
	dh = pSprite->GetPolygonHeight();

	pSprite->SetDrawPos(0.0f, 0.0f);
	pSprite->SetCutPos(0, 0);
	pSprite->SetPolygonSize(pSprite->GetTextureWidth() * 3.2f, pSprite->GetTextureHeight() * 3.2f);
}

void GameObject::Uninit(void)
{
	delete pSprite;
	pSprite = NULL;
}

void GameObject::Update(void)
{
	pSprite->SetDrawPos(pos.x - pSprite->GetPolygonWidth() / 2, pos.y - pSprite->GetPolygonHeight() / 2);
}

void GameObject::Draw(void)
{
	pSprite->Draw();
}

void GameObject::SetPosition(float x, float y)
{
	pos.x = x;
	pos.y = y;
}

D3DXVECTOR2 GameObject::GetPosition(void)
{
	return this->pos;
}

float GameObject::GetPolygonWidth(void)
{
	return this->dw;
}

float GameObject::GetPolygonHeight(void)
{
	return this->dh;
}

void GameObject::SetType(OType type)
{
	this->Uninit();
	this->type = type;
	this->Init(type);
}

GameObject::OType GameObject::GetType(void)
{
	return this->type;
}