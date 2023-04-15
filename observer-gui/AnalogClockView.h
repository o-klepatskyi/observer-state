#pragma once

#include "IObject.h"
#include "Time.h"
#include "Circle.h"
#include "Line.h"
#include "ClockModel.h"
#include "../observer-final/MultithreadObserver.h"

#include <math.h>

class AnalogClockView : public IObject, public MultithreadObserver<Time> {
public:
	AnalogClockView(int centerX, int centerY, int radius, 
		const SDL_Color& color, const Time& time = { 0,0 })
		: MultithreadObserver([&](Time time) {setTime(time); }),
		
		m_cx(centerX), m_cy(centerY), m_radius(radius), m_time(time),
		m_circle(centerX, centerY, radius, color),
		m_hourArrow(0, 0, 0, 0, color), m_minuteArrow(0, 0, 0, 0, color) {
		m_hourArrow.setFirstPoint(centerX, centerY);
		m_minuteArrow.setFirstPoint(centerX, centerY);

		moveArrows();
	}

	void doRender(SDL_Renderer* renderer) override {
		check_for_change();
		m_circle.render(renderer);
		m_hourArrow.render(renderer);
		m_minuteArrow.render(renderer);
	}

	void setTime(const Time& time) {
		m_time = time;
		moveArrows();
	}

private:
	void moveArrows() {
		{
			double alpha = (3 - m_time.hours()) * M_PI / 6 - m_time.minutes() * M_PI / 360;
			int x = m_cx + m_radius * 0.5 * cos(alpha);
			int y = m_cy - m_radius * 0.5 * sin(alpha);
			m_hourArrow.setSecondPoint(x, y);
		}
		{
			double alpha = (15 - m_time.minutes()) * M_PI / 30;
			int x = m_cx + m_radius * 0.9 * cos(alpha);
			int y = m_cy - m_radius * 0.9 * sin(alpha);
			m_minuteArrow.setSecondPoint(x, y);
		}
	}

	int m_cx;
	int m_cy;
	int m_radius;
	Time m_time;
	Circle m_circle;
	Line m_hourArrow;
	Line m_minuteArrow;
};