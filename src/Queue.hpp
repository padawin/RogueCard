#ifndef __QUEUE__
#define __QUEUE__

#define MAX_SIZE_VALUE 128

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct S_QueueItem {
	char value[MAX_SIZE_VALUE] = "";
	struct S_QueueItem *next = 0;
} S_QueueItem;

class Queue {
	protected:
	S_QueueItem *m_current = 0;
	S_QueueItem *m_first = 0;
	S_QueueItem *m_last = 0;
	long unsigned m_uSize = 0;

	public:
	void push(const char value[MAX_SIZE_VALUE]) {
		S_QueueItem *item = (S_QueueItem*) malloc(sizeof(S_QueueItem));
		item->next = 0;
		strncpy(item->value, value, MAX_SIZE_VALUE);
		if (m_uSize == 0) {
			m_first = item;
		}
		else {
			m_last->next = item;
		}
		m_last = item;
		++m_uSize;
	}

	void pop() {
		if (m_first == 0) {
			return;
		}

		S_QueueItem *newFirst = m_first->next;
		free(m_first);
		m_first = newFirst;
		if (m_first == 0) {
			m_last = 0;
		}
		--m_uSize;
	}

	S_QueueItem *current() {
		return m_current;
	}

	S_QueueItem *next() {
		if (m_current == 0) {
			m_current = m_first;
		}
		else {
			m_current = m_current->next;
		}

		return m_current;
	}

	void reset() {
		m_current = 0;
	}

	void clear() {
		while (current()) {
			pop();
		}
	}

	long unsigned getSize() {
		return m_uSize;
	}
};

#endif
