#pragma once

// C++��STL���g����悤�ɂ���
#include <string>
#include <vector>
#include <list>

// Direct3D�̃��C�u�������g�p�ł���悤�ɂ���
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

// Direct3D�̌^�E�N���X�E�֐��Ȃǂ��Ăׂ�悤�ɂ���
#include <d3d11.h>
#include <d3dcompiler.h>

// DirectXMath(���w���C�u����)���g�p�ł���悤�ɂ���
#include <DirectXMath.h>

// ComPtr���g�p�ł���悤�ɂ���
#include <wrl/client.h>
using Microsoft::WRL::ComPtr;

// ----------------------------------------------------------
// D3DManager�N���X
// ----------------------------------------------------------
class D3DManager
{
public:

	//--------------------------------------------
	// Direct3D�����������A�g�p�ł���悤�ɂ���
	// hWnd		: �E�B���h�E�n���h��
	// width	: ��ʂ̕�
	// height	: ��ʂ̍���
	//--------------------------------------------
	bool Initialize(HWND hWnd, int width, int height);


	// �C���X�^���X�쐬
	static void CreateInstance()
	{
		DeleteInstance();

		s_instance = new D3DManager();
	}

	// �C���X�^���X�폜
	static void DeleteInstance()
	{
		if (s_instance != nullptr)
		{
			delete s_instance;
			s_instance = nullptr;
		}
	}

	static D3DManager& GetInstance() { return *s_instance; } // �B��̃C���X�^���X���擾

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

	D3DManager() {} // �R���X�g���N�^�iprivate�j	
};

