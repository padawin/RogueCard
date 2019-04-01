#ifndef __FLOOR__
#define __FLOOR__

enum FloorDirection {FLOOR_DOWN, FLOOR_UP};

class Floor {
	private:
	int m_iLevel = 1;

	public:
	int getLevel() const;
	void setLevel(int level);
	void toNextLevel();
	void toPreviousLevel();
	bool reachedMaxLevel() const;
};

#endif
