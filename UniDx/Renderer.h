#pragma once

#include <memory>
#include <map>

#include <SimpleMath.h>

#include "Component.h"
#include "Shader.h"


namespace UniDx {

class Camera;
class Texture;

// --------------------
// Materialクラス
// --------------------
class Material : public Object
{
public:
    Shader shader;
    ReadOnlyProperty<Texture*> mainTexture;

    Material();

    template<typename TVertex>
    void initialize(std::wstring shaderPath) { shader.Compile<TVertex>(shaderPath); }

    void setForRender() const;

    void addTexture(std::unique_ptr<Texture> tex);

protected:
    ComPtr<ID3D11Buffer> constantBuffer;
    std::vector<std::unique_ptr<Texture>> textures;

    virtual const std::wstring& getName() const override { return shader.name; }
};


// --------------------
// Rendererクラス
// --------------------
class Renderer : public Component
{
public:
    std::vector< std::unique_ptr<Material> > materials;

    virtual void Render(const Camera& camera) {}

protected:
    ComPtr<ID3D11Buffer> constantBuffer0;

    virtual void OnEnable() override;
    virtual void UpdatePositionCameraCBuffer(const UniDx::Camera& camera) const;
    virtual void SetShaderForRender() const;
};


class CubeRenderer : public Renderer
{
public:
};


} // namespace UniDx
