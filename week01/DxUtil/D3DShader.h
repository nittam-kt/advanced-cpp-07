#pragma once

// C++のSTL
#include <string>

// Direct3Dの型・クラス・関数など
#include <d3d11.h>
#include <d3dcompiler.h>

// ComPtr
#include <wrl/client.h>
using Microsoft::WRL::ComPtr;

// このライブラリ共通機能
#include "DxUtilCommon.h"


// ----------------------------------------------------------
// D3DShaderクラス
// ----------------------------------------------------------
class D3DShader
{
public:
	// シェーダーのパスを指定してコンパイル
	bool Compile(const wchar_t* filePath);

	// 描画のため、D3DDeviceContextにこのシェーダーをセット
	void SetToContext();

private:
	ComPtr<ID3D11VertexShader>	m_vertex = nullptr;	// 頂点シェーダー
	ComPtr<ID3D11PixelShader>	m_pixel = nullptr;	// ピクセルシェーダー
	ComPtr<ID3D11InputLayout>	m_inputLayout = nullptr;// 入力レイアウト
};

