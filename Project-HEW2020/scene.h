//----------------------------------------------------------------------------
// 
// Project-HEW2020 [scene.h]
// �V�[����{�N���X
// 
// Date:   2020/11/06
// Author: AT12D187_17_���i
// 
//----------------------------------------------------------------------------
#pragma once

#include <cmath>
#include "config.h"
#include "player.h"
#include "object.h"
#include "overlay.h"
#include "controller.h"
#include "input.h"
#include "d3dfont.h"

//-----------------------------------------------------------------------------
// �Q�[���V�[���E��{�N���X - �K���h��������Ă�������
//-----------------------------------------------------------------------------
class GameScene
{
public:
	GameScene();
	virtual ~GameScene();

	virtual void Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual void Debug(void) = 0;

	// �v���C���[�̃C���X�^���X���擾�i�|�C���^�[�j
	GamePlayer* GetPlayer(void);
	// �w��̍��W�Ɉ�ԋ߂��A����̃I�u�W�F�N�g���擾
	// ����:
	//	position	... �w�肷����W
	//	objectType	... ����̃I�u�W�F�N�g�^�C�v
	GameObject* GetNearestObject(D3DXVECTOR2 position, GameObject::ObjectType objectType);

	// �g��E�k���Q�ƃf�[�^��ݒ�
	static void SetGlobalScaling(float scaling);
	// �g��E�k���Q�ƃf�[�^���擾
	static float GetGlobalScaling(void);

	static void Freeze(bool bFrozen);

protected:
	// �v���C���[�̍X�V����
	virtual void UpdatePlayer(void) = 0;
	// �I�u�W�F�N�g�̍X�V����
	virtual void UpdateObject(void) = 0;
	// �I�[�o�[���C�̍X�V����
	virtual void UpdateOverlay(void) = 0;
	// �v���C���[����̏���
	virtual void PlayerControl(void);

	static bool isDarkness(void);
	static void isDarkness(bool bDarkness);

	static float fGlobalScaling;						// ���ׂẴe�N�X�`���̊g��E�k���Q�ƃf�[�^
	GamePlayer* pPlayer;								// �v���C���[�̃C���X�^���X
	GameObject* pObjects[SINGLE_SCENE_OBJECT_MAX];		// �Q�[���I�u�W�F�N�g�̃C���X�^���X
	GameOverlay* pOverlays[SINGLE_SCENE_OVERLAY_MAX];	// �Q�[���I�[�o�[���C�̃C���X�^���X
	GameOverlay* pUI[UI_OVERLAY_MAX];
	D3DXVECTOR2 fBgScroll;								// �V�[���E�w�i�̑��d�X�N���[���̎Q�ƃf�[�^
	D3DXVECTOR2 fBgScrollMax;							// �V�[���E�w�i�̑��d�X�N���[���̎Q�ƃf�[�^�i�ő�l�j
	float fGroundHeight;								// �n�ʂ̍���

	static bool bDarkness;
	static bool bFrozen;
};
