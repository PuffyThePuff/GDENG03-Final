#pragma once
#include"AUIPanel.h"
#include"StateSnapshot.h"

class ActionMemento
{
public:
	ActionMemento(StateSnapshot* before_state, StateSnapshot* after_state);
	~ActionMemento();

	StateSnapshot* getBeforeState();
	StateSnapshot* getAfterState();
	std::string getObjectName();

private:
	StateSnapshot* mBeforeState;
	StateSnapshot* mAfterState;
};