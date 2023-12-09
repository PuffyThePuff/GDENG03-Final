#pragma once
#include<vector>
#include"AInputListener.h"
#include"Point.h"

class InputManager
{
public:
	static InputManager* getInstance();
	static void destroy();

	void addListener(AInputListener* listener);
	void removeListener(AInputListener* listener);

	void update();

	bool isKeyDown(int key);

private:
	static InputManager* instance;

	void onPress(int key);
	void onRelease(int key);

	void onMouseMove(Point delta_position);
	void onLMBPress(Point mouse_position);
	void onLMBRelease(Point mouse_position);
	void onRMBPress(Point mouse_position);
	void onRMBRelease(Point mouse_position);

	std::vector<AInputListener*> mListenerList;

	unsigned char mCurrKeyStates[256] = {};
	unsigned char mPrevKeyStates[256] = {};

	Point mPrevMousePosition;
	bool mIsFirstCall = true;

	InputManager() {}
	~InputManager();
	InputManager(InputManager const&) {};
	InputManager& operator =(InputManager const&) {};
};