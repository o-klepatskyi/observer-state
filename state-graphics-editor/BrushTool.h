#pragma once
#include "Tool.h"
#include "ICanvas.h"
#include "Point.h"

class BrushTool : public Tool {
public:
	BrushTool(ICanvas& canvas) : Tool(canvas) {}

	virtual void onMousePressed(SDL_MouseButtonEvent& event) {
		if (event.button == SDL_BUTTON_LEFT) {
			mouse_dragged = true;
			m_canvas.add(std::make_shared<Point>(event.x, event.y));
		}
	};

	virtual void onMouseReleased(SDL_MouseButtonEvent& event) {
		if (event.button == SDL_BUTTON_LEFT) {
			mouse_dragged = false;
		}
	};

	virtual void onMouseMoved(SDL_MouseMotionEvent& event) {
		if (mouse_dragged) {
			m_canvas.add(std::make_shared<Point>(event.x, event.y));
		}
	};

private:
	bool mouse_dragged = false;
};
