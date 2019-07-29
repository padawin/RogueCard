#ifndef __HEALTH__
#define __HEALTH__

class Health {
	private:
	int m_iCurrent = 0;
	int m_iMax = 0;

	public:
	Health(int current, int max);
	void operator-=(int value);

	int getCurrent() const;
	int getMax() const;
	void setCurrent(int value);
	void setMax(int value);
};

#endif
