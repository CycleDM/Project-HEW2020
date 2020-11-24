//----------------------------------------------------------------------------
// 
// Project-HEW2020 [sprite.cpp]
// �e�N�X�`���[�A�X�v���C�g����
// 
// Date:   2020/10/25
// Author: AT12D187_17_���i
// 
//----------------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include "sprite.h"
#include "d3dutility.h"

//----------------------------------------------------------------------------
// �O���[�o���ϐ��錾�A������
//----------------------------------------------------------------------------
LPDIRECT3DDEVICE9 Sprite::pDevice = NULL;
LPDIRECT3DVERTEXBUFFER9 Sprite::pVertexBuffer = NULL;
LPDIRECT3DINDEXBUFFER9 Sprite::pIndexBuffer = NULL;
bool Sprite::isDeviceInit = false;

//----------------------------------------------------------------------------
// �\���̐錾
//----------------------------------------------------------------------------
// ���_�\����
typedef struct Vertex2D_tag
{
	D3DXVECTOR4 Position;
	D3DCOLOR Color;
	D3DXVECTOR2 TextCoord;
} Vertex2D;
#define FVF_VERTEX2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//----------------------------------------------------------------------------
// �X�v���C�g�̊�{�N���X
//----------------------------------------------------------------------------
Sprite::Sprite()
{
	do
	{
		// �f�o�C�X�ƃo�b�t�@�̏������͈�񂾂��s��
		if (!isDeviceInit)
		{
			pDevice = D3DUtility::GetDevice();
			if (!pDevice)
			{
				MessageBox(NULL, "Direct3D�f�o�C�X�̎擾�Ɏ��s���܂���", "�G���[", MB_OK);
				// �f�o�C�X�̎擾�Ɏ��s�̂��߁A�i�܂Ȃ�
				break;
			}
			pDevice->CreateVertexBuffer(
				sizeof(Vertex2D) * 4,   // ���_�o�b�t�@�̗ʁi�o�C�g�j
				D3DUSAGE_WRITEONLY,     // �g����
				FVF_VERTEX2D,           // FVF
				D3DPOOL_DEFAULT,        // �������̊Ǘ����@
				&pVertexBuffer,			// �擾�����C���^�[�t�F�[�X�̃A�h���X���L�^���邽�߂̃|�C���^�̃A�h���X
				NULL
			);

			pDevice->CreateIndexBuffer(
				sizeof(WORD) * 6,
				D3DUSAGE_WRITEONLY,
				D3DFMT_INDEX16,
				D3DPOOL_DEFAULT,
				&pIndexBuffer,
				NULL
			);

			// ����������
			isDeviceInit = true;
		}
	} while (0);

	color = 0xffffffff;
	pTexture = NULL;
	txWidth = 0;
	txHeight = 0;
	filename[0] = 0;

	dx = dy = dw = dh = 0.0f;
	cx = cy = angle = 0.0f;
	tcx = tcy = 0;
	tcw = tch = 0;
	bHorizontalFlip = bVerticalFlip = false;
}

Sprite::~Sprite()
{
	if (pVertexBuffer)
	{
		pVertexBuffer->Release();
		pVertexBuffer = NULL;
	}
	if (pIndexBuffer)
	{
		pIndexBuffer->Release();
		pIndexBuffer = NULL;
	}
	if (pTexture)
	{
		pTexture->Release();
		pTexture = NULL;
	}
	filename[0] = 0;
	txWidth = 0;
	txHeight = 0;
}

