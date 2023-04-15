#pragma once
#include <memory>
#include "SDL.h"
class IObject {
public:
	using Ptr = std::shared_ptr<IObject>;

	virtual ~IObject() {}
	void render(SDL_Renderer* renderer) {
		if (renderer != nullptr) {
			doRender(renderer);
		}
	}
protected:
	virtual void doRender(SDL_Renderer* renderer) = 0;
};