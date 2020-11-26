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
#include "fade.h"

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
	// （スクリーンの幅 / テクスチャの切り取り幅）は拡大・縮小の参照データ
	SetGlobalScaling((float)SCREEN_WIDTH / 384);
	isDarkness(false);

	fBgScroll = D3DXVECTOR2(0.0f, 0.0f);
	fBgScrollMax = D3DXVECTOR2(264.0f, 0.0f);
	fGroundHeight = 64.0f;

	// プレイヤーインスタンスを作成
	pPlayer = new GamePlayer;
	// プレイヤーの座標
	pPlayer->SetGlobalPos(64.0f, (float)SCREEN_HEIGHT - fGroundHeight);

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
	// ゲームオブジェクト・インスタンス(s)
	// BED
	pObjects[0] = new GameObject(GameObject::OBJ_BED);
	pObjects[0]->SetGlobalPos(120.0f, 435.0f);
	// FLOOR
	pObjects[1] = new GameObject(GameObject::OBJ_FLOOR);
	pObjects[1]->SetGlobalPos(940.0f, 310.0f);
	// LADDER 1
	pObjects[2] = new GameObject(GameObject::OBJ_LADDER);
	pObjects[2]->SetGlobalPos(455.0f, 490.0f);
	// LADDER 2
	pObjects[3] = new GameObject(GameObject::OBJ_LADDER);
	pObjects[3]->SetGlobalPos(1255.0f, 490.0f);
	// LOCK
	pObjects[4] = new GameObject(GameObject::OBJ_LOCK);
	pObjects[4]->SetGlobalPos(1020.5f, 170.0f);
	pObjects[4]->SetSize(pObjects[4]->GetWidth() * 0.3f, pObjects[4]->GetHeight() * 0.3f);


	// オブジェクトのサイズ一気に初期化
	for (GameObject* obj : pObjects)
	{
		if (NULL == obj) continue;
		if (GameObject::OBJ_LOCK == obj->GetType()) continue;
		obj->SetSize(obj->GetWidth() * fGlobalScaling, obj->GetHeight() * fGlobalScaling);
	}

	// FLOOR Overlay
	pOverlays[2] = new GameOverlay(TEXTURE_OBJ_FLOOR_OVERLAY);
	pOverlays[2]->SetSize(pOverlays[2]->GetWidth() * fGlobalScaling, pOverlays[2]->GetHeight() * fGlobalScaling);

	// 見える範囲 Overlay
	pOverlays[3] = new GameOverlay(TEXTURE_OVERLAY_RANGE);
	pOverlays[3]->SetScreenPos(pPlayer->GetScreenPos().x, pPlayer->GetScreenPos().y + pPlayer->GetCollision()->GetHalfHeight());
	pOverlays[3]->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	pOverlays[3]->GetSprite()->SetCutPos(640, 360);
	pOverlays[3]->GetSprite()->SetCutRange(SCREEN_WIDTH, SCREEN_HEIGHT);
	pOverlays[3]->SetSize(pOverlays[3]->GetWidth() * fGlobalScaling * 4.0f, pOverlays[3]->GetHeight() * fGlobalScaling * 4.0f);


	// ロック
	pCodedLockUI = new CodedLockUI;
	pCodedLockUI->SetPassword(6, 8, 9);

	FadeEffect::Start(FADE_IN, 0.0f, 0.0f, 0.0f, 30);
}

void TestScene::Uninit(void)
{
	// メモリ解放
	delete pPlayer;
	pPlayer = NULL;
	for (GameObject* p : pObjects)
	{
		delete p;
	}
	memset(pObjects, NULL, sizeof(pObjects));
	for (GameOverlay* p : pOverlays)
	{
		delete p;
	}
	memset(pOverlays, NULL, sizeof(pOverlays));

	delete pCodedLockUI;
	pCodedLockUI = NULL;
}

void TestScene::Update(void)
{
	// 背景のスクロール
	fBgScroll.x = pPlayer->GetGlobalPos().x - (float)SCREEN_WIDTH / 2;
	fBgScroll.x /= fGlobalScaling;

	// スクロール修正
	if (fBgScroll.x > fBgScrollMax.x)
		fBgScroll.x = fBgScrollMax.x;
	if (fBgScroll.x < 0.0f)
		fBgScroll.x = 0.0f;
	if (fBgScroll.y > fBgScrollMax.y)
		fBgScroll.y = fBgScrollMax.y;
	if (fBgScroll.y < 0.0f)
		fBgScroll.y = 0.0f;

	UpdatePlayer();
	UpdateObject();
	UpdateOverlay();
}

