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
	pDevice = D3DUtility_GetDevice();
	pVertexBuffer = NULL;
	pIndexBuffer = NULL;
	if (!pDevice)
	{
		MessageBox(NULL, "Direct3D�f�o�C�X�̎擾�Ɏ��s���܂���", "�G���[", MB_OK);
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
	color = 0xffffffff;
	pTexture = NULL;
	txWidth = 0;
	txHeight = 0;
	filename[0] = 0;
}

Sprite::~Sprite()
{
	if (pVertexBuffer)
	{
		pVertexBuffer->Release();
		pVertexBuffer = NULL;
	}
	pTexture->Release();
	pTexture = NULL;
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
		const char* msg = strcpy(filename, "\n�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���");
		MessageBox(NULL, msg, "�G���[", MB_OK);
	}
}

unsigned long Sprite::GetTextureWidth()
{
	return txWidth;
}
unsigned long Sprite::GetTextureHeight()
{
	return txHeight;
}

LPDIRECT3DTEXTURE9 Sprite::GetTexture()
{
	return pTexture;
}

void Sprite::SetColor(D3DCOLOR color_to_set)
{
	color = color_to_set;
}


//----------------------------------------------------------------------------
// �X�v���C�g�h���N���X - SpriteNormal
//----------------------------------------------------------------------------
SpriteNormal::SpriteNormal()
{
	dx = dy = tcx = tcy = tcw = tch = 0;
}

void SpriteNormal::Draw(void)
{
	// �f�o�C�X��FVF�̐ݒ������
	pDevice->SetFVF(FVF_VERTEX2D);

	// �f�o�C�X�Ƀe�N�X�`���̐ݒ������
	pDevice->SetTexture(0, GetTexture());

	// �|���S���̃T�C�Y�̓e�N�X�`���T�C�Y
	unsigned long w = GetTextureWidth();
	unsigned long h = GetTextureHeight();

	// �e�N�X�`���؂���UV���W
	float u0 = (float)tcx / w;
	float v0 = (float)tcy / h;
	float u1 = (float)(tcx + tcw) / w;
	float v1 = (float)(tcy + tch) / h;

	// ���_�f�[�^
	Vertex2D v[] = {
		{D3DXVECTOR4(dx - 0.5f, dy - 0.5f, 1.0f, 1.0f), color, D3DXVECTOR2(u0, v0)},
		{D3DXVECTOR4(dx + tcw - 0.5f, dy - 0.5f, 1.0f, 1.0f), color, D3DXVECTOR2(u1, v0)},
		{D3DXVECTOR4(dx - 0.5f, dy + tch - 0.5f, 1.0f, 1.0f), color, D3DXVECTOR2(u0, v1)},
		{D3DXVECTOR4(dx + tcw - 0.5f, dy + tch - 0.5f, 1.0f, 1.0f), color, D3DXVECTOR2(u1, v1)} };

	Vertex2D* pV;
	pVertexBuffer->Lock(0, 0, (void**)&pV, 0);
	memcpy(pV, v, sizeof(v));
	pVertexBuffer->Unlock();

	// �f�o�C�X�ɗ��p���钸�_�o�b�t�@���w�肷��
	pDevice->SetStreamSource(0, pVertexBuffer, 0, sizeof(Vertex2D));

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

void SpriteNormal::SetDrawPos(float x, float y)
{
	dx = x;
	dy = y;
}

void SpriteNormal::SetCutPos(float x, float y)
{
	tcx = x;
	tcy = y;
}

void SpriteNormal::SetCutSize(float width, float height)
{
	tcw = width;
	tch = height;
}