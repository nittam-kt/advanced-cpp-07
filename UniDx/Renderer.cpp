#include "Renderer.h"

#include "GameObject.h"
#include "Transform.h"
#include "D3DManager.h"
#include "Debug.h"

namespace UniDx{

// -----------------------------------------------------------------------------
// 頂点シェーダー側と共有する、モデルビュー行列の定数バッファ
//     UniDxではすべてのシェーダーでスロット0番に共通で指定する
// -----------------------------------------------------------------------------
struct VSConstantBuffer0
{
    Matrix world;
    Matrix view;
    Matrix projection;
};


// -----------------------------------------------------------------------------
// マテリアルの初期化
// -----------------------------------------------------------------------------
void Material::initialize(std::wstring shaderPath)
{
    shader.Compile(shaderPath);
}


// -----------------------------------------------------------------------------
// 有効化
// -----------------------------------------------------------------------------
void Renderer::OnEnable()
{
    UniDx::Debug::Log(L"OnEnable");
    // 行列用の定数バッファ生成
    D3D11_BUFFER_DESC desc{};
    desc.ByteWidth = sizeof(VSConstantBuffer0);
    desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    desc.CPUAccessFlags = 0;
    desc.Usage = D3D11_USAGE_DEFAULT;
    D3DManager::instance->GetDevice()->CreateBuffer(&desc, nullptr, constantBuffer0.GetAddressOf());
}


// -----------------------------------------------------------------------------
// 現在の姿勢とカメラをシェーダーの定数バッファに転送
// -----------------------------------------------------------------------------
void Renderer::UpdatePositionCameraCBuffer(const UniDx::Camera& camera) const
{
    // ─ ワールド行列を位置に合わせて作成
    VSConstantBuffer0 cb{};
    cb.world = Matrix::CreateTranslation(transform->position);
    cb.view = Matrix::Identity;   // 今回は固定カメラ
    cb.projection = Matrix::Identity;   // 必要なら透視／正射影を別途セット

    // 定数バッファ更新
    D3DManager::instance->GetContext()->UpdateSubresource(constantBuffer0.Get(), 0, nullptr, &cb, 0, 0);
}


// -----------------------------------------------------------------------------
// 現在の姿勢とカメラをシェーダーの定数バッファに転送
// -----------------------------------------------------------------------------
void Renderer::SetShaderForRender() const
{
    for(auto& material : materials)
    {
        material.setForRender();

        ID3D11Buffer* cbs[1] = { constantBuffer0.Get() };
        D3DManager::instance->GetContext()->VSSetConstantBuffers(0, 1, cbs);
    }
}


}
