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
	virtual void Play(Sprite* pSprite);
	// �A�j���[�V�������Đ�����i��񂾂��j
	virtual void PlayOnce(Sprite* pSprite);
	// �A�j���[�V�������ꎞ�I�ɒ��~����
	virtual void Pause(Sprite* pSprite);
	// ������
	virtual void Init(Sprite* pSprite = NULL);
	// �A�j���[�^�[�̊e��p�����[�^��������
	// ����:
	//	nMaxCntX	... �e�N�X�`���̐؂���X�̍ő吔
	//	nMaxCntY	... �e�N�X�`���̐؂���Y�̍ő吔
	//	nInterval	... �e�N�X�`���؂�ւ��̊Ԋu�i�t���[���j
	virtual void Preset(int nMaxCntX, int nMaxCntY, int nInterval);
	// �e�N�X�`���̏�Ԃ����ɖ߂��i���f�[�^�ɂ��j
	virtual void Reset(Sprite* pSprite);

private:
	int nFrame;				// �t���[���v���p�̕ϐ�
	int nAnimationCnt;		// �e�N�X�`���̐؂���ԍ�

	int nMaxCntX;			// �e�N�X�`���̐؂���X�̍ő�l
	int nMaxCntY;			// �e�N�X�`���̐؂���Y�̍ő�l
	int nInterval;			// �e�N�X�`���؂�ւ��̊Ԋu�i�t���[���j

	int originalData[2];	// �e�N�X�`���̌��f�[�^���i�[���鏊(tcx, tcy)

	bool bOncePlayed;		// PlayOnce()�Ŏg����t���O
};

