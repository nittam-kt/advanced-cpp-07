#pragma once

#include <string>

#ifdef _DEBUG

namespace UniDx
{

// デバッグ用ネームスペース
namespace Debug
{

    template<typename T>
    inline void Log(const T& value)
    {
        OutputDebugStringW(std::to_wstring(value).c_str());
        OutputDebugStringW(L"\n");
    }
    inline void Log(const wchar_t* value)
    {
        OutputDebugStringW(value);
        OutputDebugStringW(L"\n");
    }
}

}

#else

namespace UniDx
{

namespace Debug
{
    template<typename T>
    inline void Log(const T& value) { }
}

}

#endif
