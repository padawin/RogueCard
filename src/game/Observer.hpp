#ifndef __OBSERVER__
#define __OBSERVER__

enum E_Event : short;
enum E_NotifyResult {NOTIFY_OK, NOTIFY_UNOBSERVE};

class Observer {
	public:
	virtual ~Observer() {}
	virtual E_NotifyResult onNotify(E_Event event, void* data) = 0;
};

#endif
