#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

class Paint {
private:
	IDirect3D9Ex* object = NULL;
	IDirect3DDevice9Ex* device = NULL;
	D3DPRESENT_PARAMETERS params;
	ID3DXFont* font = 0;
	HWND TargetHWND;
	int width, height;

	int init(HWND hWND);

	void drawText(char* string, int x, int y, int a, int r, int g, int b) {
		RECT rect;
		rect.top = y;
		rect.left = x;
		font->DrawTextA(0, string, strlen(string), &rect, DT_NOCLIP, D3DCOLOR_ARGB(a, r, g, b));
	}

public:
	int render();

	Paint();
	Paint(HWND overlayHWND, HWND targetHWND, int width, int height);
};

