#include "Component.h"
#include "GameObject.h"
#include "Transform.h"

namespace UniDx{

const std::wstring& Component::getName()
{
    return gameObject->name;
}

Matrix Camera::GetViewMatrix() const {
    auto t = gameObject->GetComponent<Transform>();
    Vector3 pos = t->position;
    Vector3 look = pos + Vector3(0, 0, 1);
    Vector3 up = Vector3(0, 1, 0);
    return XMMatrixLookAtLH(pos, look, up);
}

}
