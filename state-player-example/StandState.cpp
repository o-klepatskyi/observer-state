#include <iostream>
#include "StandState.h"
#include "JumpState.h"
#include "Player.h"

StandState::StandState(Player& owner) :
	State(owner),
	m_countDown(5 + (rand() % 6)) {
	std::cout << "STAND Ctor: countdown is " << m_countDown << "\n";
}

void StandState::step() {
	m_countDown--;
	std::cout << "STAND State... countdown is " << m_countDown << "\n";
	if (m_countDown <= 0) {
		m_owner.changeCurrentState<JumpState>();
		return;
	}

	// Be careful! We are deleted here
}