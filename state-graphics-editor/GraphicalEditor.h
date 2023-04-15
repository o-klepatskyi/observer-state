#pragma once
#include "Canvas.h"
#include "ToolController.h"
#include "../observer-gui/SDLApp.h"

class GraphicalEditor : public SDLApp {
	static const int SCREEN_WIDTH = 640;
	static const int SCREEN_HEIGHT = 480;
public:
	GraphicalEditor() :
		SDLApp("Graphical editor",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT),
		m_canvas(std::make_shared<Canvas>()),
		m_toolController(*m_canvas) {
		addObject(m_canvas);
		m_toolController.setKeyBinding(binding_map);
	}

	~GraphicalEditor() {}

protected:
	void eventCallback(SDL_Event& event) override {
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			m_canvas->onMousePressed(event.button);
		}
		else if (event.type == SDL_MOUSEBUTTONUP) {
			m_canvas->onMouseReleased(event.button);
		}
		else if (event.type == SDL_MOUSEMOTION) {
			m_canvas->onMouseMoved(event.motion);
		}
		else if (event.type == SDL_KEYDOWN) {
			m_toolController.chooseTool(event.key.keysym.scancode);
		}
	}

private:
	std::shared_ptr<Canvas> m_canvas;
	ToolController<SDL_Scancode> m_toolController;
	static ToolController<SDL_Scancode>::ToolBindingMap binding_map;
};