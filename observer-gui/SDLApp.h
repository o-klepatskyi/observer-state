#pragma once

#include <iostream>
#include <unordered_set>
#include <atomic>

#include "SDL.h"
#include "IObject.h"

class SDLApp {
public:
	SDLApp(const char* title, int x, int y, int w, int h) {
		init(title, x, y, w, h);
	}

	virtual ~SDLApp() {
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}

	void run() {
		while (m_running) {
			checkEvents();
			render();

			SDL_Delay(1000 / FPS);
		}
	}

	bool isRunning() const {
		return m_running;
	}

protected:
	virtual void eventCallback(SDL_Event& event) {}

	bool addObject(IObject::Ptr object) {
		auto [_, inserted] = m_objects.insert(object);
		return inserted;
	}

	bool removeObject(IObject::Ptr object) {
		return m_objects.erase(object);
	}

private:
	void checkEvents() {
		SDL_Event event;

		if (SDL_PollEvent(&event)) {
			eventCallback(event);

			switch (event.type)
			{
			case SDL_QUIT:
				m_running = false;
				break;
			}
		}
	}

	void render() {
		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
		SDL_RenderClear(m_renderer);

		for (auto& object : m_objects) {
			object->render(m_renderer);
		}

		SDL_RenderPresent(m_renderer);
	}

private:
	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;
	std::atomic<bool> m_running = true;

	std::unordered_set<IObject::Ptr> m_objects;

	void init(const char* title, int x, int y, int w, int h) {
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			std::cout << "SDL cound not be initialized: \n"
				<< SDL_GetError() << "\n";
			return;
		}
		else {
			std::cout << "SDL is initialized!\n";
		}

		m_window = SDL_CreateWindow(title, x, y, w, h, SDL_WINDOW_SHOWN);
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	}

	static const int FPS = 300;
};