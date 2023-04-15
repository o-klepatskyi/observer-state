#include <iostream>
#include "Player.h"
#include "JumpState.h"
#include "StandState.h"

JumpState::JumpState(Player& owner) :
	State(owner),
	m_countDown(2 + rand() % 3) {
	std::cout << "JUMP Ctor: countdown is " << m_countDown << "\n";
}

void JumpState::step() {
	m_countDown--;
	std::cout << "JUMP State... countdown is " << m_countDown << "\n";
	if (m_countDown <= 0) {
		m_owner.changeCurrentState<StandState>();
		return;
	}

	// Be careful! We are deleted here
}