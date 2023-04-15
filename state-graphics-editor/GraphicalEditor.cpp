#include "GraphicalEditor.h"
#include "BrushTool.h"
#include "LineTool.h"
#include "CircleTool.h"
#include "ClearTool.h"

// here we can change bindings for buttons

ToolController<SDL_Scancode>::ToolBindingMap GraphicalEditor::binding_map = {
	{SDL_SCANCODE_1, std::make_shared<ToolFactory<BrushTool>>() },
	{SDL_SCANCODE_2, std::make_shared<ToolFactory<LineTool>>() },
	{SDL_SCANCODE_3, std::make_shared<ToolFactory<CircleTool>>() },
	{SDL_SCANCODE_SPACE, std::make_shared<ToolFactory<ClearTool>>() },
};