void TestScene::Draw(void)
{
	// 背景
	pOverlays[0]->Draw();

	for (GameObject* object : pObjects)
	{
		if (NULL == object) continue;
		object->Draw();
	}

	pPlayer->Draw();
	pOverlays[1]->Draw();
	pOverlays[2]->Draw();
	if (isDarkness())
		pOverlays[3]->Draw();

	pCodedLockUI->Draw();

	// デバッグ文字の表示
	if (Game::DebugMode()) this->Debug();
}

// プレイヤーの更新処理
void TestScene::UpdatePlayer(void)
{
	this->PlayerControl();

	// プレイヤーのコリジョンを取得
	Collision* collision = pPlayer->GetCollision();
	// スクリーン座標とワールド座標の同期
	float offsetX = fBgScroll.x * fGlobalScaling;
	float offsetY = 0.0f;
	// 背景はスクロールしていない状態 -> スクリーン座標は変更できる
	// 背景はスクロールしている状態	-> スクリーン座標は変更できない
	// グローバル座標（世界座標）はいつも正常に変わる
	if (fBgScroll.x <= 0.0f || fBgScroll.x >= fBgScrollMax.x)
		pPlayer->SetScreenPos(pPlayer->GetGlobalPos().x - offsetX, pPlayer->GetGlobalPos().y);
	else
		pPlayer->SetScreenPos((float)SCREEN_WIDTH / 2, pPlayer->GetGlobalPos().y);

	// プレイヤーは画面を出ることを防止
	float minimumX = 0.0f + collision->GetHalfWidth();
	float maximumX = (float)SCREEN_WIDTH - collision->GetHalfWidth() + offsetX;
	float minimumY = 0.0f + collision->GetHalfHeight();
	float maximumY = (float)SCREEN_HEIGHT - fGroundHeight - collision->GetHalfHeight();
	//	プレイヤーが2F以上の場合
	do
	{
		// 一番近いFLOORを取得
		GameObject* floor = GetNearestObject(collision->GetPosition(), GameObject::OBJ_FLOOR);
		// 取得出来なかった場合、break;
		if (NULL == floor) break;
		
		// プレイヤーが下に移動する場合、break;
		if (pPlayer->isClimbing() && pPlayer->GetDirection().y > 0.0f) break;

		// floorの上境界(Collision)
		float fTop = floor->GetCollision()->GetPosition().y - floor->GetCollision()->GetHalfHeight();
		// プレイヤーの中心座標y > floorの中心座標y ... break
		if (pPlayer->GetGlobalPos().y > floor->GetCollision()->GetPosition().y) break;

		maximumY = fTop - pPlayer->GetCollision()->GetHalfHeight();
		minimumX = floor->GetGlobalPos().x - floor->GetCollision()->GetHalfWidth() + pPlayer->GetCollision()->GetHalfWidth();
		maximumX = floor->GetGlobalPos().x + floor->GetCollision()->GetHalfWidth() - pPlayer->GetCollision()->GetHalfWidth();
	} while (0);
	// プレイヤーは画面を出ることを防止
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

	// 当たり判定(テスト用)
	do
	{
		GameObject* obj = GetNearestObject(collision->GetPosition(), GameObject::OBJ_LADDER);
		if (NULL == obj) break;
		if (obj->GetGlobalPos().x - collision->GetPosition().x < obj->GetCollision()->GetHalfWidth() + collision->GetHalfWidth())
		{
			//pPlayer->SetGlobalPos(obj->GetGlobalPos().x - obj->GetCollision()->GetHalfWidth() - collision->GetHalfWidth(), pPlayer->GetGlobalPos().y);
		}
	} while (0);

	// プレイヤーインスタンスを更新
	pPlayer->Update();
}

// オブジェクトの更新処理
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

// オーバーレイの更新処理
void TestScene::UpdateOverlay(void)
{
	pOverlays[0]->GetSprite()->SetCutPos((int)fBgScroll.x, (int)fBgScroll.y);
	pOverlays[1]->GetSprite()->SetCutPos((int)fBgScroll.x, (int)fBgScroll.y);

	float fGlobalPosOffset = fBgScroll.x * fGlobalScaling;
	pOverlays[2]->SetScreenPos(pObjects[1]->GetScreenPos().x + 120.0f, pObjects[1]->GetScreenPos().y - 24.0f);
	pOverlays[3]->SetScreenPos(pPlayer->GetScreenPos().x, pPlayer->GetScreenPos().y + pPlayer->GetCollision()->GetHalfHeight() + 32.0f);


	// ここからはUIの更新処理
	do
	{
		pCodedLockUI->Update();
		// ...
		// ...
		// ...
	} while (0);
}

