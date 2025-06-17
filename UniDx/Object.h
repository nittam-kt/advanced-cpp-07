#pragma once
#include <string>

#include "UniDxDefine.h"
#include "Property.h"

namespace UniDx {

// --------------------
// Object基底クラス
// --------------------
class Object
{
public:
    virtual ~Object() {}

    ReadOnlyProperty<const std::wstring&> name;

    Object() : name([this]() { return getName(); }) {}

protected:
    virtual const std::wstring& getName() = 0;
};

} // namespace UniDx
