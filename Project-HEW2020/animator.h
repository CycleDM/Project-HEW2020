//----------------------------------------------------------------------------
// 
// Project-HEW2020 [animator.h]
// �A�j���[�V�������䃂�W���[��
// 
// Date:   2020/11/12
// Author: AT12D187_17_���i
// 
//----------------------------------------------------------------------------
#pragma once

#include "sprite.h"

class Animator
{
public:
	Animator();
	virtual ~Animator();

	// �A�j���[�V�������Đ�����
	virtual void Play(void);
	// �A�j���[�V�������ꎞ�I�ɒ��~����
	virtual void Pause(void);
	// ������
	virtual void Init(Sprite* pSprite = NULL);
	// �������E�w�肵���l��������
	// ����:
	//	pSprite		... ���삳���X�v���C�g
	//	nMaxCntX	... �e�N�X�`���̐؂���X�̍ő吔
	//	nMaxCntY	... �e�N�X�`���̐؂���Y�̍ő吔
	//	nInterval	... �e�N�X�`���؂�ւ��̊Ԋu�i�t���[���j
	virtual void Init(Sprite* pSprite, int nMaxCntX, int nMaxCntY, int nInterval);

private:
	Sprite* pSprite;	// �A�j���[�V�����Ƃ��Ďg����X�v���C�g
	int nFrame;			// �t���[���v���p�̕ϐ�
	int nAnimationCnt;	// �e�N�X�`���̐؂���ԍ�

	int nMaxCntX;		// �e�N�X�`���̐؂���X�̍ő�l
	int nMaxCntY;		// �e�N�X�`���̐؂���Y�̍ő�l
	int nInterval;		// �e�N�X�`���؂�ւ��̊Ԋu�i�t���[���j
};

