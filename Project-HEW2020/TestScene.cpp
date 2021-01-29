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
	GameScene::Freeze(false);
	// （スクリーンの幅 / テクスチャの切り取り幅）は拡大・縮小の参照データ
	SetGlobalScaling((float)SCREEN_WIDTH / 384);
	isDarkness(false);

	fBgScroll = D3DXVECTOR2(0.0f, 0.0f);
	fBgScrollMax = D3DXVECTOR2(264.0f, 0.0f);
	fGroundHeight = 64.0f;
	bIdea = false;
	bDoorOpened = false;

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
	// FLOOR Overlay
	pOverlays[2] = new GameOverlay(TEXTURE_OBJ_FLOOR_OVERLAY);
	pOverlays[2]->SetScreenPos((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2);
	pOverlays[2]->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	pOverlays[2]->GetSprite()->SetCutPos(0, 0);
	pOverlays[2]->GetSprite()->SetCutRange(384, 216);
	// IDEA
	pOverlays[3] = new GameOverlay(TEXTURE_PLAYER_IDEA);
	pOverlays[3]->SetScale(1.3f);
	// ゲームオブジェクト・インスタンス(s)
	// FLOOR
	pObjects[0] = new GameObject(GameObject::OBJ_FLOOR);
	pObjects[0]->SetGlobalPos(950.0f, 300.0f);
	// LADDER 1
	pObjects[1] = new GameObject(GameObject::OBJ_LADDER);
	pObjects[1]->SetGlobalPos(455.0f, 490.0f);
	// LADDER 2
	pObjects[2] = new GameObject(GameObject::OBJ_LADDER);
	pObjects[2]->SetGlobalPos(1345.0f, 490.0f);
	// LOCK
	pObjects[3] = new GameObject(GameObject::OBJ_CODED_LOCK);
	pObjects[3]->SetGlobalPos(1198.5f, 210.0f);
	pObjects[3]->SetScale(0.2f);
	// DOOR1
	pObjects[4] = new GameObject(GameObject::OBJ_DOOR1);
	pObjects[4]->SetGlobalPos(1557.0f, 520.0f);

	// オブジェクトのサイズ一気に初期化
	for (GameObject* obj : pObjects)
	{
		if (NULL == obj) continue;
		if (GameObject::OBJ_CODED_LOCK == obj->GetType()) continue;
		obj->SetSize(obj->GetWidth() * fGlobalScaling, obj->GetHeight() * fGlobalScaling);
	}

	// 見える範囲 Overlay
	pOverlays[63] = new GameOverlay(TEXTURE_OVERLAY_RANGE);
	pOverlays[63]->SetScreenPos(pPlayer->GetScreenPos().x, pPlayer->GetScreenPos().y + pPlayer->GetCollision()->GetHalfHeight());
	pOverlays[63]->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	pOverlays[63]->GetSprite()->SetCutPos(640, 360);
	pOverlays[63]->GetSprite()->SetCutRange(SCREEN_WIDTH, SCREEN_HEIGHT);
	pOverlays[63]->SetScale(fGlobalScaling * 4.0f);

	// ロック
	pCodedLockUI = new CodedLockUI;
	pCodedLockUI->SetPassword(6, 8, 9);
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

	// END
	if (pPlayer->GetGlobalPos().x > 2000.0f)
	{
		Game::LoadNextScene(Game::SCENE_FINAL);
	}
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
	if (isDarkness()) pOverlays[63]->Draw();
	if (bIdea) pOverlays[3]->Draw();

	pCodedLockUI->Draw();

#ifdef _DEBUG
	// デバッグ文字の表示
	if (Game::DebugMode()) this->Debug();
#endif // _DEBUG
}

