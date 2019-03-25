#ifndef __OBJECT_ACTION__
#define __OBJECT_ACTION__

#include <memory>
#include "../sdl2/Renderer.hpp"
#include "../sdl2/Text.hpp"
#include "../ObjectCard.hpp"

enum E_ObjectActionMenuItem {USE, INFO, DISCARD, ACTIONBAR, BACK, NB_ITEMS};

class ObjectAction {
	int m_iNbVisibleItems = 0;
	int m_iSelectedItemIndex = 0;
	E_ObjectActionMenuItem m_selectedAction = USE;
	int m_iCursorPosition = 0;
	std::shared_ptr<ObjectCard> m_card = nullptr;
	std::pair<Text, int> m_itemTexts[NB_ITEMS]= {};
	std::shared_ptr<SDL2Renderer> m_renderer;

	protected:
	void _renderBackground(int spriteIndex, int y);
	void _renderItems();
	void _renderCursor();
	void _renderItem(int itemIndex, int visibleIndex);
	void _setSelectedAction();
	void _setCursorPosition();
	void _reset();

	public:
	ObjectAction(std::shared_ptr<SDL2Renderer> m_renderer);
	~ObjectAction() {}
	void open(std::shared_ptr<ObjectCard> card, bool inActionBar);
	bool isOpen() const;
	void close();
	void render();
	void selectPrevious();
	void selectNext();
	E_ObjectActionMenuItem getSelectedAction() const;
};

#endif
