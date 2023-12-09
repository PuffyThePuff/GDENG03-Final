#include"BackendManager.h"

BackendManager* BackendManager::instance = nullptr;

BackendManager* BackendManager::getInstance() {
	return instance;
}

void BackendManager::initialize() {
	instance = new BackendManager();
}

void BackendManager::destroy() {}

BackendManager::EditorMode BackendManager::getEditorMode() {
	return mEditorMode;
}

void BackendManager::setEditorMode(EditorMode editor_mode) {
	mEditorMode = editor_mode;
}

bool BackendManager::isInFrameStep() {
	return mIsInFrameStep;
}

void BackendManager::startFrame() {
	mIsInFrameStep = true;
}

void BackendManager::endFrame() {
	mIsInFrameStep = false;
}

BackendManager::BackendManager() {}

BackendManager::~BackendManager() {
	delete instance;
}