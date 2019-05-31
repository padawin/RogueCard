#ifndef __OBJECT_META__
#define __OBJECT_META__

#include <map>
#include <string>
#include "../common/ResourceManager.hpp"
#include "../common/types.hpp"

class ObjectMeta {
	private:
	ResourceManager<S_ObjectMeta> m_resourceManager;
	std::map<std::string, int> m_mMetaDataMapping = {};

	public:
	ObjectMeta();
	bool prepare(std::string file);
	int getSize();
	S_ObjectMeta get(int index);
};

#endif
