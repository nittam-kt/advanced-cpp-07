#pragma once

#include <windows.h>
#include <Keyboard.h>

#include "Singleton.h"

namespace UniDx
{

// ÉGÉìÉWÉìÇÃÉÅÉCÉì
class Engine : public Singleton<Engine>
{
public:
    virtual void Initialize(HWND hWnd);
    virtual int mainLoop();

    void ProcessKeyboardMessage(UINT message, WPARAM wParam, LPARAM lParam)
    {
        DirectX::Keyboard::ProcessMessage(message, wParam, lParam);
    }

protected:
    virtual void FixedUpdate();
    virtual void Physics();
    virtual void Input();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Render();
    virtual void Finalize();
};

}