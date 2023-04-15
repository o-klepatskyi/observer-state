#pragma once
#include "Tool.h"
#include "ICanvas.h"
#include "Point.h"
#include "../observer-gui/Line.h"

class LineTool : public Tool {
public:
	LineTool(ICanvas& canvas) : Tool(canvas) {}

	virtual void onMousePressed(SDL_MouseButtonEvent& event) {
		if (event.button == SDL_BUTTON_LEFT) {
			mouse_dragged = true;
			m_line = std::make_shared<Line>(event.x, event.y, event.x, event.y);
		}
	};

	virtual void onMouseReleased(SDL_MouseButtonEvent& event) {
		if (event.button == SDL_BUTTON_LEFT) {
			mouse_dragged = false;
			if (m_line) {
				m_canvas.add(m_line);
				m_line.reset();
			}
		}
	};

	virtual void onMouseMoved(SDL_MouseMotionEvent& event) {
		if (mouse_dragged) {
			m_line->setSecondPoint(event.x, event.y);
		}
	};

protected:
	void doRender(SDL_Renderer* renderer) override {
		if (m_line) {
			m_line->render(renderer);
		}
	}

private:
	bool mouse_dragged = false;
	std::shared_ptr<Line> m_line = nullptr;
};