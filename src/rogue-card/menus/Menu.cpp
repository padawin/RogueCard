#include "Menu.hpp"
#include "globals.hpp"
#include "sdl2/TextureManager.hpp"

const int MARGIN_X = 16;
const int MARGIN_Y = 16;

Menu::Menu(std::shared_ptr<SDL2Renderer> renderer) :
	m_renderer(renderer)
{
}

void Menu::_renderBackground(int spriteIndex, int y) {
	TextureManager::Instance()->drawFrame(
		"menu-background",
		m_iX,
		y,
		m_iWidth,
		16,
		0, spriteIndex,
		m_renderer->getRenderer()
	);
}

void Menu::_renderItems() {
	_renderBackground(0, m_iY);
	int nbItems = _getNbItems();
	for (int renderIndex = 0, itemIndex = 0; itemIndex < nbItems; ++itemIndex) {
		S_MenuItem &item = _getItem(itemIndex);
		if (item.valid) {
			_renderBackground(1, m_iY + MARGIN_Y + renderIndex * 16);
			_renderItem(item, renderIndex);
			if (renderIndex == m_iSelectedItemIndex) {
				_renderCursor();
			}
			++renderIndex;
		}
	}
	_renderBackground(2, m_iY + MARGIN_Y + m_iNbVisibleItems * 16);
}

void Menu::_renderCursor() {
	TextureManager::Instance()->drawFrame(
		"menu-background",
		m_iX,
		m_iCursorPosition,
		m_iWidth,
		16,
		0, 3,
		m_renderer->getRenderer()
	);
}

void Menu::_renderItem(S_MenuItem item, int visibleIndex) {
	const int x = m_iX + MARGIN_X + (m_iTextMaxWidth - item.text.getLength()) / 2;
	const int y = m_iY + MARGIN_Y + visibleIndex * 16;
	item.text.render(m_renderer->getRenderer(), x, y);
}

void Menu::_setSelectedAction() {
	int nbItems = _getNbItems();
	for (int renderIndex = 0, itemIndex = 0; itemIndex < nbItems; ++itemIndex) {
		S_MenuItem &item = _getItem(itemIndex);
		if (item.valid) {
			if (renderIndex == m_iSelectedItemIndex) {
				m_selectedAction = itemIndex;
				break;
			}
			++renderIndex;
		}
	}
}

void Menu::_setCursorPosition() {
	m_iCursorPosition = m_iY + MARGIN_Y + m_iSelectedItemIndex * 16;
}

void Menu::_reset() {
	m_iNbVisibleItems = 0;
	m_iSelectedItemIndex = 0;
	_setCursorPosition();
}

bool Menu::_isItemValid(int itemIndex) {
	unsigned int context = _getItem(itemIndex).context;
	return context == 0 || (context & m_iContext) == context;
}


void Menu::init() {
	m_iWidth = SCREEN_WIDTH - m_iX * 2;
	m_iTextMaxWidth = m_iWidth - MARGIN_X * 2;
	int nbItems = _getNbItems();
	for (int i = 0; i < nbItems; ++i) {
		S_MenuItem &item = _getItem(i);
		if (_isItemValid(i)) {
			++m_iNbVisibleItems;
			item.valid = true;
		}
		else {
			item.valid = false;
		}
	}
	_setSelectedAction();
	_setCursorPosition();
}

void Menu::render() {
	_renderItems();
	_renderCursor();
}

void Menu::selectPrevious() {
	m_iSelectedItemIndex = (m_iNbVisibleItems + m_iSelectedItemIndex - 1) % m_iNbVisibleItems;
	_setSelectedAction();
	_setCursorPosition();
}

void Menu::selectNext() {
	m_iSelectedItemIndex = (m_iSelectedItemIndex + 1) % m_iNbVisibleItems;
	_setSelectedAction();
	_setCursorPosition();
}

void Menu::setContext(unsigned int context) {
	m_iContext = context;
}
