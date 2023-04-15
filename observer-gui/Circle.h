#pragma once
#include "IObject.h"

class Circle : public IObject {
public:
    Circle(int x, int y, int radius, const SDL_Color& color = {255,255,255})
		: m_cx(x), m_cy(y), m_radius(radius), m_color(color) {}

	void doRender(SDL_Renderer* renderer) override {
        SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);

        const int diameter = (m_radius * 2);

        int32_t x = (m_radius - 1);
        int32_t y = 0;
        int32_t tx = 1;
        int32_t ty = 1;
        int32_t error = (tx - diameter);

        while (x >= y)
        {
            SDL_RenderDrawPoint(renderer, m_cx + x, m_cy - y);
            SDL_RenderDrawPoint(renderer, m_cx + x, m_cy + y);
            SDL_RenderDrawPoint(renderer, m_cx - x, m_cy - y);
            SDL_RenderDrawPoint(renderer, m_cx - x, m_cy + y);
            SDL_RenderDrawPoint(renderer, m_cx + y, m_cy - x);
            SDL_RenderDrawPoint(renderer, m_cx + y, m_cy + x);
            SDL_RenderDrawPoint(renderer, m_cx - y, m_cy - x);
            SDL_RenderDrawPoint(renderer, m_cx - y, m_cy + x);

            if (error <= 0)
            {
                ++y;
                error += ty;
                ty += 2;
            }

            if (error > 0)
            {
                --x;
                tx += 2;
                error += (tx - diameter);
            }
        }
	}

    void setRadius(int r) {
        if (r > 0) {
            m_radius = r;
        }
    }

    int cx() { return m_cx; }
    int cy() { return m_cy; }

private:
	int m_cx;
	int m_cy;
	int m_radius;
	SDL_Color m_color;
};