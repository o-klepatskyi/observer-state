#pragma once
#include "ICanvas.h"
#include <vector>

class Canvas : public ICanvas {
public:
	void add(IObject::Ptr object) {
		m_objects.push_back(object);
	}

	void clear() override {
		m_objects.clear();
	}

protected:
	void renderCanvas(SDL_Renderer* renderer) override {
		for (auto& object : m_objects) {
			object->render(renderer);
		}
	}

private:
	SDL_Color m_color = { 255,255,255 };
	std::vector<IObject::Ptr> m_objects;
};