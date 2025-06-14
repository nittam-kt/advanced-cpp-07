#pragma once
#include <SimpleMath.h>

#include "Object.h"
#include "Property.h"

using namespace DirectX::SimpleMath;

namespace UniDx {

// 前方宣言
class Behaviour;
class GameObject;


// --------------------
// Component基底クラス
// --------------------
class Component : public Object
{
public:
    GameObject* gameObject = nullptr;
    virtual ~Component() = default;

protected:
    const std::wstring& getName() override;
};


// --------------------
// Behaviour基底クラス
// --------------------
class Behaviour : public Component
{
public:
    virtual void Update() {}
    virtual ~Behaviour() = default;
};


// --------------------
// Cameraクラス
// --------------------
class Camera : public Behaviour
{
public:
    float fov = 60.0f;
    float nearClip = 0.1f;
    float farClip = 1000.0f;

    Matrix GetViewMatrix() const;

    Matrix GetProjectionMatrix(float aspect) const {
        using namespace DirectX;
        return XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(fov), aspect, nearClip, farClip);
    }
};

} // namespace UniDx