void Sprite::LoadTexture(const char* pFileName)
{
	strcpy(filename, pFileName);

	// �e�N�X�`���̓ǂݍ���
	HRESULT hr = D3DXCreateTextureFromFile(pDevice, filename, &pTexture);
	if (SUCCEEDED(hr))
	{
		// �e�N�X�`���̉𑜓x�i���E�����j�̒���
		D3DXIMAGE_INFO info;
		D3DXGetImageInfoFromFile(filename, &info);
		txWidth = info.Width;
		txHeight = info.Height;
	}
	else
	{
		char msg[128] = {};
		strcat(msg, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���\n�t�@�C�����F");
		strcat(msg, filename);
		MessageBox(NULL, msg, "�G���[", MB_OK);
	}
}

unsigned long Sprite::GetTextureWidth(void)
{
	return txWidth;
}
unsigned long Sprite::GetTextureHeight(void)
{
	return txHeight;
}

LPDIRECT3DTEXTURE9 Sprite::GetTexture(void)
{
	return pTexture;
}

void Sprite::SetColor(D3DCOLOR color)
{
	this->color = color;
}

//----------------------------------------------------------------------------
// �X�v���C�g�h���N���X - SpriteNormal
//----------------------------------------------------------------------------
SpriteNormal::SpriteNormal()
{
	// ����������
	Init();
}
// �I�[�o���[�h
SpriteNormal::SpriteNormal(const char* pFileName)
{
	// ����������
	Init();
	// �e�N�X�`���̓ǂݍ���
	LoadTexture(pFileName);
}

SpriteNormal::~SpriteNormal()
{

}

void SpriteNormal::Init(void)
{
	dx = dy = dw = dh = 0.0f;
	cx = cy = angle = 0.0f;
	tcx = tcy = 0;
	tcw = tch = 0;
	bHorizontalFlip = bVerticalFlip = false;
}

void SpriteNormal::Draw(void)
{
	// �f�o�C�X��FVF�̐ݒ������
	pDevice->SetFVF(FVF_VERTEX2D);

	// �f�o�C�X�Ƀe�N�X�`���̐ݒ������
	pDevice->SetTexture(0, pTexture);

	// �|���S���̃T�C�Y�̓e�N�X�`���T�C�Y
	unsigned long w = GetTextureWidth();
	unsigned long h = GetTextureHeight();

	// �؂�����W��0��������e�N�X�`���̃f�t�H���g�T�C�Y�ɐݒ�
	if (!tcw || !tch)
	{
		tcw = GetTextureWidth();
		tch = GetTextureHeight();
	}
	// �|���S���T�C�Y��0��������e�N�X�`���̃f�t�H���g�T�C�Y�ɐݒ�
	if (!dw || !dh)
	{
		dw = (float)GetTextureWidth();
		dh = (float)GetTextureHeight();
	}

	// �e�N�X�`���؂���UV���W
	float u0, u1, v0, v1;
	u0 = (float)tcx / w;
	u1 = (float)(tcx + tcw) / w;
	v0 = (float)tcy / h;
	v1 = (float)(tcy + tch) / h;
	// UV���]����
	if (bHorizontalFlip)
	{
		u0 = (float)(tcx + tcw) / w;
		u1 = (float)tcx / w;
	}
	if (bVerticalFlip)
	{
		v0 = (float)(tcy + tch) / h;
		v1 = (float)tcy / h;
	}

	// ���_�f�[�^
	Vertex2D v[] = {
		{D3DXVECTOR4(-0.5f, -0.5f, 1.0f, 1.0f), color, D3DXVECTOR2(u0, v0)},
		{D3DXVECTOR4(dw - 0.5f, -0.5f, 1.0f, 1.0f), color, D3DXVECTOR2(u1, v0)},
		{D3DXVECTOR4(-0.5f, dh - 0.5f, 1.0f, 1.0f), color, D3DXVECTOR2(u0, v1)},
		{D3DXVECTOR4(dw - 0.5f, dh - 0.5f, 1.0f, 1.0f), color, D3DXVECTOR2(u1, v1)} };

	// ���s�ړ��s��
	D3DXMATRIX mtxTranslationC;
	D3DXMatrixTranslation(&mtxTranslationC, -cx, -cy, 0.0f);

	D3DXMATRIX mtxTranslationI;
	D3DXMatrixTranslation(&mtxTranslationI, cx + dx, cy + dy, 0.0f);

	// ��]�s��
	D3DXMATRIX mtxRotation;
	D3DXMatrixRotationZ(&mtxRotation, angle);

	D3DXMATRIX mtxScale;
	D3DXMatrixScaling(&mtxScale, 1.0f, 1.0f, 1.0f);

	// �s��̍���
	D3DXMATRIX mtxWorld;
	mtxWorld = mtxTranslationC * mtxScale * mtxRotation * mtxTranslationI;

	// ���W�ϊ�
	for (int i = 0; i < 4; i++)
	{
		D3DXVec4Transform(&v[i].Position, &v[i].Position, &mtxWorld);
	}

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2D));
}

void SpriteNormal::SetDrawPos(float dx, float dy)
{
	this->dx = dx;
	this->dy = dy;
}
void SpriteNormal::SetCutPos(int tcx, int tcy)
{
	this->tcx = tcx;
	this->tcy = tcy;
}
void SpriteNormal::SetCutRange(int tcw, int tch)
{
	this->tcw = tcw;
	this->tch = tch;
}

int SpriteNormal::GetCutWidth(void)
{
	return tcw;
}

int SpriteNormal::GetCutHeight(void)
{
	return tch;
}

void SpriteNormal::SetPolygonSize(float dw, float dh)
{
	this->dw = dw;
	this->dh = dh;
}
float SpriteNormal::GetPolygonWidth(void)
{
	return dw;
}
float SpriteNormal::GetPolygonHeight(void)
{
	return dh;
}

void SpriteNormal::SetRotation(float cx, float cy, float angle)
{
	this->cx = cx;
	this->cy = cy;
	this->angle = angle;
}
void SpriteNormal::SetHorizontalFlip(bool bFlip)
{
	this->bHorizontalFlip = bFlip;
}
void SpriteNormal::SetVerticalFlip(bool bFlip)
{
	this->bVerticalFlip = bFlip;
}