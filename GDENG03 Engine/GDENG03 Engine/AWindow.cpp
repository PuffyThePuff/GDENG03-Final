#include"AWindow.h"
#include"GlobalProperties.h"
#include"imgui_impl_win32.h"

AWindow* window = nullptr;

AWindow::AWindow() {}

AWindow::~AWindow() {}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND window_handle, UINT msg, WPARAM w_param, LPARAM l_param) {
	if (ImGui_ImplWin32_WndProcHandler(window_handle, msg, w_param, l_param)) return true;

	switch (msg) {
	case WM_CREATE: {
		window->setWindowHandle(window_handle);
		window->onCreate();
		break;
	}
	case WM_DESTROY: {
		window->onDestroy();
		PostQuitMessage(0);
		break;
	}
	default: return ::DefWindowProc(window_handle, msg, w_param, l_param);
	}

	return NULL;
}

bool AWindow::initialize() {
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	TimeManager::initialize();
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;

	wc.lpszClassName = L"AWindowClass";
	wc.lpszMenuName = L"";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;

	if (!::RegisterClassEx(&wc)) return false;

	if (!window) window = this;
	mWindowHandle = ::CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		L"AWindowClass",
		L"Group 4 MCO: Scene Editor",
		WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		GlobalProperties::WINDOW_WIDTH,
		GlobalProperties::WINDOW_HEIGHT,
		NULL,
		NULL,
		NULL,
		NULL
	);
	if (!mWindowHandle) return false;

	::ShowWindow(mWindowHandle, SW_SHOW);
	::UpdateWindow(mWindowHandle);

	mIsRunning = true;

	TimeManager::logFrameStart();
	TimeManager::logFrameEnd();

	return true;
}

bool AWindow::broadcast() {
	TimeManager::logFrameStart();
	window->onUpdate();

	MSG msg;

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Sleep(1);
	TimeManager::logFrameEnd();

	return true;
}

bool AWindow::release() {
	if (!::DestroyWindow(mWindowHandle)) return false;

	return true;
}

bool AWindow::isRunning() {
	return mIsRunning;
}

RECT AWindow::getWindowRect()
{
	RECT windowRect;
	::GetClientRect(mWindowHandle, &windowRect);
	return windowRect;
}

void AWindow::setWindowHandle(HWND window_handle) {
	mWindowHandle = window_handle;
}

void AWindow::onCreate() {}

void AWindow::onUpdate() {}

void AWindow::onDestroy() {
	mIsRunning = false;
}