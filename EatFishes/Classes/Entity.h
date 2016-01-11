#ifndef ENTITY_H
#define ENTITY_H

#include "cocos2d.h"

USING_NS_CC;

class Entity : public Node {
public:
	void bindSprite(Sprite* sprite);
	Sprite* getSprite() const;
	
	CC_SYNTHESIZE(Point, m_postion, EntityPosition);
	CC_SYNTHESIZE_READONLY(Size, m_size, EntitySize);
protected:
	Entity();
	virtual ~Entity();

	Sprite* m_sprite;
};

#endif // !ENTITY_H
