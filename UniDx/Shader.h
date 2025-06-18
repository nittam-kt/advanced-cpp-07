#pragma once

// C++のSTL
#include <string>
#include <array>

// Direct3Dの型・クラス・関数など
#include <d3d11.h>
#include <d3dcompiler.h>

// ComPtr
#include <wrl/client.h>
using Microsoft::WRL::ComPtr;

#include "UniDxDefine.h"
#include "Object.h"

namespace UniDx
{

// 頂点バッファ
struct VertexP
{
	Vector3 Pos;

	static const std::array< D3D11_INPUT_ELEMENT_DESC, 1> layout;
};
struct VertexPN
{
	Vector3 Pos;
	Vector3 Normal;

	static const std::array< D3D11_INPUT_ELEMENT_DESC, 2> layout;
};
struct VertexPT
{
	Vector3 Pos;
	Vector2 UV0;

	static const std::array< D3D11_INPUT_ELEMENT_DESC, 2> layout;
};
struct VertexPC
{
	Vector3 Pos;
	Color Color;

	static const std::array< D3D11_INPUT_ELEMENT_DESC, 2> layout;
};
struct VertexPNT
{
	Vector3 Pos;
	Vector3 Normal;
	Vector2 UV0;

	static const std::array< D3D11_INPUT_ELEMENT_DESC, 3> layout;
};


// ----------------------------------------------------------
// Shaderクラス
// ----------------------------------------------------------
class Shader : public Object
{
public:
	// シェーダーのパスを指定してコンパイル
	bool Compile(std::wstring filePath, const D3D11_INPUT_ELEMENT_DESC* layout, size_t layout_size);

	template<typename TVertex>
	bool Compile(std::wstring filePath) { return Compile(filePath, TVertex::layout.data(), TVertex::layout.size()); }

	// 描画のため、D3DDeviceContextにこのシェーダーをセット
	void SetToContext() const;

protected:
	virtual const std::wstring& getName() const override { return fileName; }
	std::wstring fileName;

private:
	ComPtr<ID3D11VertexShader>	m_vertex = nullptr;	// 頂点シェーダー
	ComPtr<ID3D11PixelShader>	m_pixel = nullptr;	// ピクセルシェーダー
	ComPtr<ID3D11InputLayout>	m_inputLayout = nullptr;// 入力レイアウト
};

}