#pragma once

#include "../observer-gui/IObject.h"

class Point : public IObject {
public:
	Point(int x, int y, SDL_Color color = {255,255,255}) :
		m_x(x), m_y(y), m_color(color) {}


protected:
	void doRender(SDL_Renderer* renderer) {
		SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);
		SDL_RenderDrawPoint(renderer, m_x, m_y);
	}

private:
	int m_x, m_y;
	SDL_Color m_color;
};