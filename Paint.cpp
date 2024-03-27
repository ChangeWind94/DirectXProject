#include "Paint.h"

int Paint::init(HWND hWND)
{
    if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &object))) {
        exit(1);
    }

    ZeroMemory(&params, sizeof(params));

    params.BackBufferWidth = width;
    params.BackBufferHeight = height;
    params.Windowed = true;
    params.hDeviceWindow = hWND;
    params.SwapEffect = D3DSWAPEFFECT_DISCARD;
    params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
    params.BackBufferFormat = D3DFMT_A8R8G8B8;
    params.EnableAutoDepthStencil = TRUE;
    params.AutoDepthStencilFormat = D3DFMT_D16;

    object->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWND, D3DCREATE_HARDWARE_VERTEXPROCESSING, &params, 0, &device);

    D3DXCreateFont(device, 50, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEVICE_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, L"Comic Sans", &font);

    return 0;
}

int Paint::render()
{
    if (device == nullptr)
        return 1;

    device->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);
    device->BeginScene();

    if (TargetHWND == GetForegroundWindow()) {
        drawText((char*)"U goat backed broo", width / 10, height / 10, 255, 171, 0, 182);
    }

    device->EndScene();
    device->PresentEx(0, 0, 0, 0, 0);

    return 0;
}

Paint::Paint()
{
}

Paint::Paint(HWND overlayHWND, HWND targetHWND, int width, int height)
{
    this->width = width;
    this->height = height;
    this->TargetHWND = targetHWND;
    init(overlayHWND);
}
