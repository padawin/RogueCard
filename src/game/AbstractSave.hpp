#ifndef __ABSTRACT_SAVE__
#define __ABSTRACT_SAVE__

class AbstractSave {
	public:
	virtual ~AbstractSave() {}

	static void clean();
	virtual bool exists() = 0;
	virtual void load() = 0;
	virtual void create() = 0;
};

#endif
