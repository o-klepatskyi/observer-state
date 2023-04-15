#pragma once
// by Tony Van Eerd

#include <vector>
#include <algorithm>
#include <string>

#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>
#include <memory>
#include <atomic>

class Subject
{
	std::string s;
	std::recursive_mutex mu;
	typedef std::lock_guard<std::recursive_mutex> LockGuard;
public:
	void set(std::string str) {
		LockGuard lock(mu);
		if (s != str) {
			s = str;
			notifyListeners();
		}
	}

	std::string get() {
		LockGuard lock(mu);  return s;
	}

	struct Listener
	{
		Listener() : newData(false), keepGoing(false) { }

		virtual void onNotify(std::string s) = 0;
		virtual ~Listener() {}

		void stop() {
			keepGoing = false; condvar.notify_all();
		}

		void for_every_change()
		{
			keepGoing = true;
			while (keepGoing)
			{
				std::unique_lock<std::mutex> lock(mu);
				condvar.wait(lock, [&] { return newData || !keepGoing; });
				newData = false; // no more data
				std::string temp = info;
				lock.unlock();
				onNotify(temp);
			}
		}

		void check_for_change()
		{
			std::unique_lock<std::mutex> lock(mu);
			if (newData) {
				newData = false;
				std::string temp = info;
				lock.unlock();
				onNotify(temp);
			}
		}

		void informSubjectChanged(std::string s)
		{
			{
				std::lock_guard<std::mutex> lock(mu);
				// push onto a queue usually
				info = s;
				newData = true;
			}
			condvar.notify_all();
		}

	private:
		// info can be a queue of events
		std::string info;
		std::mutex mu;
		std::condition_variable condvar;
		bool newData;
		std::atomic<bool> keepGoing;
	};

	void addListener(Listener* listener) {
		LockGuard lock(mu);
		listeners.push_back(listener);
	}

	bool removeListener(Listener* listener) {
		LockGuard lock(mu);
		for (auto it = listeners.end(); it != listeners.begin(); )
		{
			it--;
			if (*it == listener) {
				listeners.erase(it);
				return true;
			}
		}
		return false;
	}

private:

	void notifyListeners() {
		LockGuard lock(mu);
		for (auto listener : listeners)
			listener->informSubjectChanged(get());
	}

	std::vector<Listener* > listeners;
};
