#ifndef __OBJECT_ACTION__
#define __OBJECT_ACTION__

#include <memory>
#include "../sdl2/Renderer.hpp"
#include "../sdl2/Text.hpp"
#include "../ObjectCard.hpp"

enum E_ObjectActionMenuItem {USE, INFO, DISCARD, ADD_ACTIONBAR, REMOVE_ACTIONBAR, SORT, BACK, NB_ITEMS};

const unsigned int FLAG_CONTEXT_NOT_IN_FIGHT = 0x01;
const unsigned int FLAG_CONTEXT_CARD_IN_ACTIONBAR = 0x02;
const unsigned int FLAG_CONTEXT_CARD_NOT_IN_ACTIONBAR = 0x04;

struct S_MenuItem {
	Text text = Text();
	unsigned int objectFlags = 0;
	unsigned int context = 0;
	bool valid = false;
};

class ObjectAction {
	int m_iNbVisibleItems = 0;
	int m_iSelectedItemIndex = 0;
	E_ObjectActionMenuItem m_selectedAction = USE;
	int m_iCursorPosition = 0;
	unsigned int m_iContext = 0;
	std::shared_ptr<ObjectCard> m_card = nullptr;
	S_MenuItem m_itemTexts[NB_ITEMS]= {};
	std::shared_ptr<SDL2Renderer> m_renderer;

	protected:
	void _renderBackground(int spriteIndex, int y);
	void _renderItems();
	void _renderCursor();
	void _renderItem(int itemIndex, int visibleIndex);
	void _setSelectedAction();
	void _setCursorPosition();
	void _reset();
	bool _isActionValid(int actionIndex) const;

	public:
	ObjectAction(std::shared_ptr<SDL2Renderer> m_renderer);
	~ObjectAction() {}
	void setContext(unsigned int context);
	void open(std::shared_ptr<ObjectCard> card);
	bool isOpen() const;
	void close();
	void render();
	void selectPrevious();
	void selectNext();
	E_ObjectActionMenuItem getSelectedAction() const;
};

#endif
