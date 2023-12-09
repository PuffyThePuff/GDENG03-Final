#include"InputManager.h"
#include<Windows.h>
#include<iostream>

InputManager* InputManager::instance = nullptr;

InputManager* InputManager::getInstance() {
	if (!instance) instance = new InputManager();
	return instance;
}

void InputManager::destroy() {
	if (instance) instance->mListenerList.clear();
}

void InputManager::addListener(AInputListener* listener) {
	mListenerList.push_back(listener);
}

void InputManager::removeListener(AInputListener* listener) {
	int index = -1;
	for (int i = 0; i < mListenerList.size(); i++) {
		if (mListenerList[i] == listener) {
			index = i;
			break;
		}
	}

	if (index > -1) {
		mListenerList.erase(mListenerList.begin() + index);
	}
}

void InputManager::update() {
	POINT currMousePosition = {};
	GetCursorPos(&currMousePosition);

	if (mIsFirstCall) {
		mPrevMousePosition = Point(currMousePosition.x, currMousePosition.y);
		mIsFirstCall = false;
	}

	if (
		mPrevMousePosition.getX() != currMousePosition.x ||
		mPrevMousePosition.getY() != currMousePosition.y
	) {
		Point deltaPosition = Point(
			currMousePosition.x - mPrevMousePosition.getX(),
			currMousePosition.y - mPrevMousePosition.getY()
		);
		onMouseMove(deltaPosition);
	}

	mPrevMousePosition = Point(currMousePosition.x, currMousePosition.y);

	if (GetKeyboardState(mCurrKeyStates)) {
		for (int i = 0; i < ARRAYSIZE(mCurrKeyStates); i++) {
			if (mCurrKeyStates[i] & 0x80 && mCurrKeyStates[i] != mPrevKeyStates[i]) {
				if (i == VK_LBUTTON && mCurrKeyStates[i] != mPrevKeyStates[i]) {
					Point mousePosition = Point(currMousePosition.x, currMousePosition.y);
					onLMBPress(mousePosition);
				}
				else if (i == VK_RBUTTON && mCurrKeyStates[i] != mPrevKeyStates[i]) {
					Point mousePosition = Point(currMousePosition.x, currMousePosition.y);
					onRMBPress(mousePosition);
				}
				else onPress(i);
			}
			else if (mCurrKeyStates[i] != mPrevKeyStates[i]) {
				if (i == VK_LBUTTON && mCurrKeyStates[i] != mPrevKeyStates[i]) {
					Point mousePosition = Point(currMousePosition.x, currMousePosition.y);
					onLMBRelease(mousePosition);
				}
				else if (i == VK_RBUTTON && mCurrKeyStates[i] != mPrevKeyStates[i]) {
					Point mousePosition = Point(currMousePosition.x, currMousePosition.y);
					onRMBRelease(mousePosition);
				}
				else onRelease(i);
			}
		}
	}

	::memcpy(mPrevKeyStates, mCurrKeyStates, 256 * sizeof(unsigned char));
}

bool InputManager::isKeyDown(int key) {
	for (int i = 0; i < ARRAYSIZE(mCurrKeyStates); i++) {
		if (mCurrKeyStates[i] & 0x80 && i == key) return true;
		else if (i == key) return false;
	}

	return false;
}

void InputManager::onPress(int key) {
	for (int i = 0; i < mListenerList.size(); i++) {
		mListenerList[i]->onPress(key);
	}
}

void InputManager::onRelease(int key) {
	for (int i = 0; i < mListenerList.size(); i++) {
		mListenerList[i]->onRelease(key);
	}
}

void InputManager::onMouseMove(Point delta_position) {
	for (int i = 0; i < mListenerList.size(); i++) {
		mListenerList[i]->onMouseMove(delta_position);
	}
}

void InputManager::onLMBPress(Point mouse_position) {
	for (int i = 0; i < mListenerList.size(); i++) {
		mListenerList[i]->onLMBPress(mouse_position);
	}
}

void InputManager::onLMBRelease(Point mouse_position) {
	for (int i = 0; i < mListenerList.size(); i++) {
		mListenerList[i]->onLMBRelease(mouse_position);
	}
}

void InputManager::onRMBPress(Point mouse_position) {
	for (int i = 0; i < mListenerList.size(); i++) {
		mListenerList[i]->onRMBPress(mouse_position);
	}
}

void InputManager::onRMBRelease(Point mouse_position) {
	for (int i = 0; i < mListenerList.size(); i++) {
		mListenerList[i]->onRMBRelease(mouse_position);
	}
}

InputManager::~InputManager() {
	delete instance;
}