//----------------------------------------------------------------------------
// 
// Project-HEW2020 [TestScene.cpp]
// プロトタイプシーン
// 
// Date:   2020/11/06
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#include <stdio.h>
#include "TestScene.h"
#include "debug_font.h"
#include "game.h"

TestScene::TestScene()
{
	this->Init();
}

TestScene::~TestScene()
{
	this->Uninit();
}

void TestScene::Init(void)
{
	GameScene::SetGlobalScaling(3.33333f);
	fBgScroll.x = 0.0f;
	fBgScroll.y = 0.0f;
	fGroundHeight = 64.0f;

	// プレイヤーインスタンス
	pPlayer = new GamePlayer;
	// プレイヤーの座標
	pPlayer->SetGlobalPos(0.0f, (float)SCREEN_HEIGHT);

	// 背景
	pOverlays[0] = new GameOverlay(TEXTURE_BG);
	pOverlays[0]->SetScreenPos((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2);
	pOverlays[0]->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	pOverlays[0]->GetSprite()->SetCutPos(0, 0);
	pOverlays[0]->GetSprite()->SetCutRange(384, 216);
	// ドアフレーム（Overlay）
	pOverlays[1] = new GameOverlay(TEXTURE_BG_OVERLAY);
	pOverlays[1]->SetScreenPos((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2);
	pOverlays[1]->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	pOverlays[1]->GetSprite()->SetCutPos(0, 0);
	pOverlays[1]->GetSprite()->SetCutRange(384, 216);
	pOverlays[1]->GetSprite()->SetColor(D3DCOLOR_RGBA(255, 255, 255, 230));
	// ゲームオブジェクト・インスタンス
	// BED
	pObjects[0] = new GameObject(GameObject::OBJ_BED);
	pObjects[0]->SetGlobalPos(120.0f, 435.0f);
	// FLOOR
	pObjects[1] = new GameObject(GameObject::OBJ_FLOOR);
	pObjects[1]->SetGlobalPos(940.0f, 310.0f);
	// LADDER
	pObjects[2] = new GameObject(GameObject::OBJ_LADDER);
	pObjects[2]->SetGlobalPos(455.0f, 490.0f);
	pObjects[3] = new GameObject(GameObject::OBJ_LADDER);
	pObjects[3]->SetGlobalPos(1255.0f, 490.0f);


	// オブジェクトのサイズ一気に初期化
	for (GameObject* object : pObjects)
	{
		if (NULL == object) continue;
		object->SetSize(object->GetWidth() * fGlobalScaling, object->GetHeight() * fGlobalScaling);
		//object->GetSprite()->SetPolygonSize(object->GetSprite()->GetTextureWidth() * fGlobalScaling, object->GetSprite()->GetTextureHeight() * fGlobalScaling);
	}

	// FLOOR Overlay
	pOverlays[2] = new GameOverlay(TEXTURE_OBJ_FLOOR_OVERLAY);
	pOverlays[2]->SetSize(pOverlays[2]->GetWidth() * fGlobalScaling, pOverlays[2]->GetHeight() * fGlobalScaling);
}

void TestScene::Uninit(void)
{
	delete pPlayer;
	pPlayer = NULL;

	delete[] pObjects;
	memset(pObjects, NULL, sizeof(pObjects));

	delete[] pOverlays;
	memset(pOverlays, NULL, sizeof(pOverlays));
}

void TestScene::Update(void)
{
	// 背景のスクロール
	fBgScroll.x = pPlayer->GetGlobalPos().x - (float)SCREEN_WIDTH / 2;
	fBgScroll.x /= fGlobalScaling;
	// 修正
	if (fBgScroll.x > 264.0f)
		fBgScroll.x = 264.0f;
	if (fBgScroll.x < 0.0f)
		fBgScroll.x = 0.0f;

	UpdatePlayer();
	UpdateObject();
	UpdateOverlay();
}

void TestScene::Draw(void)
{
	pOverlays[0]->Draw();

	for (GameObject* object : pObjects)
	{
		if (NULL == object) continue;
		object->Draw();
	}

	pPlayer->Draw();
	pOverlays[1]->Draw();
	pOverlays[2]->Draw();

	// デバッグ文字の表示
	if (Game_IsDebugMode()) this->Debug();
}

void TestScene::UpdatePlayer(void)
{
	// プレイヤーのコリジョンを取得
	Collision* collision = pPlayer->GetCollision();
	// スクリーン座標とワールド座標の同期
	float offsetX = fBgScroll.x * fGlobalScaling;
	float offsetY = 0.0f;
	// 背景はスクロールしない状態はスクリーンの座標をUnlock
	// その逆、プレイヤーの描画座標を常にスクリーンの真ん中に設置
	if (fBgScroll.x <= 0.0f || fBgScroll.x >= 264.0f)
		pPlayer->SetScreenPos(pPlayer->GetGlobalPos().x - offsetX, pPlayer->GetGlobalPos().y);
	else
		pPlayer->SetScreenPos((float)SCREEN_WIDTH / 2, pPlayer->GetGlobalPos().y);

	// プレイヤーは画面を出ることを防止
	float minimumX = 0.0f + collision->GetHalfWidth();
	float maximumX = (float)SCREEN_WIDTH - collision->GetHalfWidth() + offsetX;
	float minimumY = 0.0f + collision->GetHalfHeight();
	float maximumY = (float)SCREEN_HEIGHT - fGroundHeight - collision->GetHalfHeight();
	// 左壁
	if (collision->GetPosition().x < minimumX)
		pPlayer->SetGlobalPos(minimumX, pPlayer->GetGlobalPos().y);
	// 右壁
	if (collision->GetPosition().x > maximumX)
		pPlayer->SetGlobalPos(maximumX, pPlayer->GetGlobalPos().y);
	// 上境界
	if (collision->GetPosition().y < minimumY)
		pPlayer->SetGlobalPos(pPlayer->GetGlobalPos().x, minimumY);
	// 下境界
	if (collision->GetPosition().y > maximumY)
		pPlayer->SetGlobalPos(pPlayer->GetGlobalPos().x, maximumY);

	// プレイヤーインスタンスを更新
	pPlayer->Update();
}

void TestScene::UpdateObject(void)
{
	float fGlobalPosOffset = fBgScroll.x * fGlobalScaling;
	for (GameObject* object : pObjects)
	{
		if (NULL == object) continue;
		object->SetScreenPos(object->GetGlobalPos().x - fGlobalPosOffset, object->GetGlobalPos().y);
		object->Update();
	}
}

void TestScene::UpdateOverlay(void)
{
	pOverlays[0]->GetSprite()->SetCutPos((int)fBgScroll.x, 0);
	pOverlays[1]->GetSprite()->SetCutPos((int)fBgScroll.x, 0);

	float fGlobalPosOffset = fBgScroll.x * fGlobalScaling;
	pOverlays[2]->SetScreenPos(pObjects[1]->GetScreenPos().x + 120.0f, pObjects[1]->GetScreenPos().y - 24.0f);
}

// デバッグ文字の表示
void TestScene::Debug(void)
{
	char buf[64];

	sprintf_s(buf, "BgScroll=(%.2f, %.2f)", fBgScroll.x, fBgScroll.y);
	DebugFont_Draw(0.0f, 32.0f, buf);


	sprintf_s(buf, "[PlayerInfo]");
	DebugFont_Draw(0.0f, 64.0f, buf);
	sprintf_s(buf, ">ScreenPos(%.2f, %.2f)", pPlayer->GetScreenPos().x, pPlayer->GetScreenPos().y);
	DebugFont_Draw(0.0f, 96.0f, buf);
	sprintf_s(buf, ">GlobalPos(%.2f, %.2f)", pPlayer->GetGlobalPos().x, pPlayer->GetGlobalPos().y);
	DebugFont_Draw(0.0f, 128.0f, buf);
	sprintf_s(buf, ">CollisionCenter(%.2f, %.2f)", pPlayer->GetCollision()->GetPosition().x, pPlayer->GetCollision()->GetPosition().y);
	DebugFont_Draw(0.0f, 160.0f, buf);
	sprintf_s(buf, ">CollisionSize(%.2f, %.2f)", pPlayer->GetCollision()->GetWidth(), pPlayer->GetCollision()->GetHeight());
	DebugFont_Draw(0.0f, 192.0f, buf);

	sprintf_s(buf, ">LADDER1(%.2f, %.2f)", pObjects[2]->GetGlobalPos().x, pObjects[2]->GetGlobalPos().y);
	DebugFont_Draw(0.0f, 224.0f, buf);
}