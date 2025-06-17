#pragma once

#include <UniDx.h>
#include <Renderer.h>


class TestRenderer : public UniDx::Renderer
{
public:
    void Render(const UniDx::Camera& camera);

protected:
    virtual void OnEnable();
};