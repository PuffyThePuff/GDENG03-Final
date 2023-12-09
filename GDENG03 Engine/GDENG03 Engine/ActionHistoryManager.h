#pragma once
#include<stack>
#include"ActionMemento.h"
#include"AGameObject.h"
#include"AInputListener.h"

class ActionHistoryManager : public AInputListener
{
public:
	static ActionHistoryManager* getInstance();
	static void initialize();
	static void destroy();

	void startAction(AGameObject* game_object);
	void endAction();
	bool canUndo();
	bool canRedo();
	void applyState(StateSnapshot* state);
	void undoAction();
	void redoAction();
	void clearUndo();
	void clearRedo();

	virtual void onPress(int key) override;
	virtual void onRelease(int key) override;

	virtual void onMouseMove(Point delta_position) override;
	virtual void onLMBPress(Point mouse_position) override;
	virtual void onLMBRelease(Point mouse_position) override;
	virtual void onRMBPress(Point mouse_position) override;
	virtual void onRMBRelease(Point mouse_position) override;

private:
	ActionHistoryManager();
	~ActionHistoryManager();
	ActionHistoryManager(ActionHistoryManager const&) {};
	ActionHistoryManager& operator =(ActionHistoryManager const&) {};

	static ActionHistoryManager* instance;

	AGameObject* mCurrentObject;
	StateSnapshot* mBeforeState;

	std::stack<ActionMemento*> mUndoStack;
	std::stack<ActionMemento*> mRedoStack;
};