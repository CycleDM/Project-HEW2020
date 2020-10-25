//----------------------------------------------------------------------------
// 
// Project-HEW2020 [texture.cpp]
// �e�N�X�`������
// 
// Date:   2020/10/22
// Author: AT12D187_17_���i
// 
//----------------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <d3dx9.h>
#include <string.h>
#include "texture.h"
#include "d3dutility.h"

//-----------------------------------------------------------------------------
// �萔
//-----------------------------------------------------------------------------
#define TEXTURE_MAX (1024) // �e�N�X�`���Ǘ��ő吔

//-----------------------------------------------------------------------------
// �\���̐錾
//-----------------------------------------------------------------------------
typedef struct Texture_tag
{
	LPDIRECT3DTEXTURE9 pTexture;
	unsigned long width;
	unsigned long height;
	char filename[TEXTURE_FILENAME_MAX];
} Texture;

//-----------------------------------------------------------------------------
// �O���[�o���ϐ��錾
//-----------------------------------------------------------------------------
// �e�N�X�`���Ǘ��e�[�u��
static Texture g_Textures[TEXTURE_MAX];

// �e�N�X�`���Ǘ����W���[���̏�����
void Texture_Initialize(void)
{
	// �e�N�X�`���Ǘ��e�[�u���̏�����
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		g_Textures[i].pTexture = NULL;
		g_Textures[i].width = 0;
		g_Textures[i].height = 0;
		g_Textures[i].filename[0] = 0;
	}
}

// �e�N�X�`���Ǘ����W���[���̏I������
void Texture_Finalize(void)
{
	Texture_AllRelease();
}

// �e�N�X�`���t�@�C���̓ǂݍ��ݗ\��
//
// ����:pFileName ... �t�@�C����
//
// �߂�l:�e�N�X�`���Ǘ��ԍ��@�ő�Ǘ����𒴂��Ă����ꍇ��INVALID_TEXTURE_ID
//
int Texture_SetTextureLoadFile(const char* pFileName)
{
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		// �e�[�u�����󂢂Ă�����X�L�b�v
		if (g_Textures[i].filename[0] == 0)
		{
			continue;
		}
		// ���łɎw��̃t�@�C�����\�񂳂�Ă��邩�H
		if (strcmp(pFileName, g_Textures[i].filename) == 0)
		{
			// �\�񂳂�Ă���I
			return i;
		}
	}

	// �V�K�\��
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		// �e�[�u�����g�p����������X�L�b�v
		if (g_Textures[i].filename[0] != 0)
		{
			continue;
		}

		// �t�@�C�������e�[�u���ɃR�s�[����
		strcpy(g_Textures[i].filename, pFileName);
		return i;
	}

	return INVALID_TEXTURE_ID;
}

// �e�N�X�`���̓ǂݍ���
//
// �E�\�񂳂�Ă���t�@�C����ǂݍ��݂܂�
//
// �߂�l:�ǂݍ��߂Ȃ������t�@�C����
//
int Texture_Load(void)
{
	int err_count = 0;

	// Direct3D�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = D3DUtility_GetDevice();
	if (!pDevice)
	{
		return -1;
	}

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (g_Textures[i].filename[0] == 0)
		{
			// ��̃e�[�u��
			continue;
		}

		if (g_Textures[i].pTexture != NULL)
		{
			// ���łɓǂݍ��܂�Ă���
			continue;
		}

		// �e�N�X�`���̓ǂݍ���
		HRESULT hr = D3DXCreateTextureFromFile(pDevice, g_Textures[i].filename, &g_Textures[i].pTexture);
		if (FAILED(hr))
		{
			// �f�o�C�X�̎擾�Ɏ��s
			err_count++;
		}
		else
		{
			// �e�N�X�`���̉𑜓x�i���E�����j�̒���
			D3DXIMAGE_INFO info;
			D3DXGetImageInfoFromFile(g_Textures[i].filename, &info);
			g_Textures[i].width = info.Width;
			g_Textures[i].height = info.Height;
		}
	}

	return err_count; // �ǂݍ��߂Ȃ�������
}

// �e�N�X�`���̕������
//
// ����:textureIds[] ... ���������textureId��������int�^�z��̐擪�A�h���X
//		count		... �������e�N�X�`���̐�
void Texture_Release(int textureIds[], int count)
{
	for (int i = 0; i < count; i++)
	{
		if (g_Textures[textureIds[i]].pTexture)
		{
			g_Textures[textureIds[i]].pTexture->Release();
			g_Textures[textureIds[i]].pTexture = NULL;
		}
		g_Textures[textureIds[i]].filename[0] = 0;
		g_Textures[textureIds[i]].width = 0;
		g_Textures[textureIds[i]].height = 0;
	}
}

// �e�N�X�`���̑S���
void Texture_AllRelease(void)
{
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (g_Textures[i].pTexture)
		{
			g_Textures[i].pTexture->Release();
			g_Textures[i].pTexture = NULL;
		}
		g_Textures[i].filename[0] = 0;
		g_Textures[i].width = 0;
		g_Textures[i].height = 0;
	}
}

// �e�N�X�`���̕��̎擾
//
// ����: �e�N�X�`���Ǘ��ԍ�
//
// �߂�l:�e�N�X�`���̕�
//
unsigned long Texture_GetTextureWidth(int textureId)
{
	return g_Textures[textureId].width;
}

// �e�N�X�`���̍����̎擾
//
// ����: �e�N�X�`���Ǘ��ԍ�
//
// �߂�l:�e�N�X�`���̍���
//
unsigned long Texture_GetTextureHeight(int textureId)
{
	return g_Textures[textureId].height;
}

// �e�N�X�`���C���^�[�t�F�[�X�|�C���^�̎擾
//
// ����:�e�N�X�`���Ǘ��ԍ�
//
// �߂�l:�e�N�X�`���C���^�[�t�F�[�X�|�C���^
//
LPDIRECT3DTEXTURE9 Texture_GetTexture(int textureId)
{
	return g_Textures[textureId].pTexture;
}