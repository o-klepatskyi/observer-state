#pragma once
// ---- <ISubject.h> --------------------------------------------------------

#include "IObserver.h"
#include <unordered_set>

class ISubject {
public:
	void attach(IObserver* observer) {
		if (observer != nullptr) {
			m_observers.insert(observer);
		}
	}

	void detach(IObserver* observer) {
		m_observers.erase(observer);
	}

	void notify() {
		for (auto observer : m_observers) {
			observer->onNotify();
		}
	}

private:
	std::unordered_set<IObserver*> m_observers;
};

