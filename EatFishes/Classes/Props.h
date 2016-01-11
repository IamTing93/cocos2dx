#ifndef PROPS_H
#define PROPS_H

#include "Entity.h"
#include "Global.h"
#include <string>

USING_NS_CC;



class Props : public Entity {

public:
	Props();
	~Props();
	virtual void appear();
	bool isCollidedWithPlayer();
	virtual void affect() = 0;
	virtual void reset();
	bool isAppeared() const;

protected:
	virtual Point getStartPoint();
	virtual Point getDestination();

	CC_SYNTHESIZE_READONLY(Direction, m_direction, PropsDirection);
	CC_SYNTHESIZE_READONLY(std::string, m_name, PropName);

protected:
	Point m_startPoint;
	Point m_destination;
	bool m_isAppeared;
};

#endif