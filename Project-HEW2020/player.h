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
	void SetPosition(float x, float y);
	// �v���C���[�̍��W���擾
	D3DXVECTOR2 GetPosition(void);
	// �v���C���[�̗̑͂��擾
	int GetHealth(void);
	// �v���C���[�̃X�R�A���擾
	int GetScore(void);

	float GetSpeed(void);
	D3DXVECTOR2 GetDirection(void);

	void MoveLeft(void);
	void MoveRight(void);
	void SetJump(void);

private:
	D3DXVECTOR2 pos;	// ���W
	D3DXVECTOR2 dirc;	// ����
	float speed;		// ���x
	float velocity;		// �����x
	int hp;				// �̗�
	int score;			// �X�R�A
	bool bJumping;		// �W�����v���̔���
};