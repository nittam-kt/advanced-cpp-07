#pragma once

#include <memory>
#include <SimpleMath.h>

#include "Component.h"

using namespace DirectX::SimpleMath;

namespace UniDx {

// --------------------
// Transformクラス
// --------------------
class Transform : public Component
{
public:
    // ローカルの姿勢
    Property<Vector3> localPosition;
    Property<Vector3> localRotation;
    Property<Vector3> localScale;

    // ダーティフラグと行列
    mutable bool m_dirty = true;
    mutable Matrix m_localMatrix = Matrix::Identity;
    mutable Matrix m_worldMatrix = Matrix::Identity;

    // グローバルposition
    Property<Vector3> position;

    Transform* parent = nullptr;

    // 子GameObject
    // トップ以外のGameObjectはTransformによって保持される
    std::vector<std::shared_ptr<GameObject>> children;

    // バッキングフィールド
private:
    Vector3 _localPosition{ 0,0,0 };
    Vector3 _localRotation{ 0,0,0 };
    Vector3 _localScale{ 1,1,1 };

public:
    Transform()
        : localPosition(
            // getter
            [this]() { return _localPosition; },
            // setter
            [this](const Vector3& v) { _localPosition = v; m_dirty = true; }
        ),
        localRotation(
            [this]() { return _localRotation; },
            [this](const Vector3& v) { _localRotation = v; m_dirty = true; }
        ),
        localScale(
            [this]() { return _localScale; },
            [this](const Vector3& v) { _localScale = v; m_dirty = true; }
        ),
        position(
            // getter: グローバル座標
            [this]() {
                UpdateMatrices();
                return m_worldMatrix.Translation();
            },
            // setter: グローバル座標からlocalPositionを逆算
            [this](const Vector3& worldPos) {
                if (parent) {
                    parent->UpdateMatrices();
                    Matrix invParent = parent->m_worldMatrix.Invert();
                    _localPosition = Vector3::Transform(worldPos, invParent);
                } else {
                    _localPosition = worldPos;
                }
                m_dirty = true;
            }
        )
    {
    }

    virtual ~Transform();

    // 親の変更
    std::shared_ptr<GameObject> SetParent(Transform* newParent);

    // 親のいないTransformを持つGameObjectに親を設定
    static void SetParent(std::shared_ptr<GameObject> gameObjectPtr, Transform* newParent);

    size_t ChildCount() const { return children.size(); }

    Transform* GetChildTransform(size_t index) const {
        if (index < children.size() && children[index]) {
            return children[index]->transform;
        }
        return nullptr;
    }

    // ローカル行列
    const Matrix& GetLocalMatrix() const {
        if (m_dirty) {
            m_localMatrix = Matrix::CreateScale(_localScale)
                * Matrix::CreateFromYawPitchRoll(_localRotation.y, _localRotation.x, _localRotation.z)
                * Matrix::CreateTranslation(_localPosition);
        }
        return m_localMatrix;
    }

    // ワールド行列
    const Matrix& GetWorldMatrix() const {
        UpdateMatrices();
        return m_worldMatrix;
    }

private:
    // 行列の更新
    void UpdateMatrices() const;
};

} // namespace UniDx
