#pragma once
// ---- <ConcreteSubject.h> --------------------------------------------------------

#include "ISubject.h"

class ConcreteSubject : public ISubject {
public:
	ConcreteSubject() : m_state(0) {}

	void setState(int i) {
		m_state = i;
		notify();
	}

	int getState() {
		return m_state;
	}

private:
	int m_state;
};
