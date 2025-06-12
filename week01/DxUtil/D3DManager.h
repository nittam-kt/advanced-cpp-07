#pragma once

// C++のSTLを使えるようにする
#include <string>
#include <vector>
#include <list>

// Direct3Dのライブラリを使用できるようにする
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

// Direct3Dの型・クラス・関数などを呼べるようにする
#include <d3d11.h>
#include <d3dcompiler.h>

// DirectXMath(数学ライブラリ)を使用できるようにする
#include <DirectXMath.h>

// ComPtrを使用できるようにする
#include <wrl/client.h>
using Microsoft::WRL::ComPtr;

// ----------------------------------------------------------
// D3DManagerクラス
// ----------------------------------------------------------
class D3DManager
{
public:

	//--------------------------------------------
	// Direct3Dを初期化し、使用できるようにする
	// hWnd		: ウィンドウハンドル
	// width	: 画面の幅
	// height	: 画面の高さ
	//--------------------------------------------
	bool Initialize(HWND hWnd, int width, int height);


	// インスタンス作成
	static void CreateInstance()
	{
		DeleteInstance();

		s_instance = new D3DManager();
	}

	// インスタンス削除
	static void DeleteInstance()
	{
		if (s_instance != nullptr)
		{
			delete s_instance;
			s_instance = nullptr;
		}
	}

	static D3DManager& GetInstance() { return *s_instance; } // 唯一のインスタンスを取得

	const ComPtr<ID3D11Device>&			GetDevice() const { return m_device; }
	const ComPtr<ID3D11DeviceContext>&	GetContext() const { return m_context; }

	// バックバッファレンダーターゲットをクリア
	void Clear(float r, float g, float b, float a);

	// バックバッファの内容を画面に表示
	void Present()
	{
		m_swapChain->Present(1, 0);
	}


private:
	static D3DManager* s_instance; // インスタンス	

	ComPtr<ID3D11Device>			m_device; // Direct3Dデバイス
	ComPtr<ID3D11DeviceContext>		m_context; // Direct3Dデバイスコンテキスト
	ComPtr<IDXGISwapChain>			m_swapChain; // スワップチェイン
	ComPtr<ID3D11RenderTargetView>	m_renderTarget; // バックバッファーのRTビュー

	D3DManager() {} // コンストラクタ（private）	
};

