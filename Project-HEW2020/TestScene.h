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

#include <d3dx9.h>
#include "scene.h"

class TestScene : public GameScene
{
public:
	TestScene();
	~TestScene();

	virtual void Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void Debug(void);

	virtual void UpdatePlayer(void);
	virtual void UpdateObject(void);
	virtual void UpdateOverlay(void);
};