//----------------------------------------------------------------------------
// 
// Project-HEW2020 [TestScene.h]
// �v���g�^�C�v�V�[��
// 
// Date:   2020/11/06
// Author: AT12D187_17_���i
// 
//----------------------------------------------------------------------------
#pragma once

#include "scene.h"

class TestScene : public GameScene
{
public:
	TestScene();
	~TestScene();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	float fBgScroll;

};