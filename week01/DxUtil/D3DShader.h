#pragma once

// C++��STL
#include <string>

// Direct3D�̌^�E�N���X�E�֐��Ȃ�
#include <d3d11.h>
#include <d3dcompiler.h>

// ComPtr
#include <wrl/client.h>
using Microsoft::WRL::ComPtr;

// ���̃��C�u�������ʋ@�\
#include "DxUtilCommon.h"


// ----------------------------------------------------------
// D3DShader�N���X
// ----------------------------------------------------------
class D3DShader
{
public:
	// �V�F�[�_�[�̃p�X���w�肵�ăR���p�C��
	bool Compile(const wchar_t* filePath);

	// �`��̂��߁AD3DDeviceContext�ɂ��̃V�F�[�_�[���Z�b�g
	void SetToContext();

private:
	ComPtr<ID3D11VertexShader>	m_vertex = nullptr;	// ���_�V�F�[�_�[
	ComPtr<ID3D11PixelShader>	m_pixel = nullptr;	// �s�N�Z���V�F�[�_�[
	ComPtr<ID3D11InputLayout>	m_inputLayout = nullptr;// ���̓��C�A�E�g
};

