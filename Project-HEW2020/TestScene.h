//----------------------------------------------------------------------------
// 
// Project-HEW2020 [TestScene.h]
// プロトタイプシーン
// 
// Date:   2020/11/06
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#pragma once

#include <d3dx9.h>
#include "scene.h"
#include "coded_lock_ui.h"

class TestScene : public GameScene
{
public:
	TestScene();
	~TestScene();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
#ifdef _DEBUG
	void Debug(void);
#endif // _DEBUG

private:
	void UpdatePlayer(void);
	void UpdateObject(void);
	void UpdateOverlay(void);
	void PlayerControl(void);

	bool bIdea;
	bool bDoorOpened;

	CodedLockUI* pCodedLockUI;
};