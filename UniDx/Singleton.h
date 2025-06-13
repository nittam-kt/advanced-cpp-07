#pragma once

#include <memory>

namespace UniDx
{

template<class T>
class Singleton
{
public:
    static void create()
    {
        spInstance = std::make_unique<T>();
    }

    static std::unique_ptr<T>& instance() { return spInstance; }

protected:
    Singleton() {}

    static std::unique_ptr<T> spInstance;
};

template<class T>
inline std::unique_ptr<T> Singleton<T>::spInstance;

}