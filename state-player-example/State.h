#pragma once
class Player;

class State {
public:
	State(Player& owner);
	virtual ~State() {}
	virtual void step() = 0;
protected:
	Player& m_owner;
};


