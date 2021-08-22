#include "Observable.hpp"

void Observable::notify(E_Event event, void* data) {
	auto it = m_vObservers.begin();
	while (it != m_vObservers.end()) {
		E_NotifyResult res = (*it)->onNotify(event, data);
		if (res == E_NotifyResult::NOTIFY_UNOBSERVE) {
			it = m_vObservers.erase(it);
		} else {
			++it;
		}
	}
}

void Observable::addObserver(Observer* observer) {
	m_vObservers.push_back(observer);
}