void TestScene::PlayerControl(void)
{
	GameScene::PlayerControl();

	if (GameScene::bFrozen) return;
	// ロックに関する処理
	do
	{
		GameObject* lock = GetNearestObject(pPlayer->GetGlobalPos(), GameObject::OBJ_LOCK);
		if (NULL == lock) break;
		if (64.0f < abs(lock->GetGlobalPos().x - pPlayer->GetGlobalPos().x)) break;

		if (!pCodedLockUI->isUnlocked() && GameControl::GetKeyPress(GameControl::USE))
		{
			pCodedLockUI->OpenUI();
		}
	} while (0);
}

// デバッグ文字の表示
void TestScene::Debug(void)
{
	char buf[1024];
	float y = 0.0f;

	sprintf_s(buf, "BgScroll(%.2f, %.2f)", fBgScroll.x, fBgScroll.y);
	y += 32.0f;
	DebugFont::Draw(0.0f, y, buf);

	y += 64.0f;
	sprintf_s(buf, "[PlayerInfo]");
	DebugFont::Draw(0.0f, y, buf);
	y += 32.0f;
	sprintf_s(buf, ">MoveSpeed = %.2f", pPlayer->GetSpeed());
	DebugFont::Draw(0.0f, y, buf);
	y += 32.0f;
	sprintf_s(buf, ">ScreenPos(%.2f, %.2f)", pPlayer->GetScreenPos().x, pPlayer->GetScreenPos().y);
	DebugFont::Draw(0.0f, y, buf);
	y += 32.0f;
	sprintf_s(buf, ">GlobalPos(%.2f, %.2f)", pPlayer->GetGlobalPos().x, pPlayer->GetGlobalPos().y);
	DebugFont::Draw(0.0f, y, buf);
	y += 32.0f;
	sprintf_s(buf, ">CollisionCenter(%.2f, %.2f)", pPlayer->GetCollision()->GetPosition().x, pPlayer->GetCollision()->GetPosition().y);
	DebugFont::Draw(0.0f, y, buf);
	y += 32.0f;
	sprintf_s(buf, ">CollisionSize(%.2f, %.2f)", pPlayer->GetCollision()->GetWidth(), pPlayer->GetCollision()->GetHeight());
	DebugFont::Draw(0.0f, y, buf);
	y += 32.0f;
	sprintf_s(buf, ">isOnLadder = %d", pPlayer->isOnLadder());
	DebugFont::Draw(0.0f, y, buf);
	y += 32.0f;
	sprintf_s(buf, ">isClimbing = %d", pPlayer->isClimbing());
	DebugFont::Draw(0.0f, y, buf);

	y += 64.0f;
	sprintf_s(buf, "[ObjectInfo]");
	DebugFont::Draw(0.0f, y, buf);
	y += 32.0f;
	sprintf_s(buf, ">FLOOR S(%.2f, %.2f) G(%.2f, %.2f) CollisionSize(%.2f, %.2f)",
		pObjects[1]->GetScreenPos().x, pObjects[1]->GetScreenPos().y,
		pObjects[1]->GetGlobalPos().x, pObjects[1]->GetGlobalPos().y,
		pObjects[1]->GetCollision()->GetWidth(), pObjects[1]->GetCollision()->GetHeight());
	DebugFont::Draw(0.0f, y, buf);
	y += 32.0f;
	sprintf_s(buf, ">LADDER1 S(%.2f, %.2f) G(%.2f, %.2f) CollisionPos(%.2f, %.2f)",
		pObjects[2]->GetScreenPos().x, pObjects[2]->GetScreenPos().y, 
		pObjects[2]->GetGlobalPos().x, pObjects[2]->GetGlobalPos().y,
		pObjects[2]->GetCollision()->GetPosition().x, pObjects[2]->GetCollision()->GetPosition().y);
	DebugFont::Draw(0.0f, y, buf);
	y += 32.0f;
	sprintf_s(buf, ">LADDER2 S(%.2f, %.2f) G(%.2f, %.2f) CollisionSize(%.2f, %.2f)",
		pObjects[3]->GetScreenPos().x, pObjects[3]->GetScreenPos().y,
		pObjects[3]->GetGlobalPos().x, pObjects[3]->GetGlobalPos().y,
		pObjects[3]->GetCollision()->GetWidth(), pObjects[2]->GetCollision()->GetHeight());
	DebugFont::Draw(0.0f, y, buf);
}