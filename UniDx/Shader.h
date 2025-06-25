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

enum VertexType
{
	VertexTypeUnknown,
	VertexTypeP,
	VertexTypePN,
	VertexTypePT,
	VertexTypePC,
	VertexTypePNT,
	VertexTypePNC,
};

// 頂点バッファ
struct VertexP
{
	Vector3 Pos;

	static VertexType type() { return VertexTypeP; }
	static const std::array< D3D11_INPUT_ELEMENT_DESC, 1> layout;
};
struct VertexPN
{
	Vector3 Pos;
	Vector3 Normal;

	static VertexType type() { return VertexTypePN; }
	static const std::array< D3D11_INPUT_ELEMENT_DESC, 2> layout;
};
struct VertexPT
{
	Vector3 Pos;
	Vector2 UV0;

	static VertexType type() { return VertexTypePT; }
	static const std::array< D3D11_INPUT_ELEMENT_DESC, 2> layout;
};
struct VertexPC
{
	Vector3 Pos;
	Color Color;

	static VertexType type() { return VertexTypePC; }
	static const std::array< D3D11_INPUT_ELEMENT_DESC, 2> layout;
};
struct VertexPNT
{
	Vector3 Pos;
	Vector3 Normal;
	Vector2 UV0;

	static VertexType type() { return VertexTypePNT; }
	static const std::array< D3D11_INPUT_ELEMENT_DESC, 3> layout;
};
struct VertexPNC
{
	Vector3 Pos;
	Vector3 Normal;
	Color Color;

	static VertexType type() { return VertexTypePNC; }
	static const std::array< D3D11_INPUT_ELEMENT_DESC, 3> layout;
};


// ----------------------------------------------------------
// Shaderクラス
// ----------------------------------------------------------
class Shader : public Object
{
public:
	Shader() : vertexType(VertexTypeUnknown) {}

	// シェーダーのパスを指定してコンパイル
	bool compile(std::wstring filePath, const D3D11_INPUT_ELEMENT_DESC* layout, size_t layout_size);

	template<typename TVertex>
	bool compile(std::wstring filePath) { vertexType = TVertex::type(); return compile(filePath, TVertex::layout.data(), TVertex::layout.size()); }

	// 描画のため、D3DDeviceContextにこのシェーダーをセット
	void setToContext() const;

protected:
	virtual const std::wstring& getName() const override { return fileName; }
	std::wstring fileName;
	VertexType vertexType;

private:
	ComPtr<ID3D11VertexShader>	m_vertex = nullptr;	// 頂点シェーダー
	ComPtr<ID3D11PixelShader>	m_pixel = nullptr;	// ピクセルシェーダー
	ComPtr<ID3D11InputLayout>	m_inputLayout = nullptr;// 入力レイアウト
};

}