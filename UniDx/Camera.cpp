#include "Camera.h"

#include "GameObject.h"
#include "Transform.h"

namespace UniDx{

// static なメインカメラ
Camera* Camera::main;

Matrix Camera::GetViewMatrix() const {
    auto t = gameObject->GetComponent<Transform>();
    Vector3 pos = t->position;
    Vector3 look = pos + Vector3(0, 0, 1);
    Vector3 up = Vector3(0, 1, 0);
    return XMMatrixLookAtLH(pos, look, up);
}


void Camera::OnEnable()
{
    if (main == nullptr)
    {
        main = this;
    }
}


void Camera::OnDisable()
{
    if (main == this)
    {
        main = nullptr;
    }
}

}
