#pragma once

#include <string> //save error
#include <Windows.h>

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <DxErr.h> //get error from error code
#pragma comment(lib, "dxerr.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")

#include <time.h>
#include "tchar.h"

#include "fmod.hpp"

class Paint {
private:
	IDirect3D9Ex* d3dObject = NULL; //used to create device
	IDirect3DDevice9Ex* d3dDevice = NULL; //contains functions like begin and end scene 
	D3DPRESENT_PARAMETERS d3dparams; //parameters for creating device
	ID3DXFont* d3dFont = 0; // font used when displaying text
	HWND targetWnd;
	int width;
	int height;

	int d3D9Init(HWND hWnd);
	void drawText(char* String, int x, int y, int a, int r, int g, int b);

	int minute = 0;
	int second = 0;
	clock_t start;
	clock_t end;
	double duration;
	int time;
	std::string text;
	
	HWND targetHWnd;
	DWORD soundAlarm;

	FMOD::System* system;
	FMOD::Sound* sound;
	FMOD::Channel* channel;

	bool isPlaying = false;


public:
	int soundSetup();
	Paint();
	Paint(HWND hWnd, HWND targetWnd, int width, int height);
	int render();
};