#pragma once
#include <functional>
#include <exception>
#include <mutex>

template<typename Data>
class MultithreadObserver
{
public:
	using NotifyCallback = std::function<void(Data)>;

	explicit MultithreadObserver(NotifyCallback notifyCallback)
		: m_onUpdate(std::move(notifyCallback)) {
		if (!m_onUpdate) {
			throw std::exception("You need to provide non-empty function.");
		}
	}

	virtual ~MultithreadObserver() {
		stop();
	}

	void stop() {
		keepGoing = false;
		condvar.notify_all();
	}

	void for_every_change() {
		keepGoing = true;
		while (keepGoing)
		{
			std::unique_lock<std::mutex> lock(mu);
			condvar.wait(lock, [&] { return newData || !keepGoing; });
			if (!keepGoing) {
				return;
			}
			newData = false; // no more data
			Data temp = info;
			lock.unlock();
			m_onUpdate(temp);
		}
	}

	void check_for_change() {
		std::unique_lock<std::mutex> lock(mu);
		if (newData) {
			newData = false;
			Data temp = info;
			lock.unlock();
			m_onUpdate(temp);
		}
	}

	void onNotify(Data s) {
		{
			std::lock_guard<std::mutex> lock(mu);
			// push onto a queue usually
			info = s;
			newData = true;
		}
		condvar.notify_all();
	}

private:
	NotifyCallback m_onUpdate;
	std::mutex mu;
	std::condition_variable condvar;
	bool newData = false;
	std::atomic<bool> keepGoing = false;
	Data info;
};