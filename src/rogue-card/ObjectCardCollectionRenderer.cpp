#include "../game/globals.hpp"
#include "../sdl2/TextureManager.hpp"
#include "ObjectCardCollectionRenderer.hpp"

#define OFFSET_X 16
#define OFFSET_Y 16
#define PAGE_WIDTH_CARDS 6

ObjectCardCollectionRenderer::ObjectCardCollectionRenderer(
	UserActions &userActions,
	ObjectCardCollection &collection,
	Equipment &equipment,
	int pageSize,
	std::string background,
	std::shared_ptr<SDL2Renderer> renderer
) :
	m_iPageSize(pageSize),
	m_sBackground(background),
	m_userActions(userActions),
	m_collection(collection),
	m_equipment(equipment),
	m_renderer(renderer)
{
	m_iLastPage = (CARD_COLLECTION_SIZE - m_iPageSize) / PAGE_WIDTH_CARDS + 1;
}

void ObjectCardCollectionRenderer::update() {
	if (m_userActions.getActionState("CURSOR_UP")) {
		moveCursorUp();
	}
	else if (m_userActions.getActionState("CURSOR_DOWN")) {
		moveCursorDown();
	}
	else if (m_userActions.getActionState("CURSOR_LEFT")) {
		moveCursorLeft();
	}
	else if (m_userActions.getActionState("CURSOR_RIGHT")) {
		moveCursorRight();
	}
}

void ObjectCardCollectionRenderer::moveCursorUp() {
	// Cursor on the first row, go at the bottom
	if (m_cursorPosition < PAGE_WIDTH_CARDS) {
		if (m_iPage == 1) {
			m_cursorPosition += PAGE_WIDTH_CARDS * (m_iPageSize / PAGE_WIDTH_CARDS - 1);
			m_iPage = m_iLastPage;
		}
		else {
			m_iPage--;
		}
	}
	// Cursor anywhere else, go up
	else {
		m_cursorPosition -= PAGE_WIDTH_CARDS;
	}
}

void ObjectCardCollectionRenderer::moveCursorDown() {
	if (m_cursorPosition >= m_iPageSize - PAGE_WIDTH_CARDS) {
		// go at the top
		if (m_iPage == m_iLastPage) {
			m_cursorPosition = m_cursorPosition % PAGE_WIDTH_CARDS;
			m_iPage = 1;
		}
		else {
			m_iPage++;
		}
	}
	else {
		m_cursorPosition += 6;
	}
}

void ObjectCardCollectionRenderer::moveCursorLeft() {
	if (m_cursorPosition % PAGE_WIDTH_CARDS == 0) {
		m_cursorPosition += PAGE_WIDTH_CARDS - 1;
	}
	else {
		m_cursorPosition--;
	}
}

void ObjectCardCollectionRenderer::moveCursorRight() {
	if ((m_cursorPosition + 1) % PAGE_WIDTH_CARDS == 0) {
		m_cursorPosition -= PAGE_WIDTH_CARDS - 1;
	}
	else {
		m_cursorPosition++;
	}
}


void ObjectCardCollectionRenderer::render() const {
	_renderBackground();
	_renderCards();
	_renderCursor();
}

void ObjectCardCollectionRenderer::_renderBackground() const {
	TextureManager::Instance()->draw(
		m_sBackground,  0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, m_renderer->getRenderer()
	);
}

void ObjectCardCollectionRenderer::_renderCards() const {
	int startCard = (m_iPage - 1) * PAGE_WIDTH_CARDS;
	int endCard = startCard + m_iPageSize;

	for (int c = startCard; c < endCard; ++c) {
		auto card = m_collection.getCard(c);
		if (card == nullptr) {
			continue;
		}
		int positionIndexX = (c - startCard) % PAGE_WIDTH_CARDS;
		int positionIndexY = (c - startCard) / PAGE_WIDTH_CARDS;
		int x = OFFSET_X + CARD_WIDTH * (int) positionIndexX;
		int y = OFFSET_Y + CARD_HEIGHT * (int) positionIndexY;
		card->render(m_renderer->getRenderer(), x, y);
	}
}

void ObjectCardCollectionRenderer::_renderCursor() const {
	int x = OFFSET_X + CARD_WIDTH * ((int) m_cursorPosition % PAGE_WIDTH_CARDS);
	int y = OFFSET_Y + CARD_HEIGHT * ((int) m_cursorPosition / PAGE_WIDTH_CARDS);
	TextureManager::Instance()->draw(
		"cursor", x, y, CARD_WIDTH, CARD_HEIGHT, m_renderer->getRenderer()
	);
}

/**
 * Return the index in the player's inventory of the card under the cursor.
 */
int ObjectCardCollectionRenderer::getSelectedCardIndex() const {
	return (m_iPage - 1) * PAGE_WIDTH_CARDS + m_cursorPosition;
}

void ObjectCardCollectionRenderer::reset() {
	m_cursorPosition = 0;
	m_iPage = 1;
}
