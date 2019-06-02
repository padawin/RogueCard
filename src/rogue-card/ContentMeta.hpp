#ifndef __CONTENT_META__
#define __CONTENT_META__

#include <map>
#include <string>
#include "../common/ResourceManager.hpp"
#include "../common/types.hpp"

template <class contentType> class ContentMeta {
	private:
	ResourceManager<contentType> m_resourceManager;
	std::map<std::string, int> m_mMetaDataMapping = {};

	public:
	ContentMeta();
	bool prepare(std::string file);
	int getSize();
	contentType get(int index);
};

#include "ContentMeta.tpp"

#endif
