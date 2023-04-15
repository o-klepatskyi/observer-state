#pragma once
// ---- <ConcreteObserver.h> --------------------------------------------------------

#include "IObserver.h"
#include "ConcreteSubject.h"
#include <iostream>

class ConcreteObserver : public IObserver {
public:
	ConcreteObserver(ConcreteSubject& subject)
		: m_subject(subject), m_observerState(subject.getState()) {
		m_subject.attach(this);
	}

	void onNotify() {
		m_observerState = m_subject.getState();
		std::cout << "Notified and updated state to "
			<< m_observerState << "\n";
	}

private:
	ConcreteSubject& m_subject;
	int m_observerState;
};

