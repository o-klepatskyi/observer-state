#pragma once
#include "Tool.h"
#include "ICanvas.h"
#include <unordered_map>

template<typename EnumType>
class ToolController {
public:

	using ToolBindingMap = std::unordered_map<EnumType, IToolFactory::Ptr>;

	ToolController(ICanvas& canvas) :
		m_canvas(canvas) {}

	void setKeyBinding(ToolBindingMap map) {
		m_toolmap = std::move(map);
	}

	void chooseTool(EnumType key) {
		auto factory = m_toolmap.find(key);
		if (factory != m_toolmap.end()) {
			m_canvas.changeTool(factory->second);
		}
	}

private:
	ICanvas& m_canvas;
	ToolBindingMap m_toolmap;
};