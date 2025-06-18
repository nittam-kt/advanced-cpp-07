#pragma once

#include <UniDx.h>
#include <Renderer.h>


class TestRenderer : public UniDx::Renderer
{
public:
    void Render(const UniDx::Camera& camera);

protected:
    virtual void OnEnable();

    ComPtr<ID3D11Buffer> vb; // 頂点バッファ
};