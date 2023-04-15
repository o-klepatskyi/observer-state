#pragma once
#include "State.h"

class StandState : public State {
public:
	StandState(Player& owner);
	void step() override;
private:
	int m_countDown;
};