#ifndef __FLOOR__
#define __FLOOR__

#include <map>
#include <vector>
#include "../common/types.hpp"

enum FloorDirection {FLOOR_DOWN, FLOOR_UP};

class Floor {
	private:
	static std::map<int, std::vector<S_FloorContent>> m_mFloorContentMeta;
	int m_iLevel = 1;

	public:
	static bool prepareMeta(std::string file);
	std::vector<S_FloorContent> &getContent();
	int getLevel() const;
	void setLevel(int level);
	void toNextLevel();
	void toPreviousLevel();
	bool isLast() const;
};

#endif
