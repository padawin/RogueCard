#ifndef __OBJECT_CARD_LOOPABLE__
#define __OBJECT_CARD_LOOPABLE__

class IObjectCardsLoopable {
	protected:
	int m_iCurrentCard = 0;

    public:
	virtual ~IObjectCardsLoopable() {}
	virtual bool next() = 0;
	virtual std::shared_ptr<ObjectCard> current() const = 0;
	virtual void reset() = 0;
	virtual int getCurrentIndex() const {
		return m_iCurrentCard;
	}
};

#endif
