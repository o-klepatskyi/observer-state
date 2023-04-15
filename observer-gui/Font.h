#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include <iostream>
#include <unordered_map>
#include <memory>

const char* const DIGITAL_FONT = SOLUTION_DIR R"(fonts\digital-7.ttf)";

class Font {
public:
	using Ptr = std::shared_ptr<Font>;
private:
	class FontsConfig;
	static FontsConfig i;

	// we need to store pair of font file and font size
	// for correct behaviour, but that's fine for now
	using FontMap = std::unordered_map<std::string, Font::Ptr>;
	static FontMap fonts;
public:
	~Font() {
		if (m_font != nullptr) {
			TTF_CloseFont(m_font);
		}
	}

	static Font::Ptr getFont(const std::string path, int ptsize) {
		auto it = fonts.find(path);
		if (it != fonts.end()) {
			return it->second;
		}

		// TODO bad practise ahead because of private ctor
		// must be like that
		// auto font = std::make_shared<Font>(path, ptsize);
		auto fptr = new Font(path, ptsize);
		Font::Ptr font(fptr);
		fonts.insert({path, font });
		return fonts.find(path)->second;
	}

	TTF_Font* get() {
		return m_font;
	}

	operator TTF_Font* () {
		return m_font;
	}

private:
	Font(const std::string path, int ptsize)
		: m_font(nullptr) {
		m_font = TTF_OpenFont(path.c_str(), ptsize);
		if (m_font != nullptr) {
			std::cout << "Opened font: " << path << "\n";
		}
	}

	Font& operator=(const Font&) = delete;
	Font(const Font&) = delete;

	TTF_Font* m_font;
};

class Font::FontsConfig {
public:
	FontsConfig() {
		if (TTF_Init() < 0) {
			std::cout << "Fonts cound not be initialized.\n";
		}
		else {
			std::cout << "Fonts were initialized.\n";
		}
	}

	~FontsConfig() {
		fonts.clear();
		TTF_Quit();
		std::cout << "TTF closed.\n";
	}
}; 

Font::FontMap Font::fonts;
Font::FontsConfig Font::i;
