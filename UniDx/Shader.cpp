#include "Shader.h"

#include <d3d11.h>

#include "D3DManager.h"
#include "Debug.h"

#pragma comment(lib, "d3dcompiler.lib")

namespace UniDx
{

bool Shader::Compile(std::wstring filePath)
{
	// 頂点シェーダーを読み込み＆コンパイル
	ComPtr<ID3DBlob> compiledVS;
	if (FAILED(D3DCompileFromFile(filePath.c_str(), nullptr, nullptr, "VS", "vs_5_0", 0, 0, &compiledVS, nullptr)))
	{
		Debug::Log(L"頂点シェーダーのコンパイルエラー");
		return false;
	}
	// ピクセルシェーダーを読み込み＆コンパイル
	ComPtr<ID3DBlob> compiledPS;
	if (FAILED(D3DCompileFromFile(filePath.c_str(), nullptr, nullptr, "PS", "ps_5_0", 0, 0, &compiledPS, nullptr)))
	{
		Debug::Log(L"ピクセルシェーダーシェーダーのコンパイルエラー");
		return false;
	}

	// 頂点シェーダー作成
	if (FAILED(D3DManager::instance->GetDevice()->CreateVertexShader(compiledVS->GetBufferPointer(), compiledVS->GetBufferSize(), nullptr, &m_vertex)))
	{
		Debug::Log(L"頂点シェーダーの作成エラー");
		return false;
	}
	// ピクセルシェーダー作成
	if (FAILED(D3DManager::instance->GetDevice()->CreatePixelShader(compiledPS->GetBufferPointer(), compiledPS->GetBufferSize(), nullptr, &m_pixel)))
	{
		Debug::Log(L"ピクセルシェーダーの作成エラー");
		return false;
	}

	// １頂点の詳細な情報
	std::vector<D3D11_INPUT_ELEMENT_DESC> layout = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,		0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	// 頂点インプットレイアウト作成
	if (FAILED(D3DManager::instance->GetDevice()->CreateInputLayout(&layout[0], (UINT)layout.size(), compiledVS->GetBufferPointer(), compiledVS->GetBufferSize(), &m_inputLayout)))
	{
		Debug::Log(L"頂点インプットレイアウトの作成エラー");
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