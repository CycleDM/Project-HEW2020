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

class Player
{
public:
	Player();
	~Player();

	void Init(void);
	void Update(void);
	void Draw(void);
	void SetPos(float x, float y);
	D3DXVECTOR2 GetPos(void);

private:
	D3DXVECTOR2 pos;	// ���W
	D3DXVECTOR2 dirc;	// ����
	float speed;		// ���x
	int hp;				// �̗�
	int score;			// �X�R�A
};