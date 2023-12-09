#pragma once

class BackendManager
{
public:
	static BackendManager* getInstance();
	static void initialize();
	static void destroy();

	enum EditorMode {
		EDIT = 0,
		PLAY = 1,
		PAUSED = 2
	};

	EditorMode getEditorMode();
	void setEditorMode(EditorMode editor_mode);
	bool isInFrameStep();
	void startFrame();
	void endFrame();

private:
	BackendManager();
	~BackendManager();
	BackendManager(BackendManager const&) {};
	BackendManager& operator =(BackendManager const&) {};

	static BackendManager* instance;

	EditorMode mEditorMode = EDIT;
	bool mIsInFrameStep = false;
};