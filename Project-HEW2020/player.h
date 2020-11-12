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
	float GetPolygonWidth(void);
	float GetPolygonHeight(void);

	float GetSpeed(void);
	D3DXVECTOR2 GetDirection(void);
	bool GetMovingStatus(void);

	void MoveLeft(void);
	void MoveRight(void);
	void Jump(void);

private:
	D3DXVECTOR2 screenPos;	// �X�N���[�����W
	D3DXVECTOR2 globalPos;	// ���[���h���W
	D3DXVECTOR2 dirc;		// ����
	float speed;			// ���x
	float velocity;			// �����x

	bool isMoving;			// �ړ����̔���
	bool isJumping;			// �W�����v���̔���
	bool isClimbingUp;
	bool isClimbingDown;
};