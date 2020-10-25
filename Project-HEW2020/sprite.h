//----------------------------------------------------------------------------
// 
// Project-HEW2020 [sprite.h]
// �e�N�X�`���[�A�X�v���C�g����
// 
// Date:   2020/10/25
// Author: AT12D187_17_���i
// 
//----------------------------------------------------------------------------
#pragma once

#include <d3dx9.h>

#define TEXTURE_FILENAME_MAX (64)	// �e�N�X�`���t�@�C�����ő啶����
#define TEXTURE_MAX (1024)			// �e�N�X�`���Ǘ��ő吔

class Sprite
{
public:
	Sprite();
	virtual ~Sprite();

	void LoadTexture(const char* pFileName);
	unsigned long GetTextureWidth(void);
	unsigned long GetTextureHeight(void);
	LPDIRECT3DTEXTURE9 GetTexture(void);

	// �X�v���C�g��`��Ɋ֘A����֐��i�������z�֐��𗘗p����΁A�K���I�[�o���C�h���Ă��������j
	virtual void Draw(void) = 0;
	virtual void SetDrawPos(float x, float y) = 0;
	virtual void SetCutPos(float x, float y) = 0;
	virtual void SetCutSize(float width, float height) = 0;
	virtual void SetColor(D3DCOLOR color_to_set);

protected:
	LPDIRECT3DDEVICE9 pDevice;
	LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;
	LPDIRECT3DINDEXBUFFER9 pIndexBuffer;
	LPDIRECT3DTEXTURE9 pTexture;
	D3DCOLOR color;
	unsigned long txWidth, txHeight;
	char filename[TEXTURE_FILENAME_MAX];
};

class SpriteNormal : public Sprite
{
public:
	//SpriteNormal();
	//~SpriteNormal();

	// �X�v���C�g�`��̊e��l���w��
	//
	// ����:
	//	dx		... �`����Wx�i����w��j
	//	dy		... �`����Wy�i����w��j
	//	tcx		... �e�N�X�`���̐؂�����Wx
	//	tcy		... �e�N�X�`���̐؂�����Wy
	//	tcw		... �e�N�X�`���̐؂��蕝
	//	tch		... �e�N�X�`���̐؂��荂��
	void SetDrawPos(float x, float y);
	void SetCutPos(float x, float y);
	void SetCutSize(float width, float height);
	void Draw(void);
private:
	float dx, dy;
	int tcx,tcy, tcw, tch;
};