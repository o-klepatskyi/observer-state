#pragma once
#include "SDLApp.h"
#include "AnalogClockView.h"
#include "DigitalClockView.h"

class ClockApp : public SDLApp {

public:
	ClockApp() :
		SDLApp("Clock Application",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT),

		m_digitalClock(std::make_shared<DigitalClockView>(
			SCREEN_WIDTH / 3, 0, Font::getFont(FONT, 100), WHITE)),

		m_analogClock(std::make_shared<AnalogClockView>(
			SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 150, WHITE
		)),

		m_clockModel(std::make_shared<ClockModel>(Time(15, 30), 1000)) {

		addObject(m_analogClock);
		addObject(m_digitalClock);
		m_clockModel->attach(m_digitalClock);
		m_clockModel->attach(m_analogClock);

		std::thread timerThread([&]() { m_clockModel->run(); });
		timerThread.detach();
	}

	void eventCallback(SDL_Event& event) override {
		if (event.type == SDL_KEYUP) {
			processKeyPressed(event.key.keysym.scancode);
		}
	}

private:
	void processKeyPressed(SDL_Scancode& key) {
		if (key == SDL_SCANCODE_1) {
			if (m_digitalAttached) {
				m_clockModel->detach(m_digitalClock);
				std::cout << "Digital clock detached!\n";
			}
			else {
				m_clockModel->attach(m_digitalClock);
				std::cout << "Digital clock attached!\n";
			}
			m_digitalAttached = !m_digitalAttached;
		} else if (key == SDL_SCANCODE_2) {
			if (m_analogAttached) {
				m_clockModel->detach(m_analogClock);
				std::cout << "Analog clock detached!\n";
			}
			else {
				m_clockModel->attach(m_analogClock);
				std::cout << "Analog clock attached!\n";
			}
			m_analogAttached = !m_analogAttached;
		}
	}

	bool m_analogAttached = true;
	bool m_digitalAttached = true;

	std::shared_ptr<AnalogClockView> m_analogClock;
	std::shared_ptr<DigitalClockView> m_digitalClock;
	std::shared_ptr<ClockModel> m_clockModel;

	static const char* const FONT;
	static const int SCREEN_WIDTH = 640;
	static const int SCREEN_HEIGHT = 480;
	static const int KEY_1 = 30;
	static const int KEY_2 = 31;
	static const SDL_Color WHITE;
};

const char* const ClockApp::FONT = DIGITAL_FONT;
const SDL_Color ClockApp::WHITE = { 255,255,255 };