#pragma once

#include "TestRenderer.h"

#include <Texture.h>
#include <D3DManager.h>


using namespace DirectX;
using namespace UniDx;


VertexPT vertex[4] = {
    {{-0.5,-0.5,0},{0,1}},
    {{-0.5,0.5,0},{0,0}},
    {{0.5,-0.5,0},{1,1}},
    {{0.5,0.5,0},{1,0}},
};


void TestRenderer::OnEnable()
{
    Renderer::OnEnable();

    // マテリアルを追加
    materials.push_back(std::make_unique<Material>());

    // マテリアルをシェーダーを読み込んで初期化
    materials.back()->initialize<VertexPT>(L"../UniDx/Albedo.hlsl");

    // テクスチャを読み込んでマテリアルに追加
    std::unique_ptr<Texture> t = std::make_unique<Texture>();
    t->load(L"Resource/floor.png");
    materials.back()->addTexture(std::move(t));

    // 作成するバッファの仕様を決める
    D3D11_BUFFER_DESC vbDesc = {};
    vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// デバイスにバインドするときの種類(頂点バッファ、インデックスバッファ、定数バッファなど)
    vbDesc.ByteWidth = sizeof(vertex);				// 作成するバッファのバイトサイズ
    vbDesc.MiscFlags = 0;							// その他のフラグ
    vbDesc.StructureByteStride = 0;					// 構造化バッファの場合、その構造体のサイズ
    vbDesc.Usage = D3D11_USAGE_DEFAULT;				// 作成するバッファの使用法
    vbDesc.CPUAccessFlags = 0;

    // 上の仕様を渡して頂点バッファを作ってもらう
    D3D11_SUBRESOURCE_DATA initData = { vertex, sizeof(vertex), 0 };	// 書き込むデータ

    // 頂点バッファの作成
    D3DManager::instance->GetDevice()->CreateBuffer(&vbDesc, &initData, &vb);
}


void TestRenderer::Render(const UniDx::Camera& camera)
{
    // 現在のTransformとカメラの情報をシェーダーのConstantBufferに転送
    Renderer::UpdatePositionCameraCBuffer(camera);

    // 描画処理
    // 三角形の描画
    {
        //++++++++++++++++++++ ここから描画していきます ++++++++++++++++++++

        // 頂点バッファを描画で使えるようにセットする
        UINT stride = sizeof(VertexPT);
        UINT offset = 0;
        D3DManager::instance->GetContext()->IASetVertexBuffers(0, 1, vb.GetAddressOf(), &stride, &offset);

        // プロミティブ・トポロジーをセット
        D3DManager::instance->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

        //-----------------------------
        // シェーダーをセット
        //-----------------------------
        SetShaderForRender();

        //-----------------------------
        // 描画実行
        //-----------------------------
        // デバイスコンテキスト、上記のセットした内容で描画してください、とお願いする
        D3DManager::instance->GetContext()->Draw(4, 0);
    }
}
