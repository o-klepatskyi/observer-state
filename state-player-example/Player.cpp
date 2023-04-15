#include "Player.h"
#include "StandState.h"
#include <iostream>

Player::Player() :
	m_currentState(std::make_unique<StandState>(*this)) {
	
}

void Player::step() {
	m_currentState->step();
}


