// CreateDefaultScene.cpp
// デフォルトのシーンを生成します

#include <UniDx.h>
#include <Scene.h>
#include <GameObject.h>
#include <Component.h>
#include <Transform.h>
#include <Camera.h>

#include "TestRenderer.h"
#include "TestCameraBehaviour.h"

using namespace std;
using namespace UniDx;


unique_ptr<UniDx::Scene> CreateDefaultScene()
{
    return make_unique<Scene>(

        make_unique<GameObject>(L"オブジェクトルート",
            make_unique<TestRenderer>()
        ),

        make_unique<GameObject>(L"カメラルート",
            make_unique<Camera>(),
            make_unique<TestCameraBehaviour>()
        )
    );
}
