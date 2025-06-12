// week01.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "framework.h"
#include "main.h"
#include "classTest.h"

#include <Keyboard.h>          // DirectXTK
#include <SimpleMath.h>        // DirectXTK 便利数学ユーティリティ
using namespace DirectX;
using namespace DirectX::SimpleMath;

// DirectXテクスチャライブラリを使用できるようにする
#include <DirectXTex.h>

// DirextXフォントライブラリを使用できるようにする
#include <SpriteFont.h>

#include "DxUtil/D3DManager.h"
#include "DxUtil/D3DShader.h"
#include "DxUtil/DxUtilCommon.h"

#define MAX_LOADSTRING 100

// グローバル変数:
HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
WCHAR szWindowClass[MAX_LOADSTRING];            // メイン ウィンドウ クラス名

// キーボード
std::unique_ptr<Keyboard> g_keyboard;   // DirectXTK Keyboard

// フォント描画用
std::unique_ptr<SpriteBatch> g_spriteBatch;
std::unique_ptr<SpriteFont>  g_spriteFont;
std::wstring text[4];

using namespace std;


// このコード モジュールに含まれる関数の宣言を転送します:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
void                Update();
void                Render();
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ここにコードを挿入してください。

    // グローバル文字列を初期化する
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WEEK01, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // アプリケーション初期化の実行:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WEEK01));

    MSG msg;

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

        //============================================
        // ゲームの処理を書く
        //============================================
        // 画面を塗りつぶす
        D3DManager::GetInstance().Clear(0.3f, 0.5f, 0.9f, 1.0f);
        
        // 更新処理
        Update();

        // 描画処理
        Render();

        // バックバッファの内容を画面に表示
        D3DManager::GetInstance().Present();
    }

    return (int) msg.wParam;
}



//
//  関数: Update()
//
//  目的: ゲームの更新処理を行います。
//
void Update()
{
    text[0] = std::to_wstring(0);
    text[1] = std::to_wstring(0);
    text[2] = std::to_wstring(0);
    text[3] = std::to_wstring(0);
}


//
//  関数: Render()
//
//  目的: 画面の描画処理を行います。
//
void Render()
{
    g_spriteBatch->Begin();

    Vector2 drawPos(100, 100);
    for (auto & str : text)
    {
        g_spriteFont->DrawString(g_spriteBatch.get(),
            str.c_str(),
            drawPos);
        drawPos.y += 50;
    }

    g_spriteBatch->End();
}


//
//  関数: MyRegisterClass()
//
//  目的: ウィンドウ クラスを登録します。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WEEK01));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WEEK01);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   関数: InitInstance(HINSTANCE, int)
//
//   目的: インスタンス ハンドルを保存して、メイン ウィンドウを作成します
//
//   コメント:
//
//        この関数で、グローバル変数でインスタンス ハンドルを保存し、
//        メイン プログラム ウィンドウを作成および表示します。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // グローバル変数にインスタンス ハンドルを格納する

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   // Direct3Dインスタンス作成
   D3DManager::CreateInstance();

   // Direct3D初期化
   D3DManager::GetInstance().Initialize(hWnd, 1280, 720);

   // キー入力の初期化
   g_keyboard = std::make_unique<Keyboard>();

   // フォント初期化
   g_spriteBatch = std::make_unique<SpriteBatch>(D3DManager::GetInstance().GetContext().Get());
   g_spriteFont = std::make_unique<SpriteFont>(D3DManager::GetInstance().GetDevice().Get(), L"M PLUS 1.spritefont");

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  関数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: メイン ウィンドウのメッセージを処理します。
//
//  WM_COMMAND  - アプリケーション メニューの処理
//  WM_PAINT    - メイン ウィンドウを描画する
//  WM_DESTROY  - 中止メッセージを表示して戻る
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 選択されたメニューの解析:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: HDC を使用する描画コードをここに追加してください...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_ACTIVATE:
    case WM_ACTIVATEAPP:
        Keyboard::ProcessMessage(message, wParam, lParam);
        break;
    case WM_SYSKEYDOWN:
        if (wParam == VK_RETURN && (lParam & 0x60000000) == 0x20000000)
        {
            // This is where you'd implement the classic ALT+ENTER hotkey for fullscreen toggle
        }
        Keyboard::ProcessMessage(message, wParam, lParam);
        break;

    case WM_KEYDOWN:
    case WM_KEYUP:
    case WM_SYSKEYUP:
        Keyboard::ProcessMessage(message, wParam, lParam);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// バージョン情報ボックスのメッセージ ハンドラーです。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
