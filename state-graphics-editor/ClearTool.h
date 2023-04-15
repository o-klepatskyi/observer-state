#pragma once
#include "Tool.h"
#include "ICanvas.h"

class ClearTool : public Tool {
public:
	ClearTool(ICanvas& canvas) : Tool(canvas) {
		canvas.clear();
	}
};
