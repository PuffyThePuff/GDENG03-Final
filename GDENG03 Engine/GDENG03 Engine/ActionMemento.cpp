#include"ActionMemento.h"

ActionMemento::ActionMemento(StateSnapshot* before_state, StateSnapshot* after_state) {
	mBeforeState = before_state;
	mAfterState = after_state;
}

ActionMemento::~ActionMemento() {
	delete mBeforeState;
	delete mAfterState;
}

StateSnapshot* ActionMemento::getBeforeState() {
	return mBeforeState;
}

StateSnapshot* ActionMemento::getAfterState() {
	return mAfterState;
}

std::string ActionMemento::getObjectName() {
	return mBeforeState->getObjectName();
}