#ifndef __OBJECT_CARD_COLLECTION_RENDERER__
#define __OBJECT_CARD_COLLECTION_RENDERER__

#include <string>
#include <memory>
#include "../sdl2/Renderer.hpp"
#include "../sdl2/Text.hpp"
#include "../game/UserActions.hpp"
#include "ObjectCardCollection.hpp"
#include "Equipment.hpp"

class ObjectCardCollectionRenderer {
	private:
	int m_cursorPosition = 0;
	int m_iPage = 1;
	int m_iLastPage = 1;
	int m_iPageSize;

	std::string m_sBackground;
	UserActions &m_userActions;
	ObjectCardCollection &m_collection;
	Equipment &m_equipment;
	Text m_equippedText;
	std::shared_ptr<SDL2Renderer> m_renderer;

	void _renderBackground() const;
	void _renderCards() const;
	void _renderCursor() const;

	public:
	ObjectCardCollectionRenderer(
		UserActions &userActions,
		ObjectCardCollection &collection,
		Equipment &equipment,
		int pageSize,
		std::string background,
		std::shared_ptr<SDL2Renderer> renderer
	);
	~ObjectCardCollectionRenderer() {}
	void update();
	void moveCursorUp();
	void moveCursorDown();
	void moveCursorLeft();
	void moveCursorRight();
	void render() const;
	int getSelectedCardIndex() const;
	void reset();
};

#endif
