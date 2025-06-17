#include "Component.h"
#include "GameObject.h"
#include "Transform.h"

namespace UniDx{

// コンストラクタ
Component::Component() :
    enabled(
        // get
        [this]() { return _enabled && isCalledAwake; },

        // set
        [this](bool value) {
            if (!_enabled && value) {
                if (!isCalledAwake) { Awake(); isCalledAwake = true; }
                OnEnable();
            }
            else if (_enabled && !value) {
                if (isCalledAwake) { OnDisable(); }
            }
            _enabled = value;
        }
    ),
    transform(
        [this]() { return gameObject->transform; }
    ),
    _enabled(true),
    isCalledAwake(false),
    isCalledStart(false)
{

}
    
const std::wstring& Component::getName()
{
    return gameObject->name;
}

}
