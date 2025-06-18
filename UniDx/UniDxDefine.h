#pragma once

#include <vector>
#include <memory>

#include <SimpleMath.h>

namespace UniDx
{
using DirectX::SimpleMath::Vector3;
using DirectX::SimpleMath::Vector2;
using DirectX::SimpleMath::Color;

class Object;
class GameObject;
class Component;
class Transform;

typedef std::vector<std::unique_ptr<GameObject>> GameObjectContainer;

}
