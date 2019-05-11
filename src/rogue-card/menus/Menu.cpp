#include "Menu.hpp"
#include "../game/globals.hpp"
#include "../sdl2/TextureManager.hpp"

const int POSITION_X = 32;
const int POSITION_Y = 32;
const int MARGIN_X = 16;
const int MARGIN_Y = 16;
const int TEXT_POS_X = POSITION_X + MARGIN_X;
const int TEXT_POS_Y = POSITION_Y + MARGIN_Y;
const int MENU_WIDTH = SCREEN_WIDTH - POSITION_X * 2;
const int TEXT_MAX_WIDTH = MENU_WIDTH - MARGIN_X * 2;

Menu::Menu(std::shared_ptr<SDL2Renderer> renderer) :
	m_renderer(renderer)
{
}

void Menu::_renderBackground(int spriteIndex, int y) {
	TextureManager::Instance()->drawFrame(
		"menu-background",
		POSITION_X,
		y,
		MENU_WIDTH,
		16,
		0, spriteIndex,
		m_renderer->getRenderer()
	);
}

void Menu::_renderItems() {
	_renderBackground(0, POSITION_Y);
	int nbItems = _getNbItems();
	for (int renderIndex = 0, itemIndex = 0; itemIndex < nbItems; ++itemIndex) {
		S_MenuItem &item = _getItem(itemIndex);
		if (item.valid) {
			_renderBackground(1, TEXT_POS_Y + renderIndex * 16);
			_renderItem(item, renderIndex);
			if (renderIndex == m_iSelectedItemIndex) {
				_renderCursor();
			}
			++renderIndex;
		}
	}
	_renderBackground(2, TEXT_POS_Y + m_iNbVisibleItems * 16);
}

void Menu::_renderCursor() {
	TextureManager::Instance()->drawFrame(
		"menu-background",
		POSITION_X,
		m_iCursorPosition,
		MENU_WIDTH,
		16,
		0, 3,
		m_renderer->getRenderer()
	);
}

void Menu::_renderItem(S_MenuItem item, int visibleIndex) {
	const int x = TEXT_POS_X + (TEXT_MAX_WIDTH - item.text.getLength()) / 2;
	const int y = TEXT_POS_Y + visibleIndex * 16;
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
	m_iCursorPosition = TEXT_POS_Y + m_iSelectedItemIndex * 16;
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
