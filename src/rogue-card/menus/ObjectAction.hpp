#ifndef __OBJECT_ACTION__
#define __OBJECT_ACTION__

#include <memory>
#include "../sdl2/Renderer.hpp"
#include "../sdl2/Text.hpp"
#include "../ObjectCard.hpp"

class ObjectAction {
	const int m_iNbItems = 6;
	int m_iNbVisibleItems = 0;
	int m_iCursorPosition = 0;
	std::shared_ptr<ObjectCard> m_card = nullptr;
	std::pair<Text, int> m_itemTexts[6]= {};
	std::shared_ptr<SDL2Renderer> m_renderer;

	protected:
	void _renderBackground(int spriteIndex, int y);
	void _renderItems();
	void _renderCursor();
	void _renderItem(int itemIndex, int visibleIndex);

	public:
	ObjectAction(std::shared_ptr<SDL2Renderer> m_renderer);
	void setCard(std::shared_ptr<ObjectCard> card);
	void reset();
	void render();
};

#endif
