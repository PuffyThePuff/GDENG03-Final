#pragma once
#define NOMINMAX
#include<Windows.h>
#include"TimeManager.h"

class AWindow
{
public:
	AWindow();
	~AWindow();

	bool initialize();
	bool broadcast();
	bool release();
	bool isRunning();
	RECT getWindowRect();
	void setWindowHandle(HWND window_handle);

	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();

protected:
	HWND mWindowHandle;
	bool mIsRunning = false;
};