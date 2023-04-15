#pragma once

class Time {
public:
	Time(int hours = 0, int minutes = 0)
		: m_hours(hours), m_minutes(minutes) {
		validate();
	}

	Time(const Time&) = default;
	Time& operator=(const Time&) = default;

	void changeInMinutes(int dm = 1) {
		m_minutes += dm;
		validate();
	}

	void changeInHours(int dh = 1) {
		m_hours += dh;
		validate();
	}

	int minutes() const {
		return m_minutes;
	}

	int hours() const {
		return m_hours;
	}

private:
	void validate() {
		m_hours += m_minutes / 60;
		m_minutes = m_minutes % 60;
		if (m_minutes < 0) {
			m_minutes += 60;
			m_hours -= 1;
		}
		m_hours = m_hours % 24;
		if (m_hours < 0)
			m_hours += 24;
	}

	int m_hours;
	int m_minutes;
};

bool operator==(const Time& lhs, const Time& rhs) {
	return lhs.hours() == rhs.hours() && lhs.minutes() == rhs.minutes();
}

bool operator!=(const Time& lhs, const Time& rhs) {
	return !(lhs == rhs);
}