//----------------------------------------------------------------------------
// 
// Project-HEW2020 [d3dutility.cpp]
// Direct3D�֘A���W���[��
// 
// Date:   2020/10/22
// Author: AT12D187_17_���i
// 
//----------------------------------------------------------------------------
#include "d3dutility.h"
#include "config.h"

//-----------------------------------------------------------------------------
// �O���[�o���ϐ��錾
//-----------------------------------------------------------------------------
static LPDIRECT3D9 g_pD3D = NULL;          // Direct3D�C���^�[�t�F�[�X
static LPDIRECT3DDEVICE9 g_pDevice = NULL; // Direct3D�f�o�C�X�C���^�[�t�F�[�X

// Direct3D�֘A�̏�����
bool D3DUtility_Init(HWND hWnd)
{
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (NULL == g_pD3D)
	{
		MessageBox(NULL, "Direct3D�C���^�[�t�F�[�X�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return false;
	}

    // �f�o�C�X�̎擾�ɕK�v�ȏ��\���̂̍쐬
    D3DPRESENT_PARAMETERS d3dpp = {};
    d3dpp.BackBufferWidth = SCREEN_WIDTH;                       // �o�b�N�o�b�t�@�̉���
    d3dpp.BackBufferHeight = SCREEN_HEIGHT;                     // �o�b�N�o�b�t�@�̏c��
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;                    // �o�b�N�o�b�t�@�̃t�H�[�}�b�g
    d3dpp.BackBufferCount = 1;                                  // �o�b�N�o�b�t�@�̐�
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;                   // �X���b�v���@�̐ݒ�
    d3dpp.Windowed = TRUE;                                      // �E�B���h�E or �t���X�N����
    d3dpp.EnableAutoDepthStencil = TRUE;                        // �[�x�o�b�t�@�E�X�e���V���o�b�t�@�̎g�p
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;                  // �[�x�o�b�t�@�E�X�e���V���o�b�t�@�̃t�H�[�}�b�g
    d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; // �t���X�N���[�����̃��t���b�V�����[�g�̎w��
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;   // ���t���b�V�����[�g��Present�����̊֌W
    //d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; // ���t���b�V�����[�g��Present�����̊֌W

    // Direct3D�f�o�C�X�̎擾
    HRESULT hr;
    hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pDevice);

    // HRESULT�^�ϐ��͐����⎸�s���l�Ƃ��ē����Ă���̂�
    // ���s�␬���������肷��ꍇ�̓}�N���𗘗p����@FAILED(hr) SUCCEEDED(hr)
    if (FAILED(hr)) MessageBox(NULL, "Direct3D�f�o�C�X�̎擾�Ɏ��s���܂���", "�G���[", MB_OK);

    // UV�A�h���b�V���O���[�h�̐ݒ�
    g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
    g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
    //g_pDevice->SetSamplerState(0, D3DSAMP_BORDERCOLOR, D3DCOLOR_RGBA(255, 255, 0, 255));

    // �e�N�X�`���t�B���_�����O�̐ݒ�
    g_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    g_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    g_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

    // �A���t�@�u�����h�̐ݒ�
    g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE); // �A���t�@�u�����h��L���ɂ���
    // �������c�`��F = ������`�悷��RGB * ������`�悷�郿 + ��ʂ�RGB * ( 1 - ������`�悷�郿 )
    g_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
    g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

    // ���_�J���[�ƃe�N�X�`���̃u�����h�̐ݒ�
    g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

    return true; // ����������
}

// Direct3D�֘A�̏I������
void D3DUtility_Uninit(void)
{
    if (g_pDevice)
    {
        g_pDevice->Release();
        g_pDevice = NULL;
    }
    if (g_pD3D)
    {
        g_pD3D->Release();
        g_pD3D = NULL;
    }
}

// Direct3D�̃f�o�C�X��n��
LPDIRECT3DDEVICE9 D3DUtility_GetDevice(void)
{
    return g_pDevice;
}