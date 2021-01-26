//----------------------------------------------------------------------------
// 
// Project-HEW2020 [player.h]
// �v���C���[���䃂�W���[��
// 
// Date:   2020/10/28
// Author: AT12D187_17_���i
// 
//----------------------------------------------------------------------------
#pragma once

#include <d3dx9.h>
#include "collision.h"
#include "sprite.h"
#include "animator.h"

class GamePlayer
{
public:
	GamePlayer();
	~GamePlayer();

	void Init(void);
	void Update(void);
	void Draw(void);
	void Uninit(void);
	// �v���C���[�̍��W��ݒ�
	void SetScreenPos(float x, float y);
	void SetGlobalPos(float x, float y);
	// �v���C���[�̍��W���擾
	D3DXVECTOR2 GetScreenPos(void);
	D3DXVECTOR2 GetGlobalPos(void);
	// �v���C���[�̃e�N�X�`���̕����擾�i�R���W�����͕ʁj
	float GetPolygonWidth(void);
	float GetPolygonHeight(void);

	Collision* GetCollision(void);
	D3DXVECTOR2 GetDirection(void);
	float GetSpeed(void);

	bool isWalking(void);
	void isWalking(bool bState);
	bool isClimbing(void);
	void isClimbing(bool bState);
	bool isOnLadder(void);
	void isOnLadder(bool bState);

	void MoveLeft(void);
	void MoveRight(void);
	void MoveUp(void);
	void MoveDown(void);
	void Jump(void);
	void SetWalkingSpeed(float speed);

private:
	Sprite* pSprite;
	D3DXVECTOR2 screenPos;			// �X�N���[�����W
	D3DXVECTOR2 globalPos;			// ���[���h���W
	D3DXVECTOR2 dirc;				// ����
	float speed;					// ���x
	float velocity;					// �����x
	int currentFloor;				// �v���C���[�����K�ڂɂ���

	bool bWalking;					// �ړ����̔���
	bool bJumping;					// �W�����v���̔���
	bool bClimbingUp;
	bool bClimbingDown;
	bool bOnLadder;

	Collision* pCollision;			// �v���C���[�̃R���W����
	Animator* pAnimator;			// �A�j���[�V��������
};