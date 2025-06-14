#pragma once

// Direct3D�̃��C�u�������g�p�ł���悤�ɂ���
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

// Direct3D�̌^�E�N���X�E�֐��Ȃǂ��Ăׂ�悤�ɂ���
#include <d3d11.h>
#include <d3dcompiler.h>

// ComPtr���g�p�ł���悤�ɂ���
#include <wrl/client.h>
using Microsoft::WRL::ComPtr;

#include "Singleton.h"

namespace UniDx{

// ----------------------------------------------------------
// D3DManager�N���X
// ----------------------------------------------------------
class D3DManager : public Singleton<D3DManager>
{
public:

	//--------------------------------------------
	// Direct3D�����������A�g�p�ł���悤�ɂ���
	// hWnd		: �E�B���h�E�n���h��
	// width	: ��ʂ̕�
	// height	: ��ʂ̍���
	//--------------------------------------------
	bool Initialize(HWND hWnd, int width, int height);

	const ComPtr<ID3D11Device>&			GetDevice() const { return m_device; }
	const ComPtr<ID3D11DeviceContext>&	GetContext() const { return m_context; }

	// �o�b�N�o�b�t�@�����_�[�^�[�Q�b�g���N���A
	void Clear(float r, float g, float b, float a);

	// �o�b�N�o�b�t�@�̓��e����ʂɕ\��
	void Present()
	{
		m_swapChain->Present(1, 0);
	}

private:
	static D3DManager* s_instance; // �C���X�^���X	

	ComPtr<ID3D11Device>			m_device; // Direct3D�f�o�C�X
	ComPtr<ID3D11DeviceContext>		m_context; // Direct3D�f�o�C�X�R���e�L�X�g
	ComPtr<IDXGISwapChain>			m_swapChain; // �X���b�v�`�F�C��
	ComPtr<ID3D11RenderTargetView>	m_renderTarget; // �o�b�N�o�b�t�@�[��RT�r���[
};

} // UniDx
