#ifndef __OBSERVABLE__
#define __OBSERVABLE__

#include <vector>
#include "Observer.hpp"

class Observable {
	private:
	std::vector<Observer*> m_vObservers = {};

	public:
	virtual ~Observable() {}
	void addObserver(Observer* observer);
	void notify(E_Event event, void* data = nullptr);
};

#endif
