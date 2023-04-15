#pragma once
#include "SDL.h"
#include <iostream>

class SurfaceWrapper {
public:
	SurfaceWrapper(SDL_Surface* surface = nullptr) : m_surface(surface) {}

	~SurfaceWrapper() {
		if (m_surface != nullptr) {
			SDL_FreeSurface(m_surface);
		}
	}

	SDL_Surface* get() {
		return m_surface;
	}

	operator SDL_Surface* () {
		return m_surface;
	}

private:
	SDL_Surface* m_surface;
};