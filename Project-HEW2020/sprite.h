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

	// �X�v���C�g��`��Ɋ֘A����֐�
	// �������z�֐��͕K���I�[�o���C�h���Ă�������
	// �V�����@�\�𗘗p�������ꍇ�A�h���N���X����V�����֐�������Ă�������
	virtual void Draw(void) = 0;
	virtual void SetDrawPos(float, float) = 0;
	virtual void SetColor(D3DCOLOR color_to_set);

protected:
	static LPDIRECT3DDEVICE9 pDevice;
	static LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;
	static LPDIRECT3DINDEXBUFFER9 pIndexBuffer;
	LPDIRECT3DTEXTURE9 pTexture;
	D3DCOLOR color;
	unsigned long txWidth, txHeight;
	char filename[TEXTURE_FILENAME_MAX];
};

class SpriteNormal : public Sprite
{
public:
	SpriteNormal();
	//~SpriteNormal();

	// �X�v���C�g�`��̍��W���w��
	// ����:
	//	x->dx	... �`����Wx�i����w��j
	//	y->dy	... �`����Wy�i����w��j
	virtual void SetDrawPos(float x, float y);
	// �e�N�X�`���̐؂�����W���W���w��
	// ����:
	//	x->tcx	... �e�N�X�`���̐؂�����Wx
	//	y->tcy	... �e�N�X�`���̐؂�����Wy
	virtual void SetCutPos(float x, float y);
	// �e�N�X�`���̐؂��蕝���w��
	// ����:
	//	width->tcw	... �e�N�X�`���̐؂��蒷��
	//	height->tcy	... �e�N�X�`���̐؂��荂��
	virtual void SetCutSize(float width, float height);
	// �X�v���C�g�`������s
	virtual void Draw(void);
protected:
	float dx, dy, tcx, tcy, tcw, tch;
};