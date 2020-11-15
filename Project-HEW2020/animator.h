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
	~Animator();

	// �A�j���[�V�������Đ�����
	void Play();
	// ������
	void Init(Sprite* pSprite = NULL);
	// �������E�w�肵���l��������
	// ����:
	//	pSprite		... ���삳���X�v���C�g
	//	nMaxCntX	... �e�N�X�`���̐؂���X�̍ő�l
	//	nMaxCntY	... �e�N�X�`���̐؂���Y�̍ő�l
	//	nInterval	... �e�N�X�`���؂�ւ��̊Ԋu�i�t���[���j
	void Init(Sprite* pSprite, int nMaxCntX, int nMaxCntY, int nInterval);

private:
	Sprite* pSprite;	// �A�j���[�V�����Ƃ��Ďg����X�v���C�g
	int nFrame;			// �t���[���v���p�̕ϐ�
	int nAnimationCnt;	// �e�N�X�`���̐؂���ԍ�

	int nMaxCntX;		// �e�N�X�`���̐؂���X�̍ő�l
	int nMaxCntY;		// �e�N�X�`���̐؂���Y�̍ő�l
	int nInterval;		// �e�N�X�`���؂�ւ��̊Ԋu�i�t���[���j
};

