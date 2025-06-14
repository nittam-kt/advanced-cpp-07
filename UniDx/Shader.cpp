#include "Shader.h"

#include <d3d11.h>

#include "D3DManager.h"
#include "Debug.h"

#pragma comment(lib, "d3dcompiler.lib")

namespace UniDx
{

bool Shader::Compile(std::wstring filePath)
{
	// ���_�V�F�[�_�[��ǂݍ��݁��R���p�C��
	ComPtr<ID3DBlob> compiledVS;
	if (FAILED(D3DCompileFromFile(filePath.c_str(), nullptr, nullptr, "VS", "vs_5_0", 0, 0, &compiledVS, nullptr)))
	{
		Debug::Log(L"���_�V�F�[�_�[�̃R���p�C���G���[");
		return false;
	}
	// �s�N�Z���V�F�[�_�[��ǂݍ��݁��R���p�C��
	ComPtr<ID3DBlob> compiledPS;
	if (FAILED(D3DCompileFromFile(filePath.c_str(), nullptr, nullptr, "PS", "ps_5_0", 0, 0, &compiledPS, nullptr)))
	{
		Debug::Log(L"�s�N�Z���V�F�[�_�[�V�F�[�_�[�̃R���p�C���G���[");
		return false;
	}

	// ���_�V�F�[�_�[�쐬
	if (FAILED(D3DManager::instance->GetDevice()->CreateVertexShader(compiledVS->GetBufferPointer(), compiledVS->GetBufferSize(), nullptr, &m_vertex)))
	{
		Debug::Log(L"���_�V�F�[�_�[�̍쐬�G���[");
		return false;
	}
	// �s�N�Z���V�F�[�_�[�쐬
	if (FAILED(D3DManager::instance->GetDevice()->CreatePixelShader(compiledPS->GetBufferPointer(), compiledPS->GetBufferSize(), nullptr, &m_pixel)))
	{
		Debug::Log(L"�s�N�Z���V�F�[�_�[�̍쐬�G���[");
		return false;
	}

	// �P���_�̏ڍׂȏ��
	std::vector<D3D11_INPUT_ELEMENT_DESC> layout = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,		0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	// ���_�C���v�b�g���C�A�E�g�쐬
	if (FAILED(D3DManager::instance->GetDevice()->CreateInputLayout(&layout[0], (UINT)layout.size(), compiledVS->GetBufferPointer(), compiledVS->GetBufferSize(), &m_inputLayout)))
	{
		Debug::Log(L"���_�C���v�b�g���C�A�E�g�̍쐬�G���[");
		return false;
	}

	return true;
}

void Shader::SetToContext()
{
	D3DManager::instance->GetContext()->VSSetShader(m_vertex.Get(), 0, 0);
	D3DManager::instance->GetContext()->PSSetShader(m_pixel.Get(), 0, 0);
	D3DManager::instance->GetContext()->IASetInputLayout(m_inputLayout.Get());
}

}