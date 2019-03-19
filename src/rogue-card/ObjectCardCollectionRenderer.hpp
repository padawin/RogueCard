#ifndef __OBJECT_CARD_COLLECTION_RENDERER__
#define __OBJECT_CARD_COLLECTION_RENDERER__

#include <string>
#include <memory>
#include "../sdl2/Renderer.hpp"
#include "../game/UserActions.hpp"
#include "ObjectCardCollection.hpp"

class ObjectCardCollectionRenderer {
	private:
	unsigned int m_cursorPosition = 0;
	unsigned int m_iPage = 1;
	unsigned int m_iLastPage = 1;
	unsigned int m_iPageSize;

	std::string m_sBackground;
	UserActions &m_userActions;
	ObjectCardCollection &m_collection;
	std::shared_ptr<SDL2Renderer> m_renderer;

	void _renderBackground() const;
	void _renderCards() const;
	void _renderCursor() const;

	public:
	ObjectCardCollectionRenderer(
		UserActions &userActions,
		ObjectCardCollection &collection,
		unsigned int pageSize,
		std::string background,
		std::shared_ptr<SDL2Renderer> renderer
	);
	void update();
	void moveCursorUp();
	void moveCursorDown();
	void moveCursorLeft();
	void moveCursorRight();
	void render() const;
	unsigned int getSelectedCardIndex() const;
	void reset();
};

#endif
