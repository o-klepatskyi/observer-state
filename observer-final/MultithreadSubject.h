#pragma once
#include <mutex>
#include <vector>
#include <memory>
#include "MultithreadObserver.h"

template <typename Data>
class MultithreadSubject
{
	using LockGuard = std::lock_guard<std::recursive_mutex>;
	using Observer = MultithreadObserver<Data>;
	using ObserverPtr = std::weak_ptr<Observer>;

public:
	void set(Data newData) {
		LockGuard lock(mu);
		if (m_data != newData) {
			m_data = newData;
			notify();
		}
	}

	Data get() {
		LockGuard lock(mu);
		return m_data;
	}

	void attach(ObserverPtr&& observer) {
		if (observer.lock()) {
			LockGuard lock(mu);
			m_observers.push_back(std::move(observer));
		}
	}

	bool detach(const ObserverPtr& observer) {
		if (!observer.lock()) {
			return false;
		}

		LockGuard lock(mu);
		for (auto it = m_observers.end(); it != m_observers.begin(); ) {
			it--;
			if (!it->owner_before(observer) && !observer.owner_before(*it)) {
				m_observers.erase(it);
				return true;
			}
		}
		return false;
	}

private:
	void notify() {
		LockGuard lock(mu);

		for (auto it = m_observers.begin(); it != m_observers.end();) {
			if (it->expired()) {
				// delete if it doesn't exist
				it = m_observers.erase(it);
			}
			else {
				// otherwise notify!
				it->lock()->onNotify(get());
				it++;
			}
		}
	}

	Data m_data;
	std::vector<ObserverPtr> m_observers;
	std::recursive_mutex mu;
};