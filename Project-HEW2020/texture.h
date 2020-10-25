//----------------------------------------------------------------------------
// 
// Project-HEW2020 [texture.h]
// �e�N�X�`������
// 
// Date:   2020/10/22
// Author: AT12D187_17_���i
// 
//----------------------------------------------------------------------------

#pragma once

#include <d3d9.h>

#define TEXTURE_FILENAME_MAX (64) // �e�N�X�`���t�@�C�����ő啶����
#define INVALID_TEXTURE_ID (-1)	  // �����ȃe�N�X�`���Ǘ��ԍ�

// �e�N�X�`���Ǘ����W���[���̏�����
void Texture_Init(void);

// �e�N�X�`���Ǘ����W���[���̏I������
void Texture_Uninit(void);

// �e�N�X�`���t�@�C���̓ǂݍ��ݗ\��
//
// ����:pFileName ... �t�@�C����
//
// �߂�l:�e�N�X�`���Ǘ��ԍ��@�ő�Ǘ����𒴂��Ă����ꍇ��INVALID_TEXTURE_ID
//
int Texture_SetTextureLoadFile(const char* pFileName);

// �e�N�X�`���̓ǂݍ���
//
// �E�\�񂳂�Ă���t�@�C����ǂݍ��݂܂�
//
// �߂�l:�ǂݍ��߂Ȃ������t�@�C����
//
int Texture_Load(void);

// �e�N�X�`���̕������
//
// ����:textureIds[] ... ���������textureId��������int�^�z��̐擪�A�h���X
//		count		... �������e�N�X�`���̐�
void Texture_Release(int textureIds[], int count);

// �e�N�X�`���̑S���
void Texture_AllRelease(void);

// �e�N�X�`���̕��̎擾
//
// ����: �e�N�X�`���Ǘ��ԍ�
//
// �߂�l:�e�N�X�`���̕�
//
unsigned long Texture_GetTextureWidth(int textureId);

// �e�N�X�`���̍����̎擾
//
// ����: �e�N�X�`���Ǘ��ԍ�
//
// �߂�l:�e�N�X�`���̍���
//
unsigned long Texture_GetTextureHeight(int textureId);

// �e�N�X�`���C���^�[�t�F�[�X�|�C���^�̎擾
//
// ����:�e�N�X�`���Ǘ��ԍ�
//
// �߂�l:�e�N�X�`���C���^�[�t�F�[�X�|�C���^
//
LPDIRECT3DTEXTURE9 Texture_GetTexture(int textureId);