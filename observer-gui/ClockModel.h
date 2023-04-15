#pragma once

#include "Time.h"
#include "../observer-final/MultithreadSubject.h"

#include <atomic>

class ClockModel : public MultithreadSubject<Time>  {
public:
	ClockModel(const Time& start, int updateRateMs)
		: m_currentTime(start), m_updateRateMs(updateRateMs) {
	}

	~ClockModel() {
		stop();
	}

	void run() {
		m_running = true;
		while (m_running) {
			std::this_thread::sleep_for(std::chrono::milliseconds(m_updateRateMs));
			m_currentTime.changeInMinutes(1);
			set(m_currentTime);
		}
	}

	void stop() {
		m_running = false;
	}

	Time time() const {
		return m_currentTime;
	}

private:
	Time m_currentTime;
	int m_updateRateMs;
	std::atomic<bool> m_running = true;
};