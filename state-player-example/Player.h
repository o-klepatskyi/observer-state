#pragma once
#include <memory>

#include "State.h"

class Player {
public:
	Player();
	void step();

	template<typename T>
	void changeCurrentState();
private:
	std::unique_ptr<State> m_currentState;
};

template<typename T>
void Player::changeCurrentState() {
	m_currentState = std::make_unique<T>(*this);
}

