#ifndef __ABSTRACT_SAVE__
#define __ABSTRACT_SAVE__

class AbstractSave {
	public:
	virtual ~AbstractSave() {}

	static void clean();
	static bool exists();
	virtual void load() = 0;
	virtual void create() = 0;
};

#endif