// プレイヤーの更新処理
void TestScene::UpdatePlayer(void)
{
	this->PlayerControl();

	// プレイヤーのコリジョンを取得
	Collision* pPC = pPlayer->GetCollision();
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
	float minimumX = 0.0f + pPC->GetHalfWidth();
	float maximumX = (float)SCREEN_WIDTH - pPC->GetHalfWidth() + offsetX;
	float minimumY = 0.0f + pPC->GetHalfHeight();
	float maximumY = (float)SCREEN_HEIGHT - fGroundHeight - pPC->GetHalfHeight();
	//	プレイヤーが2F以上の場合
	do
	{
		// 一番近いFLOORを取得
		GameObject* floor = GetNearestObject(pPlayer->GetGlobalPos(), GameObject::OBJ_FLOOR);
		// 取得出来なかった場合、break;
		if (NULL == floor) break;
		
		// プレイヤーが下に移動する場合、break;
		if (pPlayer->isClimbing() && pPlayer->GetDirection().y > 0.0f) break;

		// floorの上境界(Collision)
		float fTop = floor->GetCollision()->GetPosition().y - floor->GetCollision()->GetHalfHeight();
		// プレイヤーの中心座標y > floorの中心座標y ... break
		if (pPlayer->GetGlobalPos().y > floor->GetCollision()->GetPosition().y) break;

		maximumY = fTop - pPC->GetHalfHeight();
		minimumX = floor->GetGlobalPos().x - floor->GetCollision()->GetHalfWidth() + pPC->GetHalfWidth();
		maximumX = floor->GetGlobalPos().x + floor->GetCollision()->GetHalfWidth() - pPC->GetHalfWidth();
	} while (0);
	// プレイヤーは画面を出ることを防止
	// 左壁
	if (pPC->GetPosition().x < minimumX)
		pPlayer->SetGlobalPos(minimumX, pPlayer->GetGlobalPos().y);
	// 右壁
	if (pPC->GetPosition().x > maximumX)
		pPlayer->SetGlobalPos(maximumX, pPlayer->GetGlobalPos().y);
	// 上境界
	if (pPC->GetPosition().y < minimumY)
		pPlayer->SetGlobalPos(pPlayer->GetGlobalPos().x, minimumY);
	// 下境界
	if (pPC->GetPosition().y > maximumY)
		pPlayer->SetGlobalPos(pPlayer->GetGlobalPos().x, maximumY);

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

	// コリジョンにより当たり判定
	Collision* pPC = pPlayer->GetCollision();

	GameObject* obj = GetNearestObject(pPC->GetPosition(), GameObject::OBJ_DOOR1);
	Collision* pOC = obj->GetCollision();
	do
	{
		if (NULL == obj) break;
		if (NULL == pOC) break;

		if (pCodedLockUI->isUnlocked())
		{
			if(!bDoorOpened) PlaySound(SOUND_LABEL_SE_DOOR_OPEN1);
			bDoorOpened = true;
			obj->GetAnimator()->PlayOnce(obj->GetSprite());
			// DOOR1 コリジョンの調整
			pOC->SetPosition(pOC->GetPosition().x, pOC->GetPosition().y - pOC->GetHalfHeight());
			pOC->SetSize(pOC->GetWidth(), 0.0f);
		}
		else
		{
			pOC->SetPosition(obj->GetGlobalPos().x, obj->GetGlobalPos().y);
			pOC->SetSize(obj->GetSprite()->GetPolygonWidth(), obj->GetSprite()->GetPolygonHeight());
		}

		//-----------------------------------------------------------------------------------
		if (abs(pPC->GetPosition().y - pOC->GetPosition().y)
			> pPC->GetHalfHeight() + pOC->GetHalfHeight()) break;
		//-----------------------------------------------------------------------------------

		if (obj->GetGlobalPos().x - pPC->GetPosition().x < pOC->GetHalfWidth() + pPC->GetHalfWidth())
		{
			pPlayer->SetGlobalPos(obj->GetGlobalPos().x - pOC->GetHalfWidth() - pPC->GetHalfWidth(), pPlayer->GetGlobalPos().y);
		}
	} while (0);

	// IDEA & CODE LOCK
	if (GameScene::bFrozen) return;
	bIdea = false;
	obj = GetNearestObject(pPC->GetPosition(), GameObject::OBJ_CODED_LOCK);
	do
	{
		if (pPlayer->GetGlobalPos().y >= (float)SCREEN_HEIGHT / 2) break;
		if (pCodedLockUI->isUnlocked()) break;
		if (abs(obj->GetGlobalPos().x - pPlayer->GetGlobalPos().x) <= 64.0f)
		{
			if (Input::GetKeyTrigger(DIK_E))
			{
				pCodedLockUI->OpenUI();
			}
			bIdea = true;
		}
	} while (0);
}

