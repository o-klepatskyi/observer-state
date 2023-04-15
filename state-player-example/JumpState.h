#pragma once
#include "State.h"

class JumpState : public State {
public:
	JumpState(Player& owner);
	void step() override;
private:
	int m_countDown;
};