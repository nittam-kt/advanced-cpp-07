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

    const std::vector<std::unique_ptr<Component>>& GetComponents() { return components; }

    GameObject(const std::wstring& name = L"GameObject") : name_(name)
    {
        // デフォルトでTransformを追加
        transform = AddComponent<Transform>();
    }

    // 可変長引数でunique_ptr<Component>を受け取るコンストラクタ
    template<typename... ComponentPtrs>
    GameObject(const std::wstring& name, ComponentPtrs&&... components) : name_(name)
    {
        transform = AddComponent<Transform>();
        AddComponent(std::forward<ComponentPtrs>(components)...);
    }

    void AddComponent() {} // ヘルパー関数でパック展開

    template<typename First, typename... Rest>
    void AddComponent(First&& first, Rest&&... rest)
    {
        first->gameObject = this;
        components.push_back(std::move(first));
        AddComponent(std::forward<Rest>(rest)...);
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
    std::vector<std::unique_ptr<Component>> components;

    const std::wstring& getName() const override { return name_; }
};

} // namespace UniDx
