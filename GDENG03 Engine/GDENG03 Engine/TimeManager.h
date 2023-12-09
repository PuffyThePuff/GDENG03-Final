#pragma once
#include<iostream>
#include<chrono>
#include<ctime>

class AWindow;

class TimeManager
{
public:
	static void initialize();
	static double getDeltaTime();

private:
	TimeManager();
	~TimeManager();
	TimeManager(TimeManager const&) {}
	TimeManager& operator=(TimeManager const&) {}

	static TimeManager* instance;

	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;

	double deltaTime = 0.0;

	static void logFrameStart();
	static void logFrameEnd();

	friend class AWindow;
};