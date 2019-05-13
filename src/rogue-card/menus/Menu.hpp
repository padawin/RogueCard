#ifndef __MENU__
#define __MENU__

#include <memory>
#include "../sdl2/Renderer.hpp"
#include "../sdl2/Text.hpp"

struct S_MenuItem {
	Text text = Text();
	unsigned int context = 0;
	bool valid = false;
};

class Menu {
	protected:
	std::shared_ptr<SDL2Renderer> m_renderer;
	int m_iNbVisibleItems = 0;
	int m_iSelectedItemIndex = 0;
	int m_selectedAction = 0;
	int m_iCursorPosition = 0;
	unsigned int m_iContext = 0;
	int m_iX = 0;
	int m_iY = 0;
	int m_iWidth = 0;
	int m_iTextMaxWidth = 0;

	void _renderBackground(int spriteIndex, int y);
	void _renderItems();
	void _renderCursor();
	void _renderItem(S_MenuItem item, int visibleIndex);
	void _setSelectedAction();
	void _setCursorPosition();
	void _reset();
	virtual int _getNbItems() const = 0;
	virtual S_MenuItem &_getItem(int itemIndex) = 0;
	virtual bool _isItemValid(int itemIndex);

	public:
	Menu(std::shared_ptr<SDL2Renderer> renderer);
	virtual ~Menu() {}
	void init();
	void setContext(unsigned int context);
	void render();
	void selectPrevious();
	void selectNext();
};

#endif
