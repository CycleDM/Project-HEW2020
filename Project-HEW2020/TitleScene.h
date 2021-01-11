//----------------------------------------------------------------------------
// 
// Project-HEW2020 [TitleScene.h]
// �^�C�g����ʃV�[��
// 
// Date:   2020/11/27
// Author: AT12D187_17_���i
// 
//----------------------------------------------------------------------------
#pragma once

#include "scene.h"

class TitleScene : public GameScene
{
public:
	TitleScene();
	~TitleScene();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Debug(void);

private:
	void UpdatePlayer(void);
	void UpdateObject(void);
	void UpdateOverlay(void);

	Animator* pAnimator;
};

