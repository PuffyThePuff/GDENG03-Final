#include "TimeManager.h"

TimeManager* TimeManager::instance = nullptr;

void TimeManager::initialize() {
	if (!instance) instance = new TimeManager();
}

double TimeManager::getDeltaTime() {
	std::chrono::duration<double> deltaTime = instance->start - instance->end;
	return deltaTime.count();
}

TimeManager::TimeManager() {}

TimeManager::~TimeManager() {
	delete instance;
}

void TimeManager::logFrameStart() {
	instance->start = std::chrono::system_clock::now();
}

void TimeManager::logFrameEnd() {
	instance->end = instance->start;
}