#pragma once

#include "TestRenderer.h"
#include "D3DManager.h"

using namespace DirectX;
using namespace UniDx;


void TestRenderer::Render(const UniDx::Camera& camera)
{
    // 現在のTransformとカメラの情報をシェーダーのConstantBufferに転送
    Renderer::UpdatePositionCameraCBuffer(camera);

    UniDx::Debug::Log(L"Render");

    // 描画処理
    // 三角形の描画
    {
        // １頂点の形式(今回は座標だけ)
        struct VertexType
        {
            Vector3 Pos;	// 座標
        };
        // 三角形を作るため、頂点を３つ作る
        VertexType v[4] = {
            {{-0.5,-0.5,0}},
            {{-0.5,0.5,0}},
            {{0.5,-0.5,0}},
            {{0.5,0.5,0}},
        };
        //-----------------------------
        // 頂点バッファ作成
        // ・ビデオメモリ側に「頂点バッファ」という形で作る必要がある
        // ・今回は描画のたびに作る
        //-----------------------------
        // 作成するバッファの仕様を決める
        D3D11_BUFFER_DESC vbDesc = {};
        vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// デバイスにバインドするときの種類(頂点バッファ、インデックスバッファ、定数バッファなど)
        vbDesc.ByteWidth = sizeof(v);					// 作成するバッファのバイトサイズ
        vbDesc.MiscFlags = 0;							// その他のフラグ
        vbDesc.StructureByteStride = 0;					// 構造化バッファの場合、その構造体のサイズ
        vbDesc.Usage = D3D11_USAGE_DEFAULT;				// 作成するバッファの使用法
        vbDesc.CPUAccessFlags = 0;

        // 上の仕様を渡して頂点バッファを作ってもらう
        ComPtr<ID3D11Buffer> vb;
        D3D11_SUBRESOURCE_DATA initData = { &v[0], sizeof(v), 0 };	// 書き込むデータ

        // 頂点バッファの作成
        D3DManager::instance->GetDevice()->CreateBuffer(&vbDesc, &initData, &vb);

        //++++++++++++++++++++ ここから描画していきます ++++++++++++++++++++

        // 頂点バッファを描画で使えるようにセットする
        UINT stride = sizeof(VertexType);
        UINT offset = 0;
        D3DManager::instance->GetContext()->IASetVertexBuffers(0, 1, vb.GetAddressOf(), &stride, &offset);

        // プロミティブ・トポロジーをセット
        D3DManager::instance->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

        UniDx::Debug::Log(__LINE__);
        //-----------------------------
        // シェーダーをセット
        //-----------------------------
        SetShaderForRender();

        //-----------------------------
        // 描画実行
        //-----------------------------
        // デバイスコンテキスト、上記のセットした内容で描画してください、とお願いする
        D3DManager::instance->GetContext()->Draw(4, 0);
        UniDx::Debug::Log(__LINE__);
    }
}


void TestRenderer::OnEnable()
{
    Renderer::OnEnable();
    materials.push_back(Material());
    materials.back().initialize(L"../UniDx/SimplePositionShader.hlsl");
}