#ifndef FISH_H
#define FISH_H

#include "Entity.h"
#include "Player.h"


class Fish : public Entity {
public:
	Fish();
	~Fish();

	static Fish* create(Sprite* sprite, int level);
	virtual bool init();

	void swim();
	bool escape(Player* player, float speed);
	bool isFinishSwimming();
	void stopSwimming();
	void reset();

	bool isCollideWithPlayer(Player* player);
	bool isColsedToPlayer(Player* player);

	CC_SYNTHESIZE(int, m_level, FishLevel);
	CC_SYNTHESIZE(int, m_energy, FishEnergy);
	CC_SYNTHESIZE(int, m_randomKey, RandomKey);
	CC_SYNTHESIZE(float, m_speed, FishSpeed);
	CC_SYNTHESIZE_READONLY(Point, m_startPoint, FishStartPoint);
	CC_SYNTHESIZE_READONLY(Point, m_destination, FishDestination);

private:
	Point getStartPosition();
	void changeDirection();
	
private:
	int m_direction;
	bool m_finishSwimming;
	bool m_escaping;
};

#endif