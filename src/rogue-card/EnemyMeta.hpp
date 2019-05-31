#ifndef __ENEMY_META__
#define __ENEMY_META__

#include <map>
#include <string>
#include "../common/ResourceManager.hpp"
#include "../common/types.hpp"

class EnemyMeta {
	private:
	ResourceManager<S_EnemyMeta> m_resourceManager;
	std::map<std::string, int> m_mMetaDataMapping = {};

	public:
	EnemyMeta();
	bool prepare(std::string file);
	int getSize();
	S_EnemyMeta get(int index);
};

#endif
