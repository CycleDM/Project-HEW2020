//----------------------------------------------------------------------------
// 
// Project-HEW2020 [test_scene.cpp]
// シーン0
// 
// Date:   2020/10/28
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#include <cmath>
#include "config.h"
#include "test_scene.h"
#include "game.h"
#include "player.h"

//-----------------------------------------------------------------------------
// グローバル変数宣言
//-----------------------------------------------------------------------------
static GamePlayer* g_pPlayer = NULL;
static Sprite* g_pSpriteBg = NULL;
static GameObject* g_pObjects[16];
static float g_fBgScroll = 0.0f;

void TestScene::Init(void)
{
	memset(g_pObjects, NULL, sizeof(g_pObjects));
	g_pSpriteBg = NULL;
	g_fBgScroll = 0.0f;

	g_pPlayer = new GamePlayer;

	g_pSpriteBg = new SpriteNormal(TEXTURE_BG);
	g_pSpriteBg->SetDrawPos(0.0f, 0.0f);
	g_pSpriteBg->SetCutPos(0.0f, 0.0f);
	g_pSpriteBg->SetCutRange(384.0f, 216.0f);
	g_pSpriteBg->SetPolygonSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);

	g_pObjects[0]= new GameObject(GameObject::FLOOR);
	g_pObjects[1]= new GameObject(GameObject::LADDER);
	g_pObjects[2]= new GameObject(GameObject::LADDER);
	g_pObjects[3]= new GameObject(GameObject::BED);
}

void TestScene::Update(void)
{
	if (g_pPlayer->GetPosition().x < (float)SCREEN_WIDTH / 2 + 10.0f && g_pPlayer->GetPosition().x > (float)SCREEN_WIDTH / 2 - 10.0f)
	{
		if (g_fBgScroll < 0.0f)
		{
			g_fBgScroll = 0.0f;
		}
		else if (g_fBgScroll > 264.0f)
		{
			g_fBgScroll = 264.0f;
		}
		else
		{
			g_pPlayer->SetPosition((float)SCREEN_WIDTH / 2, g_pPlayer->GetPosition().y);
			g_fBgScroll += g_pPlayer->GetSpeed() * g_pPlayer->GetDirection().x * 0.3f;
		}
	}
	g_pSpriteBg->SetCutPos(g_fBgScroll, 0);

	// FLOOR
	g_pObjects[0]->SetPosition(950.0f - g_fBgScroll / 0.3f, 300.0f);
	// LADDER
	g_pObjects[1]->SetPosition(455.0f - g_fBgScroll / 0.3f, 490.0f);
	g_pObjects[2]->SetPosition(1255.0f - g_fBgScroll / 0.3f, 490.0f);
	// BED
	g_pObjects[3]->SetPosition(120.0f - g_fBgScroll / 0.3f, 440.0f);

	for (GameObject* object : g_pObjects)
	{
		if (NULL != object)
		{
			object->Update();
		}
	}
}

void TestScene::Draw(void)
{
	g_pSpriteBg->Draw();
	for (GameObject* object : g_pObjects)
	{
		if (NULL != object)
		{
			object->Draw();
		}
	}

	g_pPlayer->Draw();
}

void TestScene::Uninit(void)
{
	delete g_pPlayer;
	g_pPlayer = NULL;

	delete g_pSpriteBg;
	g_pSpriteBg = NULL;

	delete[] g_pObjects;
	memset(g_pObjects, NULL, sizeof(g_pObjects));
}


GameObject* TestScene::GetNearestLadder(void)
{
	GameObject* target = NULL;
	for (GameObject* object : g_pObjects)
	{
		if (NULL == object || GameObject::LADDER != object->GetType()) continue;
		D3DXVECTOR2 ladderPos = object->GetPosition();
		D3DXVECTOR2 playerPos = g_pPlayer->GetPosition();

		//if (abs(ladderPos.y - playerPos.y) > object->GetPolygonHeight() + g_pPlayer->GetPolygonHeight() + 64.0f) break;

		if (abs(ladderPos.x - playerPos.x) < g_pPlayer->GetPolygonWidth() / 2)
		{
			target = object;
			break;
		}
	}
	return target;
}

GameObject* TestScene::GetNearestFloor(void)
{
	GameObject* target = NULL;
	for (GameObject* object : g_pObjects)
	{
		if (NULL == object || GameObject::FLOOR != object->GetType()) continue;

		D3DXVECTOR2 floorPos = object->GetPosition();
		D3DXVECTOR2 playerPos = g_pPlayer->GetPosition();

		if (floorPos.y - playerPos.y > 0.0f)
		{
			target = object;
			break;
		}
	}
	return target;
}

GamePlayer* TestScene::GetPlayer(void)
{
	return g_pPlayer;
}