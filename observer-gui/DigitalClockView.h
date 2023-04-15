#pragma once
#include "IObject.h"
#include "ClockModel.h"
#include "TextElement.h"
#include "../observer-final/MultithreadObserver.h"

std::string toString(const Time& time);

class DigitalClockView : public IObject, public MultithreadObserver<Time> {
public:
	DigitalClockView(int x, int y, Font::Ptr font, const SDL_Color& color = { 0,255,0 }, const Time& startTime = {0,0})
	: MultithreadObserver([&](Time time) { setTime(time); }), 
		m_text(toString(startTime), font, x, y, 0, 0, color) {

	}

	void doRender(SDL_Renderer* renderer) {
		check_for_change();
		m_text.render(renderer);
	}

	void setTime(const Time& time) {
		m_text.setText(toString(time));
	}

private:
	TextElement m_text;
};

std::string toString(const Time& time) {
	std::string str;

	str += ('0' + time.hours() / 10);
	str += ('0' + time.hours() % 10);
	str += ':';
	str += ('0' + time.minutes() / 10);
	str += ('0' + time.minutes() % 10);

	return str;
}