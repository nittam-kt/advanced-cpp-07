// week01.cpp : �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "Engine.h"

#include <string>
#include <chrono>

#include <Keyboard.h>          // DirectXTK
#include <SimpleMath.h>        // DirectXTK �֗����w���[�e�B���e�B
using namespace DirectX;
using namespace DirectX::SimpleMath;

// DirectX�e�N�X�`�����C�u�������g�p�ł���悤�ɂ���
#include <DirectXTex.h>

// DirextX�t�H���g���C�u�������g�p�ł���悤�ɂ���
#include <SpriteFont.h>

#include "D3DManager.h"
#include "UniDxTime.h"
#include "Debug.h"

// �L�[�{�[�h
std::unique_ptr<Keyboard> g_keyboard;   // DirectXTK Keyboard

// �t�H���g�`��p
std::unique_ptr<SpriteBatch> g_spriteBatch;
std::unique_ptr<SpriteFont>  g_spriteFont;
std::wstring text[4];

using namespace std;
using namespace UniDx;

namespace UniDx
{

    //
    //   �֐�: Initialize(HWND hWnd)
    //
    void Engine::Initialize(HWND hWnd)
    {
        // Direct3D�C���X�^���X�쐬
        D3DManager::create();

        // Direct3D������
        D3DManager::instance->Initialize(hWnd, 1280, 720);

        // �L�[���͂̏�����
        g_keyboard = std::make_unique<Keyboard>();

        // �t�H���g������
        g_spriteBatch = std::make_unique<SpriteBatch>(D3DManager::instance->GetContext().Get());
        g_spriteFont = std::make_unique<SpriteFont>(D3DManager::instance->GetDevice().Get(), L"Resource/M PLUS 1.spritefont");
    }


    int Engine::mainLoop()
    {
        MSG msg;

        Time::Start();
        double restFixedUpdateTime = 0.0f;

        // ���C�� ���b�Z�[�W ���[�v:
        while (true)
        {
            if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
            {
                //============================================
                // �E�B���h�E���b�Z�[�W����
                //============================================
                // �I�����b�Z�[�W������
                if (msg.message == WM_QUIT) {
                    break;
                }
                else
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
            }

            using clock = std::chrono::steady_clock;          // ���m�g�j�b�N�Ȃ̂Ōo�ߎ��Ԍv������
            auto start = clock::now();

            //============================================
            // �Q�[���̏���������
            //============================================
            // ��ʂ�h��Ԃ�
            D3DManager::instance->Clear(0.3f, 0.5f, 0.9f, 1.0f);

            Time::SetDeltaTimeFixed();

            while (restFixedUpdateTime > Time::fixedDeltaTime)
            {
                // �Œ莞�ԍX�V�X�V
                FixedUpdate();

                // �����v�Z
                Physics();

                restFixedUpdateTime -= Time::fixedDeltaTime;
            }

            Time::SetDeltaTimeFrame();

            // ���͍X�V
            Input();

            // �X�V����
            Update();

            // ��X�V����
            LateUpdate();

            // �`�揈��
            Render();

            // �o�b�N�o�b�t�@�̓��e����ʂɕ\��
            D3DManager::instance->Present();

            // ���Ԍv�Z
            double deltaTime = std::chrono::duration<double>(clock::now() - start).count();
            restFixedUpdateTime += deltaTime;

            Time::UpdateFrame(deltaTime);
        }

        // �I������
        Finalize();

        return (int)msg.wParam;
    }


    // �Œ莞�ԍX�V�X�V
    void Engine::FixedUpdate()
    {
    }


    // �����v�Z
    void Engine::Physics()
    {

    }


    // ���͍X�V
    void Engine::Input()
    {

    }


    //
    //  �֐�: Update()
    //
    //  �ړI: �Q�[���̍X�V�������s���܂��B
    //
    void Engine::Update()
    {
        text[0] = std::to_wstring(0);
        text[1] = std::to_wstring(0);
        text[2] = std::to_wstring(0);
        text[3] = std::to_wstring(0);
    }


    // ��X�V����
    void Engine::LateUpdate()
    {

    }

    //
    //  �֐�: Render()
    //
    //  �ړI: ��ʂ̕`�揈�����s���܂��B
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


    // �I������
    void Engine::Finalize()
    {

    }

}