#pragma once

#include "Tool.h"
#include "../observer-gui/IObject.h"
#include <vector>

class ICanvas : public IObject {
public:
	virtual void add(IObject::Ptr) = 0;

	void onMousePressed(SDL_MouseButtonEvent& event) {
		if (m_tool) {
			m_tool->onMousePressed(event);
		}
	};

	void onMouseReleased(SDL_MouseButtonEvent& event) {
		if (m_tool) {
			m_tool->onMouseReleased(event);
		}
	};

	void onMouseMoved(SDL_MouseMotionEvent& event) {
		if (m_tool) {
			m_tool->onMouseMoved(event);
		}
	};

	/*
	if we have some switch-case for choosing
	appropriate template instantiation, that's fine
	
	template<class Tool>
	void changeTool() {
		m_tool = std::make_unique<Tool>(*this);
	}
	*/

	void changeTool(IToolFactory::Ptr toolFactory) {
		m_tool = toolFactory->createUniqueTool(*this);
	}

	virtual void clear() = 0;

protected:
	void doRender(SDL_Renderer* renderer) override {
		if (m_tool) {
			m_tool->render(renderer);
		}	
		renderCanvas(renderer);
	}

	virtual void renderCanvas(SDL_Renderer* renderer) = 0;

private:
	std::unique_ptr<Tool> m_tool = nullptr;
};