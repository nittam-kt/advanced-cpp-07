#pragma once

#include <vector>
#include <memory>

namespace UniDx
{

class Object;
class GameObject;
class Component;
class Transform;

typedef std::vector<std::unique_ptr<GameObject>> GameObjectContainer;

}
