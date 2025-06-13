// week01.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "Engine.h"

namespace
{
#include <cstdlib>
}
#include <string>
#include <chrono>

#include <Keyboard.h>          // DirectXTK
#include <SimpleMath.h>        // DirectXTK 便利数学ユーティリティ
using namespace DirectX;
using namespace DirectX::SimpleMath;

// DirectXテクスチャライブラリを使用できるようにする
#include <DirectXTex.h>

// DirextXフォントライブラリを使用できるようにする
#include <SpriteFont.h>

#include "D3DManager.h"
#include "UniDxTime.h"
#include "Debug.h"

// キーボード
std::unique_ptr<Keyboard> g_keyboard;   // DirectXTK Keyboard

// フォント描画用
std::unique_ptr<SpriteBatch> g_spriteBatch;
std::unique_ptr<SpriteFont>  g_spriteFont;
std::wstring text[4];

using namespace std;
using namespace UniDx;

namespace UniDx
{

    //
    //   関数: Initialize(HWND hWnd)
    //
    void Engine::Initialize(HWND hWnd)
    {
        // Direct3Dインスタンス作成
        D3DManager::CreateInstance();

        // Direct3D初期化
        D3DManager::GetInstance().Initialize(hWnd, 1280, 720);

        // キー入力の初期化
        g_keyboard = std::make_unique<Keyboard>();

        // フォント初期化
        g_spriteBatch = std::make_unique<SpriteBatch>(D3DManager::GetInstance().GetContext().Get());
        g_spriteFont = std::make_unique<SpriteFont>(D3DManager::GetInstance().GetDevice().Get(), L"Resource/M PLUS 1.spritefont");
    }


    int Engine::mainLoop()
    {
        MSG msg;

        Time::frameCount = 0;
        Time::time = 0.0f;
        Time::unscaledDeltaTime = 0.0f;
        double deltaTime = 0.0f;
        double restFixedUpdateTime = 0.0f;

        // メイン メッセージ ループ:
        while (true)
        {
            if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
            {
                //============================================
                // ウィンドウメッセージ処理
                //============================================
                // 終了メッセージがきた
                if (msg.message == WM_QUIT) {
                    break;
                }
                else
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
            }

            using clock = std::chrono::steady_clock;          // モノトニックなので経過時間計測向き
            auto start = clock::now();

            //============================================
            // ゲームの処理を書く
            //============================================
            // 画面を塗りつぶす
            D3DManager::GetInstance().Clear(0.3f, 0.5f, 0.9f, 1.0f);

            while (restFixedUpdateTime > Time::fixedDeltaTime)
            {
                Time::deltaTime = Time::fixedDeltaTime;

                // 固定時間更新更新
                FixedUpdate();

                // 物理計算
                Physics();

                restFixedUpdateTime -= Time::fixedDeltaTime;
            }

            Time::deltaTime = float(deltaTime);

            // 入力更新
            Input();

            // 更新処理
            Update();

            // 後更新処理
            LateUpdate();

            // 描画処理
            Render();

            // バックバッファの内容を画面に表示
            D3DManager::GetInstance().Present();

            // 時間計算
            deltaTime = std::chrono::duration<double>(clock::now() - start).count();
            restFixedUpdateTime += deltaTime;

            Time::time += float(deltaTime * Time::timeScale);
            Time::unscaledDeltaTime = float(deltaTime);
            Time::unscaledTime += float(deltaTime);
            Time::frameCount++;
        }

        // 終了処理
        Finalize();

        return (int)msg.wParam;
    }


    // 固定時間更新更新
    void Engine::FixedUpdate()
    {
    }


    // 物理計算
    void Engine::Physics()
    {

    }


    // 入力更新
    void Engine::Input()
    {

    }


    //
    //  関数: Update()
    //
    //  目的: ゲームの更新処理を行います。
    //
    void Engine::Update()
    {
        text[0] = std::to_wstring(0);
        text[1] = std::to_wstring(0);
        text[2] = std::to_wstring(0);
        text[3] = std::to_wstring(0);
    }


    // 後更新処理
    void Engine::LateUpdate()
    {

    }

    //
    //  関数: Render()
    //
    //  目的: 画面の描画処理を行います。
    //
    void Engine::Render()
    {
        g_spriteBatch->Begin();

        Vector2 drawPos(100, 100);
        for (auto& str : text)
        {
            g_spriteFont->DrawString(g_spriteBatch.get(),
                str.c_str(),
                drawPos);
            drawPos.y += 50;
        }

        g_spriteBatch->End();
    }


    // 終了処理
    void Engine::Finalize()
    {

    }

}