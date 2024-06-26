#include "Paint.h"

int Paint::d3D9Init(HWND hWnd) {

	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &d3dObject))) {
		exit(1);
	}

	ZeroMemory(&d3dparams, sizeof(d3dparams));

	d3dparams.BackBufferWidth = width;
	d3dparams.BackBufferHeight = height;
	d3dparams.Windowed = TRUE;
	d3dparams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dparams.hDeviceWindow = hWnd;
	d3dparams.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	d3dparams.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dparams.EnableAutoDepthStencil = TRUE;
	d3dparams.AutoDepthStencilFormat = D3DFMT_D16;

	HRESULT res = d3dObject->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dparams, 0, &d3dDevice);

	if (FAILED(res)) {
		DXGetErrorString(res);
		std::wstring ws(DXGetErrorString(res));
		std::string str(ws.begin(), ws.end());
		std::wstring ws2(DXGetErrorDescription(res));
		std::string str2(ws2.begin(), ws2.end());
		std::string error = "Error: " + str + " error description: " + str2;
		exit(1);
	}

	D3DXCreateFont(d3dDevice, 50, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEVICE_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, L"Comic Sans", &d3dFont);

	return 0;

}

int Paint::soundSetup() {
	
	system = nullptr;
	sound = nullptr;
	channel = nullptr;

	FMOD_RESULT result;
	unsigned int version;
	void* extradriverdata(nullptr);

	result = FMOD::System_Create(&system);
	if (result != FMOD_OK) return -1;

	result = system->getVersion(&version);
	if (result != FMOD_OK) return -1;
	else printf("FMOD version %08x\n", version);

	result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
	if (result != FMOD_OK) return -1;

	result = system->createSound("alarm.wav", FMOD_LOOP_OFF, 0, &sound);
	if (result != FMOD_OK) return -1;

}

Paint::Paint() {};

Paint::Paint(HWND hWnd, HWND targetWnd, int width, int height) {
	this->width = width;
	this->height = height;
	this->targetWnd = targetWnd;
	d3D9Init(hWnd);
	start = clock();
	
	soundSetup();

}


int Paint::render()
{
	if (d3dDevice == nullptr)
		return 1;
	d3dDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);
	d3dDevice->BeginScene();

	//if (targetWnd == GetForegroundWindow())
	//{
		end = clock();

		// 메소 회수 타이밍 출력
		duration = (double)(end - start) / CLOCKS_PER_SEC;
		time = (int)duration % 110 + 1;
		minute = time / 60.0;
		second = time % 60;
		text = std::to_string(minute) + ":";
		if (second < 10) {
			text += "0";
		}
		text += std::to_string(second);
		drawText(text.data(), width / 2, height / 2, 255, 171, 0, 182);

		// 메소 회수 사운드
		channel->isPlaying(&isPlaying);
		if (time == 110 && !isPlaying) {
			system->playSound(sound, 0, false, &channel);
		}

		// 전체 시간 출력
		time = (int)duration + 1;
		minute = time / 60.0;
		second = time % 60;
		text = std::to_string(minute) + ":";
		if (second < 10) {
			text += "0";
		}
		text += std::to_string(second);
		
		drawText(text.data(), width / 2, height / 2 - 50, 255, 255, 102, 102);

		
	//}

	d3dDevice->EndScene();
	d3dDevice->PresentEx(0, 0, 0, 0, 0);

	return 0;
}


void Paint::drawText(char* String, int x, int y, int a, int r, int g, int b)
{
	RECT FontPos;
	FontPos.left = x;
	FontPos.top = y;
	d3dFont->DrawTextA(0, String, strlen(String), &FontPos, DT_NOCLIP, D3DCOLOR_ARGB(a, r, g, b));
}
