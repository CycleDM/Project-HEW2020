//----------------------------------------------------------------------------
// 
// Project-HEW2020 [FinalScene.h]
// クレジット画面
// 
// Date:   2020/01/29
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#pragma once

#include <string>
#include "scene.h"

using namespace std;

class FinalScene : public GameScene
{
public:
	FinalScene();
	~FinalScene();

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

	static const string strThanks;
	static const string strPlaner[2];
	static const string strProgrammer[2];
	static const string strDesigner[4];
	static const string strSpecial[2];

	unsigned long long frameCnt;
	int nPosYIndex;
	bool bFinished;
	bool bEndScene;

	GameOverlay* pBgOverlay;
};