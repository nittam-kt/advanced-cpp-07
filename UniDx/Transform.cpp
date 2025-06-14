#include "Transform.h"

#include "GameObject.h"


namespace UniDx
{

Transform::~Transform() 
{
    for (auto child : children)
    {
        if (child) child->transform->parent = nullptr;
    }
}


// 親の変更
std::shared_ptr<GameObject> Transform::SetParent(Transform * newParent)
{
    // 親のTransformから自分を外す
    if (parent == nullptr)
    {
        // 新規Transformに親を設定する場合はsmart_ptrを渡すstatic版を使ってください
        abort();
        return nullptr;
    }
    auto& siblings = parent->children;

    // 以前の親からGameObjectのスマートポインタをコピー
    auto gameObject_ptr = *std::find_if(
        siblings.begin(), siblings.end(),
        [this](const std::shared_ptr<GameObject>& ptr) { return ptr->transform == this; });

    assert(gameObject_ptr != nullptr);

    // 以前の親から自分を持つGameObjectを削除
    std::remove_if(siblings.begin(), siblings.end(), [this](const std::shared_ptr<GameObject>& ptr) { return ptr->transform == this; });

    // 新しい親を設定
    parent = newParent;

    if (parent)
    {
        // 新しい親に自分を持つGameObjectを追加
        parent->children.push_back(gameObject_ptr);
    }
    m_dirty = true;

    return gameObject_ptr;
}


void Transform::SetParent(std::shared_ptr<GameObject> gameObjectPtr, Transform* newParent)
{
    // 親のTransformから自分を外す
    if (gameObjectPtr->transform->parent != nullptr)
    {
        // すでに親がある場合はメンバ変数版を使ってください
        abort();
        return;
    }

    // 新しい親を設定
    gameObjectPtr->transform->parent = newParent;

    if (newParent)
    {
        // 新しい親に自分を持つGameObjectを追加
        newParent->children.push_back(gameObjectPtr);
    }
    gameObjectPtr->transform->m_dirty = true;
}


void Transform::UpdateMatrices() const
{
    if (m_dirty)
    {
        m_localMatrix = Matrix::CreateScale(_localScale)
            * Matrix::CreateFromYawPitchRoll(_localRotation.y, _localRotation.x, _localRotation.z)
            * Matrix::CreateTranslation(_localPosition);
        if (parent) {
            parent->UpdateMatrices();
            m_worldMatrix = m_localMatrix * parent->m_worldMatrix;
        }
        else {
            m_worldMatrix = m_localMatrix;
        }
        m_dirty = false;
    }
}


}
