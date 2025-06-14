#pragma once
#include <vector>
#include <memory>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <DirectXMath.h>

#include "Object.h"

namespace UniDx {

// 前方宣言
class GameObject;
class Component;
class Behaviour;
class Transform;



// --------------------
// GameObjectクラス
// --------------------
class GameObject : public Object
{
public:
    Transform* transform;

    std::vector<std::unique_ptr<Component>> components;

    GameObject(const std::wstring& name = L"GameObject") : name_(name) {
        // デフォルトでTransformを追加
        transform = AddComponent<Transform>();
    }

    template<typename T, typename... Args>
    T* AddComponent(Args&&... args) {
        static_assert(std::is_base_of<Component, T>::value, "T must be a Component");
        auto comp = std::make_unique<T>(std::forward<Args>(args)...);
        comp->gameObject = this;
        T* ptr = comp.get();
        components.push_back(std::move(comp));
        return ptr;
    }

    template<typename T>
    T* GetComponent() {
        for (auto& comp : components) {
            if (auto casted = dynamic_cast<T*>(comp.get())) {
                return casted;
            }
        }
        return nullptr;
    }

protected:
    std::wstring name_;

    const std::wstring& getName() override { return name_; }
};

} // namespace UniDx
