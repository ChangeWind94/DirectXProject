// DirectXProject.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include <Dwmapi.h>
#include "framework.h"
#include "DirectXProject.h"
#include "Paint.h"
#include "time.h"
#include <string>
#include "Utils.h"
#include "tchar.h"

#include "Mmsystem.h"
#include "Digitalv.h"
#pragma comment(lib, "winmm.lib")

// 전역 변수:
HINSTANCE hInst;                                // current instance
WCHAR overlayWindowName[100] = L"MapleStoryUtils";  // main window class name & The title bar text
LPCSTR targetWindowName = "MapleStory";  // main window class name & The title bar text
HWND targetHWND, targetHWND2, overlayHWND;
int width, height;
Paint paint;
Utils utils;
int second = 0;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                registerClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    registerClass(hInstance);

    utils = Utils();

    targetHWND2 = FindWindowExA(NULL, NULL, NULL, "MapleStory");
    if (targetHWND2 != NULL) {

        while (targetHWND2 != NULL) {

            RECT rect;
            GetWindowRect(targetHWND2, &rect);
            int width2 = rect.right - rect.left;
            int height2 = rect.bottom - rect.top;

            if (width2 > 500) {
                targetHWND = targetHWND2;
                width = width2;
                height = height2;
            }

            targetHWND2 = FindWindowExA(NULL, targetHWND2, NULL, "MapleStory");
        }

    }
    else
        return FALSE;

    // Perform application initialization:
    if (!InitInstance(hInstance, SW_SHOW)) {
        return FALSE;
    }
    paint = Paint(overlayHWND, targetHWND, width, height);
    
    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0)) {
        
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        RECT rect;
        GetWindowRect(targetHWND, &rect);
        width = rect.right - rect.left;
        height = rect.bottom - rect.top;

        MoveWindow(overlayHWND, rect.left, rect.top, width, height, true);

    }

    return (int)msg.wParam;
}



ATOM registerClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = 0;
    wcex.hCursor = LoadCursor(nullptr, IDC_CROSS);
    wcex.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
    wcex.lpszMenuName = overlayWindowName;
    wcex.lpszClassName = overlayWindowName;
    wcex.hIconSm = 0;

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    overlayHWND = CreateWindowExW(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED, overlayWindowName, overlayWindowName, WS_POPUP,
        1, 1, width, height, nullptr, nullptr, hInstance, nullptr);

    if (!overlayHWND) {
        return FALSE;
    }
    SetLayeredWindowAttributes(overlayHWND, RGB(0, 0, 0), 0, LWA_COLORKEY);

    ShowWindow(overlayHWND, nCmdShow);

    return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_PAINT:
        paint.render();
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}