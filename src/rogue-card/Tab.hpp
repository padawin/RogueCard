#ifndef __TAB__
#define __TAB__

#include <string>
#include "../sdl2/Text.hpp"

class Tab {
	private:
	// The Tab will take the whole screen width, and can be placed vertically
	// only
	int m_iY = 0;
	int m_iSelectedTab = 0;
	// The tab has 2 texts only
	Text m_text1 = Text();
	Text m_text2 = Text();
	int m_iText1X = 0;
	int m_iText2X = 0;

	void _updateCursorPos();

	public:
	Tab(std::string text1, std::string text2, int y, int selected = 0);
	void render(SDL_Renderer *renderer);
	void selectNext();
	void selectPrev();
};

#endif
