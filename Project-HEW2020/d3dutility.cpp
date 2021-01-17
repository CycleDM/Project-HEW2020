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
LPDIRECT3D9 D3DUtility::pD3D = NULL;          // Direct3D�C���^�[�t�F�[�X
LPDIRECT3DDEVICE9 D3DUtility::pDevice = NULL; // Direct3D�f�o�C�X�C���^�[�t�F�[�X

// Direct3D�֘A�̏�����
bool D3DUtility::Init(HWND hWnd, HINSTANCE hInstance)
{
	pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (NULL == pD3D)
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
    //d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;   // ���t���b�V�����[�g��Present�����̊֌W
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; // ���t���b�V�����[�g��Present�����̊֌W

    // Direct3D�f�o�C�X�̎擾
    HRESULT hr;
    hr = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &pDevice);

    // HRESULT�^�ϐ��͐����⎸�s���l�Ƃ��ē����Ă���̂�
    // ���s�␬���������肷��ꍇ�̓}�N���𗘗p����@FAILED(hr) SUCCEEDED(hr)
    if (FAILED(hr)) MessageBox(NULL, "Direct3D�f�o�C�X�̎擾�Ɏ��s���܂���", "�G���[", MB_OK);

    // UV�A�h���b�V���O���[�h�̐ݒ�
    pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
    pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
    //g_pDevice->SetSamplerState(0, D3DSAMP_BORDERCOLOR, D3DCOLOR_RGBA(255, 255, 0, 255));

    // �e�N�X�`���t�B���_�����O�̐ݒ�
    pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
    pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
    pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
    //g_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    //g_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
    //g_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
    pDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 16);

    // �A���t�@�u�����h�̐ݒ�
    pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE); // �A���t�@�u�����h��L���ɂ���
    // �������c�`��F = ������`�悷��RGB * ������`�悷�郿 + ��ʂ�RGB * ( 1 - ������`�悷�郿 )
    pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
    pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

    // ���_�J���[�ƃe�N�X�`���̃u�����h�̐ݒ�
    pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

    return true; // ����������
}

// Direct3D�֘A�̏I������
void D3DUtility::Uninit(void)
{
    if (pDevice)
    {
        pDevice->Release();
        pDevice = NULL;
    }
    if (pD3D)
    {
        pD3D->Release();
        pD3D = NULL;
    }
}

// Direct3D�̃f�o�C�X��n��
LPDIRECT3DDEVICE9 D3DUtility::GetDevice(void)
{
    return pDevice;
}