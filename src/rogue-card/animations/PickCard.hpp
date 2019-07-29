#ifndef __PICK_CARD_ANIMATION__
#define __PICK_CARD_ANIMATION__

class PickCardAnimation {
	private:
	bool m_bRunning = false;
	int m_iX = 0;
	int m_iY = 0;
	int m_iStartTime = 0;

	public:
	void init();
	void update();
	int running() const;
	int getX() const;
	int getY() const;
};

#endif
