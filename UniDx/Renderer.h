#pragma once

#include <SimpleMath.h>

#include "Component.h"
#include "Shader.h"


namespace UniDx {

class Camera;

// --------------------
// Materialクラス
// --------------------
class Material : public Object
{
public:
    Shader shader;

    void initialize(std::wstring shaderPath);
    void setForRender() const { shader.SetToContext(); }

protected:
    ComPtr<ID3D11Buffer> constantBuffer;

    virtual const std::wstring& getName() override { return shader.name; }
};


// --------------------
// Rendererクラス
// --------------------
class Renderer : public Component
{
public:
    std::vector< Material> materials;

    virtual void Render(const Camera& camera) {}

protected:
    ComPtr<ID3D11Buffer> constantBuffer0;

    virtual void OnEnable() override;
    virtual void UpdatePositionCameraCBuffer(const UniDx::Camera& camera) const;
    virtual void SetShaderForRender() const;
};


} // namespace UniDx
