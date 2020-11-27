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

//----------------------------------------------------------------------------
// �X�v���C�g�N���X�i���ۃN���X�j
//----------------------------------------------------------------------------
class Sprite
{
public:
	Sprite();
	virtual ~Sprite();

	void LoadTexture(const char*);
	unsigned long GetTextureWidth(void);
	unsigned long GetTextureHeight(void);
	LPDIRECT3DTEXTURE9 GetTexture(void);

	//----------------------------------------------------------
	// �X�v���C�g��`��Ɋ֘A����֐�
	// �������z�֐��͕K���I�[�o���C�h���Ă�������
	// �V�����@�\�𗘗p�������ꍇ�A�h���N���X����V�����֐�������Ă�������
	//----------------------------------------------------------
	// �F�ݒ�
	virtual void SetColor(D3DCOLOR);
	// �X�v���C�g�`������s
	virtual void Draw(void) = 0;
	// �X�v���C�g�`��̍��W���w��
	// ����:
	//	dx	... �`����Wx�i����w��j
	//	dy	... �`����Wy�i����w��j
	virtual void SetDrawPos(float dx, float dy) = 0;
	// �e�N�X�`���̐؂�����W���W���w��
	// ����:
	//	tcx	... �e�N�X�`���̐؂�����Wx
	//	tcy	... �e�N�X�`���̐؂�����Wy
	virtual void SetCutPos(int tcx, int tcy) = 0;
	// �e�N�X�`���̐؂�����W���W���擾
	virtual D3DXVECTOR2 GetCutPos(void) = 0;
	// �e�N�X�`���̐؂��蕝���w��
	// ����:
	//	tcw	... �e�N�X�`���̐؂��蒷��
	//	tch	... �e�N�X�`���̐؂��荂��
	virtual void SetCutRange(int tcw, int tch) = 0;
	// �e�N�X�`���̐؂��蕝���擾
	virtual int GetCutWidth(void) = 0;
	virtual int GetCutHeight(void) = 0;
	// �|���S���T�C�Y���w��
	// ����:
	//	dw	... �|���S���T�C�Y����
	//	dh	... �|���S���T�C�Y����
	virtual void SetPolygonSize(float dw, float dh) = 0;
	// �|���S���T�C�Y���擾
	virtual float GetPolygonWidth(void) = 0;
	virtual float GetPolygonHeight(void) = 0;
	// �e�N�X�`���̉�]�p�x���w��
	// ����:
	//	cx	... ��]�̒��S���Wx
	//	cy	... ��]�̒��S���Wy
	//	angle	... �e�N�X�`���̉�]�p�x
	//	�f�t�H���g�͂��ׂ� 0.0f -> �|���S���̍���
	virtual void SetRotation(float cx, float cy, float angle) = 0;
	// �e�N�X�`���̔��]�����i���E�j
	// ����:
	//	true	... ���]����
	//	false	... ���]���Ȃ�
	//	�f�t�H���g�͔��]���Ȃ����
	virtual void SetHorizontalFlip(bool bFlip) = 0;
	// �e�N�X�`���̔��]�����i�㉺�j
	// ����:
	//	true	... ���]����
	//	false	... ���]���Ȃ�
	//	�f�t�H���g�͔��]���Ȃ����
	virtual void SetVerticalFlip(bool bFlip) = 0;
	// �����o�[�ϐ��̏���������
	virtual void Init(void) = 0;

protected:
	// �h���N���X�Ƌ��ʂ̕ϐ��Ȃ̂�static�Ɏw��
	static LPDIRECT3DDEVICE9 pDevice;
	static LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;
	static LPDIRECT3DINDEXBUFFER9 pIndexBuffer;
	static bool isDeviceInit;

	LPDIRECT3DTEXTURE9 pTexture;
	D3DCOLOR color;
	char filename[TEXTURE_FILENAME_MAX];
	unsigned long txWidth, txHeight;

protected:
	float dx, dy;
	float dw, dh;
	float cx, cy;
	float angle;
	int tcx, tcy;
	int tcw, tch;
	bool bHorizontalFlip;
	bool bVerticalFlip;
};

//----------------------------------------------------------------------------
// �X�v���C�g�h���N���X - SpriteNormal
//----------------------------------------------------------------------------
class SpriteNormal : public Sprite
{
public:
	SpriteNormal();
	SpriteNormal(const char* pFileName);
	~SpriteNormal();

	// �X�v���C�g�`��̍��W���w��
	virtual void SetDrawPos(float dx, float dy);
	// �e�N�X�`���̐؂�����W���W���w��
	virtual void SetCutPos(int tcx, int tcy);
	// �e�N�X�`���̐؂��蕝���w��
	virtual void SetCutRange(int tcw, int tch);
	// �e�N�X�`���̐؂��蕝���擾
	virtual D3DXVECTOR2 GetCutPos(void);
	// �|���S���T�C�Y���w��
	virtual void SetPolygonSize(float dw, float dh);
	// �e�N�X�`���̐؂��蕝���擾
	virtual int GetCutWidth(void);
	virtual int GetCutHeight(void);
	// �|���S���T�C�Y���擾
	virtual float GetPolygonWidth(void);
	virtual float GetPolygonHeight(void);
	// �e�N�X�`���̉�]�p�x���w��
	virtual void SetRotation(float cx, float cy, float angle);
	// �e�N�X�`�����]�̐ݒ�i���E�j
	virtual void SetHorizontalFlip(bool bFlip);
	// �e�N�X�`�����]�̐ݒ�i�㉺�j
	virtual void SetVerticalFlip(bool bFlip);
	// �X�v���C�g�`������s
	virtual void Draw(void);
	// �����o�[�ϐ��̏���������
	virtual void Init(void);
};
