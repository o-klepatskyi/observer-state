#pragma once

#include "Tool.h"
#include "ICanvas.h"

#include "../observer-gui/Circle.h"

#include <cmath>

class CircleTool : public Tool {
public:
	CircleTool(ICanvas& canvas) : Tool(canvas) {}

	virtual void onMousePressed(SDL_MouseButtonEvent& event) {
		if (event.button == SDL_BUTTON_LEFT) {
			mouse_dragged = true;
			m_circle = std::make_shared<Circle>(event.x, event.y, 0);
		}
	};

	virtual void onMouseReleased(SDL_MouseButtonEvent& event) {
		if (event.button == SDL_BUTTON_LEFT) {
			mouse_dragged = false;
			if (m_circle) {
				m_canvas.add(m_circle);
				m_circle.reset();
			}
		}
	};

	virtual void onMouseMoved(SDL_MouseMotionEvent& event) {
		if (mouse_dragged) {
			setNewRadius(event.x, event.y);
		}
	};

protected:
	void doRender(SDL_Renderer* renderer) override {
		if (m_circle) {
			m_circle->render(renderer);
		}
	}

private:

	void setNewRadius(int x, int y) {
		int dx = m_circle->cx() - x;
		int dy = m_circle->cy() - y;

		int radius = sqrt(dx * dx + dy * dy);
		if (m_circle) {
			m_circle->setRadius(radius);
		}
	}

	bool mouse_dragged = false;
	std::shared_ptr<Circle> m_circle;
};