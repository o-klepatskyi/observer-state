#pragma once

#include "SDL.h"

class TextureWrapper {
public:
	TextureWrapper(SDL_Texture* texture = nullptr) : m_surface(texture) {}

	~TextureWrapper() {
		if (m_surface != nullptr) {
			SDL_DestroyTexture(m_surface);
		}
	}

	SDL_Texture* get() {
		return m_surface;
	}

	operator SDL_Texture* () {
		return m_surface;
	}

private:
	SDL_Texture* m_surface;
};