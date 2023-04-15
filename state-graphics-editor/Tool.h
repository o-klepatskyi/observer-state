#pragma once

#include "../observer-gui/IObject.h"
#include <string>
class ICanvas;

class Tool : public IObject {
public:
	Tool(ICanvas& canvas) : m_canvas(canvas) {}
	virtual ~Tool() {}

	virtual void onMousePressed(SDL_MouseButtonEvent& event) {};
	virtual void onMouseReleased(SDL_MouseButtonEvent& event) {};
	virtual void onMouseMoved(SDL_MouseMotionEvent& event) {};
protected:
	virtual void doRender(SDL_Renderer* renderer) override {};

	ICanvas& m_canvas;
};


class IToolFactory {
public:
	using Ptr = std::shared_ptr<IToolFactory>;

	virtual std::unique_ptr<Tool> createUniqueTool(ICanvas& canvas) = 0;
};

template<typename ToolDerived>
class ToolFactory : public IToolFactory {
public:
	std::unique_ptr<Tool> createUniqueTool(ICanvas& canvas) override {
		return std::make_unique<ToolDerived>(canvas);
	}
};