// オーバーレイの更新処理
void TestScene::UpdateOverlay(void)
{
	pOverlays[0]->GetSprite()->SetCutPos((int)fBgScroll.x, (int)fBgScroll.y);
	pOverlays[1]->GetSprite()->SetCutPos((int)fBgScroll.x, (int)fBgScroll.y);
	pOverlays[2]->GetSprite()->SetCutPos((int)fBgScroll.x, (int)fBgScroll.y);

	float fGlobalPosOffset = fBgScroll.x * fGlobalScaling;
	pOverlays[63]->SetScreenPos(pPlayer->GetScreenPos().x, pPlayer->GetScreenPos().y + pPlayer->GetCollision()->GetHalfHeight() + 32.0f);


	// ここからはUIの更新処理
	do
	{
		pCodedLockUI->Update();
		pOverlays[3]->SetScreenPos(pPlayer->GetScreenPos().x, pPlayer->GetScreenPos().y - 140.0f);
	} while (0);
}

void TestScene::PlayerControl(void)
{
	GameScene::PlayerControl();
}

#ifdef _DEBUG
// デバッグ文字の表示
void TestScene::Debug(void)
{
	char buf[1024];
	int y = 32;

	sprintf_s(buf, "BgScroll(%.2f, %.2f)", fBgScroll.x, fBgScroll.y);
	y += 32;
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);

	y += 32;
	sprintf_s(buf, "[PlayerInfo]");
	D3DFont::Draw(0, y, buf, FONT_NAME, 32, D3DCOLOR_RGBA(100, 220, 255, 255));
	y += 32;
	sprintf_s(buf, ">ScreenPos(%.2f, %.2f)", pPlayer->GetScreenPos().x, pPlayer->GetScreenPos().y);
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);
	y += 32;
	sprintf_s(buf, ">GlobalPos(%.2f, %.2f)", pPlayer->GetGlobalPos().x, pPlayer->GetGlobalPos().y);
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);
	y += 32;
	sprintf_s(buf, ">CollisionCenter(%.2f, %.2f)", pPlayer->GetCollision()->GetPosition().x, pPlayer->GetCollision()->GetPosition().y);
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);
	y += 32;
	sprintf_s(buf, ">isOnLadder = %d", pPlayer->isOnLadder());
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);
	y += 32;
	sprintf_s(buf, ">isClimbing = %d", pPlayer->isClimbing());
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);

	sprintf_s(buf, "[Mouse States]");
	y += 32;
	D3DFont::Draw(0, y, buf, FONT_NAME, 32, D3DCOLOR_RGBA(100, 220, 255, 255));
	sprintf_s(buf, ">LB = %d", Input::GetMouseButtonPress(0));
	y += 32;
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);
	sprintf_s(buf, ">RB = %d", Input::GetMouseButtonPress(1));
	y += 32;
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);
	sprintf_s(buf, ">MB = %d", Input::GetMouseButtonPress(2));
	y += 32;
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);
	sprintf_s(buf, ">deltaX = %d", Input::GetMouseDeltaX());
	y += 32;
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);
	sprintf_s(buf, ">deltaY = %d", Input::GetMouseDeltaY());
	y += 32;
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);
	sprintf_s(buf, ">deltaZ = %d", Input::GetMouseDeltaWheel());
	y += 32;
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);
	sprintf_s(buf, ">PosX = %d", Input::GetMouseX());
	y += 32;
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);
	sprintf_s(buf, ">PosY = %d", Input::GetMouseY());
	y += 32;
	D3DFont::Draw(0, y, buf, FONT_NAME, 32);
}
#endif // _DEBUG