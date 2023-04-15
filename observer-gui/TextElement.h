#pragma once
#include "IObject.h"
#include "SurfaceWrapper.h"
#include "TextureWrapper.h"
#include "Font.h"
#include <string>

class TextElement : public IObject {
public:
	TextElement(const std::string& text, 
		Font::Ptr font, 
		int x, int y, int w = 0, int h = 0, 
		const SDL_Color& color = {255,255,255})
		: m_text(text), m_bounds(), m_font(font), m_color(color)
	{
		initBounds(x, y, w, h);
	}

	void setText(const std::string& newText) {
		m_text = newText;
		m_surface = nullptr;
		m_surface = nullptr;
	}

protected:
	void doRender(SDL_Renderer* renderer) override {
		if (m_surface == nullptr) {
			initTexture(renderer);
		}

		SDL_RenderCopy(renderer, m_texture->get(), NULL, &m_bounds);
	}

	void initTexture(SDL_Renderer* renderer) {
		m_surface = std::make_unique<SurfaceWrapper>(
			TTF_RenderText_Solid(m_font->get(), m_text.c_str(), m_color));
		m_texture = std::make_unique<TextureWrapper>(
			SDL_CreateTextureFromSurface(renderer, m_surface->get()));


		if (m_bounds.w == 0) {
			m_bounds.w = m_surface->get()->w;
		}
		if (m_bounds.h == 0) {
			m_bounds.h = m_surface->get()->h;
		}
	}

	void initBounds(int x, int y, int w, int h) {
		m_bounds.x = x;
		m_bounds.y = y;
		m_bounds.w = w;
		m_bounds.h = h;
	}

private:
	std::string m_text;
	SDL_Rect m_bounds;
	Font::Ptr m_font;
	SDL_Color m_color;
	std::unique_ptr<SurfaceWrapper> m_surface;
	std::unique_ptr<TextureWrapper> m_texture;
};