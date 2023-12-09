#pragma once
#include"Point.h"

class AInputListener
{
public:
	virtual void onPress(int key) = 0;
	virtual void onRelease(int key) = 0;

	virtual void onMouseMove(Point delta_position) = 0;
	virtual void onLMBPress(Point mouse_position) = 0;
	virtual void onLMBRelease(Point mouse_position) = 0;
	virtual void onRMBPress(Point mouse_position) = 0;
	virtual void onRMBRelease(Point mouse_position) = 0;
};