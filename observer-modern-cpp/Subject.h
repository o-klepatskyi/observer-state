#pragma once
// Copyright (C) 2022 Klaus Iglberger - All Rights Reserved
// ---- <Subject.h> --------------------------------------------------------
#include "Observer.h"
#include <list>

template<class Derived, typename StateTag>
class Subject {
public:

	void attach(Observer<Derived, StateTag>* observer) {
		m_observers.push_back(observer);
	}

	void detach(Observer<Derived, StateTag>* observer) {
		m_observers.remove(observer);
	}

	void notify(StateTag property) {
		for (auto o : m_observers) {
			o->onNotify(*static_cast<Derived*>(this), property);
		}
	}

private:
	std::list<Observer<Derived, StateTag>*> m_observers;
};

