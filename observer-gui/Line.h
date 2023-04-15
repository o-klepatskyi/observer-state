#pragma once
#include "IObject.h"

class Line : public IObject {
public:
	Line(int x1, int y1, int x2, int y2, const SDL_Color& color = {255,255,255})
		: m_x1(x1), m_y1(y1), m_x2(x2), m_y2(y2), m_color(color)
	{}

	void doRender(SDL_Renderer* renderer) override {
		SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);
		SDL_RenderDrawLine(renderer, m_x1, m_y1, m_x2, m_y2);
	}

	void setFirstPoint(int x1, int y1) {
		m_x1 = x1;
		m_y1 = y1;
	}

	void setSecondPoint(int x2, int y2) {
		m_x2 = x2;
		m_y2 = y2;
	}

private:
	int m_x1;
	int m_y1;
	int m_x2;
	int m_y2;
	SDL_Color m_color;
};